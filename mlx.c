/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <cerebus@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 15:54:45 by cerebus           #+#    #+#             */
/*   Updated: 2021/04/27 22:24:20 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
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
#include "parse_args.h"
#include "do_screenshot.h"

int	render_next_frame(t_data *m_struct)
{
	make_move(m_struct);
	draw_floor_ceil(m_struct, m_struct->params->screen_h);
	draw_lab_dda(m_struct);
	return (1);
}

int	cross_hook(t_data *m_struct)
{
	free_all(m_struct);
	exit (0);
}

void	check_print_screen(t_data *m_struct, char *s, int argc)
{
	if (argc == 3)
	{
		render_next_frame(m_struct);
		check_save(s);
		save(m_struct);
	}
}

int	main(int argc, char *argv[])
{
	t_data	m_struct;

	check_args_num(argc);
	check_map_arg(argc, argv);
	m_struct.mlx = mlx_init();
	init_all(&m_struct);
	parse_map(&m_struct, argv[1]);
	get_textures_paths(m_struct.textu, &m_struct);
	if (init_textu_arr(m_struct.textu, 128, 128) == -1)
		free_all(&m_struct);
	if (set_sprite_info(m_struct.sprite_info, 64, 64, \
						m_struct.params->sprite_tex_path) == -1)
		free_all(&m_struct);
	m_struct.img = mlx_new_image(m_struct.mlx, m_struct.params->screen_w, \
								m_struct.params->screen_h);
	m_struct.mlx_win = mlx_new_window(m_struct.mlx, m_struct.params->screen_w, \
									m_struct.params->screen_h, PROG_NAME);
	mlx_hook(m_struct.mlx_win, KEY_PRESS, 1L << 0, key_press, &m_struct);
	mlx_hook(m_struct.mlx_win, KEY_RELEASE, 1L << 1, key_release, &m_struct);
	mlx_hook(m_struct.mlx_win, CROSS_PRESS, 1L << 5, cross_hook, &m_struct);
	m_struct.addr = mlx_get_data_addr(m_struct.img, &m_struct.bits_per_pixel, &m_struct.line_length, \
										&m_struct.endian);
	mlx_loop_hook(m_struct.mlx, render_next_frame, &m_struct);
	check_print_screen(&m_struct, argv[2], argc);
	mlx_loop(m_struct.mlx);
}
