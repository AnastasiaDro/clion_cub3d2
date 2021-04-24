//
// Created by  Anastasia on 23.03.2021.
//

#include "minilibx_opengl_20191021/mlx.h"
#include "cub_utils.h"




int main (void) {

	t_data m_struct;
	t_data tx_struct;

	char *relative_path = "/Users/anastasia/CLionProjects/clion_cub3d/textures/128caves_wall.xpm";



	m_struct.mlx = mlx_init();

	//tx_struct.mlx = mlx_init();

	m_struct.screen_width = 512;
	m_struct.screen_higth = 512;

	m_struct.mlx_win = mlx_new_window(m_struct.mlx, m_struct.screen_width, m_struct.screen_higth, "hello, world!");
	m_struct.img = mlx_new_image(m_struct.mlx, m_struct.screen_width, m_struct.screen_higth);
	m_struct.addr = mlx_get_data_addr(m_struct.img, &m_struct.bits_per_pixel, &m_struct.line_length,
									  &m_struct.endian);

	int size = 128;
	tx_struct.img = mlx_xpm_file_to_image(tx_struct.mlx, relative_path, &size, &size);
	tx_struct.addr = mlx_get_data_addr(tx_struct.img, &tx_struct.bits_per_pixel, &tx_struct.line_length, &tx_struct.endian);

	int color;

	int x = 0;
	int y = 0;
	while (y < 128)
	{
		x = 0;
		while (x<128)
		{
			color = cerebus_mlx_pixel_get(&tx_struct, x, y);
			cerebus_mlx_pixel_put(&m_struct, x , y, color);
			x++;
		}

		y++;
	}

	mlx_put_image_to_window(m_struct.mlx, m_struct.mlx_win, m_struct.img, 0, 0);
	//тут сегается
	//mlx_put_image_to_window(tx_struct.mlx, tx_struct.mlx_win, tx_struct.t_img, 0, 0);

	//render_next_frame2(&m_struct);
	mlx_loop(m_struct.mlx);





}