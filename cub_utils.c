
#include "cub_utils.h"
#include "unistd.h"
#include "minilibx_opengl_20191021/mlx.h"
#include <stdio.h>
#include <math.h>
#include <libc.h>


void     cerebus_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;
    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}



int draw_voxel1(t_data *m_struct, int voxel_size, int color)
{
    int x = m_struct->voxel_x;
    int y = m_struct->voxel_y;

    int x_end = m_struct->voxel_x + voxel_size;
    int y_end = m_struct->voxel_y +voxel_size;
    //пока х меньше старт + voxel_size
    while (y< y_end)
    {
        x = m_struct->voxel_x;
        while (x<x_end)
        {
            cerebus_mlx_pixel_put(m_struct, x, y, color);
            x++;
        }
        y++;
    }
    return 1;
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



int draw_lines(t_data *m_struct)
{
		float x;
		float y;
		//float c = 1; //расстояние до игрока
		int ray_color = 0x990099;
		x = m_struct->player_x;
		y = m_struct->player_y;
		float angle;

		int i = 0;
		int t = 0;
		while (i < m_struct->screen_width) //рисуем видимость
		{
			x = m_struct->player_x;
			y = m_struct->player_y;
			angle = m_struct->player_a - m_struct->fov / 2 + m_struct->fov * i / (float) (m_struct->screen_width);
			//while (m_struct->map[(int)(y/ m_struct->voxel_size)][(int)(x / m_struct->voxel_size)] != '1')
			while (m_struct->map[(int)((y-1)/ m_struct->voxel_size)][(int)((x-1)/ m_struct->voxel_size)] != '1')
			{
				x += cos(angle);

				y += sin(angle);
				//ПАЧИМУ НЕ РАБОТАИТ?!?!?!?!?!
				//cerebus_mlx_pixel_put(m_struct->mlx, (int)x-1, (int)y-1, 0x990099);
				mlx_pixel_put(m_struct->mlx, m_struct->mlx_win, x, y, ray_color);
			}
			i++;
		}

		return 1;
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

int set_color(float angle, float r_x, float r_y, t_data *m_struct)
{
	int color = 0x990099;
	if (fabsf(r_x - m_struct->player_x) < fabsf(r_y - m_struct->player_y))
		color = sinf(angle) <= 0 ? EAST_COLOR : WEST_COLOR;
	else
		color = cosf(angle)<= 0 ? NORTH_COLOR : SOUTH_COLOR;

	//if (cosf(angle) > -0.95241298041 && cosf(angle) < 0.81418097052)  //45 и 135
	//	color = 0xFFFFFF;
	return color;
}

int draw_colored_column(t_data *m_struct, float x, float y_start, float higth, float angle, float r_x, float r_y)
{
	int color = set_color(angle, r_x, r_y, m_struct);
	while (y_start < higth)
	{
		cerebus_mlx_pixel_put(m_struct, (int)x, (int)y_start, color);
		y_start++;
	}
	return 1;
}


int draw_texture(t_data *m_struct, float x, float y_start, float higth, char *texture_path)
{
	m_struct->img = mlx_xpm_file_to_image(m_struct->mlx, texture_path, m_struct->screen_width, m_struct->screen_width);
	mlx_put_image_to_window(m_struct->mlx, m_struct->mlx_win, m_struct->img, 0, 0);
}

int draw_lab_dda(t_data *m_struct)
{
	double posX = m_struct->map_player_x; // не уверенаБ что так. Т.к. нужны координаты вектора игрока
	double posY = m_struct->map_player_y; // у Лодева оно по карте определяется

	//int w = 16; //в файле map.cub у нас по иксу 16 клеток
	//но хз, что это блять за w
	//int h = 16;
	int w = m_struct->screen_width;
	int h = m_struct->screen_higth;

	//нужен первоначальный вектор направления:
	double dirX = -1;
	double dirY = 0;

	double planeX = 0; //the 2d raycaster version of camera plane
	double planeY = 0.66; //the 2d raycaster version of camera plane

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
		int side; //was a NS or a EW wall hit?

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
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			if(m_struct->map[mapY][mapX] == '1')
				hit = 1;
		}
		//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		if(side == 0)
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


		int color = 0x990099;
		//give x and y sides different brightness
		if(side == 1) {color = color / 2;}
		//int draw_column(t_data *m_struct, float x, float y_start, float higth, int color)
		draw_column(m_struct, (float)x, (float)drawStart, (float)drawEnd, color);
		mlx_put_image_to_window(m_struct->mlx, m_struct->mlx_win, m_struct->img, 0, 0);
		x++;
	}

	return 1;
}


int draw_labyrinth(t_data *m_struct)
{
	float p_x;
	float p_y;
	//float c = 1; //расстояние до игрока
	int walls_color = 0x990099;
	p_x = m_struct->player_x;
	p_y = m_struct->player_y;
	float angle;
	float r_x = 0;
	float r_y = 0;
	int i = 0;
	int v = 0;

	//путь к текстуре


	int map_width = 16*m_struct->voxel_size;
	int map_higth = 16*m_struct->voxel_size;

	//размер текстуры:
	float texture_h = m_struct->voxel_size;
	float texture_w = m_struct->voxel_size;

	//высота столбцаб рисуемого нами
	float column_h = 0;
	float y_start = 0; //верхняя точка, откуда рисовать столбец

	//расстояние до projection plane
	//float half_plane = map_width/2;
	float half_plane = m_struct->screen_width/2;
	float p_space = half_plane/tan(m_struct->fov/2); //расстояние до projection_plane

	//длина луча
	float ray_length = 0;
	//while (i < m_struct->screen_width) //рисуем видимость
	//while (i < map_width) //рисуем видимость
	while (i < m_struct->screen_width)
	{
		//p_x = m_struct->player_x;
		p_y = m_struct->player_y;
		r_x = m_struct->player_x;
		r_y = m_struct->player_y;

		//старое
		//angle = m_struct->player_a - m_struct->fov / 2 + m_struct->fov * i / (float) (map_width);
		angle = m_struct->player_a - m_struct->fov / 2 + m_struct->fov * i / (float) (m_struct->screen_width);
		//angle = atanf((i - half_plane)/(p_space));

		//while (m_struct->map[(int)(y/ m_struct->voxel_size)][(int)(p_x / m_struct->voxel_size)] != '1')
		while (m_struct->map[(int)((r_y)/ m_struct->voxel_size)][(int)((r_x) / m_struct->voxel_size)] != '1')
		{
			r_x += cosf(angle);
			r_y += sinf(angle);
		}
		//длина луча - долго

		ray_length = abs((int)(((p_y - r_y)/sinf(angle)) * cosf(angle - m_struct->player_a)));
		//ray_length = abs((int)(((p_y - r_y)/sinf(angle))));
		//ray_length = abs((int)(((p_y - r_y)/sinf(angle))));
		column_h = texture_h/ ray_length*p_space;

		if (column_h > m_struct->screen_higth)
			column_h = m_struct->screen_higth;

		y_start = (float)(m_struct->screen_higth) / 2 - column_h / 2;
		//draw_column(m_struct, i, y_start, column_h + y_start, walls_color);
		draw_colored_column(m_struct, i, y_start, column_h + y_start, angle, r_x, r_y);
		mlx_put_image_to_window(m_struct->mlx, m_struct->mlx_win, m_struct->img, 0, 0);
		v++;
		i++;
		printf("сего лучей: %d\n", i);
	}
	printf("сего лучей: %d\n", i);
	return 1;
}



int draw_rect(t_data *m_struct, int x_start, int y_start, int higth, int width, int color)
{
int x_end = x_start + width;
int y_end = y_start +higth;
int x;

	while (y_start < y_end)
	{
		x = x_start;
		while (x < x_end)
		{
			cerebus_mlx_pixel_put(m_struct, x, y_start, color);
			x++;
		}
		y_start++;
	}
	return 1;
}


int draw_player(t_data *m_struct, int voxel_size, int color)
{
	int x = m_struct->map_player_x * m_struct->voxel_size;
	int y = m_struct->map_player_y * m_struct->voxel_size;

	int x_end = x + voxel_size;
	int y_end = y + voxel_size;
	//пока х меньше старт + voxel_size
	while (y< y_end)
	{
		x = m_struct->map_player_x * m_struct->voxel_size;
		while (x<x_end)
		{
			cerebus_mlx_pixel_put(m_struct, x, y, color);
			x++;
		}
		y++;
	}
	return 1;
}
