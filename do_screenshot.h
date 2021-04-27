/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_screenshot.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <cerebus@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 16:15:14 by cerebus           #+#    #+#             */
/*   Updated: 2021/04/27 22:38:34 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DO_SCREENSHOT_H
# define DO_SCREENSHOT_H

typedef struct s_scr_shot {
	int				fd;
	unsigned char	*header;
	int				size;
}				t_scr_shot;

void	save(t_data *m_struct);

#endif
