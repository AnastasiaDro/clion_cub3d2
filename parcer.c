#include "libft/libft.h"
#include "fcntl.h"
#include "get_next_line/get_next_line.h"
#include "new_cub_utils.h"


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
		   printf("player coordinates is x = %d\n", i);
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
            //printf(m_struct->)
			//m_struct->sprites_in_map[m_struct->sprite_info->num_sprites].x = i + 0.5;
//			printf("x = %f\n", m_struct->sprites_in_map[m_struct->sprite_info->num_sprites].x);
//			printf("y = %f\n", m_struct->sprites_in_map[m_struct->sprite_info->num_sprites].y);
			m_struct->sprite_info->num_sprites += 1;
			printf("counted sprite %d\n", m_struct->sprite_info->num_sprites);
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
               //  m_struct->map_player_x = (double)(is_player + m_struct->voxel_size);
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
   int fd = open("/Users/cerebus/Documents/clion_cub3d/map1.cub", O_RDONLY);
  //ДОМ
 // int fd = open("/Users/anastasia/CLionProjects/clion_cub3d/map1.cub", O_RDONLY);
    char *line;
    t_list *last_elem = NULL;
    int elems_num = 0;

//нам нужно считать карту, чувак хочет её строки в список, а потом превратить его
// в двумерный массив чаров, но идет от начала к концу,
// мы будем заполнять список в обратном порядке, чтобы программа работала быстрее
    while (get_next_line(fd, &line))
    {
     //   write(1, "GNL\n", 4);
         ft_lstadd_front(&last_elem, ft_lstnew(line));
         elems_num++;
    }
    ft_lstadd_front(&last_elem, ft_lstnew(line));
   // free(line);
    elems_num++;
    m_struct->lst = last_elem;
    //создадим массив для спрайтов
    //РАЗМЕР МОЖЕТ ОКАЗАТЬСЯ МАЛ! т.к. только количество строк задаем
	//m_struct->sprites_in_map = ft_calloc(sizeof(t_sprite), elems_num);
	//переделаем под список
	//m_struct->sprites_list = sprite_lstnew(0, 0);
	//if (!m_struct->sprites_list)
		write(1, "NULL", 4);
    m_struct->sprite_info->sprite_list = malloc(1*sizeof (t_sprite *));
    *(m_struct->sprite_info->sprite_list) = NULL;
    fill_map(&last_elem, elems_num, m_struct);
    //сега
  //  ft_lstclear(&last_elem, free);
   	close(fd);
}
