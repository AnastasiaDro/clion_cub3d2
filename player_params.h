//
// Created by Cesar Erebus on 4/24/21.
//

#ifndef PLAYER_PARAMS_H
# define PLAYER_PARAMS_H
# include "cub_utils.h"

int	set_player_direction(t_data *m_struct, double dirX, double dirY);

int	set_camera_plane(t_data *m_struct, double planeY, double PlaneX);

int	set_player_vision(char c, t_data *m_struct);

#endif
