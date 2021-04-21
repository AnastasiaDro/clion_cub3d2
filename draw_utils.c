#include "new_cub_utils.h"

int draw_background(int y, int limit, int screen_width, int color, t_data *m_struct)
{
	int x;

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
	return (y);
}

int draw_floor_ceil(t_data *m_struct, int screen_higth, int screen_width)
{
   int half;
   int y;
   int floor_color;
   int ceiling_color;

   half = screen_higth/2;
   y = 0;
   floor_color = m_struct->params->floor_color;
   ceiling_color = m_struct->params->ceil_color;
   y = draw_background(y, half, screen_width, ceiling_color, m_struct);
   draw_background(y, screen_higth, screen_width, floor_color, m_struct);
   return (0);
}
