/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sortSprites.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <cerebus@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 01:54:03 by cerebus           #+#    #+#             */
/*   Updated: 2021/04/27 01:55:33 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SORTSPRITES_H
# define SORTSPRITES_H
# include "cub_utils.h"
# include "sprites_utils.h"
# include "draw_sprites.h"

typedef struct s_sort_spr {
	int		found;
	double	sec_distance;
	double	tmp_distance;
	double	sec_x;
	double	sec_y;
	double	tmp_x;
	double	tmp_y;
}				t_sort_spr;

void	sortSprites(t_sprite **sprite_list);

void	move(t_sprite **t1, t_sprite **t2, t_sort_spr *t_sort);

void	parse_t2_smaller(t_sprite **t1, t_sprite **t2, t_sort_spr *t_sort);

void	parse_t2_biger(t_sprite **t1, t_sprite **t2, t_sort_spr *t_sort);

#endif
