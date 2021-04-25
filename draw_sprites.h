//
// Created by  Anastasia on 23.04.2021.
//

#ifndef DRAW_SPRITES_H
# define DRAW_SPRITES_H
# include "sprites_utils.h"
# include "cub_utils.h"

typedef struct s_spr_draw
{
	double sprite_x;
	double sprite_y;
	double transform_x;
	double transform_y;
    int screen_x;

    double h;
    double w;

    int draw_start_x;
    int draw_end_x;
    int draw_start_y;
    int draw_end_y;
}				t_spr_draw;


void set_sprite_data(t_data *m_struct);

void set_sprite_pos(t_spr_draw *spr_raw, t_sprite *sprite_lst, t_data *m_struct);

void draw_sprite_line(t_spr_draw *spr_draw, t_data *m_struct, int line_i, int texX);

void set_sprite_draw_limits(t_spr_draw *spr_draw, t_data *m_struct, double coef);

void draw_sprite(t_spr_draw *spr_draw, t_data *m_struct, double const *z_buffer);

#endif //CLION_CUB3D2_DRAW_SPRITES_H
