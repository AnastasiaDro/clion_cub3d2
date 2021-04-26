/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exceptions.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <cerebus@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 14:14:07 by cerebus           #+#    #+#             */
/*   Updated: 2021/04/26 14:14:27 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXCEPTIONS_H
# define EXCEPTIONS_H
# include "cub_utils.h"

# define NORTH_TEX_PATH_ERROR "Invalid North texture path"
# define SOUTH_TEX_PATH_ERROR "Invalid South texture path"
# define WEST_TEX_PATH_ERROR "Invalid West texture path"
# define EAST_TEX_PATH_ERROR "Invalid East texture path"
# define SPRITE_PATH_ERROR "Invalid Sprite texture path"
# define INVALID_MAP "Invalid map"
# define INVALID_RESOLUTION "Invalid resolution"
# define NO_PLAYER "There is no player at the map!"
# define MORE_PLAYERS "Too many players at the map!"
# define INVALID_FLOOR_COLOR "Invalid floor color"
# define MALLOC_ERROR "Malloc Error"

void	throw_exception(char *msg);

int		free_all(t_data *m_struct);

#endif
