/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehuang <yehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 19:30:02 by yehuang           #+#    #+#             */
/*   Updated: 2019/11/03 09:18:53 by yehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void		scale(t_mlx *f, int type, double sc)
{
	int	i;
	int	j;

	if (type == 4)
		sc = 1 / sc;
	i = -1;
	while (++i < f->row)
	{
		j = -1;
		while (++j < f->col)
		{
			f->map[i][j].xf *= sc;
			f->map[i][j].yf *= sc;
			f->map[i][j].zf *= sc;
		}
	}
}

void		shift(t_mlx *f, int type, int judge)
{
	int	i;
	int	j;

	if (type == 123 || type == 126)
		judge *= -1;
	i = -1;
	while (++i < f->row)
	{
		j = -1;
		while (++j < f->col)
		{
			if (type == 123 || type == 124)
				f->map[i][j].xf += judge;
			else if (type == 125 || type == 126)
				f->map[i][j].yf += judge;
		}
	}
}

static void	rotate_norm(int type, double ang, t_mlx *f, t_coor *coor)
{
	float	x;
	float	y;
	float	z;

	x = coor->xf;
	y = coor->yf;
	z = coor->zf;
	if (type == 0 || type == 6)
	{
		coor->yf = y * cos(ang) - z * sin(ang);
		coor->zf = y * sin(ang) + z * cos(ang);
	}
	else if (type == 1 || type == 7)
	{
		coor->xf = x * cos(ang) + z * sin(ang);
		coor->zf = -x * sin(ang) + z * cos(ang);
	}
	else if (type == 2 || type == 8)
	{
		coor->xf = x * cos(ang) - y * sin(ang);
		coor->yf = x * sin(ang) + y * cos(ang);
	}
}

void		rotate(t_mlx *f, int type, double rad)
{
	int	i;
	int	j;

	if (type == 6 || type == 7 || type == 8)
		rad *= -1;
	i = -1;
	while (++i < f->row)
	{
		j = -1;
		while (++j < f->col)
			rotate_norm(type, rad, f, &f->map[i][j]);
	}
}

/*void		chagetype(t_mlx *f)
{
	int		i;
	int		j;
	float	s[2];
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
			f->map[i][j].xf = s[0];
			f->map[i][j].yf = s[1];
			f->map[i][j].zf = 0;
		}
	}
}*/
