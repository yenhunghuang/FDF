/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehuang <yehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 23:12:06 by yehuang           #+#    #+#             */
/*   Updated: 2019/11/03 06:59:30 by yehuang          ###   ########.fr       */
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