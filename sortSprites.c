//
// Created by Cesar Erebus on 4/27/21.
//


#include "cub_utils.h"
#include "sortSprites.h"

parse_t2_smaller(t_sprite **t1, t_sprite **t2, t_sort_spr *t_sort)
{
    t_sort->sec_distance = (*t2)->dist;

    t_sort->sec_x = (*t1)->x;
    t_sort-> = (*t1)->y;
    (*t2)->dist = (*t1)->dist;
    t_sort->sec_x = (*t2)->x;
    (*t2)->x = (*t1)->x;
    t_sort->sec_y = (*t2)->y;
    (*t2)->y = (*t1)->y;
    t_sort->found = 1;
    (*t2) = (*t2)->next;
}

int parse_t2_biger(t_sprite **t1, t_sprite **t2, t_sort_spr *t_sort)
{
    t_sort->tmp_distance = t_sort->sec_distance;
    t_sort->sec_distance = (*t2)->dist;
    (*t2)->dist = t_sort->tmp_distance;
    t_sort->tmp_x = t_sort->sec_x;
    t_sort->sec_x = (*t2)->x;
    (*t2)->x = t_sort->tmp_x;
    t_sort->tmp_y = t_sort->sec_y;
    t_sort->sec_y = (*t2)->y;
    (*t2)->y = t_sort->tmp_y;
}


void	sortSprites(t_sprite **head)
{
    t_sprite	*t1;
    t_sprite	*t2;
    t_sort_spr t_sort;


    t1 = (*head)->next;
    while (t1 !=NULL)
    {
        t_sort.sec_distance = t1->dist;
        t_sort.sec_x = t1->x;
        t_sort.sec_y = t1->y;

        t_sort.found = 0;
        t2 = *head;
        while (t2 != t1)
        {
            if (t2->dist < t1->dist && t_sort.found == 0)
            {

                parse_t2_smaller(&t1, &t2, &t_sort);
            }   else {
                if (t_sort.found == 1)
                {
                    parse_t2_biger(&t1, &t2, &t_sort);
//                    tmp_distance = sec_distance;
//                    sec_distance = t2->dist;
//                    t2->dist = tmp_distance;
//                    tmp_x = sec_x;
//                    sec_x = t2->x;
//                    t2->x = tmp_x;
//                    tmp_y = sec_y;
//                    sec_y = t2->y;
//                    t2->y = tmp_y;
                }
                t2 = t2->next;
            }
        }
        t2->dist = t_sort.sec_distance;
        t2->x = t_sort.sec_x;
        t2->y = t_sort.sec_y;
        t1 = t1->next;
    }
}