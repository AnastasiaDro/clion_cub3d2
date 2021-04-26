/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <cerebus@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 23:01:03 by cerebus           #+#    #+#             */
/*   Updated: 2021/04/26 23:02:30 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_CHECKER_H
# define MAP_CHECKER_H
# include "constants.h"
# include "libft/libft.h"
# include "exceptions.h"

int	check_map (char **map, int elems_num);

int	big_first_str(char *cur_s, int next_s_len, int cur_s_len);

int	small_first_str(char *next_s, int next_s_len, int cur_s_len);

int	check_spc_borders(int start_i, char **map, char *cur_s, int s_num);

int	check_borders(char **map, int l_i, int i, int coef);

#endif
