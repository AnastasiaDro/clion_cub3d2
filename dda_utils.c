//
// Created by  Anastasia on 23.04.2021.
//

#include "dda_utils.h"
#include "wall_utils.h"
#include "texture_parse.h"


//jump to next map square, OR in x-direction, OR in y-direction

void go_to_the_wall(t_ray *ray, t_data *m_struct)
{
	while (ray->hit == 0)
	{
		//jump to next map square, OR in x-direction, OR in y-direction
		if (ray->sideDistX <= ray->sideDistY) {
			ray->sideDistX += ray->deltaDistX;
			ray->mapX += ray->stepX;
			m_struct->side = 0;
		} else {
			ray->sideDistY += ray->deltaDistY;

			ray->mapY += ray->stepY;
			m_struct->side = 1;
		}
		//Check if ray has hit a wall
		if (m_struct->map[ray->mapY][ray->mapX] == '1')
			ray->hit = 1;
	}
}

void calc_camera_dist(t_ray *ray, t_data *m_struct)
{
	if (m_struct->side == 0)
		ray->perpWallDist = (ray->mapX - m_struct->map_player_x + (1 - (double) ray->stepX) / 2) / ray->DirX;
	else
	{
		double firstPart = (double) (ray->mapY - m_struct->map_player_y + (1 - (double) ray->stepY) / 2);
		ray->perpWallDist = firstPart / ray->DirY;
	}
}

//x coordinate on the texture
void calc_x_textu_coord(t_data *m_struct, t_ray *ray, t_wall *wall, t_txdraw *txdraw)
{
	txdraw->texX = (int) (wall->wallX * (double) (txdraw->textu->width));
	if (m_struct->side == 0 && ray->DirX > 0)
		txdraw->texX = txdraw->textu->height - txdraw->texX - 1;
	if (m_struct->side == 1 && ray->DirY < 0)
		txdraw->texX = txdraw->textu->width - txdraw->texX - 1;

}
