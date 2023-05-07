/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-bakk < iel-bakk@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 16:41:20 by iel-bakk          #+#    #+#             */
/*   Updated: 2023/02/02 23:49:54 by iel-bakk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	my_mlx_pixel_put(t_j_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	create_image(t_j_img *img, void *mlx, int width, int height)
{
	img->img = mlx_new_image(mlx, width, height);
	img->addr = mlx_get_data_addr(img->img,
			&img->bits_per_pixel, &img->line_length, &img->endian);
}

void	call_mouvement(t_data *data)
{
	right_left_arrow(data);
	front_back_key(data);
	sliding_key(data);
}

void	draw_rays_helper(struct s_data *data)
{
	int	i;

	i = -1;
	call_mouvement(data);
	while (++i < data->p.raysnumber)
	{
		vertical_intersection(data);
		horizontal_intersection(data);
		if (data->p.v_dist > data->p.h_dist)
		{
			data->p.rayy = data->p.h_rayy;
			data->p.rayx = data->p.h_rayx;
			data->p.raysdistance[i] = data->p.h_dist;
			drawheight(data, i, 1);
		}
		else
		{
			data->p.rayx = data->p.v_rayx;
			data->p.rayy = data->p.v_rayy;
			data->p.raysdistance[i] = data->p.v_dist;
			drawheight(data, i, 2);
		}
		data->p.rayangle += data->p.fieldangle / data->p.raysnumber;
	}
}

void	drawrays(struct s_data *data)
{
	data->p.rayangle = data->p.rotationangle - (data->p.fieldangle / 2);
	if (!data->render.addr)
		create_image(&data->render, data->mlx_ptr,
			data->win_width, data->win_hight);
	else
	{
		mlx_destroy_image(data->mlx_ptr, data->render.img);
		create_image(&data->render, data->mlx_ptr,
			data->win_width, data->win_hight);
	}
	draw_rays_helper(data);
	mlx_put_image_to_window(data->mlx_ptr,
		data->win_ptr, data->render.img, 0, 0);
}
