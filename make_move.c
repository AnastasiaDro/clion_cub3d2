//
// Created by Cesar Erebus on 4/27/21.
//

#include "key_hooking.h"

int make_move(t_press_flgs *press_flgs, t_data *m_struct)
{
    if (press_flgs->forw)
        step_forw_back(m_struct, 0.0872665, 13);
    if (press_flgs->backw)
        step_forw_back(m_struct, 0.0872665, 1);
    if (press_flgs->left)
        step_left_rigth(m_struct, 0.0872665, 0);
    if (press_flgs->right)
        step_left_rigth(m_struct, 0.0872665, 2);
    if (press_flgs->rot_left)
        rotate(m_struct, 0.0872665, 123);
    if (press_flgs->rot_right)
        rotate(m_struct, 0.0872665, 124);
    return (0);
}
