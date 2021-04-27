/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press_release.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <cerebus@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 22:27:22 by cerebus           #+#    #+#             */
/*   Updated: 2021/04/27 22:27:34 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_hooking.h"

int	key_press(int keycode, t_data *m_struct)
{
	if (keycode == 53)
	{
		free_all(m_struct);
		exit(0);
	}
	turn_on_flags(keycode, m_struct);
	return (0);
}

int	key_release(int keycode, t_data *m_struct)
{
	if (keycode == 53)
	{
		free_all(m_struct);
		exit(0);
	}
	turn_off_flags(keycode, m_struct);
	return (0);
}
