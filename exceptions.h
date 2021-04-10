//
// Created by Cesar Erebus on 4/4/21.
//

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include "new_cub_utils.h"

#define NORTH_TEX_PATH_ERROR "Invalid North Texture path"
#define SOUTH_TEX_PATH_ERROR "Invalid South Texture path"
#define WEST_TEX_PATH_ERROR "Invalid West Texture path"
#define EAST_TEX_PATH_ERROR "Invalid East Texture path"

void throwException(char *msg);
int free_all(t_data *m_struct);

#endif //EXCEPTIONS_H
