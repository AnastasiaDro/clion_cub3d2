//
// Created by Cesar Erebus on 4/27/21.
//
#include "exceptions.h"

void	throw_file_except(t_data *m_struct)
{
    throw_exception(INVALID_FILE);
    free_all(m_struct);
    exit(0);
}
