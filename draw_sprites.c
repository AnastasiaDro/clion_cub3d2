//
// Created by  Anastasia on 23.04.2021.
//
#include "draw_sprites.h"
#include "draw_utils.h"

void set_sprite_data(t_data *m_struct)
{
	t_sprite *sprite_lst;

	sprite_lst = *(m_struct->sprite_info->sprite_list);
	while (sprite_lst != NULL)
	{
		sprite_lst->distance = ((m_struct->map_player_x - sprite_lst->x) * (m_struct->map_player_x - sprite_lst->x) + (m_struct->map_player_y
		        - sprite_lst->y) * (m_struct->map_player_y - sprite_lst->y));
		sprite_lst = sprite_lst->next;
	}
	sprite_lst = *(m_struct->sprite_info->sprite_list);
	sortSprites(&sprite_lst); //сортировка спрайтов
}

//translate sprite position to relative to camera


void set_sprite_pos(t_spr_draw *sprDraw, t_sprite *sprite_lst, t_data *m_struct)
{
    double invDet;

    sprDraw->spriteX = sprite_lst->x - m_struct->map_player_x;
    sprDraw->spriteY = sprite_lst->y - m_struct->map_player_y;
    invDet = 1.0 / (m_struct->planeX * m_struct->dirY - m_struct->dirX * m_struct->planeY);
    sprDraw->transformX = invDet * (m_struct->dirY * sprDraw->spriteX - m_struct->dirX * sprDraw->spriteY);
    sprDraw->transformY = invDet * (-m_struct->planeY * sprDraw->spriteX + m_struct->planeX * sprDraw->spriteY); //this is actually the depth inside the screen, that what Z is in 3D
    sprDraw->spriteScreenX = (int)((m_struct->params->screen_width * 0.5) * (1 + sprDraw->transformX / sprDraw->transformY));
}

void set_sprite_draw_limits(t_spr_draw *sprDraw, t_data *m_struct, double coef)
{
    sprDraw->spriteHeight = fabs(m_struct->params->screen_higth / (sprDraw->transformY) * coef);
    //calculate lowest and highest pixel to fill in current stripe
    sprDraw->drawStartY = (int)round(-sprDraw->spriteHeight / 2 + (double)m_struct->params->screen_higth  / 2 );
    if(sprDraw->drawStartY < 0)
        sprDraw->drawStartY = 0;
    sprDraw->drawEndY = (int)round(sprDraw->spriteHeight / 2 + (double)m_struct->params->screen_higth  / 2);
    if(sprDraw->drawEndY >= m_struct->params->screen_higth )
        sprDraw->drawEndY = m_struct->params->screen_higth  - 1;
    //calculate width of the sprite
    sprDraw->spriteWidth = fabs((m_struct->params->screen_higth / (sprDraw->transformY) * coef));
    sprDraw->drawStartX = (int) round(-sprDraw->spriteWidth / 2 + sprDraw->spriteScreenX);
    if(sprDraw->drawStartX < 0)
        sprDraw->drawStartX = 0;
    sprDraw->drawEndX = (int) round(sprDraw->spriteWidth / 2 + sprDraw->spriteScreenX);
    if(sprDraw->drawEndX >= m_struct->params->screen_width)
        sprDraw->drawEndX = m_struct->params->screen_width - 1;
}

void draw_sprite_line(t_spr_draw *sprDraw, t_data *m_struct, int line_i, int texX)
{
    int y;
    int texY;
    int d;
    int color;

    y = sprDraw->drawStartY;
    while( y < sprDraw->drawEndY) //for every pixel of the current stripe
    {
        d = (y) * 256 - m_struct->params->screen_higth * 128 +
            sprDraw->spriteHeight * 128; //256 and 128 factors to avoid floats
        texY = ((d * m_struct->sprite_info->h) / sprDraw->spriteHeight) / 256;
        color = sprite_mlx_pixel_get(m_struct->sprite_info, texX, texY);
        if ((color & 0x00FFFFFF) != 0)
        {
            cerebus_mlx_pixel_put(m_struct, m_struct->params->screen_width - line_i, y, color);
        }
        y++;
    }
}


void draw_sprite(t_spr_draw *sprDraw, t_data *m_struct, double const *z_buffer)
{
    int line_i;

    line_i = sprDraw->drawStartX;
    while(line_i < sprDraw->drawEndX)
    {
        int texX = (int) (256 * (line_i - (-sprDraw->spriteWidth / 2 + sprDraw->spriteScreenX)) * m_struct->sprite_info->w /
                       sprDraw->spriteWidth) / 256;
        if (sprDraw->transformY > 0 && (sprDraw->drawEndX - line_i) > 0 &&
            (sprDraw->drawEndX - line_i) < m_struct->params->screen_width && sprDraw->transformY < z_buffer[line_i])
                draw_sprite_line(sprDraw, m_struct, line_i, texX);
        line_i++;
    }
}