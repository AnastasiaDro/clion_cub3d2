//
// Created by  Anastasia on 29.03.2021.
//

#include "new_cub_utils.h"
#include "sprites_utils.h"
#include "minilibx_opengl_20191021/mlx.h"
#include <stdio.h>
#include "draw_utils.h"
#include "ray.h"
#include "dda_utils.h"
#include "wall_utils.h"
#include "draw_sprites.h"

t_textu  set_texture(t_data *m_struct, double rayDirX, double rayDirY)
{
	if (m_struct->side == 1)
	{
		if (rayDirY > 0)
			return m_struct->textu[1];
		else
			return m_struct->textu[0];
	}
	if (m_struct->side == 0)
	{
		if (rayDirX > 0)
			return m_struct->textu[3];
		else
			return m_struct->textu[2];
	}
    return (m_struct->textu[0]); //просто дефолт
}

//пойти вперед или назад
//
int draw_lab_dda(t_data *m_struct)
{
    t_ray ray;
    t_wall wall;
	t_textu tx_struct;
	t_txdraw txdraw;
    //1D Zbuffer
    double ZBuffer[m_struct->params->screen_width];
	//цикл для иксов
	int x = 0;
	int gg =  m_struct->params->screen_width;
	while (x < m_struct->params->screen_width)
	{
        set_ray_params(&ray, m_struct, x);
		//perform DDA
		go_to_the_wall(&ray, m_struct); //Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		calc_camera_dist(&ray, m_struct);
		calc_line_height(&wall, &ray, m_struct); //Calculate height of line to draw on screen
		calc_sart_pixels(&wall, m_struct); //calculate lowest and highest pixel to fill in current stripe
		calc_wall_x(&wall, &ray, m_struct); //новые вычисления для текстуры

        //получим текстуру



        tx_struct = set_texture(m_struct, ray.DirX, ray.DirY);
		txdraw.textu = &tx_struct;

		//x coordinate on the texture
		calc_x_textu_coord(m_struct, &ray, &wall, &txdraw);
		//получим наш массив текстур


		draw_wall_line(&wall, m_struct, &txdraw, gg);
        x++;
		gg--;
        //SET THE ZBUFFER FOR THE SPRITE CASTING
        ZBuffer[x-1] = ray.perpWallDist; //perpendicular distance is used
	}
    //SPRITE CASTING
    set_sprite_data(m_struct);
    //after sorting the sprites, do the projection and draw them

	double h = m_struct->params->screen_higth;
	double w = m_struct->params->screen_width;
	double coef = w / h * 0.77;
	t_sprite *sprite_lst = *(m_struct->sprite_info->sprite_list);
    while (sprite_lst != NULL)
    {
        //translate sprite position to relative to camera
        double spriteX = sprite_lst->x - m_struct->map_player_x;
        double spriteY = sprite_lst->y - m_struct->map_player_y;
        //transform sprite with the inverse camera matrix
        // [ planeX   dirX ] -1                                       [ dirY      -dirX ]
        // [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
        // [ planeY   dirY ]                                          [ -planeY  planeX ]
        double invDet = 1.0 / (m_struct->planeX * m_struct->dirY - m_struct->dirX * m_struct->planeY); //required for correct matrix multiplication

        double transformX = invDet * (m_struct->dirY * spriteX - m_struct->dirX * spriteY);
        double transformY = invDet * (-m_struct->planeY * spriteX + m_struct->planeX * spriteY); //this is actually the depth inside the screen, that what Z is in 3D

        int spriteScreenX = (int)((m_struct->params->screen_width * 0.5) * (1 + transformX / transformY));
        //calculate height of the sprite on screen
        double tro = m_struct->params->screen_higth / (transformY) * coef;
        double spriteHeight = fabs(m_struct->params->screen_higth / (transformY) *coef); //using 'transformY' instead of the real distance prevents fisheye

        //calculate lowest and highest pixel to fill in current stripe
        int drawStartY = (int)round(-spriteHeight / 2 + (double)m_struct->params->screen_higth  / 2 );
        if(drawStartY < 0) drawStartY = 0;
        int drawEndY = (int)round(spriteHeight / 2 + (double)m_struct->params->screen_higth  / 2);
        if(drawEndY >= m_struct->params->screen_higth ) drawEndY = m_struct->params->screen_higth  - 1;
        //calculate width of the sprite
        double spriteWidth = fabs((m_struct->params->screen_higth / (transformY) * coef));
        int drawStartX = (int) round(-spriteWidth / 2 + spriteScreenX);
        if(drawStartX < 0) drawStartX = 0;
        int drawEndX = (int) round(spriteWidth / 2 + spriteScreenX);
        if(drawEndX >= m_struct->params->screen_width) drawEndX = m_struct->params->screen_width - 1;

        //loop through every vertical stripe of the sprite on screen
        for(int stripe = drawStartX; stripe < drawEndX; stripe++)
		////for(int stripe = drawEndX-1; stripe >= drawStartX; stripe--)
        {
           // int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * texWidth / spriteWidth) / 256;
            int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * m_struct->sprite_info->w / spriteWidth) / 256;
           //the conditions in the if are:
            //1) it's in front of camera plane so you don't see things behind you
            //2) it's on the screen (left)
            //3) it's on the screen (right)
            //4) ZBuffer, with perpendicular distance

            //if(transformY > 0 && stripe > 0 && stripe < m_struct->params->screen_width && transformY < ZBuffer[stripe])
			if(transformY > 0 && (drawEndX - stripe) > 0 && (drawEndX - stripe) < m_struct->params->screen_width && transformY < ZBuffer[stripe])

                for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
                {
                    int d = (y) * 256 - m_struct->params->screen_higth * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
                    int texY = ((d * m_struct->sprite_info->h) / spriteHeight) / 256;
                    int color = sprite_mlx_pixel_get(m_struct->sprite_info, texX, texY);
                   if((color & 0x00FFFFFF) != 0)
                   {
                       cerebus_mlx_pixel_put(m_struct, m_struct->params->screen_width-stripe, y, color);
                   }; //paint pixel if it isn't black, black is the invisible color

                }
        }
        sprite_lst = sprite_lst->next;
    }
    mlx_put_image_to_window(m_struct->mlx, m_struct->mlx_win, m_struct->img, 0, 0);
	return 1;
}

