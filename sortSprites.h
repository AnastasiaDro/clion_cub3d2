//
// Created by Cesar Erebus on 4/27/21.
//

#ifndef SORTSPRITES_H
# define SORTSPRITES_H

typedef struct s_sort_spr {
        int found;
        double sec_distance;
        double tmp_distance;
        double sec_x;
        double sec_y;
        double tmp_x;
        double tmp_y;
}              t_sort_spr;

void		sortSprites(t_sprite **sprite_list);

#endif
