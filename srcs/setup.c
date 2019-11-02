/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehuang <yehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 19:31:06 by yehuang           #+#    #+#             */
/*   Updated: 2019/11/01 00:02:46 by yehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void			instructions(t_mlx *f)
{
	mlx_string_put(f->mlx, f->win, 0, 0, 0xff0000, "Instructions: ");
	mlx_string_put(f->mlx, f->win, 0, 20, 0xff0000,
		"Reposition: key <up down left right> arrows");
	mlx_string_put(f->mlx, f->win, 0, 40, 0xff0000, "Zoom in/out: mouse wheel");
	mlx_string_put(f->mlx, f->win, 0, 60, 0xff0000, "Reset: key <r>");
	mlx_string_put(f->mlx, f->win, 0, 80, 0xff0000, "Rotate x: key <a z>");
	mlx_string_put(f->mlx, f->win, 0, 100, 0xff0000, "Rotate y: key <s x>");
	mlx_string_put(f->mlx, f->win, 0, 120, 0xff0000, "Rotate z: key <d c>");
	mlx_string_put(f->mlx, f->win, 0, 140, 0xff0000,
		"Print Instructions: key <i>");
	mlx_string_put(f->mlx, f->win, 0, 160, 0xff0000,
		"Change Projection: key </>");
}

static void		set_standard_xy(t_mlx *f)
{
	int	i;
	int	j;

	i = -1;
	while (++i < f->row)
	{
		j = -1;
		while (++j < f->col)
		{
			f->max_x = (f->map[i][j].xf > f->max_x) ?\
				f->map[i][j].xf : f->max_x;
			f->min_x = (f->map[i][j].xf < f->min_x) ?\
				f->map[i][j].xf : f->min_x;
			f->max_y = (f->map[i][j].yf - f->map[i][j].zf > f->max_y) ?\
				f->map[i][j].yf - f->map[i][j].zf : f->max_y;
			f->min_y = (f->map[i][j].yf - f->map[i][j].zf < f->min_y) ?\
				f->map[i][j].yf - f->map[i][j].zf : f->min_y;
		}
	}
	if ((float)WIN_W / (f->max_x - f->min_x) <\
			(float)WIN_L / (f->max_y - f->min_y))
		f->scale = (float)WIN_W * 0.5 / (f->max_x - f->min_x);
	f->scale = (float)WIN_L * 0.5 / (f->max_y - f->min_y);
}

void			camera_calibration(t_mlx *f)
{
	int		i;
	int		j;
	float	s[3];
	float	scale;

	scale = (float)WIN_W / (WIN_W / (f->col - 1) <= WIN_L / (f->row - 1) ?\
			(f->col - 1) : (f->row - 1));
	i = -1;
	while (++i < f->row)
	{
		j = -1;
		while (++j < f->col)
		{
			s[0] = scale * (f->map[i][j].x - f->map[f->row / 2][f->col / 2].x);
			s[1] = scale * (f->map[i][j].y - f->map[f->row / 2][f->col / 2].y);
			s[2] = f->max_z == f->min_z ? 0 :\
				WIN_L * 0.1 / (f->max_z - f->min_z) * f->map[i][j].z;
			f->map[i][j].xf = s[0] * cos(f->ang) - s[1] * sin(f->ang) *\
				cos(f->ang) + s[2] * sin(f->ang) * sin(f->ang);
			f->map[i][j].yf = s[0] * sin(f->ang) + s[1] * cos(f->ang) *\
				cos(f->ang) - s[2] * sin(f->ang) * cos(f->ang);
			f->map[i][j].zf = s[0] * sin(f->ang) + s[2] * cos(f->ang);
		}
	}
}

void			set_standard(t_mlx *f)
{
	int	i;
	int j;

	f->max_z = INT_MIN;
	f->min_z = INT_MAX;
	f->max_x = INT_MIN;
	f->min_x = INT_MAX;
	f->max_y = INT_MIN;
	f->min_y = INT_MAX;
	f->ang = PI / 30;
	i = -1;
	while (++i < f->row)
	{
		j = -1;
		while (++j < f->col)
		{
			f->max_z = f->max_z > f->map[i][j].z ? f->max_z : f->map[i][j].z;
			f->min_z = f->min_z < f->map[i][j].z ? f->min_z : f->map[i][j].z;
		}
	}
	camera_calibration(f);
	set_standard_xy(f);
}
