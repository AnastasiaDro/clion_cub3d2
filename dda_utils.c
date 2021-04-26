/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <cerebus@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 23:41:25 by cerebus           #+#    #+#             */
/*   Updated: 2021/04/26 17:10:49 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dda_utils.h"
#include "wall_utils.h"
#include "texture_parse.h"
#include "draw_sprites.h"

void	go_to_the_wall(t_ray *ray, t_data *m_struct)
{
	while (ray->hit == 0)
	{
		if (ray->sideDistX <= ray->sideDistY)
		{
			ray->sideDistX += ray->deltaDistX;
			ray->mapX += ray->stepX;
			m_struct->side = 0;
		}
		else
		{
			ray->sideDistY += ray->deltaDistY;
			ray->mapY += ray->stepY;
			m_struct->side = 1;
		}
		if (m_struct->map[ray->mapY][ray->mapX] == '1')
			ray->hit = 1;
	}
}

void	calc_camera_dist(t_ray *ray, t_data *m_struct)
{
	double	first_part;

	if (m_struct->side == 0)
		ray->perpWallDist = (ray->mapX - m_struct->map_player_x \
			+ (1 - (double)ray->stepX) / 2) / ray->DirX;
	else
	{
		first_part = (double)(ray->mapY - m_struct->map_player_y \
			+ (1 - (double)ray->stepY) / 2);
		ray->perpWallDist = first_part / ray->DirY;
	}
}

void	calc_x_textu_coord(t_data *m_struct, \
			t_ray *ray, t_wall *wall, t_txdraw *txdraw)
{
	txdraw->texX = (int)(wall->wallX * (double)(txdraw->textu->width));
	if (m_struct->side == 0 && ray->DirX > 0)
		txdraw->texX = txdraw->textu->height - txdraw->texX - 1;
	if (m_struct->side == 1 && ray->DirY < 0)
		txdraw->texX = txdraw->textu->width - txdraw->texX - 1;
}

void	cast_walls(t_data *m_struct, t_ray *ray, t_wall *wall)
{
	int			x;
	int			gg;
	t_textu		tx_struct;
	t_txdraw	txdraw;

	x = 0;
	gg = m_struct->params->screen_width;
	while (x < m_struct->params->screen_width)
	{
		set_ray_params(ray, m_struct, x);
		go_to_the_wall(ray, m_struct);
		calc_camera_dist(ray, m_struct);
		calc_line_height(wall, ray, m_struct);
		calc_sart_pixels(wall, m_struct);
		calc_wall_x(wall, ray, m_struct);
		tx_struct = set_texture(m_struct, ray->DirX, ray->DirY);
		txdraw.textu = &tx_struct;
		calc_x_textu_coord(m_struct, ray, wall, &txdraw);
		draw_wall_line(wall, m_struct, &txdraw, gg);
		x++;
		gg--;
		m_struct->z_buffer[x - 1] = ray->perpWallDist;
	}
}

void	cast_sprites(t_data *m_struct)
{
	double		h;
	double		w;
	double		coef;
	t_sprite	*sprite_lst;
	t_spr_draw	spr_draw;

	h = m_struct->params->screen_higth;
	w = m_struct->params->screen_width;
	coef = w / h * 0.77;
	set_sprite_data(m_struct);
	sprite_lst = *(m_struct->sprite_info->sprite_lst);
	while (sprite_lst != NULL)
	{
		set_sprite_pos(&spr_draw, sprite_lst, m_struct);
		set_s_draw_limits(&spr_draw, m_struct, coef);
		draw_sprite(&spr_draw, m_struct);
		sprite_lst = sprite_lst->next;
	}
}
