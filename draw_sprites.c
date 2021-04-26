/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <cerebus@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 23:53:11 by cerebus           #+#    #+#             */
/*   Updated: 2021/04/26 11:48:25 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_sprites.h"
#include "draw_utils.h"

void	set_sprite_data(t_data *m_struct)
{
	t_sprite *sprite_lst;
	int		m_pl_x;
	int		m_pl_y;
	int 	diff_x;
	int		diff_y;

	diff_x = m_struct->map_player_x - sprite_lst->x;
	diff_y = m_struct->map_player_y - sprite_lst->y;
	sprite_lst = *(m_struct->sprite_info->sprite_lst);
	while (sprite_lst != NULL)
	{
		sprite_lst->dist = (diff_x * diff_x + diff_y * diff_y);
		sprite_lst = sprite_lst->next;
	}
	sprite_lst = *(m_struct->sprite_info->sprite_lst);
	sortSprites(&sprite_lst);
}

void	set_sprite_pos(t_spr_draw *spr_raw, t_sprite *sprite_lst, t_data *m_struct)
{
	double inv_det;

	spr_raw->sprite_x = sprite_lst->x - m_struct->map_player_x;
	spr_raw->sprite_y = sprite_lst->y - m_struct->map_player_y;
	inv_det = 1.0 / (m_struct->plane_x * m_struct->dir_y - m_struct->dir_x * m_struct->plane_y);
	spr_raw->transform_x = inv_det * (m_struct->dir_y * spr_raw->sprite_x - m_struct->dir_x * spr_raw->sprite_y);
	spr_raw->transform_y = inv_det * (-m_struct->plane_y * spr_raw->sprite_x + m_struct->plane_x * spr_raw->sprite_y);
	spr_raw->screen_x = (int)((m_struct->params->screen_width * 0.5) * (1 + spr_raw->transform_x / spr_raw->transform_y));
}

void	set_sprite_draw_limits(t_spr_draw *spr_draw, t_data *m_struct, double coef)
{
	int screen_h;
	int screen_w;

	screen_h = m_struct->params->screen_higth;
	screen_w = m_struct->params->screen_width;
	spr_draw->h = fabs(screen_h / (spr_draw->transform_y) * coef);
	spr_draw->start_y = (int)round(-spr_draw->h / 2 + (double)screen_h / 2 );
	if (spr_draw->start_y < 0)
		spr_draw->start_y = 0;
	spr_draw->end_y = (int)round(spr_draw->h / 2 + (double)screen_h / 2);
	if (spr_draw->end_y >= screen_h)
		spr_draw->end_y = screen_h - 1;
	spr_draw->w = fabs((screen_h / (spr_draw->transform_y) * coef));
	spr_draw->start_x = (int) round(-spr_draw->w / 2 + spr_draw->screen_x);
	if (spr_draw->start_x < 0)
		spr_draw->start_x = 0;
	spr_draw->end_x = (int) round(spr_draw->w / 2 + spr_draw->screen_x);
	if (spr_draw->end_x >= screen_w)
		spr_draw->end_x = screen_w - 1;
}

void	draw_sprite_line(t_spr_draw *spr_draw, t_data *m_struct, int line_i, int tex_x)
{
	int y;
	int tex_y;
	int d;
	int color;

	y = spr_draw->start_y;
	while(y < spr_draw->end_y)
	{
		d = (y) * 256 - m_struct->params->screen_higth * 128 +
			spr_draw->h * 128;
		tex_y = ((d * m_struct->sprite_info->h) / spr_draw->h) / 256;
		color = sprite_mlx_pixel_get(m_struct->sprite_info, tex_x, tex_y);
		if ((color & 0x00FFFFFF) != 0)
		{
			cerebus_mlx_pixel_put(m_struct, m_struct->params->screen_width - line_i, y, color);
		}
		y++;
	}
}


void	draw_sprite(t_spr_draw *spr_draw, t_data *m_struct, double *z_buffer)
{
	int		line_i;
	int		tex_x;
	int		multi;

	line_i = spr_draw->start_x;
	while (line_i < spr_draw->end_x)
	{
		multi = (line_i - (-spr_draw->w / 2 + spr_draw->screen_x));
		tex_x = (int)(256 * multi * m_struct->sprite_info->w / spr_draw->w) / 256;
		if (spr_draw->transform_y > 0 && (spr_draw->end_x - line_i) > 0 &&
			(spr_draw->end_x - line_i) < m_struct->params->screen_width \
				&& spr_draw->transform_y < z_buffer[line_i])
			draw_sprite_line(spr_draw, m_struct, line_i, tex_x);
		line_i++;
	}
}
