/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exceptions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <cerebus@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 20:54:21 by cerebus           #+#    #+#             */
/*   Updated: 2021/04/27 17:54:11 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "exceptions.h"

int	free_params(t_data *m_struct)
{
	free(m_struct->params->north_tex_path);
	free(m_struct->params->south_tex_path);
	free(m_struct->params->west_tex_path);
	free(m_struct->params->east_tex_path);
	free(m_struct->params);
	return (1);
}

int	free_sprite_info(t_data *m_struct)
{
	sprite_lstclear(m_struct->sprite_info->sprite_lst);
	free(m_struct->sprite_info->sprite_path);
	free(m_struct->sprite_info);
	return (1);
}

int	free_textu(t_data *m_struct)
{
	int	i;

	i = 0;
	while (i < 4 && m_struct->textu[i].img != NULL)
	{
		mlx_destroy_image(m_struct->textu[i].mlx, m_struct->textu[i].img);
		i++;
	}
	free(m_struct->textu);
	return (1);
}

int	free_all(t_data *m_struct)
{
	char	**ptr;

	ptr = m_struct->map;
	if (ptr == NULL)
		return (1);
	while (*ptr != NULL)
	{
		free((*ptr));
		ptr++;
	}
	free(m_struct->map);
	m_struct->map = NULL;
	free_params(m_struct);
	free_textu(m_struct);
	free_sprite_info(m_struct);
	free(m_struct->z_buffer);
	if (m_struct->img)
	{
		mlx_destroy_window(m_struct->mlx, m_struct->mlx_win);
		mlx_destroy_image(m_struct->mlx, m_struct->img);
	}
	free(m_struct->press_flgs);
	exit(0);
}

void	throw_exception(char *msg)
{
	printf("Error\n%s\n", msg);
}
