//
// Created by Cesar Erebus on 4/24/21.
//
#include "player_params.h"

int set_player_direction(t_data *m_struct, double dirX, double dirY, double planeY, double PlaneX)
{
    m_struct->dir_x = dirX;
    m_struct->dir_y = dirY;
    m_struct->plane_y = planeY;
    m_struct->plane_x = PlaneX;
    return (1);
}

int set_player_vision(char c, t_data *m_struct)
{
    if (c == 'N')
        return (set_player_direction(m_struct, 0, -1, 0, -0.66));
    if (c == 'S')
        return (set_player_direction(m_struct, 0, 1, 0, 0.66));
    if (c == 'E')
        return (set_player_direction(m_struct, 1, 0, -0.66, 0));
    if (c == 'W')
        return (set_player_direction(m_struct, -1, 0, 0.66, 0));
    return (0);
}




