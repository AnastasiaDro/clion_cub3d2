/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   press_fgs_struct.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <cerebus@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 22:34:02 by cerebus           #+#    #+#             */
/*   Updated: 2021/04/27 22:34:46 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRESS_FGS_STRUCT_H
# define PRESS_FGS_STRUCT_H

typedef struct s_press_flgs {
	int	forw;
	int	backw;
	int	left;
	int	right;
	int	rot_left;
	int	rot_right;
}				t_press_flgs;
#endif
