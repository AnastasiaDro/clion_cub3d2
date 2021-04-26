//
// Created by Cesar Erebus on 3/31/21.
//
#include <expat.h>
#include "sprites_utils.h"
#include "exceptions.h"


int set_sprite_info(t_spr_info *spr_info, int sprite_h, int sprite_w, char *path)
{
	spr_info->sprite_path = path;
	spr_info->num_sprites = 0;
	(*spr_info).mlx = mlx_init();
	if(!((*spr_info).img = mlx_xpm_file_to_image((*spr_info).mlx, (*spr_info).sprite_path, &sprite_w, &sprite_h)))
	{
		throw_exception(SPRITE_PATH_ERROR);
		return -1;
	}
	(*spr_info).addr = mlx_get_data_addr((*spr_info).img, &(spr_info->bits_per_pixel), &(spr_info->line_length),
										 &(spr_info->endian));
	spr_info->h = sprite_h;
	spr_info->w = sprite_w;
	return (1);
}



t_sprite *sprite_lstnew(double x, double y)
{
    t_sprite *new_sprite;

    new_sprite = malloc(sizeof(t_sprite));
    if (!new_sprite)
        return (NULL);
    new_sprite->x = x;
    new_sprite->y = y;
    new_sprite->next = NULL;
    return (new_sprite);
}

void	sprite_lstadd_front(t_sprite **lst, t_sprite *new)
{
    if (!*lst)
    {
        *lst = new;
        return ;
    }
    if (new)
    {
        new->next = *lst;
        *lst = new;
        return ;
    }
}


void sortSprites(t_sprite **head)
{
    t_sprite *t1 =  (*head)->next;
    while (t1 !=NULL)
    {
        double sec_distance = t1->dist;
        double sec_x = t1->x;
        double sec_y = t1->y;
        int found = 0;
        t_sprite *t2 = *head;
        while (t2 != t1)
        {
            if (t2->dist < t1->dist && found == 0)
            {
                sec_distance = t2->dist;
                t2->dist = t1->dist;
                sec_x = t2->x;
                t2->x = t1->x;
                sec_y = t2->y;
                t2->y = t1->y;
                found = 1;
                t2 = t2->next;
            }   else {
                if (found == 1) {
                    double tmp_distance = sec_distance;
                    sec_distance = t2->dist;
                    t2->dist = tmp_distance;
                    double tmp_x = sec_x;
                    sec_x = t2->x;
                    t2->x = tmp_x;
                    double tmp_y = sec_y;
                    sec_y = t2->y;
                    t2->y = tmp_y;
                }
                t2 = t2->next;
            }
        }
        t2->dist = sec_distance;
        t2->x = sec_x;
        t2->y = sec_y;
        t1 = t1->next;
    }
}

void	sprite_lstclear(t_sprite **lst)
{
    if (!lst)
        return ;
	t_sprite *p;
	t_sprite *p_next;


	if (!*lst)
		return ;
    p = *lst;
	*lst = NULL;
	while (p)
	{
		p_next = p->next;
		free(p);
		p = p_next;
	}
}


