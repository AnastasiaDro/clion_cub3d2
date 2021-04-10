//
// Created by Cesar Erebus on 3/31/21.
//

#ifndef SPRITES_UTILS_H
# define SPRITES_UTILS_H
# include "minilibx_opengl_20191021/mlx.h"
//дом
# define BARREL "/Users/anastasia/CLionProjects/clion_cub3d2/sprites/barrel.xpm"
//школа
//# define BARREL "/Users/cerebus/Documents/clion_cub3d/sprites/barrel.xpm"

typedef struct s_sprite
{
    double 	x;
    double 	y;
//    int 	code;
//    void 	*img;
    double distance;
 //   struct s_sprite *prev;
    struct s_sprite *next;
}              t_sprite;

typedef struct s_spr_info
{
	int 		num_sprites;
	t_sprite 	**sprite_list;
	int			h;
	int			w;
	int			code; //код, для идентификации, если будет неколько спрайтов
	//mlx
	void 		*mlx;
	char 		*sprite_path;
	void 		*img;
	char    	*addr;
	int         bits_per_pixel;
	int         line_length;
	int         endian;
}				t_spr_info;

int init_sprite_info(t_spr_info *spr_info, int sprite_h, int sprite_w, char *path);

t_sprite *sprite_lstnew(double x, double y);

void	sprite_lstadd_front(t_sprite **lst, t_sprite *new);

//void sortSprites(int* order, double* dist, int amount);

void sortSprites(t_sprite **sprite_list);

// получить пиксель из img спрайта
int sprite_mlx_pixel_get(t_spr_info *spr_info, int x, int y);

#endif //SPRITES_UTILS_H
