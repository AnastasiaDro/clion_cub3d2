/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooking.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <cerebus@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 20:32:29 by cerebus           #+#    #+#             */
/*   Updated: 2021/04/27 22:36:27 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEY_HOOKING_H
# define KEY_HOOKING_H
# include "cub_utils.h"
# include "exceptions.h"
# include "press_fgs_struct.h"

int	make_move(t_data *m_struct);

int	rotate(t_data *m_struct, double rot_speed, int keycode);

int	step_forw_back(t_data *m_struct, double move_speed, int keycode);

int	step_left_rigth(t_data *m_struct, double move_speed, int keycode);

int	turn_on_flags(int key_code, t_data *m_struct);

int	turn_off_flags(int key_code, t_data *m_struct);

int	key_press(int keycode, t_data *m_struct);

int	key_release(int keycode, t_data *m_struct);

#endif
