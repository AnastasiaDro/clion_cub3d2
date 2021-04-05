/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 17:16:10 by cerebus           #+#    #+#             */
/*   Updated: 2020/11/19 17:16:19 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list *new_struct;

	new_struct = malloc(sizeof(t_list));
	if (!new_struct)
		return (NULL);
	new_struct->content = content;
	new_struct->next = NULL;
	return (new_struct);
}
