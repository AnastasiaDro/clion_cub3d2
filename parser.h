#ifndef PARSER_H
# define PARSER_H
# include <string.h>
# include "cub_utils.h"
# include "parser_utils.h"
# define MAX_WIDTH_NUM_LENGTH 4
# define MAX_HEIGHT_NUM_LENGTH 4

void	parse_map(t_data *m_struct, char *map_path);

void	throw_map_except(t_data *m_struct);

int		is_map_start(char *line);

int		check_fe_line(char *s);

int		get_check_tex(char *s, t_data *m_struct, t_parse_flags *parse_f);

int		get_check_params(char *s, t_data *m_struct, t_parse_flags *parse_f);

int		go_th_params(int fd, t_data *m_s, t_list **last_elem, char **line);

void	check_file_end(char *line, t_data *m_struct);

int		cmp_space_str(char *line);

void	increase_lst(t_list **last_elem, int *elems_num, char *line);

void	throw_file_except(t_data *m_struct);

#endif
