#include <printf.h>
#include <unistd.h>
#include "exceptions.h"


int free_arr(char **arr)
{
	char **ptr = arr;
	while (*ptr != NULL)
	{
		free((*ptr));
		ptr++;
	}
	free(arr);
	arr = NULL;
	return (1);
}

int free_params(t_data *m_struct)
{
	//очистить теустуру
	free(m_struct->params->north_texture_path);
	free(m_struct->params->south_texture_path);
	free(m_struct->params->west_texture_path);
	free(m_struct->params->east_texture_path);
	free(m_struct->params);
	return (1);
}

int free_sprite_info(t_data *m_struct)
{
	sprite_lstclear(m_struct->sprite_info->sprite_list);
	free(m_struct->sprite_info->sprite_path);
	free(m_struct->sprite_info);
	return (1);
}

int free_textu(t_data *m_struct)
{
	int i;

	i = 0;
	while (i < 4)
	{
		mlx_destroy_image(m_struct->textu[i].mlx, m_struct->textu[i].img);
		//free(m_struct->textu[i].adress);
		i++;
	}
	return (1);
}

int free_all(t_data *m_struct)
{
	free_arr(m_struct->map);
	write(1, "map\n", 4);
	//params
	free_params(m_struct);
	//textu
	free_textu(m_struct);
	//sprite info
	free_sprite_info(m_struct);
	mlx_destroy_window(m_struct->mlx, m_struct->mlx_win);
	mlx_destroy_image(m_struct->mlx, m_struct->img);
	exit(0);
}


void throwException(char *msg)
{
	printf("Error\n%s\n", msg);
}