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

#include "parcer_new.h"
#include "minilibx_opengl_20191021/mlx.h"
#include "stdlib.h"
#include "libft/libft.h"
#include "new_cub_utils.h"
#include "unistd.h"
#include "constants.h"
#include "texture_parse.h"
#include "key_hooking.h"
#include "sprites_utils.h"
#include "exceptions.h"
#include "draw_utils.h"

int     render_next_frame(t_data *m_struct)
{
    draw_floor_ceil(m_struct, m_struct->params->screen_higth, m_struct->params->screen_width);
	draw_lab_dda(m_struct);
	return(1);
}

int cross_hook(t_data *m_struct)
{
	free_all(m_struct);
	exit(0);
}

int key_hook(int keycode, t_data *m_struct)
{
    if (keycode == 13)
	{
		step_forward(m_struct, 0.0872665);
		return (1);
	}
    if (keycode == 1)
	{
		step_backward(m_struct, 0.0872665);
		return (1);
	}
    if (keycode == 0)
	{
		step_left(m_struct, 0.0872665);
		return (1);
	}
    if (keycode == 2)
	{
		step_rigth(m_struct, 0.0872665);
		return (1);
	}
    if (keycode == 123)
	{
		rotate(m_struct, -0.0872665);
		return (1);
	}
	if (keycode == 124)
	{
		rotate(m_struct, 0.0872665);
		return (1);
	}
    if (keycode == 53)
	{
		free_all(m_struct);
		exit(0);
	}
    return (0);
}

int main()
{
    t_data m_struct;

    m_struct.mlx = mlx_init();
    m_struct.img = NULL;
    m_struct.mlx_win = NULL;
    m_struct.map = NULL;
    //массив текстур
    t_textu textu[4];

    //спрайты
	t_spr_info *sprite_info;
   if(!(sprite_info = malloc(sizeof(t_spr_info))))
   {
   		write(1, "NULL!", 5);
   		exit(0);
   }
    init_sprite_info(sprite_info);
    t_params *params = malloc(sizeof (t_params));
    init_params(params);
    m_struct.params = params;


	m_struct.textu = textu;
	m_struct.sprite_info = sprite_info;

    parse_map(&m_struct);
	textu[0].adress =  m_struct.params->north_texture_path;
	textu[1].adress = m_struct.params->south_texture_path;
	textu[2].adress = m_struct.params->west_texture_path;;
	textu[3].adress = m_struct.params->east_texture_path;

	if (init_textu_arr(textu, 128, 128) == -1)
		free_all(&m_struct);
	if(set_sprite_info(sprite_info, 64, 64, m_struct.params->sprite_texture_path) == -1)
		free_all(&m_struct);

	m_struct.img = mlx_new_image(m_struct.mlx, m_struct.params->screen_width, m_struct.params->screen_higth);

	m_struct.mlx_win = mlx_new_window(m_struct.mlx, m_struct.params->screen_width, m_struct.params->screen_higth, "hello, world!");

	mlx_hook(m_struct.mlx_win, KEY_PRESS, KEY_PESS_MASK, key_hook, &m_struct);
	mlx_hook(m_struct.mlx_win, KEY_PRESS, KEY_PESS_MASK, key_hook, &m_struct);
	mlx_hook(m_struct.mlx_win, CROSS_PRESS, CROSS_PRESS_MASK, cross_hook, &m_struct);
	m_struct.addr = mlx_get_data_addr(m_struct.img, &m_struct.bits_per_pixel, &m_struct.line_length,\
									  &m_struct.endian);
	mlx_loop_hook(m_struct.mlx, render_next_frame, &m_struct);
	mlx_loop(m_struct.mlx);
	exit(0);
}