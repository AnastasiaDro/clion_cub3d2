/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_inits.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <cerebus@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 14:31:50 by cerebus           #+#    #+#             */
/*   Updated: 2021/04/26 14:32:31 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_INITS_H
# define MAIN_INITS_H
# include "cub_utils.h"

void	get_textures_paths(t_textu *textu, t_data *m_struct);

void	init_t_data(t_data *m_struct);

void	set_data(t_data *m_struct, t_params *params, \
					t_textu *textu, t_spr_info *spr_info);

int		init_sprite_info(t_spr_info *sprite_info);

void	init_all(t_data *m_struct);

#endif
