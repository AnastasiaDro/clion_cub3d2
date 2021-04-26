//
// Created by Cesar Erebus on 4/26/21.
//

#include "cub_utils.h"
#include "exceptions.h"

void init_z_buffer(t_data *m_struct)
{
    m_struct->z_buffer = malloc(m_struct->params->screen_width * sizeof(double));
    if(!m_struct->z_buffer)
    {
        throw_exception(MALLOC_ERROR);
        free_all(m_struct);
    }
}
