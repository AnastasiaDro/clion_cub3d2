/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <cerebus@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 21:01:31 by cerebus           #+#    #+#             */
/*   Updated: 2021/04/21 21:01:51 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "params.h"
#include "unistd.h"

int	init_params(t_params *params)
{
	params->north_texture_path = NULL;
	params->south_texture_path = NULL;
	params->west_texture_path = NULL;
	params->east_texture_path = NULL;
	params->sprite_texture_path = NULL;
	return (1);
}
