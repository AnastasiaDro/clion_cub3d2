#include "libft/libft.h"
#include "fcntl.h"
#include "get_next_line/get_next_line.h"
#include "cub_utils.h"
#include "parser_utils.h"
#include "exceptions.h"
#include "colors.h"
#include "player_params.h"
#include "parse_resolution.h"
#include "map_checker.h"
#include "constants.h"
#include "parcer.h"
#include "fill_map.h"

int check_fe_line(char *s)
{
	int i;

	i = 0;
	while (s[i] == ' ')
		i++;
	while (s[i])
	{
		if (s[i]!= '1' && s[i]!= ' ')
			return (MAP_ERROR);
		i++;
	}
	return (1);
}

int  is_map_start(char *line)
{
    char *ptr = line;
    int i = 0;
    while (ptr[i])
    {
        if (ptr[i] == ' ')
        {
            i++;
            continue;
        }
        if (ptr[i] >= '0' && ptr[i] <= '9')
            return (MAP_STARTED);
        else if (ptr[i] == '0')
			return (ZERO_START_LINE);
        else
            return (i);
    }
    return (i);
}

int get_n_check_textures(char *s, t_data *m_struct, t_parse_flags *parse_f)
{
    if (!ft_strncmp(s, "NO", 2) && !(parse_f->north))
        return(get_texture_path(s, &m_struct->params->north_texture_path, &(parse_f->north)));
    if (!ft_strncmp(s, "SO", 2) && !parse_f->south)
        return(get_texture_path(s, &m_struct->params->south_texture_path, &(parse_f->south)));
    if (!ft_strncmp(s, "WE", 2) && !parse_f->west)
        return(get_texture_path(s, &m_struct->params->west_texture_path, &(parse_f->west)));
    if (!ft_strncmp(s, "EA", 2) && !parse_f->east)
        return(get_texture_path(s, &m_struct->params->east_texture_path, &(parse_f->east)));
    if (!ft_strncmp(s, "S", 1) && !parse_f->sprite)
        return(get_texture_path(s, &m_struct->params->sprite_texture_path, &(parse_f->sprite)));
    return (0);
}

int get_n_check_params(char *s, t_data *m_struct, t_parse_flags *parse_f)
{
    if (*s == 'R' && !parse_f->resol)
        return (parse_resolution(s, m_struct, &parse_f->resol));
    if (*s == 'F' && !parse_f->floor_color)
    {
        m_struct->params->floor_color = get_color(s, m_struct, &parse_f->floor_color);
        return (1);
    }
    if (*s == 'C' && !parse_f->ceil_color)
    {
        m_struct->params->ceil_color = get_color(s, m_struct, &parse_f->ceil_color);
        return (1);
    }
    return (0);
}


void throw_map_except(t_data *m_struct)
{
    throwException(INVALID_MAP);
    free_all(m_struct);
    exit(0);
}

void parse_map(t_data *m_struct)
{
    t_parse_flags parse_f;
    init_parse_flags(&parse_f);
//школа
  // int fd = open("/Users/cerebus/projects/clion_cub3d2/real_map1.cub", O_RDONLY);
  //ДОМ
  int fd = open("/Users/anastasia/CLionProjects/clion_cub3d2/real_map.cub", O_RDONLY);
    char *line;
    t_list *last_elem = NULL;
    int elems_num = 0;
    int index;

    while (get_next_line(fd, &line))
    {
        //вот тут проверяем начало карты
        index = is_map_start(line);
        if (index == MAP_STARTED)
        {
			if (check_fe_line(line) == MAP_ERROR)
                throw_map_except(m_struct);
            ft_lstadd_front(&last_elem, ft_lstnew(line));
            elems_num++;
            break;
        }
        else
        {
            if(is_empty(&line))
                continue;
			if (!(get_n_check_textures(&line[index], m_struct, &parse_f)) && !(get_n_check_params(&line[index],
                                                                                                  m_struct, &parse_f)))
                throw_map_except(m_struct);
        }
    }
   int res = 0;
    while ((res = get_next_line(fd, &line)))
    {
        ft_lstadd_front(&last_elem, ft_lstnew(line));
        elems_num++;
    }
    ft_lstadd_front(&last_elem, ft_lstnew(line));
    elems_num++;
    m_struct->lst = last_elem;

	line = NULL;
    //создадим список для спрайтов (с массивом еще париться по поводу памяти каждый раз...
    m_struct->sprite_info->sprite_list = malloc(1*sizeof (t_sprite *));
    *(m_struct->sprite_info->sprite_list) = NULL;
    elems_num = fill_map(&last_elem, elems_num, m_struct);
    if (check_fe_line(m_struct->map[elems_num-1]) == MAP_ERROR)
        throw_map_except(m_struct);
    ft_lstclear(&last_elem, free);
   	close(fd);

   	//проверим карту
    if (check_map(m_struct->map, elems_num) == MAP_ERROR)
        throw_map_except(m_struct);
}
