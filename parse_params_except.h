//
// Created by Cesar Erebus on 4/26/21.
//

#ifndef PARSE_PARAMS_EXCEPT_H
# define PARSE_PARAMS_EXCEPT_H
# include "exceptions.h"
# include "parser_utils.h"

void	throw_params_exception(char *msg, int *is_error);

void	throw_params_except(t_parse_flags pFlags, t_data *m_struct, int is_err);

void	throw_empty_file(t_data *m_struct);

void	was_params(t_parse_flags parseFlags, t_data *m_struct);

#endif
