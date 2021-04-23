//
// Created by  Anastasia on 23.04.2021.
//

#include "wall_utils.h"

//Calculate height of line to draw on screen

void calc_line_height(t_wall *wall, t_ray *ray, t_data *m_struct)
{
	//wall->line_height = (int) (m_struct->params->screen_higth / ray->perpWallDist);
	double coef;

	if (m_struct->params->screen_higth >= m_struct->params->screen_width)
		coef = (double) m_struct->params->screen_higth / (double)m_struct->params->screen_width * 0.77;
	else
		coef = (double)m_struct->params->screen_width / (double) m_struct->params->screen_higth * 0.77;
	wall->line_height = (int) (m_struct->params->screen_higth / ray->perpWallDist * coef) ;
}

void calc_sart_pixels(t_wall *wall, t_data *m_struct)
{
	wall->drawStart = -(wall->line_height) / 2 + m_struct->params->screen_higth / 2;
	if (wall->drawStart < 0)
		wall->drawStart = 0;
	wall->draw_end = wall->line_height / 2 + m_struct->params->screen_higth / 2;
	if (wall->draw_end >= m_struct->params->screen_higth)
		wall->draw_end = m_struct->params->screen_higth - 1;
}

void calc_wall_x(t_wall *wall, t_ray *ray, t_data *m_struct)
{

	if (m_struct->side == 0)
		wall->wallX = m_struct->map_player_y + ray->perpWallDist * ray->DirY;
	else
		wall->wallX = m_struct->map_player_x + ray->perpWallDist * ray->DirX;
	wall->wallX -= floor(wall->wallX);
}