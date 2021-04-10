#include "libft/libft.h"
#include "fcntl.h"
#include "get_next_line/get_next_line.h"
#include "new_cub_utils.h"
#include "exceptions.h"


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
        if (ptr[i] == '1')
            return -1;
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
    int res = 0;
    int start_i = 0;
    int  s_len = 0;
    if (!ft_strncmp(s, "NO", 2)) //если строки равны
    {
        start_i = find_string_start(s);
        //обработка
        m_struct->params->north_texture_path = ft_strdup(&s[start_i]);
//       s_len = ft_strlen(&s[start_i]);
//		m_struct->params->north_texture_path = ft_calloc( s_len+ 3, sizeof (char));
//		m_struct->params->north_texture_path[0] = '"';
//		m_struct->params->north_texture_path[s_len + 1] = '"';
		return (res);
    }
    if (!ft_strncmp(s, "SO", 2)) //если строки равны
    {
       start_i = find_string_start(s);
        m_struct->params->south_texture_path = ft_strdup(&s[start_i]);
        return (res);
    }
    if (!ft_strncmp(s, "WE", 2)) //если строки равны
    {
        start_i = find_string_start(s);
        m_struct->params->west_texture_path = ft_strdup(&s[start_i]);
        return (res);
    }
    if (!ft_strncmp(s, "EA", 2)) //если строки равны
    {
        start_i = find_string_start(s);
        m_struct->params->east_texture_path = ft_strdup(&s[start_i]);
        return (res);
    }
    return (-1);
}

int check_n_save_params(char *s, t_data *m_struct)
{
    int res = 0;
    if (*s == 'R') //и что этого флага ещё не было, если был - ошибка
    {
        //нужно два атои
        //берём разрешение, нужно учесть, что после Р не должно быть других букв.
        return (res);
    }
    if (*s == 'F') //и что этого флага ещё не было, если был - ошибка
    {
        //берём , цвет пола=, что после не должно быть других букв.
        return (res);
    }
    if (*s == 'F') //и что этого флага ещё не было, если был - ошибка
    {
        //берём , цвет пола, что после не должно быть других букв.
        return (res);
    }
    if (*s == 'C') //и что этого флага ещё не было, если был - ошибка
    {
        //берём , цвет потолка, что после не должно быть других букв.
        return (res);
    }
    return -1;
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
		m_struct->dirX = -1;
		m_struct->dirY = 0;
		m_struct->planeY=0.66;
		m_struct->planeX = 0;
		return 1;
	}
	if (c == 'W') //270 градусов
	{
        m_struct->dirX =   1;
        m_struct->dirY =   0;
        m_struct->planeY= -0.66;
        m_struct->planeX = 0;
        return 1;
	}
	return 0;
}

int find_player(char *s, t_data *m_struct)
{
    int i = 0;
    while (s[i])
    {
       if (s[i] == 'N' || s[i] == 'E' || s[i] == 'W' || s[i] == 'S') {
		   set_player_vision(s[i], m_struct);
		   return i;
	   }
        i++;
    }
    return -1;  
}

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


void fill_map(t_list **last_elem, int elems_num, t_data *m_struct)
{
    char **map;
    t_list *elem;
    int is_player;
    int flag_player = 0;
    
    map = ft_calloc(elems_num + 1, sizeof(char *)); //количество наших сьтрочек + 1 для зануления
    elem = *last_elem;
    while (elems_num)
    {
        map[elems_num - 1] =  (char *)elem->content;
        if (!flag_player)
        {
             if ((is_player = find_player(map[elems_num - 1], m_struct)) != -1)
             {
                 m_struct->map_player_y = (double)(elems_num - 1 + m_struct->voxel_size);
                 m_struct->map_player_x = (double)is_player;
                 m_struct->player_x = (float)is_player * (float)m_struct->voxel_size + (float)m_struct->voxel_size/2;
                m_struct->map_player_y = elems_num - 1;
				 m_struct->player_y = (float)(elems_num-1) * (float)m_struct->voxel_size + (float)m_struct->voxel_size/2;
                 flag_player = 1; 
                 map[elems_num - 1][is_player] = '0';
             }
        }
//посчитаем спрайты
        check_sprites(map[elems_num - 1], m_struct, elems_num);
        elem = elem->next;
        elems_num--;
    }
    //выведем карту
    while (map[elems_num])
    {
        //выводим строку???
        ft_putendl_fd(map[elems_num], 1);
        elems_num++;
    }
    m_struct->map = map;
}

void parse_map(t_data *m_struct)
{
   // int fd = open(argv[1], O_RDONLY);
    write(1, "PARSE_MAP\n", 10);

//школа
  // int fd = open("/Users/cerebus/Documents/clion_cub3d/real_map.cub", O_RDONLY);
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
        if (index == -1)
        {
            ft_lstadd_front(&last_elem, ft_lstnew(line));
            elems_num++;
            break;
        }
        else
        {
            //сохраняю в структуру параметров текстуры
            check_n_save_textures(&line[index], m_struct);
            //TODO
            //сохранить разрешение и другие параметры
        }
    }
   // printf("север %s\n", m_struct->params->north_texture_path);
    while (get_next_line(fd, &line))
    {
        ft_lstadd_front(&last_elem, ft_lstnew(line));
        elems_num++;
    }
    ft_lstadd_front(&last_elem, ft_lstnew(line));
   // free(line);
    elems_num++;
    m_struct->lst = last_elem;
    //создадим список для спрайтов (с массивом еще париться по поводу памяти каждый раз...
    m_struct->sprite_info->sprite_list = malloc(1*sizeof (t_sprite *));
    *(m_struct->sprite_info->sprite_list) = NULL;
    fill_map(&last_elem, elems_num, m_struct);
    //сега
  //  ft_lstclear(&last_elem, free);
   	close(fd);
}
