/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_line_checkers.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <cerebus@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 23:04:26 by cerebus           #+#    #+#             */
/*   Updated: 2021/04/26 23:04:33 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_LINE_CHECKERS_H
# define MAP_LINE_CHECKERS_H
# include "map_checker.h"

int	check_line_middle(char *cur_s, int *l_i, int i, char **map);

int	check_line_start(int *l_i, int cur_s_len, char *cur_s);

int	check_lines_ends(char **map, int i, char *cur_s);

#endif
