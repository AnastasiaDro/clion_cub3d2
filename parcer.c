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


int check_symbols(char *s, t_data *m_struct, int *flag_player)
{
	int player_i;

	if ((player_i = is_symbol_valid(s, MAP_SYMBOL)) != -1)
	{
		if (ft_strchr(PLAYER_SYMBOLS, s[player_i]) == NULL)
            throw_map_except(m_struct);
		else
		{
			if (*flag_player == 1)
                throw_map_except(m_struct);
			else {
				set_player_vision(s[player_i], m_struct);
				*flag_player = 1;
				return (player_i);
			}
		}
	}
	return (0);
}

int get_sprites_list(char *s, t_data *m_struct, int elems_num)
{
	int i;
	double x;
	double y;

	i = 0;
	while (s[i])
	{
		if (s[i] == '2')
		{
			x = i + 0.5;
			y = elems_num - 1 + 0.5;
            sprite_lstadd_front(m_struct->sprite_info->sprite_list, sprite_lstnew(x, y));
			m_struct->sprite_info->num_sprites += 1;
		}
		i++;
	}
	return i;
}


int fill_map(t_list **last_elem, int elems_num, t_data *m_struct)
{
    char **map;
    t_list *elem;
    int is_player;
    int flag_player = 0;
    
    map = ft_calloc(elems_num +1 , sizeof(char *)); //количество наших сьтрочек + 1 для зануления
    elem = *last_elem;
    char *st = (char *)elem->content;
    while('\0' == *st)
    {
        elem = elem->next;
        elems_num--;
        st = (char *)elem->content;
    }
    int el_num = elems_num;
    while (elems_num)
    {
        map[elems_num - 1] =  (char *)elem->content;
        elem->content = NULL;
		if((is_player = check_symbols(map[elems_num-1], m_struct, &flag_player)))
		{
			m_struct->map_player_x = (double)is_player + 0.5;
			m_struct->map_player_y = (double)(elems_num - 1) + 0.5;
			map[elems_num - 1][is_player] = '0';
		}

//посчитаем спрайты
        get_sprites_list(map[elems_num - 1], m_struct, elems_num);
        elem = elem->next;
        elems_num--;
    }
    if (flag_player == 0)
    {
        throwException(NO_PLAYER);
        free_all(m_struct);
        exit(0);
    }
    //выведем карту
    printf("elems_num = %d\n", elems_num);
    while (map[elems_num])
    {
        //выводим строку???
        ft_putendl_fd(map[elems_num], 1);
        elems_num++;
    }
    m_struct->map = map;
    return (el_num);
}

int is_empty(char **line)
{
    if ((*line)[0] == '\0')
    {
        free(*line);
        *line = NULL;
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
   int fd = open("/Users/cerebus/projects/clion_cub3d2/real_map1.cub", O_RDONLY);
  //ДОМ
 // int fd = open("/Users/anastasia/CLionProjects/clion_cub3d2/real_map.cub", O_RDONLY);
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
