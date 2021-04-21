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
		if (!IS_SPACE && !IS_NUM)
			return (-1);
		i++;
	}
	i++;
	while (IS_SPACE)
		i++;
	if (!IS_NUM)
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
	while(IS_NUM)
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
	while (IS_NUM)
		i++;
	while (str[i])
	{
		if (!IS_SPACE)
			return (-1);
		i++;
	}
	return (1);
}

int get_color(char *s, t_data *m_struct)
{
	int i = 0;
	int r = 0x0;
	int g = 0x0;
	int b = 0x0;
	char *str;
	str = s+1;
	int color = 0x000000;
	while(str[i] == ' ')
		i++;
	if ((r = check_color_part(&str[i])) == -1)
		make_color_exception(s, m_struct);
	i = go_to_the_next_color(i, str);
	if (i == -1 || (g = check_color_part(&str[i])) == -1)
		make_color_exception(s, m_struct);
	i = go_to_the_next_color(i, str);
	if (i == -1 || (b = check_color_part(&str[i])) == -1)
		make_color_exception(s, m_struct);
	if (check_color_s_end(str, i) == -1)
		make_color_exception(s, m_struct);
	color = r * (int)(pow(16, 4))+ g * (int)(pow(16, 2)) + b;
	free(s);
	return (color);
}
