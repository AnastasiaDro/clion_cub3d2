//
// Created by  Anastasia on 23.04.2021.
//

#include "dda_utils.h"
#include "wall_utils.h"
#include "texture_parse.h"
#include "draw_sprites.h"

void go_to_the_wall(t_ray *ray, t_data *m_struct)
{
	while (ray->hit == 0)
	{
		//jump to next map square, OR in x-direction, OR in y-direction
		if (ray->sideDistX <= ray->sideDistY)
		{
			ray->sideDistX += ray->deltaDistX;
			ray->mapX += ray->stepX;
			m_struct->side = 0;
		} else {
			ray->sideDistY += ray->deltaDistY;

			ray->mapY += ray->stepY;
			m_struct->side = 1;
		}
		//Check if ray has hit a wall
		if (m_struct->map[ray->mapY][ray->mapX] == '1')
			ray->hit = 1;
	}
}

void calc_camera_dist(t_ray *ray, t_data *m_struct)
{
	if (m_struct->side == 0)
		ray->perpWallDist = (ray->mapX - m_struct->map_player_x + (1 - (double) ray->stepX) / 2) / ray->DirX;
	else
	{
		double firstPart = (double) (ray->mapY - m_struct->map_player_y + (1 - (double) ray->stepY) / 2);
		ray->perpWallDist = firstPart / ray->DirY;
	}
}

//x coordinate on the texture
void calc_x_textu_coord(t_data *m_struct, t_ray *ray, t_wall *wall, t_txdraw *txdraw)
{
	txdraw->texX = (int) (wall->wallX * (double) (txdraw->textu->width));
	if (m_struct->side == 0 && ray->DirX > 0)
		txdraw->texX = txdraw->textu->height - txdraw->texX - 1;
	if (m_struct->side == 1 && ray->DirY < 0)
		txdraw->texX = txdraw->textu->width - txdraw->texX - 1;
}

void cast_walls(t_data *m_struct, t_ray *ray, t_wall *wall, double *z_buffer)
{
    int x;
    int gg;
    t_textu tx_struct;
    t_txdraw txdraw;

    x = 0;
    gg =  m_struct->params->screen_width;
    while (x < m_struct->params->screen_width)
    {
        set_ray_params(ray, m_struct, x);
        //perform DDA
        go_to_the_wall(ray, m_struct); //Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
        calc_camera_dist(ray, m_struct);
        calc_line_height(wall, ray, m_struct); //Calculate height of line to draw on screen
        calc_sart_pixels(wall, m_struct); //calculate lowest and highest pixel to fill in current stripe
        calc_wall_x(wall, ray, m_struct); //новые вычисления для текстуры
        tx_struct = set_texture(m_struct, ray->DirX, ray->DirY); //получим текстуру
        txdraw.textu = &tx_struct;
        calc_x_textu_coord(m_struct, ray, wall, &txdraw);
        draw_wall_line(wall, m_struct, &txdraw, gg);
        x++;
        gg--;
        z_buffer[x-1] = ray->perpWallDist; //perpendicular distance is used         //SET THE ZBUFFER FOR THE SPRITE CASTING
    }
}

void cast_sprites(t_data *m_struct, double const *z_buffer)
{
    double h;
    double w;
    double coef;
    t_sprite *sprite_lst;

    h = m_struct->params->screen_higth;
    w = m_struct->params->screen_width;
    coef = w / h * 0.77;
    set_sprite_data(m_struct);
    sprite_lst = *(m_struct->sprite_info->sprite_list);
    t_spr_draw sprDraw;
    while (sprite_lst != NULL)
    {
        set_sprite_pos(&sprDraw, sprite_lst, m_struct);
        set_sprite_draw_limits(&sprDraw, m_struct, coef);
        draw_sprite(&sprDraw, m_struct, z_buffer);
        sprite_lst = sprite_lst->next;
    }
}