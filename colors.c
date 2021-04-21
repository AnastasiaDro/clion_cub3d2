//
// Created by  Anastasia on 18.04.2021.
//
#include "colors.h"
#define IS_SPACE ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
#define IS_NUM (str[i] >= '0' && str[i] <='9')


void make_color_exception(char *s, t_data *m_struct)
{
	throwException(INVALID_FLOOR_COLOR);
	free(s);
	s = NULL;
	free_all(m_struct);
	exit (0);
}

int go_to_the_next_color(int i, char *str)
{
	while(str[i] && str[i] >= '0' && str[i] <= '9')
		i++;
	while (str[i] && str[i]!= ',')
	{
		if ((str[i] != ' ') && !(str[i] >= '0' && str[i] <= '9'))
			return (-1);
		i++;
	}
	i++;
	while (str[i] == ' ')
		i++;
	if (!(str[i] >= '0' && str[i] <= '9'))
		return (-1);
	return (i);
}

int check_color_part(char *str)
{
	int i;
	int num_start;
	int num_length;
	int color;

	i = 0;
	num_start = i;
	while(str[i] >= '0' && str[i] <= '9')
		i++;
	num_length = i - num_start;
	if (num_length > 3)
		return (-1);
	color = ft_atoi(str);
	if (color > 255)
		return (-1);
	return (color);
}

int check_color_s_end(char *str, int i)
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

int get_color(char *s, t_data *m_struct)
{
	int     i;
    t_color *m_color;
	char    *str;
    int     color;

    i = 0;
    str = s + 1;
    color = 0x000000;
    m_color = malloc(sizeof (t_color));
	while(str[i] == ' ')
		i++;
	m_color->r = check_color_part(&str[i]);
	if (m_color->r == -1)
		make_color_exception(s, m_struct);
	i = go_to_the_next_color(i, str);
	if (i == -1 || (m_color->g = check_color_part(&str[i])) == -1)
		make_color_exception(s, m_struct);
	i = go_to_the_next_color(i, str);
	if (i == -1 || (m_color->b = check_color_part(&str[i])) == -1)
		make_color_exception(s, m_struct);
	if (check_color_s_end(str, i) == -1)
		make_color_exception(s, m_struct);
	color = m_color->r * (int)(pow(16, 4))+ m_color->g * (int)(pow(16, 2)) + m_color->b;
	free(s);
	return (color);
}
