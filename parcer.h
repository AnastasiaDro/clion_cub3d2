#ifndef PARSER_H
# define PARSER_H
# include <string.h>
# include "cub_utils.h"
# define MAX_WIDTH_NUM_LENGTH 4
# define MAX_HEIGHT_NUM_LENGTH 4

void parse_map(t_data *m_struct);

void throw_map_except(t_data *m_struct);

#endif

