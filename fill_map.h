//
// Created by  Anastasia on 25.04.2021.
//

#ifndef FILL_MAP_H
# define FILL_MAP_H

int fill_map(t_list **last_elem, int elems_num, t_data *m_struct);

void find_player(int *elems_num, t_list **elem, t_data *m_struct, char **map);

void set_player_coords(t_data *m_struct, int is_player, int elems_num, char **map);

void check_was_player(int flag_player, t_data *m_struct);

#endif //CLION_CUB3D2_FILL_MAP_H
