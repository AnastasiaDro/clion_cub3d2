/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_shot.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <cerebus@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 16:15:57 by cerebus           #+#    #+#             */
/*   Updated: 2021/04/27 17:54:32 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/fcntl.h>
#include "cub_utils.h"
#include "unistd.h"
#include "do_screenshot.h"
#include "exceptions.h"

int fill_shot(t_data *m_struct, int fd)
{
    int x;
    int y;
    int color;
    y = m_struct->params->screen_h;

    while (y > 0)
    {
        x = 0;
        while (x < m_struct->params->screen_h)
         {
            color = *(int *)(m_struct->addr + (m_struct->line_length * y + \
            x * (m_struct->bits_per_pixel / 8)));
             write(fd, &color, 4);
            x++;
        }
    y--;
    }
    return (1);
}

static void fill_header(t_data *m_struct,  t_scr_shot *shot, int *fd)
{
    *fd = open("cub3D.bmp", O_CREAT | O_RDWR | O_TRUNC, 0777);
   shot->header[0] = 'B';
    shot->header[1] = 'M';
    shot->header[2] = (unsigned char)shot->size;
    shot->header[3] = (unsigned char)(shot->size >> 8);
    shot->header[4] = (unsigned char)(shot->size >> 16);
    shot->header[5] = (unsigned char)(shot->size >> 24);
    shot->header[10] = 54;
    shot->header[14] = 40;
    shot->header[18] = (unsigned char)(m_struct->params->screen_w);
    shot->header[19] = (unsigned char)(m_struct->params->screen_w >> 8);
    shot->header[20] = (unsigned char)(m_struct->params->screen_w >> 16);
    shot->header[21] = (unsigned char)(m_struct->params->screen_w >> 24);
    shot->header[22] = (unsigned char)m_struct->params->screen_h;
    shot->header[23] = (unsigned char)(m_struct->params->screen_h >> 8);
    shot->header[24] = (unsigned char)(m_struct->params->screen_h >> 16);
    shot->header[25] = (unsigned char)(m_struct->params->screen_h >> 24);
    shot->header[26] = 1;
    shot->header[28] = 32;
    write(*fd, shot->header, 54);
}

void save(t_data *m_struct)
{
    t_scr_shot shot;
    t_scr_shot *p_shot;
    int i;
    int fd;

    i = 0;
    fd = 0;
    p_shot = &shot;
    shot.size = 54 + (m_struct->bits_per_pixel / 8 * m_struct->params->screen_w * m_struct->params->screen_h);
//    all->save.size = 54 + (all->ptr.bits_per_pixel / 8 * \
//    all->map.r_width * all->map.r_height);
    shot.header  = malloc(54 * sizeof(unsigned char));
    //all->save.header = ft_calloc(54, sizeof(char));
     if (!shot.header)
     {
         throw_exception(MALLOC_ERROR);
         free_all(m_struct);
     }
     while (i < 54)
    {
         p_shot->header[i] = (unsigned char)(0);
         i++;
    }

    fill_header(m_struct, p_shot, &fd);
    fill_shot(m_struct, fd);
    free_all(m_struct);
    free(shot.header);
    exit(0);
}
