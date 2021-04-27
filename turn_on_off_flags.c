//
// Created by Cesar Erebus on 4/27/21.
//
#include <printf.h>
#include "key_hooking.h"

int turn_on_flags(int key_code, t_data *m_struct)
{
    printf("turned on!\n");
    t_press_flgs *p_f;

    p_f = m_struct->press_flgs;
    if (key_code == 13)
        p_f->forw = 1;
    else if (key_code == 1)
        p_f->backw = 1;
    else if (key_code == 0)
        p_f->left = 1;
    else if (key_code == 2)
        p_f->right = 1;
    else if (key_code == 123)
        p_f->rot_left = 1;
    else if (key_code == 124)
        p_f->rot_right = 1;
    return (0);
}

int turn_off_flags(int key_code, t_data *m_struct)
{
    printf("turned off!\n");
    t_press_flgs *p_f;
    p_f = m_struct->press_flgs;

    if (key_code == 13)
        p_f->forw = 0;
    else if (key_code == 1)
        p_f->backw = 0;
    else if (key_code == 0)
        p_f->left = 0;
    else if (key_code == 2)
        p_f->right = 0;
    else if (key_code == 123)
        p_f->rot_left = 0;
    else if (key_code == 124)
        p_f->rot_right = 0;
    return (0);
}