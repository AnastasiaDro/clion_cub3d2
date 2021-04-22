//
// Created by  Anastasia on 29.03.2021.
//

#include "new_cub_utils.h"
#include "sprites_utils.h"
#include "minilibx_opengl_20191021/mlx.h"
#include <stdio.h>
#include "draw_utils.h"
#include "ray.h"

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

int draw_lab_dda(t_data *m_struct)
{
    t_ray ray;
    //1D Zbuffer
    double ZBuffer[m_struct->params->screen_width];
	//цикл для иксов
	int x = 0;
	int gg =  m_struct->params->screen_width;
	while (x < m_struct->params->screen_width)
	{
		//calculate ray position and direction
		//точка на векторе камеры, счиается за 100% ширина экрана
        calc_ray_dir(&ray, m_struct, x);

		//which box of the map we're in
		ray.mapX = (int) m_struct->map_player_x;
		ray.mapY = (int) m_struct->map_player_y;

        calc_ray_length(&ray);

		//what direction to step in x or y-direction (either +1 or -1)

		ray.hit = 0; //was there a wall hit?
		//	int side; //was a NS or a EW wall hit?

        //calculate step and initial sideDist
        calc_step_side_dist(&ray, m_struct);

		//perform DDA
		while (ray.hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (ray.sideDistX <= ray.sideDistY) {
				ray.sideDistX += ray.deltaDistX;
				ray.mapX += ray.stepX;
				m_struct->side = 0;
			} else {
				ray.sideDistY += ray.deltaDistY;

				ray.mapY += ray.stepY;
				m_struct->side = 1;
			}
			//Check if ray has hit a wall
			if (m_struct->map[ray.mapY][ray.mapX] == '1')
				ray.hit = 1;
		}
		//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		if (m_struct->side == 0)
			ray.perpWallDist = (ray.mapX - m_struct->map_player_x + (1 - (double) ray.stepX) / 2) / ray.DirX;
		else {
			double firstPart = (double) (ray.mapY - m_struct->map_player_y + (1 - (double) ray.stepY) / 2);
			ray.perpWallDist = firstPart / ray.DirY;
			//perpWallDist = (double)(mapY - posY + (1 - (double)stepY) / 2) / DirY;
		}
		//Calculate height of line to draw on screen
		int lineHeight;
		if (ray.perpWallDist != 0)
			lineHeight = (int) (m_struct->params->screen_higth / ray.perpWallDist);
		else
			lineHeight = m_struct->params->screen_higth;;

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + m_struct->params->screen_higth / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + m_struct->params->screen_higth / 2;
		if (drawEnd >= m_struct->params->screen_higth)
			drawEnd = m_struct->params->screen_higth - 1;


//новые вычисления для текстуры
		double wallX; //where exactly the wall was hit
		if (m_struct->side == 0)
			wallX = m_struct->map_player_y + ray.perpWallDist * ray.DirY;
		else
			wallX = m_struct->map_player_x + ray.perpWallDist * ray.DirX;
		wallX -= floor((wallX));

        //получим текстуру
        t_textu tx_struct = set_texture(m_struct, ray.DirX, ray.DirY);

		//x coordinate on the texture
		int texX = (int) (wallX * (double) (tx_struct.width));
		if (m_struct->side == 0 && ray.DirX > 0) texX = tx_struct.height - texX - 1;
		if (m_struct->side == 1 && ray.DirY < 0) texX = tx_struct.width - texX - 1;

		//получим наш массив текстур


		double step = 1.0 * tx_struct.height / lineHeight;
		// Starting texture coordinate
		double texPos = (drawStart - m_struct->params->screen_higth / 2 + lineHeight / 2) * step;
		for (int y = drawStart; y < drawEnd; y++) {
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			int texY = (int) texPos;
			texPos += step;
            int color = textu_mlx_pixel_get(&tx_struct, texX, texY);
			//cerebus_mlx_pixel_put(m_struct, x, y, color);
			cerebus_mlx_pixel_put(m_struct, gg, y, color);
		}
        x++;
		gg--;
        //SET THE ZBUFFER FOR THE SPRITE CASTING
        ZBuffer[x-1] = ray.perpWallDist; //perpendicular distance is used
	}
    //SPRITE CASTING
    //sort sprites from far to close
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
    //сортировка спрайтов
    sortSprites(&sprite_lst);
    //after sorting the sprites, do the projection and draw them
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
        int spriteHeight = abs((int)(m_struct->params->screen_higth / (transformY))); //using 'transformY' instead of the real distance prevents fisheye
        //calculate lowest and highest pixel to fill in current stripe
        int drawStartY = -spriteHeight / 2 + m_struct->params->screen_higth  / 2;
        if(drawStartY < 0) drawStartY = 0;
        int drawEndY = spriteHeight / 2 + m_struct->params->screen_higth  / 2;
        if(drawEndY >= m_struct->params->screen_higth ) drawEndY = m_struct->params->screen_higth  - 1;
        //calculate width of the sprite
        int spriteWidth = abs( (int) (m_struct->params->screen_higth / (transformY)));
        int drawStartX = -spriteWidth / 2 + spriteScreenX;
        if(drawStartX < 0) drawStartX = 0;
        int drawEndX = spriteWidth / 2 + spriteScreenX;
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