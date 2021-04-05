/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <cerebus@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 14:18:12 by cerebus           #+#    #+#             */
/*   Updated: 2020/11/22 16:19:24 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list *p;
	t_list *p_next;

	p_next = (*lst)->next;
	p = *lst;
	if (!*lst)
		return ;
	*lst = NULL;
	while (p)
	{
		p_next = p->next;
		ft_lstdelone(p, del);
		p = p_next;
	}
	return ;
}
