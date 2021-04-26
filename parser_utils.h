/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <cerebus@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 18:55:54 by cerebus           #+#    #+#             */
/*   Updated: 2021/04/26 18:57:44 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_UTILS_H
# define PARSER_UTILS_H
# include "libft/libft.h"
# include "cub_utils.h"

typedef struct s_parse_flags
{
	int	resol;
	int	floor_color;
	int	ceil_color;
	int	north;
	int	south;
	int	west;
	int	east;
	int	sprite;
}				t_parse_flags;

int		get_sprites_list(char *s, t_data *m_struct, int elems_num);

int		is_empty(char **line);

void	throw_map_except(t_data *m_struct);

void	init_parse_flags(t_parse_flags *tParseFlags);

int		ft_strchr_index(char *s, char c);

int		find_string_start(char *s);

int		is_symbol_valid(char *s, char *arr);

int		get_tex_path(char *s, char **dst, int *flag);

int		check_symbols(char *s, t_data *m_struct, int *flag_player);

#endif
