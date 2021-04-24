/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_inits.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <cerebus@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 14:51:14 by cerebus           #+#    #+#             */
/*   Updated: 2021/04/22 14:53:15 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_inits.h"
#include "exceptions.h"

void	get_textures_paths(t_textu *textu, t_data *m_struct)
{
	textu[0].adress = m_struct->params->north_texture_path;
	textu[1].adress = m_struct->params->south_texture_path;
	textu[2].adress = m_struct->params->west_texture_path;
	textu[3].adress = m_struct->params->east_texture_path;
}

void	init_t_data(t_data *m_struct)
{
	m_struct->img = NULL;
	m_struct->mlx_win = NULL;
	m_struct->map = NULL;

}

void	set_data(t_data *m_struct, t_params *params, \
				t_textu *textu, t_spr_info *spr_info)
{
	m_struct->params = params;
	m_struct->textu = textu;
	m_struct->sprite_info = spr_info;

}

int init_sprite_info(t_spr_info  *sprite_info)
{
    sprite_info->sprite_list = NULL;
    sprite_info->sprite_path = NULL;
    return (1);
}


void	init_all(t_data *m_struct)
{
	t_textu		*textu;
	t_spr_info	*sprite_info;
	t_params	*params;

	init_t_data(m_struct);
	textu = malloc(sizeof (t_textu) * 4);
	sprite_info = malloc(sizeof(t_spr_info));
	params = malloc(sizeof (t_params));
	if (!textu || !sprite_info || !params)
	{
		free(textu);
		free(sprite_info);
		free(params);
		throwException(MALLOC_ERROR);
		exit (0);
	}
    textu_start_init(textu);
	init_sprite_info(sprite_info);
	init_params(params);
	set_data(m_struct, params, textu, sprite_info);
}
