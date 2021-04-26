/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <cerebus@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 23:22:41 by cerebus           #+#    #+#             */
/*   Updated: 2021/04/26 17:36:07 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_utils.h"
#include "minilibx_opengl_20191021/mlx.h"
#include "ray.h"
#include "dda_utils.h"
#include "wall_utils.h"

t_textu	set_texture(t_data *m_struct, double ray_dir_x, double ray_dir_y)
{
	if (m_struct->side == 1)
	{
		if (ray_dir_y > 0)
			return (m_struct->textu[1]);
		else
			return (m_struct->textu[0]);
	}
	if (m_struct->side == 0)
	{
		if (ray_dir_x > 0)
			return (m_struct->textu[3]);
		else
			return (m_struct->textu[2]);
	}
	return (m_struct->textu[0]);
}

int	draw_lab_dda(t_data *m_struct)
{
	t_ray	ray;
	t_wall	wall;

	cast_walls(m_struct, &ray, &wall);
	cast_sprites(m_struct);
	mlx_put_image_to_window(m_struct->mlx, \
		m_struct->mlx_win, m_struct->img, 0, 0);
	return (1);
}
