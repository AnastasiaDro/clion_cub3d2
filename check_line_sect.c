//
// Created by Cesar Erebus on 4/26/21.
//

#include "colors.h"

void parse_line_sect(int i, char *s, t_data *m_struct, int *color_part)
{
    if (i == -1)
        make_color_exception(s, m_struct);
   *color_part = check_color_part(&(s + 1)[i]);
    if (*color_part == -1)
        make_color_exception(s, m_struct);
}
