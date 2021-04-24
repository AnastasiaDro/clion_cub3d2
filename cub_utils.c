//
// Created by  Anastasia on 29.03.2021.
//

#include "cub_utils.h"
#include "minilibx_opengl_20191021/mlx.h"
#include "ray.h"
#include "dda_utils.h"
#include "wall_utils.h"

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
    return (m_struct->textu[0]);
}

int draw_lab_dda(t_data *m_struct)
{
    t_ray ray;
    t_wall wall;
    double ZBuffer[m_struct->params->screen_width];

    cast_walls(m_struct, &ray, &wall, ZBuffer);
    cast_sprites(m_struct, ZBuffer);
    mlx_put_image_to_window(m_struct->mlx, m_struct->mlx_win, m_struct->img, 0, 0);
	return (1);
}
