/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <cerebus@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 15:54:45 by cerebus           #+#    #+#             */
/*   Updated: 2021/04/22 14:51:20 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parcer.h"
#include "minilibx_opengl_20191021/mlx.h"
#include "stdlib.h"
#include "cub_utils.h"
#include "constants.h"
#include "texture_parse.h"
#include "key_hooking.h"
#include "sprites_utils.h"
#include "exceptions.h"
#include "draw_utils.h"
#include "main_inits.h"

int	render_next_frame(t_data *m_struct)
{
	draw_floor_ceil(m_struct, m_struct->params->screen_higth);
	draw_lab_dda(m_struct);
	return (1);
}

int	cross_hook(t_data *m_struct)
{
	free_all(m_struct);
	exit (0);
}

int	key_hook(int keycode, t_data *m_struct)
{
	if (keycode == 13 || keycode == 1)
		return (step_forw_back(m_struct, 0.0872665, keycode));
	if (keycode == 0 || keycode == 2)
		return (step_left_rigth(m_struct, 0.0872665, keycode));
	if (keycode == 123 || keycode == 124)
		return (rotate(m_struct, 0.0872665, keycode));
	if (keycode == 53)
	{
		free_all(m_struct);
		exit(0);
	}
	return (0);
}

int	main()
{
	t_data	m_struct;

	m_struct.mlx = mlx_init();
	init_all(&m_struct);
	parse_map(&m_struct, "/Users/cerebus/projects/clion_cub3d2/real_map1.cub");
	get_textures_paths(m_struct.textu, &m_struct);
	if (init_textu_arr(m_struct.textu, 128, 128) == -1)
		free_all(&m_struct);
	if (set_sprite_info(m_struct.sprite_info, 64, 64, \
						m_struct.params->sprite_texture_path) == -1)
		free_all(&m_struct);
	m_struct.img = mlx_new_image(m_struct.mlx, m_struct.params->screen_width, \
								m_struct.params->screen_higth);
	m_struct.mlx_win = mlx_new_window(m_struct.mlx, m_struct.params->screen_width, \
									m_struct.params->screen_higth, PROG_NAME);
	mlx_hook(m_struct.mlx_win, KEY_PRESS, 1L << 0, key_hook, &m_struct);
	mlx_hook(m_struct.mlx_win, CROSS_PRESS, 1L << 5, cross_hook, &m_struct);
	m_struct.addr = mlx_get_data_addr(m_struct.img, &m_struct.bits_per_pixel, &m_struct.line_length, \
										&m_struct.endian);
	mlx_loop_hook(m_struct.mlx, render_next_frame, &m_struct);
	mlx_loop(m_struct.mlx);
	exit(0);
}
