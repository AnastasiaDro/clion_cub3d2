//
// Created by Cesar Erebus on 4/26/21.
//

#include "cub_utils.h"
#include "parser_utils.h"

int	get_check_tex(char *s, t_data *m_struct, t_parse_flags *parse_f)
{
    t_params	*params;

    params = m_struct->params;
    if (!ft_strncmp(s, "NO", 2) && !(parse_f->north))
        return (get_tex_path(s, &params->north_tex_path, &(parse_f->north)));
    if (!ft_strncmp(s, "SO", 2) && !parse_f->south)
        return (get_tex_path(s, &params->south_tex_path, &(parse_f->south)));
    if (!ft_strncmp(s, "WE", 2) && !parse_f->west)
        return (get_tex_path(s, &params->west_tex_path, &(parse_f->west)));
    if (!ft_strncmp(s, "EA", 2) && !parse_f->east)
        return (get_tex_path(s, &params->east_tex_path, &(parse_f->east)));
    if (!ft_strncmp(s, "S", 1) && !parse_f->sprite)
        return (get_tex_path(s, &params->sprite_tex_path, &(parse_f->sprite)));
    return (0);
}
