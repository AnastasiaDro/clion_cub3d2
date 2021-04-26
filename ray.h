/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <cerebus@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 18:40:13 by cerebus           #+#    #+#             */
/*   Updated: 2021/04/26 18:41:38 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H
# include "cub_utils.h"
typedef struct s_ray
{
	double	DirX;
	double	DirY;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	double	cameraX;
	int		hit;
	int		stepX;
	int		stepY;
	int		mapX;
	int		mapY;
	double	perpWallDist;
}				t_ray;

void	calc_ray_dir(t_ray *ray, t_data *m_struct, int x);

void	calc_ray_length(t_ray *ray);

void	calc_step_side_dist(t_ray *ray, t_data *m_struct);

void	set_ray_params(t_ray *ray, t_data *m_struct, int x);

#endif
