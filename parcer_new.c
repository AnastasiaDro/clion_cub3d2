#include "libft/libft.h"
#include "fcntl.h"
#include "get_next_line/get_next_line.h"
#include "new_cub_utils.h"
#include "utils.h"
#include "exceptions.h"
#define IS_SPACE ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
#define IS_NUM (str[i] >= '0' && str[i] <='9')

#define MAP_STARTED -1
#define ZERO_START_LINE -3
#define MAP_ERROR -3

# define MAX_SCREEN_WIDTH 2560
# define MAX_SCREEN_HEIGHT 1440
# define MAX_WIDTH_NUM_LENGTH 4
# define MAX_HEIGHT_NUM_LENGTH 4
# define MAP_SYMBOL "012 "
# define PLAYER_SYMBOLS "NSWE"
#define PLAYER_FOUND 1

void make_color_exception(char *s, t_data *m_struct)
{
    throwException(INVALID_FLOOR_COLOR);
    free(s);
    s = NULL;
    free_all(m_struct);
    exit(0);
}



int go_to_the_next_color(int i, char *str)
{
    while(str[i] && str[i] >= '0' && str[i] <= '9')
        i++;
    while (str[i] && str[i]!= ',')
	{
		if (!IS_SPACE && !IS_NUM)
		{
			printf("строка s[i] = %s", &str[i]);
			return (-1);
		}
		i++;
	}
    i++;
	while (IS_SPACE)
		i++;
	if (!IS_NUM)
	{
		printf("строка s[i] = %s", &str[i]);
		return -1;
	}
    return i;
}


int check_color_part(char *str)
{
    int i;
    int num_start;
    int num_length;
    int color;

	i = 0;
    num_start = i;
    while(IS_NUM)
        i++;
    num_length = i - num_start;
    if (num_length > 3)
        return (-1);
    color = ft_atoi(str);
    if (color > 255)
        return (-1);
    return (color);
}

int check_color_s_end(char *str, int i)
{
	while (IS_NUM)
		i++;
	while (str[i])
	{
		if (!IS_SPACE)
			return (-1);
		i++;
	}
	return (1);
}

int get_color(char *s, t_data *m_struct)
{
    int i = 0;
    int r = 0x0;
    int g = 0x0;
    int b = 0x0;
    char *str;
    str = s+1;
    int color = 0x000000;
    while(str[i] == ' ')
        i++;
    if ((r = check_color_part(&str[i])) == -1)
        make_color_exception(s, m_struct);
    i = go_to_the_next_color(i, str);
    if (i == -1 || (g = check_color_part(&str[i])) == -1)
        make_color_exception(s, m_struct);
    i = go_to_the_next_color(i, str);
    if (i == -1 || (b = check_color_part(&str[i])) == -1)
        make_color_exception(s, m_struct);
	if (check_color_s_end(str, i) == -1)
		make_color_exception(s, m_struct);
	color = r*16*16*16*16 + g*16*16 + b;
    return color;
}

int check_borders(char **map, int l_i, int i, int coef)
{       //символ правее или левее         символ выше             //символ ниже

 // printf("char map[i-1][l_i] %c\n", map[i-1][l_i]);
    if (map[i][l_i + 1*coef] == ' ' || map[i-1][l_i] == ' ' || map[i + 2][l_i] == ' ')
        return MAP_ERROR;
    else
        return 1;
}


int check_space_borders(int start_i, int end_i, char **map, char *cur_s, int s_num)
{
    int start = start_i;
    int end = end_i;
    while (start < end)
    {
        if (cur_s[start] == '0')
            if (cur_s[start-1] == ' ' || cur_s[start+1] == ' '
                    || map[s_num-1][start] == ' ' || map[s_num+1][start] == ' ')
                return (MAP_ERROR);
        start++;
    }
    return (1);
}


int check_map (char **map, int elems_num)
{
    int cur_s_len;
    int next_s_len;
    int i = 1; //начнем со второй строки
    int l_i = 0; //индекс по строке
    char *cur_s;
    char *next_s;
    while (i < elems_num-2)
    {
        l_i = 0;
        cur_s = map[i];
        cur_s_len = (int)ft_strlen(cur_s);
        //слева направо
        while(l_i < cur_s_len)
        {
            if (cur_s[l_i] == '0')
                return MAP_ERROR;
            if (cur_s[l_i] == '1')
                break;
            l_i++;
        }
        if (l_i == cur_s_len)
        {
            throwException(INVALID_MAP);    //ошибка карты, мы дошли до конца, единица так и не встретилась
            return MAP_ERROR;
        }

        while(l_i < cur_s_len)
        {
            if (cur_s[l_i] == '0')
                if (check_borders(map, l_i, i, 1) == MAP_ERROR)
                    return MAP_ERROR;
                else
                    //вот тут нужно пробежаться справа налево дальше
                    break;
            l_i++;
        }

        //cправа налево
        next_s = map[i+1];
        next_s_len = ft_strlen(next_s);
        int diff = 0;
        if (cur_s_len < next_s_len)
        {
            diff = next_s_len - cur_s_len;
            while(diff > 0)
            {
                if (next_s[next_s_len-diff-1] == '0')
                    return MAP_ERROR;
                diff--;
            }
        } else {
            diff = cur_s_len - next_s_len;
            while(diff > 0)
            {
                if (cur_s[cur_s_len-diff-1] == '0') // || next_s[next_s_len-diff-1] == '0')
                    return MAP_ERROR;
                diff--;
            }
            if (diff == 0)
                if ( next_s[next_s_len-1] == '0')
                    return MAP_ERROR;
        }

        //проверим строку на пробелы
        //l_i - то, откуда начались единицы

                //int check_space_borders(int start_i, int end_i, char **map, char *cur_s, int s_num)
        if (check_space_borders(l_i, cur_s_len, map, cur_s, i) == MAP_ERROR)
            return (MAP_ERROR);
        i++;
    }
    return 1;
}


int check_fe_line(char *s)
{
	int i = 0;
	while (s[i] == ' ')
		i++;
	while (s[i])
	{
		if (s[i]!= '1' && s[i]!= ' ')
			return MAP_ERROR;
		i++;
	}
	return 1;
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
            return MAP_STARTED;
        else if (ptr[i] == '0')
			return ZERO_START_LINE;
        else
            return i;
    }
    return i;
}

int find_string_start(char *s)
{
    int i = 2; //третий индекс в массиве
    while (s[i] && s[i] == ' ' )
        i++;
    return (i); //вернем индекс символа
}

//сохраняем текстуры
int check_n_save_textures(char *s, t_data *m_struct)
{
    int start_i = 0;
    int  s_len = 0;
    if (!ft_strncmp(s, "NO", 2)) //если строки равны
    {
        start_i = find_string_start(s);
        //обработка
        m_struct->params->north_texture_path = ft_strdup(&s[start_i]);
		return (1);
    }
    if (!ft_strncmp(s, "SO", 2)) //если строки равны
    {
       start_i = find_string_start(s);
        m_struct->params->south_texture_path = ft_strdup(&s[start_i]);
        return (1);
    }
    if (!ft_strncmp(s, "WE", 2)) //если строки равны
    {
        start_i = find_string_start(s);
        m_struct->params->west_texture_path = ft_strdup(&s[start_i]);
        return (1);
    }
    if (!ft_strncmp(s, "EA", 2)) //если строки равны
    {
        start_i = find_string_start(s);
        m_struct->params->east_texture_path = ft_strdup(&s[start_i]);
        return (1);
    }
	if (!ft_strncmp(s, "S", 1))
	{
		start_i = find_string_start(s);
		m_struct->params->sprite_texture_path = ft_strdup(&s[start_i]);
		return (1);
	}
    return (0);
}

int check_n_save_params(char *s, t_data *m_struct)
{
    char *str;
    int i = 0;
    int num_start;
    int num_length;
    if (*s == 'R') //и что этого флага ещё не было, если был - ошибка
    {
        str = s+1;
        m_struct->params->screen_width = 0;
        m_struct->params->screen_higth = 0;
        while(str[i] && (str[i] == ' '))
            i++;
        num_start = i;
        while(str[i] >= '0' && str[i] <='9')
            i++;
        num_length = i - num_start;
        if (num_length > MAX_WIDTH_NUM_LENGTH)
        {
            m_struct->params->screen_width = MAX_SCREEN_WIDTH;
            m_struct->params->screen_higth = MAX_SCREEN_HEIGHT;
            free(s);
            s = NULL;
            return 1;
        }
        m_struct->params->screen_width = ft_atoi(str);
        while(str[i] && (str[i] == ' '))
            i++;
        num_start = i;
        while(str[i] >= '0' && str[i] <='9')
            i++;
        num_length = i - num_start;
        if (num_length > MAX_HEIGHT_NUM_LENGTH)
        {
            m_struct->params->screen_width = MAX_SCREEN_WIDTH;
            m_struct->params->screen_higth = MAX_SCREEN_HEIGHT;
            free(s);
            s = NULL;
            return 1;
        }
        m_struct->params->screen_higth = ft_atoi(&str[num_start]);

        if ( m_struct->params->screen_width > MAX_SCREEN_WIDTH || m_struct->params->screen_higth > MAX_SCREEN_HEIGHT)
        {
            m_struct->params->screen_width = MAX_SCREEN_WIDTH;
            m_struct->params->screen_higth = MAX_SCREEN_HEIGHT;
            free(s);
            s = NULL;
            return 1;
        }
        if(m_struct->params->screen_width<=0 ||  m_struct->params->screen_higth <= 0)
        {
            throwException(INVALID_RESOLUTION);
            free(s);
            s = NULL;
            free_all(m_struct);
            exit(0);
        }
        free(s);
        s = NULL;
        return (1);
    }
    if (*s == 'F') //и что этого флага ещё не было, если был - ошибка
    {
        m_struct->params->floor_color = get_color(s, m_struct);
        return (1);
    }
    if (*s == 'C') //и что этого флага ещё не было, если был - ошибка
    {
        //берём , цвет потолка, что после не должно быть других букв.
        m_struct->params->ceil_color = get_color(s, m_struct);
        return (1);
    }
    return 0;
}


int set_player_vision(char c, t_data *m_struct)
{
	if (c == 'N') //90 градусов
	{
        //нужен первоначальный вектор направления:
        m_struct->dirX = 0;
        m_struct->dirY = -1;
        //the 2d raycaster version of camera plane
        m_struct->planeY=0;
        m_struct->planeX = -0.66;
        return 1;
	}
	if (c == 'S') //270 градусов
	{
        m_struct->dirX = 0;
        m_struct->dirY = 1;
        m_struct->planeY=0;
        m_struct->planeX = 0.66;
        return 1;
	}
	if (c == 'E') //270 градусов
	{
        m_struct->dirX =   1;
        m_struct->dirY =   0;
        m_struct->planeY= -0.66;
        m_struct->planeX = 0;
        return 1;
	}
	if (c == 'W') //270 градусов
	{
        m_struct->dirX = -1;
        m_struct->dirY = 0;
        m_struct->planeY=0.66;
        m_struct->planeX = 0;
        return 1;
	}
	return 0;
}

//int find_player(char *s, t_data *m_struct)
//{
//    int i = 0;
//    while (s[i])
//    {
//       if (s[i] == 'N' || s[i] == 'E' || s[i] == 'W' || s[i] == 'S') {
//		   set_player_vision(s[i], m_struct);
//		   return i;
//	   }
//        i++;
//    }
//    return -1;
//}


int is_symbol_valid(char *s, char *arr)
{
	int max_index;

	max_index = (int)ft_strlen(s) - 1;
	int arr_index = 0;
	while (max_index >= 0)
	{
		arr_index = ft_strchr_index(arr, s[max_index]);
		if(arr_index == -1)
			return (max_index);
		max_index--;
	}
	return (-1);
}



int check_symbols(char *s, t_data *m_struct, int *flag_player)
{
	int player_i;

	player_i = -1;

	if ((player_i = is_symbol_valid(s, MAP_SYMBOL)) != -1)
	{
		if (ft_strchr(PLAYER_SYMBOLS, s[player_i]) == NULL)
		{
			throwException(INVALID_MAP);
			free_all(m_struct);
		}
		else
		{
			if (*flag_player == 1) {
				throwException(MORE_PLAYERS);
				free_all(m_struct);
			} else {
				set_player_vision(s[player_i], m_struct);
				*flag_player = 1;
				return (player_i);
			}
		}
	}
	return (0);
}

//int find_player(char *s, t_data *m_struct)
//{
//    int i = 0;
//    while (s[i])
//    {
//       if (s[i] == 'N' || s[i] == 'E' || s[i] == 'W' || s[i] == 'S') {
//		   set_player_vision(s[i], m_struct);
//		   return i;
//	   }
//        i++;
//    }
//    return -1;
//}


int check_sprites(char *s, t_data *m_struct, int elems_num)
{
	int i = 0;
	double x = 0;
	double y = 0;
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
    
    map = ft_calloc(elems_num + 1, sizeof(char *)); //количество наших сьтрочек + 1 для зануления
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
//        if (flag_player == 1 && ((is_player = find_player(map[elems_num - 1], m_struct)) != -1))
//        {
//            throwException(MORE_PLAYERS);
//            free_all(m_struct);
//        }
//        else if ((is_player = find_player(map[elems_num - 1], m_struct)) != -1)
//        {
//             m_struct->map_player_x = (double)is_player + 0.5;
//             m_struct->map_player_y = (double)(elems_num - 1) + 0.5;
//			flag_player = 1;
//             map[elems_num - 1][is_player] = '0';
//        }
//        }
		if((is_player = check_symbols(map[elems_num-1], m_struct, &flag_player)))
		{
			m_struct->map_player_x = (double)is_player + 0.5;
			printf("found player at x %d\n", is_player);
			m_struct->map_player_y = (double)(elems_num - 1) + 0.5;
			printf("found player at y %d\n", elems_num-1);
			map[elems_num - 1][is_player] = '0';
		}


//посчитаем спрайты
        check_sprites(map[elems_num - 1], m_struct, elems_num);
        elem = elem->next;
        elems_num--;
    }
    if (flag_player == 0)
    {
        throwException(NO_PLAYER);
        free_all(m_struct);
    }
    //выведем карту
    while (map[elems_num])
    {
        //выводим строку???
        ft_putendl_fd(map[elems_num], 1);
        elems_num++;
    }
    m_struct->map = map;
    return (el_num);
}

void parse_map(t_data *m_struct)
{
   // int fd = open(argv[1], O_RDONLY);
    write(1, "PARSE_MAP\n", 10);

//школа
   //int fd = open("/Users/cerebus/projects/clion_cub3d2/real_map1.cub", O_RDONLY);
  //ДОМ
  int fd = open("/Users/anastasia/CLionProjects/clion_cub3d2/real_map.cub", O_RDONLY);
    char *line;
    t_list *last_elem = NULL;
    int elems_num = 0;
    int index = -2;
    while (get_next_line(fd, &line))
    {
        //вот тут проверяем начало карты
        index = is_map_start(line);
        if (index == MAP_STARTED)
        {
			if (check_fe_line(line) == MAP_ERROR)
			{
				throwException(INVALID_MAP);
				free_all(m_struct);
			}
            ft_lstadd_front(&last_elem, ft_lstnew(line));
            elems_num++;
            break;
        }
        else
        {
            //сохраняю в структуру параметров текстуры
            //если у нас уже
			if (line[0] == '\0')
				continue;
			if (!(check_n_save_textures(&line[index], m_struct)) && !(check_n_save_params(&line[index], m_struct)))
			{
				throwException(INVALID_MAP);
				free_all(m_struct);
			}
            //сохранить разрешение и другие параметры
        }
    }
   // printf("север %s\n", m_struct->params->north_texture_path);
   int res = 0;
    while ((res = get_next_line(fd, &line)))
    {
    	int s_len = ft_strlen(line);
        ft_lstadd_front(&last_elem, ft_lstnew(line));
        elems_num++;
    }
    ft_lstadd_front(&last_elem, ft_lstnew(line));
   // free(line);
    elems_num++;
    m_struct->lst = last_elem;

	line = NULL;
    //создадим список для спрайтов (с массивом еще париться по поводу памяти каждый раз...
    m_struct->sprite_info->sprite_list = malloc(1*sizeof (t_sprite *));
    *(m_struct->sprite_info->sprite_list) = NULL;
    elems_num = fill_map(&last_elem, elems_num, m_struct);
    if (check_fe_line(m_struct->map[elems_num-1]) == MAP_ERROR)
    {
        throwException(INVALID_MAP);
        free_all(m_struct);
    }
    //сега
    ft_lstclear(&last_elem, free);
   	close(fd);

   	//проверим карту
    if (check_map(m_struct->map, elems_num) == MAP_ERROR)
    {
        throwException(INVALID_MAP);
        free_all(m_struct);
    }
}
