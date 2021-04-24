//
// Created by  Anastasia on 23.04.2021.
//

#ifndef DRAW_SPRITES_H
# define DRAW_SPRITES_H
# include "sprites_utils.h"
# include "cub_utils.h"

typedef struct s_spr_draw
{
	double spriteX;
	double spriteY;
	double transformX;
	double transformY;
    int spriteScreenX;

    double spriteHeight;
    double spriteWidth;

    int drawStartX;
    int drawEndX;
    int drawStartY;
    int drawEndY;
}				t_spr_draw;


void set_sprite_data(t_data *m_struct);

void set_sprite_pos(t_spr_draw *sprDraw, t_sprite *sprite_lst, t_data *m_struct);

void draw_sprite_line(t_spr_draw *sprDraw, t_data *m_struct, int line_i, int texX);

void set_sprite_draw_limits(t_spr_draw *sprDraw, t_data *m_struct, double coef);

void draw_sprite(t_spr_draw *sprDraw, t_data *m_struct, double const *z_buffer);

#endif //CLION_CUB3D2_DRAW_SPRITES_H
