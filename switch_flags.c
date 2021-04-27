//
// Created by Cesar Erebus on 4/27/21.
//
#include "key_hooking.h"

int turn_on_flags(t_press_flgs *press_flgs, int key_code, t_data *m_struct)
{
    if (key_code == 13)
        press_flgs->forw = 1;
    else if (key_code == 1)
        press_flgs->backw = 1;
    else if (key_code == 0)
        press_flgs->left = 1;
    else if (key_code == 2)
        press_flgs->right = 1;
    else if (key_code == 123)
        press_flgs->rot_left = 1;
    else if (key_code == 124)
        press_flgs->rot_right = 1;
    if (key_code == 53)
    {
        free_all(m_struct);
        exit(0);
    }
    return (0);
}

int turn_off_flags(t_press_flgs *press_flgs, int key_code, t_data *m_struct)
{
    if (key_code == 13)
        press_flgs->forw = 0;
    else if (key_code == 1)
        press_flgs->backw = 0;
    else if (key_code == 0)
        press_flgs->left = 0;
    else if (key_code == 2)
        press_flgs->right = 0;
    else if (key_code == 123)
        press_flgs->rot_left = 0;
    else if (key_code == 124)
        press_flgs->rot_right = 0;
    if (key_code == 53)
    {
        free_all(m_struct);
        exit(0);
    }
    return (0);
}