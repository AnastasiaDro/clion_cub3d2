//
// Created by  Anastasia on 23.04.2021.
//

#ifndef DRAW_SPRITES_H
# define DRAW_SPRITES_H
# include "sprites_utils.h"
# include "new_cub_utils.h"

typedef struct s_spr_draw
{
	double spriteX;
	double spriteY;
	double invDet;
	double transformX;
	double transformY;
}				t_spr_draw;


void set_sprite_data(t_data *m_struct);

#endif //CLION_CUB3D2_DRAW_SPRITES_H
