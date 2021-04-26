/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <cerebus@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 17:16:10 by cerebus           #+#    #+#             */
/*   Updated: 2021/04/27 02:10:23 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_struct;

	new_struct = malloc(sizeof(t_list));
	if (!new_struct)
		return (NULL);
	new_struct->content = content;
	new_struct->next = NULL;
	return (new_struct);
}
