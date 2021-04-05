/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <cerebus@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 15:12:41 by cerebus           #+#    #+#             */
/*   Updated: 2020/11/22 15:40:41 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list *p;
	t_list *p_next;

	p = lst;
	if (!lst || !f)
		return ;
	while (p)
	{
		p_next = p->next;
		f(p->content);
		p = p_next;
	}
	return ;
}
