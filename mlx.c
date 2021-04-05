/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <cerebus@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 15:54:45 by cerebus           #+#    #+#             */
/*   Updated: 2021/03/15 23:31:13 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parcer.h"
#include "minilibx_opengl_20191021/mlx.h"
#include "stdlib.h"
#include <stdio.h>
#include "libft/libft.h"

#include "new_cub_utils.h"
#include "draw_utils.h"
#include "unistd.h"
//библиотека математических функций
#include <math.h>
#include "constants.h"
#include "texture_parse.h"
#include "key_hooking.h"
#include "sprites_utils.h"

// 3d
int     render_next_frame(t_data *m_struct)
{
    draw_floor_ceil1(m_struct, m_struct->screen_higth, m_struct->screen_width);
	draw_lab_dda(m_struct);
	return 1;
}

int cross_hook(t_data *m_struct)
{
	mlx_destroy_window(m_struct->mlx, m_struct->mlx_win);
	mlx_destroy_image(m_struct->mlx, m_struct->img);
	ft_lstclear(&m_struct->lst, free);
	free(m_struct->map);
	exit(0);
}


int key_hook(int keycode, t_data *m_struct)
{
    printf("hello Nest! keycode is %d\n", keycode);
//шаг вперед

    if (keycode == 13)
	{
		step_forward(m_struct, 0.1);
		return 1;
	}
//шаг назад
    if (keycode == 1)
	{
		step_backward(m_struct, 0.0872665);
		return 1;
	}
    if (keycode == 0)
	{
		step_left(m_struct, 0.0872665);
		return 1;
	}
    if (keycode == 2)
	{
		step_rigth(m_struct, 0.0872665);
		return 1;
	}

//поворот налево
    if (keycode == 123)
	{
		double rotSpeed = 0.0872665; // 5 градусов
		rotate(m_struct, rotSpeed);
		return 1;
	}
//поворот направо
	if (keycode == 124)
	{
		double rotSpeed = -0.0872665; // 5 градусов
		rotate(m_struct, rotSpeed);
		return 1;
	}
    if (keycode == 53)
	{
    	mlx_destroy_window(m_struct->mlx, m_struct->mlx_win);
    	mlx_destroy_image(m_struct->mlx, m_struct->img);
		ft_lstclear(&m_struct->lst, free);
		free(m_struct->map);
		exit(0);
	}
    return 1;
}

// 2d
//int key_hook(int keycode, t_data *m_struct)
//{
//	printf("hello Nest! keycode is %d\n", keycode);
//	int p_x = m_struct->map_player_x;
//	int p_y = m_struct->map_player_y;
//	char **map = m_struct->map;
//	if (keycode == 1 && map[p_y + 1][p_x] != '1')
//	{
//		m_struct->map_player_y+=1;3
//		change_y_p_coords(m_struct);
//	}
//	if (keycode == 13 && map[p_y - 1][p_x] != '1')
//	{
//		m_struct->map_player_y-=1;
//		change_y_p_coords(m_struct);
//		//mlx_put_image_to_window(m_struct->mlx, m_struct->mlx_win, m_struct->img, 0, 0);
//		//return 1;
//	}
//	if (keycode == 2 && map[p_y][p_x + 1] != '1')
//	{
//		m_struct->map_player_x += 1;
//		change_x_p_coors(m_struct);
//	//	mlx_put_image_to_window(m_struct->mlx, m_struct->mlx_win, m_struct->img, 0, 0);
//	}
//	if (keycode == 0 && map[p_y][p_x - 1] != '1')
//	{
//		m_struct->map_player_x -= 1;
//		change_x_p_coors(m_struct);
//	//	mlx_put_image_to_window(m_struct->mlx, m_struct->mlx_win, m_struct->img, 0, 0);
//	}
//	printf("%d hello from key_hook!\n", keycode);

//	mlx_put_image_to_window(m_struct->mlx, m_struct->mlx_win, m_struct->img, 0, 0);
//	return 1;
//}


int main()
{
    t_data m_struct;

    m_struct.mlx = mlx_init();
    m_struct.screen_width = 512;
    m_struct.screen_higth = 512;
    m_struct.voxel_size = 32;

    //массив текстур
    t_textu textu[4];
    textu[0].adress = NORTH_TEXTURE;
    textu[1].adress = SOUTH_TEXTURE;
    textu[2].adress = WEST_TEXTURE;
    textu[3].adress = EAST_TEXTURE;

    //спрайты
	t_spr_info *sprite_info;
   if(!(sprite_info = malloc(sizeof(t_spr_info))))
   {
   		write(1, "NULL!", 5);
   		exit(0);
   }
    t_params *params = malloc(sizeof (t_params));
    m_struct.params = params;
    init_sprite_info(sprite_info, 64,64, BARREL);
	m_struct.sprite_info = sprite_info;

	init_textu_arr(textu, 128, 128);
	m_struct.textu = textu;
// парсинг карты
    parse_map(&m_struct);

	m_struct.img = mlx_new_image(m_struct.mlx, m_struct.screen_width, m_struct.screen_higth);

	m_struct.mlx_win = mlx_new_window(m_struct.mlx, m_struct.screen_width, m_struct.screen_higth, "hello, world!");

	mlx_hook(m_struct.mlx_win, KEY_PRESS, KEY_PESS_MASK, key_hook, &m_struct);
	// для крестика
	mlx_hook(m_struct.mlx_win, KEY_PRESS, KEY_PESS_MASK, key_hook, &m_struct);
	mlx_hook(m_struct.mlx_win, CROSS_PRESS, CROSS_PRESS_MASK, cross_hook, &m_struct);
	m_struct.addr = mlx_get_data_addr(m_struct.img, &m_struct.bits_per_pixel, &m_struct.line_length,
									  &m_struct.endian);

   // render_next_frame(&m_struct);
	mlx_loop_hook(m_struct.mlx, render_next_frame, &m_struct);
	mlx_loop(m_struct.mlx);

	ft_lstclear(&m_struct.lst, free);
	free(m_struct.map);
	exit(0);
}