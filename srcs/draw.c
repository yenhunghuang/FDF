/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehuang <yehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 19:29:47 by yehuang           #+#    #+#             */
/*   Updated: 2019/11/03 11:04:40 by yehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <stdio.h>

int				give_right_deltaxy(int *x0, int *y0, int *x1, int *y1)
{
	int j;

	j = 1;
	if (abs(*x1 - *x0) < abs(*y1 - *y0))
	{
		ft_swap(x0, y0);
		ft_swap(x1, y1);
		j = 0;
	}
	if (*x1 < *x0)
	{
		ft_swap(x0, x1);
		ft_swap(y0, y1);
	}
	return (j);
}

void			draw_line_final(t_mlx *f, t_line l, int z0, int z1)
{
	int		delta[3];
	float	err[2];
	int		ystep;
	int		j;

	j = give_right_deltaxy(&l.x0, &l.y0, &l.x1, &l.y1);
	delta[0] = l.x1 - l.x0;
	delta[1] = abs(l.y1 - l.y0);
	err[0] = 0;
	ystep = l.y0 < l.y1 ? 1 : -1;
	err[1] = (float)abs(delta[1]) / delta[0];
	while (l.x0 < l.x1)
	{
		if (j == 1)
			mlx_pixel_put(f->mlx, f->win, l.x0, l.y0, 0x87ceeb +\
					(z1 + z0) * (l.x1 - l.x0));
		else
			mlx_pixel_put(f->mlx, f->win, l.y0, l.x0, 0x87ceeb +\
					(z1 + z0) * (l.x1 - l.x0));
		err[0] += err[1];
		err[0] > 0.5 ? l.y0 += ystep : 1 == 1;
		err[0] > 0.5 ? err[0] -= 1.0 : 1 == 1;
		l.x0++;
	}
}


void			draw_line_jper(t_mlx *f, t_line line, int i, int j)
{
	line.x0 = round((int)WIN_W * 0.5 + (f->map[i][j].xf)*(6000*f->scale)/(6000*f->scale+f->map[i][j].zf));
	line.y0 = round((int)WIN_L * 0.5 + (f->map[i][j].yf)*(6000*f->scale)/(6000*f->scale+f->map[i][j].zf));
	line.x1 = round((int)WIN_W * 0.5 + (f->map[i][j + 1].xf)*(6000*f->scale)/(6000*f->scale+f->map[i][j].zf));
	line.y1 = round((int)WIN_L * 0.5 + \
			(f->map[i][j + 1].yf)*(6000*f->scale)/(6000*f->scale+f->map[i][j].zf));
	draw_line_final(f->mlx, line, f->map[i][j].z, f->map[i][j + 1].z);
	//printf("%f\n", f->scale);
}

void			draw_line_iper(t_mlx *f, t_line line, int i, int j)
{
	line.x0 = round((int)WIN_W * 0.5 + (f->map[i][j].xf)*(6000*f->scale)/(6000*f->scale+f->map[i][j].zf));
	line.y0 = round((int)WIN_L * 0.5 + (f->map[i][j].yf)*(6000*f->scale)/(6000*f->scale+f->map[i][j].zf));
	line.x1 = round((int)WIN_W * 0.5 + (f->map[i + 1][j].xf)*(6000*f->scale)/(6000*f->scale+f->map[i][j].zf));
	line.y1 = round((int)WIN_L * 0.5 + \
			(f->map[i + 1][j].yf)*(6000*f->scale)/(6000*f->scale+f->map[i][j].zf));
	draw_line_final(f->mlx, line, f->map[i][j].z, f->map[i + 1][j].z);
}
/*

void			draw_line_j(t_mlx *f, t_line line, int i, int j)
{
	line.x0 = round((int)WIN_W * 0.5 + (f->map[i][j].xf));
	line.y0 = round((int)WIN_L * 0.5 + (f->map[i][j].yf));
	line.x1 = round((int)WIN_W * 0.5 + (f->map[i][j + 1].xf));
	line.y1 = round((int)WIN_L * 0.5 + \
			(f->map[i][j + 1].yf));
	draw_line_final(f->mlx, line, f->map[i][j].z, f->map[i][j + 1].z);
}

void			draw_line_i(t_mlx *f, t_line line, int i, int j)
{
	line.x0 = round((int)WIN_W * 0.5 + (f->map[i][j].xf));
	line.y0 = round((int)WIN_L * 0.5 + (f->map[i][j].yf));
	line.x1 = round((int)WIN_W * 0.5 + (f->map[i + 1][j].xf));
	line.y1 = round((int)WIN_L * 0.5 + \
			(f->map[i + 1][j].yf));
	draw_line_final(f->mlx, line, f->map[i][j].z, f->map[i + 1][j].z);
}
*/
void			drawline(t_mlx *f)
{
	int		i;
	int		j;
	t_line	line;

	line.color = f->color;
	i = -1;
	while (++i < f->row)
	{
		j = -1;
		while (++j < f->col)
		{
			if (j + 1 < f->col)
				draw_line_jper(f, line, i, j);
			if (i + 1 < f->row)
				draw_line_iper(f, line, i, j);
		}
	}
}
