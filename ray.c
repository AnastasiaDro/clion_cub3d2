/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <cerebus@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 18:41:46 by cerebus           #+#    #+#             */
/*   Updated: 2021/04/26 18:45:16 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include "math.h"

void	calc_ray_length(t_ray *ray)
{
	ray->deltaDistX = (ray->DirY == 0) ? 0 : ((ray->DirX == 0) ? 1 : fabs(1 / ray->DirX));
	ray->deltaDistY = (ray->DirX == 0) ? 0 : ((ray->DirY == 0) ? 1 : fabs(1 / ray->DirY));
}

void	calc_ray_dir(t_ray *ray, t_data *m_struct, int x)
{
	ray->cameraX = 2 * x / (double) m_struct->params->screen_w - 1;
	ray->DirX = m_struct->dir_x + m_struct->plane_x * ray->cameraX;
	ray->DirY = m_struct->dir_y + m_struct->plane_y * ray->cameraX;
}

void	calc_step_side_dist(t_ray *ray, t_data *m_struct)
{
	if (ray->DirX < 0)
	{
		ray->stepX = -1;
		ray->sideDistX = (m_struct->map_player_x - ray->mapX) * ray->deltaDistX;
	}
	else
	{
		ray->stepX = 1;
		ray->sideDistX = (ray->mapX + 1.0 - \
				m_struct->map_player_x) * ray->deltaDistX;
	}
	if (ray->DirY < 0)
	{
		ray->stepY = -1;
		ray->sideDistY = (m_struct->map_player_y - ray->mapY) * ray->deltaDistY;
	}
	else
	{
		ray->stepY = 1;
		ray->sideDistY = (ray->mapY + 1.0 - \
				m_struct->map_player_y) * ray->deltaDistY;
	}
}

void	set_ray_params(t_ray *ray, t_data *m_struct, int x)
{
	calc_ray_dir(ray, m_struct, x);
	calc_ray_length(ray);
	ray->mapX = (int) m_struct->map_player_x;
	ray->mapY = (int) m_struct->map_player_y;
	ray->hit = 0;
	calc_step_side_dist(ray, m_struct);
}
