//
// Created by  Anastasia on 25.03.2021.
//
#include <printf.h>
#include "new_cub_utils.h"
#include "minilibx_opengl_20191021/mlx.h"
#include "texture_parse.h"


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



int set_color(t_data *m_struct, double rayDirX, double rayDirY)
{
	if (m_struct->side == 1)
	{
		if (rayDirY > 0)
			return SOUTH_COLOR;
		else
			return NORTH_COLOR;
	}
	if (m_struct->side == 0)
	{
		if (rayDirX > 0)
			return WEST_COLOR;
		else
			return EAST_COLOR;
	}
	return 0;
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

//повернуть игрока
int rotate(t_data *m_struct, double rotSpeed)
{
	double oldDirX = m_struct->dirX;
	m_struct->dirX= m_struct->dirX * cos(rotSpeed) - m_struct->dirY * sin(rotSpeed);
	m_struct->dirY = oldDirX * sin(rotSpeed) + m_struct->dirY * cos(rotSpeed);
	double oldPlaneX = m_struct->planeX;
	m_struct->planeX= m_struct->planeX * cos(rotSpeed) - m_struct->planeY * sin(rotSpeed);
	m_struct->planeY = oldPlaneX * sin(rotSpeed) + m_struct->planeY * cos(rotSpeed);
	return 1;
}



//пойти вперед или назад
int do_step(t_data *m_struct, double moveSpeed, double coef)
{
    char **map = m_struct->map;
//    if(map[int(posX + dirX * moveSpeed)][int(posY)] == '0') posX += dirX * moveSpeed;
//    if(map[int(posX)][int(posY + dirY * moveSpeed)] == '0') posY += dirY * moveSpeed;
    if(map[(int)m_struct->map_player_y][(int)(m_struct->map_player_x + coef*m_struct->dirX * moveSpeed)] == '0')
        m_struct->map_player_x += coef*m_struct->dirX * moveSpeed;
    if(map[(int)(m_struct->map_player_y + coef*m_struct->dirY * moveSpeed)][(int)m_struct->map_player_x] == '0')
        m_struct->map_player_y += coef*m_struct->dirY * moveSpeed;
    return 1;
}




int step_left_rigth(t_data *m_struct, double moveSpeed, int coef)
{
    char **map = m_struct->map;
    if(map[(int)m_struct->map_player_y][(int)(m_struct->map_player_x + coef*m_struct->planeX * moveSpeed)] == '0')
        m_struct->map_player_x += coef*m_struct->planeX * moveSpeed;
    if(map[(int)(m_struct->map_player_y + coef*m_struct->planeY * moveSpeed)][(int)m_struct->map_player_x] == '0')
        m_struct->map_player_y += coef*m_struct->planeY * moveSpeed;
    return 1;
}

int step_forward(t_data *m_struct, double moveSpeed)
{
    do_step(m_struct, moveSpeed, 1);
    return 1;
}

int step_backward(t_data *m_struct, double moveSpeed)
{
    do_step(m_struct, moveSpeed, -1);
    return 1;
}

int step_rigth(t_data *m_struct, double moveSpeed)
{
    step_left_rigth(m_struct, moveSpeed, 1);
    return 1;
}

int step_left(t_data *m_struct, double moveSpeed)
{
    step_left_rigth(m_struct, moveSpeed, -1);
    return 1;
}




int draw_lab_dda(t_data *m_struct)
{
	//зададим текстуры



	double posX = m_struct->map_player_x; // не уверенаБ что так. Т.к. нужны координаты вектора игрока
	double posY = m_struct->map_player_y; // у Лодева оно по карте определяется

	//int w = 16; //в файле map.cub у нас по иксу 16 клеток
	//но хз, что это блять за w
	//int h = 16;
	int w = m_struct->screen_width;
	int h = m_struct->screen_higth;

	//нужен первоначальный вектор направления:
//	double dirX = -1;
//	double dirY = 0;
	double dirX = m_struct->dirX;
	double dirY = m_struct->dirY;

//	double planeX = 0; //the 2d raycaster version of camera plane
//	double planeY = 0.66; //the 2d raycaster version of camera plane

	double planeX = m_struct->planeX;
	double planeY = m_struct->planeY;
	//цикл для иксов
	int x = 0;
	while (x < w)
	{
		//calculate ray position and direction
		//точка на векторе камеры, счиается за 100% ширина экрана
		double cameraX = 2 * x / (double)w - 1; //x-coordinate in camera space cameraX
		// is the x-coordinate on the camera plane that the current x-coordinate of the screen represents

		//вектор направления луча
		double rayDirX = dirX + planeX * cameraX; //
		double rayDirY = dirY + planeY * cameraX;

//		mapX and mapY represent the current square of the map the ray is in.
//		The ray position itself is a floating point number
//		and contains both info about in which square of the map we are,
//		and where in that square we are, but mapX and mapY are only the coordinates of that square.
		//which box of the map we're in
		int mapX = (int)posX;
		int mapY = (int)posY;
		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;


		//length of ray from one x or y-side to next x or y-side
		// Alternative code for deltaDist in case division through zero is not supported
		double deltaDistX = (rayDirY == 0) ? 0 : ((rayDirX == 0) ? 1 : fabs(1 / rayDirX));
		double deltaDistY = (rayDirX == 0) ? 0 : ((rayDirY == 0) ? 1 : fabs(1 / rayDirY));
//		double deltaDistX = fabs(1 / rayDirX);
//		double deltaDistY = fabs(1 / rayDirY);
		double perpWallDist;
		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
	//	int side; //was a NS or a EW wall hit?

		//calculate step and initial sideDist
		if(rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
		}
		if(rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
		}

		//perform DDA
		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if(sideDistX <= sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				m_struct->side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				m_struct->side = 1;
			}
			//Check if ray has hit a wall
			if(m_struct->map[mapY][mapX] == '1')
				hit = 1;
		}
		//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		if(m_struct->side == 0)
			//	perpWallDist = (mapX - posX + (1 - (double)stepX) / 2) / rayDirX;
			perpWallDist = (mapX - posX + (1 - (double)stepX) / 2) / rayDirX;
		else
		{
			double firstPart  =  (double)(mapY - posY + (1 - (double)stepY) / 2);
			perpWallDist = firstPart / rayDirY;
			//perpWallDist = (double)(mapY - posY + (1 - (double)stepY) / 2) / rayDirY;
		}

		//Calculate height of line to draw on screen
		int lineHeight;
		if (perpWallDist != 0)
			lineHeight = (int)( h / perpWallDist);
		else
			lineHeight = h;

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + h / 2;
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + h / 2;
		if(drawEnd >= h)
			drawEnd = h - 1;


//		int color = 0x990099;
//		//give x and y sides different brightness
//		if(m_struct->side == 1) {color = color / 2;}

		//сюда set color
		int color = set_color(m_struct, rayDirX, rayDirY);

		//int draw_column(t_data *m_struct, float x, float y_start, float higth, int color)
		draw_column(m_struct, (float)x, (float)drawStart, (float)drawEnd, color);

		x++;
	}
//    printf("высота экрана %d\n", m_struct->screen_higth);
	return 1;
}