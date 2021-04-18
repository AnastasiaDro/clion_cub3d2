//
// Created by  Anastasia on 31.03.2021.
//

#ifndef KEY_HOOKING_H
#define KEY_HOOKING_H
#include "new_cub_utils.h"

//повернуть игрока
int rotate(t_data *m_struct, double rotSpeed);

int do_step(t_data *m_struct, double moveSpeed, double coef);

int step_forward(t_data *m_struct, double move_speed);

int step_backward(t_data *m_struct, double move_speed);

int step_rigth(t_data *m_struct, double move_speed);

int step_left(t_data *m_struct, double moveSpeed);
#endif //CLION_CUB3D_KEY_HOOKING_H
