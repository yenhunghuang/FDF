/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehuang <yehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 23:12:06 by yehuang           #+#    #+#             */
/*   Updated: 2019/11/01 00:01:36 by yehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int		mouse_handler(int button, int x, int y, t_mlx *f)
{
	static int		put;
	static int		oldx;
	static int		oldy;
	static t_line	l;

	l.color = 0x00ffff;
	if (button == 4 || button == 5)
	{
		mlx_clear_window(f->mlx, f->win);
		scale(f, button, 1.10);
		drawline(f);
	}
	return (0);
}

void	draw_line_jpar(t_mlx *f, t_line line, int i, int j)
{
	line.x0 = round((int)WIN_W * 0.5 + (f->map[i][j].xf) * f->scale);
	line.y0 = round((int)WIN_L * 0.5 + f->map[i][j].yf);
	line.x1 = round((int)WIN_W * 0.5 + (f->map[i][j + 1].xf) * f->scale);
	line.y1 = round((int)WIN_L * 0.5 + f->map[i][j + 1].y);
	draw_line_final(f->mlx, line, f->map[i][j].z, f->map[i][j + 1].z);
}

void	draw_line_ipar(t_mlx *f, t_line line, int i, int j)
{
	line.x0 = round((int)WIN_W * 0.5 + (f->map[i][j].xf) * f->scale);
	line.y0 = round((int)WIN_L * 0.5 + f->map[i][j].yf);
	line.x1 = round((int)WIN_W * 0.5 + (f->map[i + 1][j].xf) * f->scale);
	line.y1 = round((int)WIN_L * 0.5 + f->map[i + 1][j].yf);
	draw_line_final(f->mlx, line, f->map[i][j].z, f->map[i + 1][j].z);
}
