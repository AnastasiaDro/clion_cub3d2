/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_params_except.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <cerebus@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 05:00:47 by cerebus           #+#    #+#             */
/*   Updated: 2021/04/27 05:00:51 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_PARAMS_EXCEPT_H
# define PARSE_PARAMS_EXCEPT_H
# include "exceptions.h"
# include "parser_utils.h"

void	throw_params_exception(char *msg, int *is_error);

void	throw_params_except(t_parse_flags pFlags, t_data *m_struct, int is_err);

void	throw_empty_file(t_data *m_struct);

void	was_params(t_parse_flags parseFlags, t_data *m_struct);

#endif
