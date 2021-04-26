/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <cerebus@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 18:16:54 by cerebus           #+#    #+#             */
/*   Updated: 2021/04/26 18:17:33 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WALL_UTILS_H
# define WALL_UTILS_H
# include "ray.h"
# include "cub_utils.h"

typedef struct s_wall
{
	int		line_height;
	int		drawStart;
	int		draw_end;
	double	wallX;
}				t_wall;

void	calc_line_height(t_wall *wall, t_ray *ray, t_data *m_struct);

void	calc_sart_pixels(t_wall *wall, t_data *m_struct);

void	calc_wall_x(t_wall *wall, t_ray *ray, t_data *m_struct);

void	draw_wall_line(t_wall *wall, t_data *m_struct, t_txdraw *tdraw, int g);

#endif
