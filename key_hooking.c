//
// Created by  Anastasia on 31.03.2021.
//
#include "key_hooking.h"
#include "stdio.h"


int rotate(t_data *m_struct, double rotSpeed)
{
	double oldDirX = m_struct->dirX;
	m_struct->dirX = m_struct->dirX * cos(rotSpeed) - m_struct->dirY * sin(rotSpeed);
	m_struct->dirY = oldDirX * sin(rotSpeed) + m_struct->dirY * cos(rotSpeed);
	double oldPlaneX = m_struct->planeX;
	m_struct->planeX= m_struct->planeX * cos(rotSpeed) - m_struct->planeY * sin(rotSpeed);
	m_struct->planeY = oldPlaneX * sin(rotSpeed) + m_struct->planeY * cos(rotSpeed);
	return 1;
}


int do_step(t_data *m_struct, double moveSpeed, double coef)
{
	char **map = m_struct->map;
	if(map[(int)m_struct->map_player_y][(int)(m_struct->map_player_x + coef*m_struct->dirX * moveSpeed)] == '0')
		m_struct->map_player_x += coef*m_struct->dirX * moveSpeed;
	if(map[(int)(m_struct->map_player_y + coef*m_struct->dirY * moveSpeed)][(int)m_struct->map_player_x] == '0')
		m_struct->map_player_y += coef*m_struct->dirY * moveSpeed;
	return 1;
}

int step_left_rigth(t_data *m_struct, double moveSpeed, int coef)
{
	char **map = m_struct->map;
	if(map[(int)m_struct->map_player_y][(int)(m_struct->map_player_x + coef*m_struct->planeX * moveSpeed)] == '0')
		m_struct->map_player_x += coef*m_struct->planeX * moveSpeed;
	if(map[(int)(m_struct->map_player_y + coef*m_struct->planeY * moveSpeed)][(int)m_struct->map_player_x] == '0')
		m_struct->map_player_y += coef*m_struct->planeY * moveSpeed;
	return 1;
}

int step_forward(t_data *m_struct, double move_speed)
{
	do_step(m_struct, move_speed, 1);
	return 1;
}

int step_backward(t_data *m_struct, double move_speed)
{
	do_step(m_struct, move_speed, -1);
	return 1;
}

int step_rigth(t_data *m_struct, double move_speed)
{
	step_left_rigth(m_struct, move_speed, -1);
	return 1;
}

int step_left(t_data *m_struct, double move_speed)
{
	step_left_rigth(m_struct, move_speed, 1);
	return 1;
}

