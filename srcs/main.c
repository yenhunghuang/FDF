/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehuang <yehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 19:29:28 by yehuang           #+#    #+#             */
/*   Updated: 2019/10/31 23:44:03 by yehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void			clean(char **data)
{
	int i;

	i = -1;
	while (data[++i])
		free(data[i]);
	free(data);
}

int				key_type(int type, t_mlx *f)
{
	if (type == 53)
		exit(0);
	mlx_clear_window(f->mlx, f->win);
	if (type == 0 || type == 1 || type == 2 || type == 6 ||
			type == 7 || type == 8)
		rotate(f, type, PI / 12);
	if (type == 44)
		chagetype(f);
	if (type == 123 || type == 124 || type == 125 || type == 126)
		shift(f, type, (int)WIN_W * 0.05);
	if (type == 34)
		instructions(f);
	if (type == 15)
		set_standard(f);
	drawline(f);
	return (0);
}

static void		read_and_put(int fd, t_mlx *f, char *filename, char **data)
{
	int		i;
	int		j;
	int		k;
	char	*line;

	fd = open(filename, O_RDONLY);
	clean(data);
	i = 0;
	while (get_next_line(fd, &line))
	{
		data = ft_strsplit(line, ' ');
		free(line);
		j = -1;
		while (data[++j])
		{
			f->map[i][j].x = j;
			f->map[i][j].y = i;
			f->map[i][j].z = ft_atoi(data[j]);
		}
		k = -1;
		clean(data);
		i++;
	}
	close(fd);
}

static void		read_file_mem(t_mlx *f, char *filename)
{
	int		fd;
	int		count;
	char	*line;
	char	**data;

	if ((fd = open(filename, O_RDONLY)) < 0)
		ft_errorexit("Error:  file does not found");
	get_next_line(fd, &line);
	data = ft_strsplit(line, ' ');
	free(line);
	count = 0;
	while (data[count])
		count++;
	f->col = count;
	count = 1;
	while (get_next_line(fd, &line) > 0 && count++)
		free(line);
	f->row = count;
	f->map = (t_coor **)ft_memalloc(sizeof(t_coor) * f->row);
	while (--count >= 0)
		f->map[count] = (t_coor *)ft_memalloc(sizeof(t_coor) * f->col);
	read_and_put(fd, f, filename, data);
	close(fd);
	set_standard(f);
}

int				main(int argc, char **argv)
{
	t_mlx	f;

	if (argc != 3 && argc != 2)
		ft_errorexit("usage: ./fdf //filename //color number");
	if (argc == 3)
	{
		f.color = (unsigned int)ft_atoi(argv[2]);
		if (f.color == 0)
			f.color = 0x87ceeb;
	}
	else
		f.color = 0x87ceeb;
	f.mlx = mlx_init();
	f.win = mlx_new_window(f.mlx, WIN_W, WIN_L, "fdf");
	read_file_mem(&f, argv[1]);
	mlx_key_hook(f.win, key_type, &f);
	mlx_mouse_hook(f.win, mouse_handler, &f);
	instructions(&f);
	drawline(&f);
	mlx_loop(f.mlx);
	return (0);
}
