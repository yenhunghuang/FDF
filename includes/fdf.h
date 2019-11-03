/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehuang <yehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 19:46:39 by yehuang           #+#    #+#             */
/*   Updated: 2019/11/03 09:40:53 by yehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>

#include "../libft/libft.h"
#include "../libft/get_next_line.h"
#include "../minilibx_macos/mlx.h"

# define WIN_L 900
# define WIN_W 1600
# define PI 3.141592654
# define INT_MAX 2147483647
# define INT_MIN -2147483648

typedef struct s_line
{
    int x0;
    int x1;
    int y0;
    int y1;
    int color;
}              t_line;

typedef struct s_coor
{
    int     x;
    int     y;
    int     z;
    float   xf;
    float   yf;
    float   zf;
}               t_coor;


typedef struct  s_mlx
{
    void            *mlx;
    void            *win;
    int             col;
    int             row;
    int             max_x;
    int             min_x;
    int             max_y;
    int             min_y;
    int             max_z;
    int             min_z;
    t_coor          **map;
    unsigned int    color;
    float           a;
    float           scale;
    int             judge;
}               t_mlx;

void    set_standard(t_mlx *f);
void    drawline(t_mlx *f);
void	rotate(t_mlx *f, int mode, double rad);
void	shift(t_mlx *f, int k, int unit);
void	instructions(t_mlx *f);
void	scale(t_mlx *f, int type, double sc);
int		mouse_handler(int button, int x, int y, t_mlx *f);
int     give_right_deltaxy(int *x0, int *y0, int *x1, int *y1);
void    chagetype(t_mlx *f);
static void		set_standard_xy(t_mlx *f);
void		draw_line_final(t_mlx *f, t_line l, int z0, int z1);

#endif