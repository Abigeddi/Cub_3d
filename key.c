/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-bakk < iel-bakk@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 16:20:49 by iel-bakk          #+#    #+#             */
/*   Updated: 2023/02/02 22:27:25 by iel-bakk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	front_back_key(struct s_data *data)
{
	double	movestep;

	movestep = data->p.walkdirection * data->p.movespeed;
	data->p.newpx = (data->p.pos_x + cos(data->p.rotationangle) * movestep);
	data->p.newpy = (data->p.pos_y + sin(data->p.rotationangle) * movestep);
	if (wall_coalision(data->p.newpx, data->p.pos_y, data) == 0)
	{
			data->p.pos_x = data->p.newpx;
	}
	if (wall_coalision(data->p.pos_x, data->p.newpy, data) == 0)
	{
			data->p.pos_y = data->p.newpy;
	}
	data->p.newppx = (data->p.pos_x + cos(data->p.rotationangle) * 30);
	data->p.newppy = (data->p.pos_y + sin(data->p.rotationangle) * 30);
}

void	sliding_key(struct s_data *data)
{
	double	movestep;

	movestep = data->p.slidedirection * data->p.movespeed;
	if (data->p.rotationangle)
	data->p.newpx = (data->p.pos_x + cos(data->p.rotationangle
					+ (M_PI / 2)) * movestep);
	data->p.newpy = (data->p.pos_y + sin(data->p.rotationangle
				+ (M_PI / 2)) * movestep);
	if (wall_coalision(data->p.newpx, data->p.pos_y, data) == 0)
			data->p.pos_x = data->p.newpx;
	if (wall_coalision(data->p.pos_x, data->p.newpy, data) == 0)
			data->p.pos_y = data->p.newpy;
	data->p.newppx = (data->p.pos_x + cos(data->p.rotationangle) * 30);
	data->p.newppy = (data->p.pos_y + sin(data->p.rotationangle) * 30);
}
