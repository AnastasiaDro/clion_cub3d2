/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   increase_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <cerebus@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 04:36:37 by cerebus           #+#    #+#             */
/*   Updated: 2021/04/27 04:37:07 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

void	increase_lst(t_list **last_elem, int *elems_num, char *line)
{
	ft_lstadd_front(last_elem, ft_lstnew(line));
	(*elems_num)++;
}
