//
// Created by  Anastasia on 21.03.2021.
//

#include <stdio.h>
#include "new_cub_utils.h"

int draw_background1(int y, int limit, int screen_width, int color, t_data *m_struct)
{
	int x = 0;
	while (y < limit)
	{
		x = 0;
        while (x < screen_width)
		{
			cerebus_mlx_pixel_put(m_struct, x, y, color);
			x++;
		}
		y++;
	}
	return y;
}


int draw_floor_ceil1(t_data *m_struct, int screen_higth, int screen_width)
{
   // printf("высота экрана %d\n", m_struct->screen_higth);
   int half = screen_higth/2;
	//int half = (int)(m_struct->screen_higth/2);
   // int half = 512/2;
	int y = 0;
	int floor_color = m_struct->params->floor_color; 	//dark gray
	int ceiling_color = m_struct->params->ceil_color;	//light white gray
	y = draw_background1(y, half, screen_width, ceiling_color, m_struct); //рисуем потолок
   draw_background1(y, screen_higth, screen_width, floor_color, m_struct);
   return 0;
}
