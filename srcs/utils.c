/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcarva <julcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 20:42:43 by julcarva          #+#    #+#             */
/*   Updated: 2022/05/17 20:08:10 by julcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	check_malloc(void *ptr)
{
	if (!ptr)
	{
		free(ptr);
		ptr = NULL;
		ft_puterror("Malloc failed", -1);
	}
}

int	apply_color(t_program m0, t_program m1)
{
	if (m0.z > 300 || m1.z > 300 || m0.z < -300 || m1.z < -300)
		return (0xee4266);
	else if (m0.z > 0 || m1.z > 0)
		return (0xff9c6d);
	else if (m0.z < 0 || m1.z < 0)
		return (0x3256a8);
	else
		return (0xffffff);
}

void	my_mlx_pixel_put(t_program *data, int x, int y, int color)
{
	char	*pixel;

	if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
	{
		pixel = data->addr + (y * data->line_length
				+ x * (data->bits_per_pixel / 8));
		*(unsigned int *)pixel = color;
	}
}

int	leave_window(void)
{
	exit(0);
}

void	reset_view(int keycode, t_program **fdf)
{
	if (keycode == 36 || keycode == 65293)
	{
		(*fdf)->adapt_x = WIDTH - MENU_WIDTH / 3;
		(*fdf)->adapt_y = HEIGHT / 2;
		(*fdf)->angle = 0.523599;
		(*fdf)->zoom = ((WIDTH - MENU_WIDTH) / HEIGHT) * 10;
		(*fdf)->zoom_z = 5;
		(*fdf)->is_isometric = 1;
	}
	draw_map(*fdf);
}
