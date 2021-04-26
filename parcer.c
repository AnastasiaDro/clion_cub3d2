#include "libft/libft.h"
#include "fcntl.h"
#include "get_next_line/get_next_line.h"
#include "cub_utils.h"
#include "parser_utils.h"
#include "exceptions.h"
#include "colors.h"
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
	throw_exception(INVALID_MAP);
    free_all(m_struct);
    exit(0);
}

void check_last_line(t_data *m_struct, t_list **last_elem, int elems_num, int fd)
{
	if (check_fe_line(m_struct->map[elems_num-1]) == MAP_ERROR)
	{
		close(fd);
		throw_map_except(m_struct);
	}
}

void parse_map(t_data *m_struct, char *map_path)
{
	int fd;
	char *line;
	t_list *last_elem;
	int elems_num;

  	fd = open(map_path, O_RDONLY);
    last_elem = NULL;
	elems_num = go_th_params(fd, m_struct, &last_elem, &line);
    while (get_next_line(fd, &line))
    {
        ft_lstadd_front(&last_elem, ft_lstnew(line));
        elems_num++;
    }
    ft_lstadd_front(&last_elem, ft_lstnew(line));
    elems_num++;
    m_struct->lst = last_elem;
	line = NULL;
    m_struct->sprite_info->sprite_lst = malloc(1 * sizeof (t_sprite *));
    *(m_struct->sprite_info->sprite_lst) = NULL;
    elems_num = fill_map(&last_elem, elems_num, m_struct);
	check_last_line(m_struct, &last_elem, elems_num, fd);
    ft_lstclear(&last_elem, free);
   	close(fd);
    if (check_map(m_struct->map, elems_num) == MAP_ERROR)
        throw_map_except(m_struct);
}
