/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_screen_shot.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <cerebus@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 16:15:14 by cerebus           #+#    #+#             */
/*   Updated: 2021/04/27 16:46:15 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_scr_shot {

    int fd; //pad
    unsigned char *header;
    int size;
    int pad;
}               t_scr_shot;

void save(t_data *m_struct);