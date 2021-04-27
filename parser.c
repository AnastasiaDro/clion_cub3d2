#include "libft/libft.h"
#include "fcntl.h"
#include "get_next_line/get_next_line.h"
#include "cub_utils.h"
#include "parser_utils.h"
#include "exceptions.h"
#include "map_checker.h"
#include "constants.h"
#include "parser.h"
#include "fill_map.h"

int	check_fe_line(char *s)
{
	int	i;

	i = 0;
	while (s[i] == ' ')
		i++;
	while (s[i])
	{
		if (s[i] != '1' && s[i] != ' ')
			return (MAP_ERROR);
		i++;
	}
	return (1);
}

void	throw_map_except(t_data *m_struct)
{
	throw_exception(INVALID_MAP);
	free_all(m_struct);
	exit(0);
}

void	check_last_line(t_data *m_struct, \
			t_list **last_elem, int elems_num, int fd)
{
	if (check_fe_line(m_struct->map[elems_num - 1]) == MAP_ERROR)
	{
		close(fd);
		throw_map_except(m_struct);
	}
}

void    check_file_end(char *line, t_data *m_struct)
{
	if (!cmp_space_str(line))
	{
		free(line);
		throw_map_except(m_struct);
		exit(0);
	}
}

// int cmp_space_str(char *line)
// {
//     int slen;
//     char *cmp_str;
//     int res;

//     if (*line == '\0')
//         return (0);
//     slen = (int)ft_strlen(line);
//     cmp_str = malloc((slen + 1) * sizeof(char));
//     while(slen >= 0)
//     {
//         cmp_str[slen-1] = ' ';
//         slen--;
//     }
//     res = ft_strncmp(line, cmp_str, slen);
//     free(cmp_str);
//     return (res);
// }

// void check_file_end(char *line, t_data *m_struct)
// {
//     if (!cmp_space_str(line))
//     {
//         free(line);
//         throw_map_except(m_struct);
//         exit(0);
//     }
// }

void	parse_map(t_data *m_struct, char *map_path)
{
	int		fd;
	char	*line;
	t_list	*last_elem;
	int		elems_num;

	fd = open(map_path, O_RDONLY);
	last_elem = NULL;
	elems_num = go_th_params(fd, m_struct, &last_elem, &line);
	while (get_next_line(fd, &line))
	{
		ft_lstadd_front(&last_elem, ft_lstnew(line));
		elems_num++;
	}
    check_file_end(line, m_struct);
	ft_lstadd_front(&last_elem, ft_lstnew(line));
	elems_num++;
	m_struct->lst = last_elem;
	line = NULL;
	m_struct->sprite_info->sprite_lst = malloc(1 * sizeof (t_sprite *));
	*(m_struct->sprite_info->sprite_lst) = NULL;
	elems_num = fill_map(&last_elem, elems_num, m_struct);
	check_last_line(m_struct, &last_elem, elems_num, fd);
	ft_lstclear(&last_elem, free);
	close (fd);
	if (check_map(m_struct->map, elems_num) == MAP_ERROR)
		throw_map_except(m_struct);
}
