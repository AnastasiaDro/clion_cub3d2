//
// Created by  Anastasia on 23.04.2021.
//

#include "wall_utils.h"
#include "draw_utils.h"

//Calculate height of line to draw on screen

void calc_line_height(t_wall *wall, t_ray *ray, t_data *m_struct)
{
	double coef;
	double h;
	double w;

	h = m_struct->params->screen_higth;
	w = m_struct->params->screen_width;
	coef = w / h * 0.77;
	wall->line_height = (int) (h / ray->perpWallDist * coef) ;
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

void draw_wall_line(t_wall *wall, t_data *m_struct, t_txdraw *txdraw, int gg) {
    double step;
    double texPos;
    double h;
    int y;

    h = m_struct->params->screen_higth;
    step = 1.0 * txdraw->textu->height / wall->line_height;
    y = wall->drawStart;
    // Starting texture coordinate
    texPos = (wall->drawStart - h / 2 + (double)wall->line_height / 2) * step;
    while(y < wall->draw_end)
    {
        // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
        txdraw->texY = (int) texPos;
        texPos += step;
        int color = textu_mlx_pixel_get(txdraw->textu, txdraw->texX, txdraw->texY);
        cerebus_mlx_pixel_put(m_struct, gg, y, color);
        y++;
    }
}
