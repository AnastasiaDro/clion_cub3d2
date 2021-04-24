//
// Created by Cesar Erebus on 4/24/21.
//

#include <printf.h>
#include "map_checkers.h"


int check_borders(char **map, int l_i, int i, int coef)
{       //символ правее или левее         символ выше             //символ ниже
    if (map[i][l_i + 1*coef] == ' ' || map[i-1][l_i] == ' ' || map[i + 2][l_i] == ' ')
        return (MAP_ERROR);
    else
        return (1);
}


int check_spc_borders(int start_i, int end_i, char **map, char *cur_s, int s_num)
{
    int start = start_i;
    int end = end_i;
    while (start < end)
    {
        if (cur_s[start] == '0')
            if (cur_s[start-1] == ' ' || cur_s[start+1] == ' '
                || map[s_num-1][start] == ' ' || map[s_num+1][start] == ' ')
                return (MAP_ERROR);
        start++;
    }
    return (1);
}

int small_first_str(char *next_s, int next_s_len, int cur_s_len)
{
    int diff;
    diff = next_s_len - cur_s_len;
    while(diff >= 0)
    {
        if (next_s[next_s_len-diff-1] == '0')
            return (MAP_ERROR);
        diff--;
    }
    return (1);
}

int big_first_str(char *cur_s, int next_s_len, int cur_s_len)
{
    int diff;

    diff = cur_s_len - next_s_len;
    while(diff >= 0)
    {
        if (cur_s[cur_s_len-diff-1] == '0')
            return (MAP_ERROR);
        diff--;
    }
    return (1);
}

int check_lines_ends(char **map, int i, char *cur_s)
{
    char *next_s;
    int next_s_len;
//    int diff;
    int cur_s_len;

    cur_s_len = (int) ft_strlen(cur_s);
    next_s = map[i + 1];
    next_s_len = (int) ft_strlen(next_s);
    if (cur_s_len < next_s_len) {
        if (small_first_str(next_s, next_s_len, cur_s_len) == MAP_ERROR)
            return (MAP_ERROR);
    } else if (cur_s_len > next_s_len) {
        if (big_first_str(cur_s, next_s_len, cur_s_len) == MAP_ERROR)
            return (MAP_ERROR);
    } else {
        if (next_s[next_s_len - 1] == '0')
            return (MAP_ERROR);
    }
    return (1);
}

int check_line_start(int *l_i, int cur_s_len, char *cur_s)
{
    while(*l_i < cur_s_len)
    {
        if (cur_s[*l_i] == '0')
            return MAP_ERROR;
        if (cur_s[*l_i] == '1')
            break;
        (*l_i)++;
    }
    return (1);
}

int check_line_middle(char *cur_s, int *l_i, int i, char **map)
{
    int cur_s_len;

    cur_s_len = (int) ft_strlen(cur_s);
    while(*l_i < cur_s_len)
    {
        if (cur_s[*l_i] == '0')
        {
            if (check_borders(map, (*l_i), i, 1) == MAP_ERROR)
                return (MAP_ERROR);
        }
        (*l_i)++;
    }
    return (1);
}


int check_map (char **map, int elems_num)
{
    int cur_s_len;
    int i;
    int l_i;
    char *cur_s;

    i = 1;
    while (i < elems_num-2)
    {
        l_i = 0;
        cur_s = map[i];
        cur_s_len = (int)ft_strlen(cur_s);
        if (check_line_start(&l_i, cur_s_len, cur_s) == MAP_ERROR \
            || check_line_middle(cur_s, &l_i, i, map) == MAP_ERROR)
            return (MAP_ERROR);
        if (check_lines_ends(map, i, cur_s) == MAP_ERROR || \
                check_spc_borders(l_i, cur_s_len, map, cur_s, i) == MAP_ERROR)
            return (MAP_ERROR);
        i++;
    }
    cur_s = map[i];
    if (check_spc_borders(0, ft_strlen(cur_s), map, cur_s, i) == MAP_ERROR)
        return (MAP_ERROR);
    return (1);
}
