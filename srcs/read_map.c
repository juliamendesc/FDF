/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcarva <julcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 20:42:40 by julcarva          #+#    #+#             */
/*   Updated: 2022/05/17 20:24:42 by julcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	get_height(char *file_name)
{
	int		fd;
	int		height;

	fd = open(file_name, O_RDONLY, 0);
	if (fd == -1)
		ft_puterror("Error: open failed", -1);
	height = 0;
	while (get_next_line_fdf(fd))
	{
		height++;
	}
	close(fd);
	return (height);
}

int	get_width(char *file_name)
{
	int		fd;
	int		width;
	char	*line;

	fd = open(file_name, O_RDONLY, 0);
	if (fd == -1)
		ft_puterror("Error: open failed", -1);
	line = get_next_line_fdf(fd);
	width = ft_wdcounter(line, ' ');
	free(line);
	close(fd);
	return (width);
}

int	fill_matrix_lines(char *line, t_program **map_matrix, int y)
{
	char	**points;
	int		x;

	points = ft_strsplit(line, ' ');
	x = 0;
	while (points[x])
	{
		map_matrix[y][x].z = ft_atoi(points[x]);
		map_matrix[y][x].x = x;
		map_matrix[y][x].y = y;
		free(points[x++]);
	}
	free(points);
	free(line);
	return (x);
}

t_program	**create_coordinates_matrix(char *file_name)
{
	t_program	**new_matrix;
	int			x;
	int			y;

	x = get_width(file_name);
	y = get_height(file_name);
	new_matrix = (t_program **)malloc(sizeof(t_program *) * (y + 1));
	check_malloc(new_matrix);
	while (y > 0)
		new_matrix[--y] = (t_program *)malloc(sizeof(t_program) * (x + 1));
	check_malloc(new_matrix);
	return (new_matrix);
}

t_program	**read_map(char *file_name)
{
	t_program	**coordinates_matrix;
	int			y;
	int			fd;
	char		*line;

	coordinates_matrix = create_coordinates_matrix(file_name);
	fd = open(file_name, O_RDONLY, 0);
	if (fd < 0)
		ft_puterror("Error opening file", -1);
	y = 0;
	line = get_next_line_fdf(fd);
	while (line)
	{
		fill_matrix_lines(line, coordinates_matrix, y++);
		line = get_next_line_fdf(fd);
	}
	free(line);
	coordinates_matrix[y] = NULL;
	close(fd);
	return (coordinates_matrix);
}
