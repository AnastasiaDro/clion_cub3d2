/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <cerebus@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 23:51:33 by cerebus           #+#    #+#             */
/*   Updated: 2021/04/25 23:52:37 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DDA_UTILS_H
# define DDA_UTILS_H
# include "cub_utils.h"
# include "ray.h"
# include "wall_utils.h"

void go_to_the_wall(t_ray *ray, t_data *m_struct);

void calc_camera_dist(t_ray *ray, t_data *m_struct);

void calc_x_textu_coord(t_data *m_struct, t_ray *ray, \
						t_wall *wall, t_txdraw *txdraw);

void cast_walls(t_data *m_struct, t_ray *ray, t_wall *wall, double *z_buffer);

void cast_sprites(t_data *m_struct, double const *z_buffer);

#endif
