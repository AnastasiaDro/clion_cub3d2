//
// Created by Cesar Erebus on 4/4/21.
//

#ifndef EXCEPTIONS_H
# define EXCEPTIONS_H

# include "new_cub_utils.h"

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

void	throwException(char *msg);
int		free_all(t_data *m_struct);

#endif
