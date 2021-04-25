/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <cerebus@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 23:53:11 by cerebus           #+#    #+#             */
/*   Updated: 2021/04/25 23:54:46 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_sprites.h"
#include "draw_utils.h"

void	set_sprite_data(t_data *m_struct)
{
	t_sprite *sprite_lst;

	sprite_lst = *(m_struct->sprite_info->sprite_list);
	while (sprite_lst != NULL)
	{
		sprite_lst->distance = ((m_struct->map_player_x - sprite_lst->x) * (m_struct->map_player_x - sprite_lst->x) + (m_struct->map_player_y
				- sprite_lst->y) * (m_struct->map_player_y - sprite_lst->y));
		sprite_lst = sprite_lst->next;
	}
	sprite_lst = *(m_struct->sprite_info->sprite_list);
	sortSprites(&sprite_lst);
}

void	set_sprite_pos(t_spr_draw *spr_raw, t_sprite *sprite_lst, t_data *m_struct)
{
	double inv_det;

	spr_raw->sprite_x = sprite_lst->x - m_struct->map_player_x;
	spr_raw->sprite_y = sprite_lst->y - m_struct->map_player_y;
	inv_det = 1.0 / (m_struct->plane_x * m_struct->dir_y - m_struct->dir_x * m_struct->plane_y);
	spr_raw->transform_x = inv_det * (m_struct->dir_y * spr_raw->sprite_x - m_struct->dir_x * spr_raw->sprite_y);
	spr_raw->transform_y = inv_det * (-m_struct->plane_y * spr_raw->sprite_x + m_struct->plane_x * spr_raw->sprite_y); //this is actually the depth inside the screen, that what Z is in 3D
	spr_raw->screen_x = (int)((m_struct->params->screen_width * 0.5) * (1 + spr_raw->transform_x / spr_raw->transform_y));
}

void	set_sprite_draw_limits(t_spr_draw *spr_draw, t_data *m_struct, double coef)
{
	spr_draw->h = fabs(m_struct->params->screen_higth / (spr_draw->transform_y) * coef);
	spr_draw->draw_start_y = (int)round(-spr_draw->h / 2 + (double)m_struct->params->screen_higth / 2 );
	if(spr_draw->draw_start_y < 0)
		spr_draw->draw_start_y = 0;
	spr_draw->draw_end_y = (int)round(spr_draw->h / 2 + (double)m_struct->params->screen_higth / 2);
	if(spr_draw->draw_end_y >= m_struct->params->screen_higth )
		spr_draw->draw_end_y = m_struct->params->screen_higth - 1;
	spr_draw->w = fabs((m_struct->params->screen_higth / (spr_draw->transform_y) * coef));
	spr_draw->draw_start_x = (int) round(-spr_draw->w / 2 + spr_draw->screen_x);
	if(spr_draw->draw_start_x < 0)
		spr_draw->draw_start_x = 0;
	spr_draw->draw_end_x = (int) round(spr_draw->w / 2 + spr_draw->screen_x);
	if(spr_draw->draw_end_x >= m_struct->params->screen_width)
		spr_draw->draw_end_x = m_struct->params->screen_width - 1;
}

void	draw_sprite_line(t_spr_draw *spr_draw, t_data *m_struct, int line_i, int texX)
{
	int y;
	int tex_y;
	int d;
	int color;

	y = spr_draw->draw_start_y;
	while(y < spr_draw->draw_end_y)
	{
		d = (y) * 256 - m_struct->params->screen_higth * 128 +
			spr_draw->h * 128;
		tex_y = ((d * m_struct->sprite_info->h) / spr_draw->h) / 256;
		color = sprite_mlx_pixel_get(m_struct->sprite_info, texX, tex_y);
		if ((color & 0x00FFFFFF) != 0)
		{
			cerebus_mlx_pixel_put(m_struct, m_struct->params->screen_width - line_i, y, color);
		}
		y++;
	}
}


void	draw_sprite(t_spr_draw *spr_draw, t_data *m_struct, double const *z_buffer)
{
	int		line_i;
	int		tex_x;

	line_i = spr_draw->draw_start_x;
	while (line_i < spr_draw->draw_end_x)
	{
		tex_x = (int)(256 * (line_i - (-spr_draw->w / 2 + spr_draw->screen_x)) * m_struct->sprite_info->w / spr_draw->w) / 256;
		if (spr_draw->transform_y > 0 && (spr_draw->draw_end_x - line_i) > 0 &&
			(spr_draw->draw_end_x - line_i) < m_struct->params->screen_width \
 && spr_draw->transform_y < z_buffer[line_i])
			draw_sprite_line(spr_draw, m_struct, line_i, tex_x);
		line_i++;
	}
}
