//
// Created by  Anastasia on 23.04.2021.
//
#include "draw_sprites.h"

void set_sprite_data(t_data *m_struct)
{
	t_sprite *sprite_lst;
	sprite_lst = *(m_struct->sprite_info->sprite_list);
	while (sprite_lst != NULL)
	{
		//spriteOrder[i] = i;
		sprite_lst->distance = ((m_struct->map_player_x - sprite_lst->x) * (m_struct->map_player_x - sprite_lst->x) + (m_struct->map_player_y
																													   - sprite_lst->y) * (m_struct->map_player_y - sprite_lst->y));
		sprite_lst = sprite_lst->next;
	}
	sprite_lst = *(m_struct->sprite_info->sprite_list);
	sortSprites(&sprite_lst); //сортировка спрайтов
}

