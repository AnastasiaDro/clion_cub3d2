//
// Created by  Anastasia on 29.03.2021.
//

#include "new_cub_utils.h"
#include "sprites_utils.h"
#include "minilibx_opengl_20191021/mlx.h"
#include <time.h>
#include <stdio.h>

int free_all(t_data *m_struct)
{
    return 0;
}

void throwException(char *msg, t_data *m_struct)
{
    printf("Error\n%s\n", msg);
    free_all(m_struct);
    exit(0);
}


void     cerebus_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char    *dst;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int change_x_p_coors(t_data *m_struct)
{
	m_struct->player_x = (float)m_struct->map_player_x * (float) m_struct->voxel_size;
	return 1;
}

int change_y_p_coords(t_data *m_struct)
{
	m_struct->player_y = (float)m_struct->map_player_y * (float) m_struct->voxel_size;
	return 1;
}


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
			return m_struct->textu[2];
		else
			return m_struct->textu[3];
	}
    return (m_struct->textu[0]); //просто дефолт
}


int draw_column(t_data *m_struct, float x, float y_start, float y_end, int color)
{
	while (y_start < y_end)
	{
		cerebus_mlx_pixel_put(m_struct, (int)x, (int)y_start, color);
		y_start++;
	}
	return 1;
}





//пойти вперед или назад

int draw_lab_dda(t_data *m_struct) {


    //1D Zbuffer
    double ZBuffer[m_struct->screen_width];

//arrays used to sort the sprites
    int spriteOrder[m_struct->screen_width];
    double spriteDistance[m_struct->screen_width];


  //  double posX = m_struct->map_player_x; // не уверенаБ что так. Т.к. нужны координаты вектора игрока
	//double posY = m_struct->map_player_y; // у Лодева оно по карте определяется

	//int w = m_struct->screen_width;
	//int h = m_struct->screen_higth;

	//нужен первоначальный вектор направления:
	//double dirX = m_struct->dirX;
	//double dirY = m_struct->dirY;

	//double planeX = m_struct->planeX;
	//double planeY = m_struct->planeY;
	//цикл для иксов
	int x = 0;
	while (x < m_struct->screen_width) {
		//calculate ray position and direction
		//точка на векторе камеры, счиается за 100% ширина экрана
		double cameraX = 2 * x / (double) m_struct->screen_width - 1; //x-coordinate in camera space cameraX
		// is the x-coordinate on the camera plane that the current x-coordinate of the screen represents

		//вектор направления луча
		double rayDirX = m_struct->dirX + m_struct->planeX * cameraX; //
		double rayDirY = m_struct->dirY + m_struct->planeY * cameraX;

//		mapX and mapY represent the current square of the map the ray is in.
//		The ray position itself is a floating point number
//		and contains both info about in which square of the map we are,
//		and where in that square we are, but mapX and mapY are only the coordinates of that square.
		//which box of the map we're in
		int mapX = (int) m_struct->map_player_x;
		int mapY = (int) m_struct->map_player_y;
		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		//length of ray from one x or y-side to next x or y-side
		// Alternative code for deltaDist in case division through zero is not supported
		double deltaDistX = (rayDirY == 0) ? 0 : ((rayDirX == 0) ? 1 : fabs(1 / rayDirX));
		double deltaDistY = (rayDirX == 0) ? 0 : ((rayDirY == 0) ? 1 : fabs(1 / rayDirY));

		double perpWallDist;
		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		//	int side; //was a NS or a EW wall hit?

		//calculate step and initial sideDist
		if (rayDirX < 0) {
			stepX = -1;
			sideDistX = (m_struct->map_player_x - mapX) * deltaDistX;
		} else {
			stepX = 1;
			sideDistX = (mapX + 1.0 - m_struct->map_player_x) * deltaDistX;
		}
		if (rayDirY < 0) {
			stepY = -1;
			sideDistY = (m_struct->map_player_y - mapY) * deltaDistY;
		} else {
			stepY = 1;
			sideDistY = (mapY + 1.0 - m_struct->map_player_y) * deltaDistY;
		}

		//perform DDA
		while (hit == 0) {
			//jump to next map square, OR in x-direction, OR in y-direction
			if (sideDistX <= sideDistY) {
				sideDistX += deltaDistX;
				mapX += stepX;
				m_struct->side = 0;
			} else {
				sideDistY += deltaDistY;

				mapY += stepY;
				m_struct->side = 1;
			}
			//Check if ray has hit a wall
			if (m_struct->map[mapY][mapX] == '1')
				hit = 1;
		}
		//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		if (m_struct->side == 0)
			perpWallDist = (mapX - m_struct->map_player_x + (1 - (double) stepX) / 2) / rayDirX;
		else {
			double firstPart = (double) (mapY - m_struct->map_player_y + (1 - (double) stepY) / 2);
			perpWallDist = firstPart / rayDirY;
			//perpWallDist = (double)(mapY - posY + (1 - (double)stepY) / 2) / rayDirY;
		}
		//Calculate height of line to draw on screen
		int lineHeight;
		if (perpWallDist != 0)
			lineHeight = (int) (m_struct->screen_higth / perpWallDist);
		else
			lineHeight = m_struct->screen_higth;;

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + m_struct->screen_higth / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + m_struct->screen_higth / 2;
		if (drawEnd >= m_struct->screen_higth)
			drawEnd = m_struct->screen_higth - 1;


//новые вычисления для текстуры
		double wallX; //where exactly the wall was hit
		if (m_struct->side == 0)
			wallX = m_struct->map_player_y + perpWallDist * rayDirY;
		else
			wallX = m_struct->map_player_x + perpWallDist * rayDirX;
		wallX -= floor((wallX));

        //получим текстуру
        t_textu tx_struct = set_texture(m_struct, rayDirX, rayDirY);

		//x coordinate on the texture
		int texX = (int) (wallX * (double) (tx_struct.width));
		if (m_struct->side == 0 && rayDirX > 0) texX = tx_struct.height - texX - 1;
		if (m_struct->side == 1 && rayDirY < 0) texX = tx_struct.width - texX - 1;

		//получим наш массив текстур


		double step = 1.0 * tx_struct.height / lineHeight;
		// Starting texture coordinate
		double texPos = (drawStart - m_struct->screen_higth / 2 + lineHeight / 2) * step;
		for (int y = drawStart; y < drawEnd; y++) {
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			int texY = (int) texPos;
			texPos += step;
            int color = textu_mlx_pixel_get(&tx_struct, texX, texY);
			cerebus_mlx_pixel_put(m_struct, x, y, color);
		}
        x++;
        //SET THE ZBUFFER FOR THE SPRITE CASTING
        ZBuffer[x-1] = perpWallDist; //perpendicular distance is used
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

        int spriteScreenX = (int)((m_struct->screen_width * 0.5) * (1 + transformX / transformY));
        //calculate height of the sprite on screen
        int spriteHeight = abs((int)(m_struct->screen_higth / (transformY))); //using 'transformY' instead of the real distance prevents fisheye
        //calculate lowest and highest pixel to fill in current stripe
        int drawStartY = -spriteHeight / 2 + m_struct->screen_higth  / 2;
        if(drawStartY < 0) drawStartY = 0;
        int drawEndY = spriteHeight / 2 + m_struct->screen_higth  / 2;
        if(drawEndY >= m_struct->screen_higth ) drawEndY = m_struct->screen_higth  - 1;
        //calculate width of the sprite
        int spriteWidth = abs( (int) (m_struct->screen_higth / (transformY)));
        int drawStartX = -spriteWidth / 2 + spriteScreenX;
        if(drawStartX < 0) drawStartX = 0;
        int drawEndX = spriteWidth / 2 + spriteScreenX;
        if(drawEndX >= m_struct->screen_width) drawEndX = m_struct->screen_width - 1;

        //loop through every vertical stripe of the sprite on screen
        for(int stripe = drawStartX; stripe < drawEndX; stripe++)
        {
           // int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * texWidth / spriteWidth) / 256;
            int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * m_struct->sprite_info->w / spriteWidth) / 256;
           //the conditions in the if are:
            //1) it's in front of camera plane so you don't see things behind you
            //2) it's on the screen (left)
            //3) it's on the screen (right)
            //4) ZBuffer, with perpendicular distance
            if(transformY > 0 && stripe > 0 && stripe < m_struct->screen_width && transformY < ZBuffer[stripe])
                for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
                {
                    int d = (y) * 256 - m_struct->screen_higth * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
                  //  int texY = ((d * texHeight) / spriteHeight) / 256;
                    int texY = ((d * m_struct->sprite_info->h) / spriteHeight) / 256;
                    int color = sprite_mlx_pixel_get(m_struct->sprite_info, texX, texY);
                  //  Uint32 color = texture[sprite[spriteOrder[i]].texture][texWidth * texY + texX]; //get current color from the texture
                   if((color & 0x00FFFFFF) != 0)
                   {
                       cerebus_mlx_pixel_put(m_struct, stripe, y, color);
                   }; //paint pixel if it isn't black, black is the invisible color

                }
        }

        sprite_lst = sprite_lst->next;
    }
    mlx_put_image_to_window(m_struct->mlx, m_struct->mlx_win, m_struct->img, 0, 0);
	return 1;
}