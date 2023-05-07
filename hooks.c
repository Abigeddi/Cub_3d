/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-bakk < iel-bakk@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 18:43:29 by iel-bakk          #+#    #+#             */
/*   Updated: 2023/02/02 23:43:41 by iel-bakk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	close_window(int key, struct s_data *data)
{
	if (key == 53)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		exit(1);
	}
	return (0);
}

void	right_left_arrow(struct s_data *data)
{
	data->p.rotationangle += data->p.turndirection * (2 * (M_PI / 180));
	data->p.rayangle += data->p.turndirection * (2 * (M_PI / 180));
	data->p.newpx = data->p.pos_x + cos(data->p.rotationangle) * 30;
	data->p.newpy = data->p.pos_y + sin(data->p.rotationangle) * 30;
}

int	k_hook(int key, struct s_data *data)
{
	double	movestep;

	movestep = 0;
	if (key == 124)
		data->p.turndirection = 1;
	if (key == 123)
		data->p.turndirection = -1;
	if (key == 1)
		data->p.walkdirection = -1;
	if (key == 13)
		data->p.walkdirection = 1;
	if (key == 2)
		data->p.slidedirection = 1;
	if (key == 0)
		data->p.slidedirection = -1;
	if (key == 53)
		free_last(data);
	return (0);
}

int	release_k_hook(int key, struct s_data *data)
{
	if (key == 124)
		data->p.turndirection = 0;
	if (key == 123)
		data->p.turndirection = 0;
	if (key == 13)
		data->p.walkdirection = 0;
	if (key == 1)
		data->p.walkdirection = 0;
	if (key == 0)
		data->p.slidedirection = 0;
	if (key == 2)
		data->p.slidedirection = 0;
	return (1);
}
