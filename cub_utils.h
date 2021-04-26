/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <cerebus@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 23:28:01 by cerebus           #+#    #+#             */
/*   Updated: 2021/04/26 17:58:29 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_UTILS_H
# define CUB_UTILS_H
# include "math.h"
# include "texture_parse.h"
# include "libft/libft.h"
# include "sprites_utils.h"
# include "params.h"

typedef struct s_data {
	void		*img;
	char		*addr;
	void		*mlx_win;
	void		*mlx;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			side;
	char		**map;
	double		map_player_x;
	double		map_player_y;
	t_params	*params;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	t_textu		*textu;
	t_spr_info	*sprite_info;
	t_list		*lst;
	double		*z_buffer;
}				t_data;

t_textu			set_texture(t_data *m_struct, \
					double ray_dir_x, double ray_dir_y);

int				draw_lab_dda(t_data *m_struct);

#endif
