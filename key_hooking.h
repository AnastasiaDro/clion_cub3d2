/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooking.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <cerebus@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 20:32:29 by cerebus           #+#    #+#             */
/*   Updated: 2021/04/21 20:42:15 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEY_HOOKING_H
# define KEY_HOOKING_H
# include "cub_utils.h"
#include "exceptions.h"

typedef struct s_press_flgs {
    int forw;
    int backw;
    int left;
    int right;
    int rot_left;
    int rot_right;
    int exit;
}              t_press_flgs;

int make_move(t_press_flgs *press_flgs, t_data *m_struct);

int	rotate(t_data *m_struct, double rot_speed, int keycode);

int	step_forw_back(t_data *m_struct, double move_speed, int keycode);

int	step_left_rigth(t_data *m_struct, double move_speed, int keycode);

int turn_on_flags(t_press_flgs *press_flgs, int key_code, t_data *m_struct);

int turn_off_flags(t_press_flgs *press_flgs, int key_code, t_data *m_struct);

#endif
