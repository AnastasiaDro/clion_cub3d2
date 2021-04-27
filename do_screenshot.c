/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_screenshot.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <cerebus@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 16:15:57 by cerebus           #+#    #+#             */
/*   Updated: 2021/04/27 17:54:32 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_utils.h"

int do_screenshot(t_data *m_struct, int fd)
{
    int x;
    int y;
    int color;
    y = m_struct->params->screen_h;

    t_data m_s = *m_struct;
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
}

static void ft_header(t_data *m_struct)
{
 all->save.fd = open("cub3D.bmp", O_CREAT | O_RDWR | O_TRUNC, 0777);
 all->save.header[0] = 'B';
 all->save.header[1] = 'M';
 all->save.header[2] = (unsigned char)all->save.size;
 all->save.header[3] = (unsigned char)(all->save.size >> 8);
 all->save.header[4] = (unsigned char)(all->save.size >> 16);
 all->save.header[5] = (unsigned char)(all->save.size >> 24);
 all->save.header[10] = 54;
 all->save.header[14] = 40;
 all->save.header[18] = (unsigned char)all->map.r_width;
 all->save.header[19] = (unsigned char)(all->map.r_width >> 8);
 all->save.header[20] = (unsigned char)(all->map.r_width >> 16);
 all->save.header[21] = (unsigned char)(all->map.r_width >> 24);
 all->save.header[22] = (unsigned char)all->map.r_height;
 all->save.header[23] = (unsigned char)(all->map.r_height >> 8);
 all->save.header[24] = (unsigned char)(all->map.r_height >> 16);
 all->save.header[25] = (unsigned char)(all->map.r_height >> 24);
 all->save.header[26] = 1;
 all->save.header[28] = 32;
 write(all->save.fd, all->save.header, 54);
}

void ft_save(t_all *all)
{
 int i;

 i = 0;
 all->save.size = 54 + (all->ptr.bits_per_pixel / 8 * \
 all->map.r_width * all->map.r_height);
 all->save.header = (char *)malloc(sizeof(char));
 if (!all->save.header)
  ft_errors(15);
 while (i < 54)
 {
  all->save.header[i] = (unsigned char)(0);
  i++;
 }
 ft_header(all);
 ft_draw_save(all);
 close(all->save.fd);
 free(all->save.header);
 exit(0);
}
