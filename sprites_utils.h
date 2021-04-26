/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <cerebus@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 18:36:56 by cerebus           #+#    #+#             */
/*   Updated: 2021/04/26 18:39:31 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITES_UTILS_H
# define SPRITES_UTILS_H
# include "minilibx_opengl_20191021/mlx.h"

typedef struct s_sprite
{
	double			x;
	double			y;
	double			dist;
	struct s_sprite	*next;
}				t_sprite;

typedef struct s_spr_info
{
	int			num_sprites;
	t_sprite	**sprite_lst;
	int			h;
	int			w;
	int			code;
	void		*mlx;
	char		*sprite_path;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_spr_info;

int			set_sprite_info(t_spr_info *spr_info, int sprite_h, \
					int sprite_w, char *path);

t_sprite	*sprite_lstnew(double x, double y);

void		sprite_lstadd_front(t_sprite **lst, t_sprite *new);

void		sprite_lstclear(t_sprite **lst);

#endif
