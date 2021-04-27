//
// Created by Cesar Erebus on 4/27/21.
//

#include "key_hooking.h"
#include "draw_utils.h"
int make_move(t_data *m_struct)
{
    t_press_flgs *p_f;
    draw_floor_ceil(m_struct, m_struct->params->screen_h);
    p_f = m_struct->press_flgs;
    if (p_f->forw)
        step_forw_back(m_struct, 0.0872665, 13);
    if (p_f->backw)
        step_forw_back(m_struct, 0.0872665, 1);
    if (p_f->left)
        step_left_rigth(m_struct, 0.0872665, 0);
    if (p_f->right)
        step_left_rigth(m_struct, 0.0872665, 2);
    if (p_f->rot_left)
        rotate(m_struct, 0.0872665, 123);
    if (p_f->rot_right)
        rotate(m_struct, 0.0872665, 124);
    return (0);
}
