/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <cerebus@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 23:18:39 by cerebus           #+#    #+#             */
/*   Updated: 2021/04/26 18:11:10 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H
# include "cub_utils.h"
# include "exceptions.h"

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}				t_color;

int				check_color_part(char *str);

int				go_to_the_next_color(int i, char *str);

void			make_color_exception(char *s, t_data *m_struct);

int				check_color_s_end(char *str, int i);

int				get_color(char *s, t_data *m_struct, int *flag);

void			parse_line_sect(int i, char *s, t_data *m_struct, int *color_part);

#endif
