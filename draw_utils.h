/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <cerebus@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 20:11:29 by cerebus           #+#    #+#             */
/*   Updated: 2021/04/21 20:11:56 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_UTILS_H
# define  DRAW_UTILS_H

int	draw_background(int y, int limit, int color, t_data *m_struct);

int	draw_floor_ceil(t_data *m_struct, int screen_higth);

void     cerebus_mlx_pixel_put(t_data *data, int x, int y, int color);

#endif
