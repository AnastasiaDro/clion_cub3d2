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
# include "new_cub_utils.h"

int	rotate(t_data *m_struct, double rotSpeed, int keycode);

int	step_forw_back(t_data *m_struct, double moveSpeed, int keycode);

int	step_left_rigth(t_data *m_struct, double moveSpeed, int keycode);

#endif
