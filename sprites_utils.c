//
// Created by Cesar Erebus on 3/31/21.
//
#include <expat.h>
#include "sprites_utils.h"


void init_sprite_info(t_spr_info *spr_info, int sprite_h, int sprite_w, char *path)
{
	spr_info->sprite_path = path;
	spr_info->num_sprites = 0;
	(*spr_info).mlx = mlx_init();
	(*spr_info).img = mlx_xpm_file_to_image((*spr_info).mlx, (*spr_info).sprite_path, &sprite_w, &sprite_h);
	(*spr_info).addr = mlx_get_data_addr((*spr_info).img, &(spr_info->bits_per_pixel), &(spr_info->line_length),
										 &(spr_info->endian));
	spr_info->h = sprite_h;
	spr_info->w = sprite_w;
}

int sprite_mlx_pixel_get(t_spr_info *spr_info, int x, int y)
{
    int color;
    char *dst;
    dst = spr_info->addr + (y * spr_info->line_length + x * (spr_info->bits_per_pixel / 8));
    color = *(int*)dst;
    return color;
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
//    new_sprite->prev = NULL;
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
     //   new->prev = NULL;
        *lst = new;
        return ;
    }
}

t_sprite 	*ft_lstlast(t_sprite *lst)
{
    t_sprite *p;

    p = lst;
    while (p)
    {
        if (p->next == NULL)
            return (p);
        p = p->next;
    }
    return (NULL);
}

void	sprite_lstadd_back(t_sprite **lst, t_sprite *new)
{
    t_sprite *last;

    if (!*lst)
    {
        *lst = new;
        return ;
    }
    last = ft_lstlast(*(lst));
    last->next = new;
}


void sortSprites(t_sprite **head)
{
    t_sprite *t1 =  (*head)->next;
    while (t1 !=NULL)
    {
        double sec_distance = t1->distance;
        double sec_x = t1->x;
        double sec_y = t1->y;
        int found = 0;
        t_sprite *t2 = *head;
        while (t2 != t1)
        {
            if (t2->distance < t1->distance && found == 0)
            {
                sec_distance = t2->distance;
                t2->distance = t1->distance;
                sec_x = t2->x;
                t2->x = t1->x;
                sec_y = t2->y;
                t2->y = t1->y;
                found = 1;
                t2 = t2->next;
            }   else {
                if (found == 1) {
                    double tmp_distance = sec_distance;
                    sec_distance = t2->distance;
                    t2->distance = tmp_distance;
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
        t2->distance = sec_distance;
        t2->x = sec_x;
        t2->y = sec_y;
        t1 = t1->next;
    }
}

//void sortSprites(int* order, double* dist, int numSprites)
//{
//    int i = 0;
//    //сортировка вставками
//    //нужно пройтись по всему массиву
//    while (i < numSprites)
//    {
//        //есть расстояние
//
//
//        i++;
//    }

