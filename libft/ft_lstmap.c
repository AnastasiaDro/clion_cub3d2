/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <cerebus@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 15:41:13 by cerebus           #+#    #+#             */
/*   Updated: 2020/11/22 16:17:28 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *p;
	t_list *new_lst;
	t_list *new_next;

	p = lst;
	if (!lst || !f)
		return (NULL);
	if (!(new_lst = ft_lstnew(f(p->content))))
	{
		ft_lstclear(&lst, del);
		return (NULL);
	}
	new_next = new_lst;
	p = p->next;
	while (p)
	{
		if (!(new_next->next = ft_lstnew(f(p->content))))
		{
			ft_lstclear(&new_lst, del);
			break ;
		}
		new_next = new_next->next;
		p = p->next;
	}
	return (new_lst);
}
