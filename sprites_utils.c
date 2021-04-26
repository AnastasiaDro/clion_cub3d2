/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <cerebus@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 22:32:03 by cerebus           #+#    #+#             */
/*   Updated: 2021/04/26 22:32:25 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <expat.h>
#include "sprites_utils.h"
#include "exceptions.h"

int	set_sprite_info(t_spr_info *spr_info, \
			int sprite_h, int sprite_w, char *path)
{
	spr_info->sprite_path = path;
	spr_info->num_sprites = 0;
	(*spr_info).mlx = mlx_init();
	(*spr_info).img = mlx_xpm_file_to_image((*spr_info).mlx, \
				(*spr_info).sprite_path, &sprite_w, &sprite_h);
	if (!((*spr_info).img))
	{
		throw_exception(SPRITE_PATH_ERROR);
		return (-1);
	}
	(*spr_info).addr = mlx_get_data_addr((*spr_info).img, &(spr_info->bits_per_pixel), \
				&(spr_info->line_length), &(spr_info->endian));
	spr_info->h = sprite_h;
	spr_info->w = sprite_w;
	return (1);
}

t_sprite	*sprite_lstnew(double x, double y)
{
	t_sprite	*new_sprite;

	new_sprite = malloc(sizeof(t_sprite));
	if (!new_sprite)
		return (NULL);
	new_sprite->x = x;
	new_sprite->y = y;
	new_sprite->next = NULL;
	return (new_sprite);
}

void	sprite_lstadd_front(t_sprite **lst, t_sprite *new)
{
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	if (new)
	{
		new->next = *lst;
		*lst = new;
		return ;
	}
}

void	sprite_lstclear(t_sprite **lst)
{
	t_sprite	*p;
	t_sprite	*p_next;

	if (!lst)
		return ;
	if (!*lst)
		return ;
	p = *lst;
	*lst = NULL;
	while (p)
	{
		p_next = p->next;
		free(p);
		p = p_next;
	}
}
