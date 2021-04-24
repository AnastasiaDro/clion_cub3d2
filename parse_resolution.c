//
// Created by Cesar Erebus on 4/24/21.
//
#include "parse_resolution.h"


int get_num_length(char *str, int *i, int *num_start)
{
    while(str[*i] && (str[*i] == ' '))
        (*i)++;
    *num_start = *i;
    while(str[*i] >= '0' && str[*i] <='9')
        (*i)++;
    return ((*i) - (*num_start));
}

int set_max_resolution(t_data *m_struct, char *s, int max_w, int max_h)
{
    m_struct->params->screen_width = max_w;
    m_struct->params->screen_higth = max_h;
    free(s);
    s = NULL;
    return (1);
}

void throw_resol_except(char **s, t_data *m_struct)
{
    throwException(INVALID_RESOLUTION);
    free(*s);
    *s = NULL;
    free_all(m_struct);
    exit(0);
}

int check_s_end(char *str, int i)
{
    while (str[i] >= '0' && str[i] <= '9')
        i++;
    while (str[i])
    {
        if (str[i] != ' ')
            return (-1);
        i++;
    }
    return (1);
}

int parse_resolution(char *s, t_data *m_struct)
{
    int num_start;
    int num_length;
    int i;
    int max_screen_w;
    int max_screen_h;

    i = 0;
    num_start = 0;
    num_length = get_num_length(s+1, &i, &num_start);
    mlx_get_screen_size(&max_screen_w, &max_screen_h);
    if (num_length > MAX_WIDTH_NUM_LENGTH)
        return (set_max_resolution(m_struct, s, max_screen_w, max_screen_h));
    m_struct->params->screen_width = ft_atoi(s+1);
    num_length = get_num_length(s+1, &i, &num_start);
    if (num_length > MAX_HEIGHT_NUM_LENGTH)
        return (set_max_resolution(m_struct, s, max_screen_w, max_screen_h));
    m_struct->params->screen_higth = ft_atoi(&(s+1)[num_start]);
    if (m_struct->params->screen_width > max_screen_w || m_struct->params->screen_higth > max_screen_h)
        return (set_max_resolution(m_struct, s, max_screen_w, max_screen_h));
    if(m_struct->params->screen_width <= 0 ||  m_struct->params->screen_higth <= 0 || check_s_end(s+1, i) == -1)
        throw_resol_except(&s, m_struct);
    free(s);
    s = NULL;
    return (1);
}
