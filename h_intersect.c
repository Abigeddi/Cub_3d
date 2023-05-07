/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_intersect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-bakk < iel-bakk@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 18:34:16 by iel-bakk          #+#    #+#             */
/*   Updated: 2023/02/01 20:10:12 by iel-bakk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	upright_hintersect(struct s_data *data)
{
	data->interh.firsty = floor(data->p.pos_y / TILE_SIZE) * TILE_SIZE;
	data->interh.firstx = data->p.pos_x + ((data->interh.firsty - data->p.pos_y)
			/ tan(data->p.rayangle));
	data->interh.ystep = -TILE_SIZE;
	data->interh.xstep = data->interh.ystep / tan(data->p.rayangle);
	if (data->interh.xstep < 0)
		data->interh.xstep *= -1;
	data->interh.xintersect = data->interh.firstx;
	data->interh.yintersect = data->interh.firsty;
	while (wallishited(data->interh.xintersect,
			data->interh.yintersect - 1, data) == 0)
	{
		data->interh.xintersect += data->interh.xstep;
		data->interh.yintersect += data->interh.ystep;
	}
	data->p.h_rayx = data->interh.xintersect;
	data->p.h_rayy = data->interh.yintersect;
	data->p.h_dist = distancebetweenpoints(data->p.pos_x,
			data->p.pos_y, data->p.h_rayx, data->p.h_rayy);
}

void	downright_hintersect(struct s_data *data)
{
	data->interh.firsty = (floor(data->p.pos_y
				/ TILE_SIZE) * TILE_SIZE) + TILE_SIZE;
	data->interh.firstx = data->p.pos_x + ((data->interh.firsty
				- data->p.pos_y) / tan(data->p.rayangle));
	data->interh.ystep = TILE_SIZE;
	data->interh.xstep = data->interh.ystep / tan(data->p.rayangle);
	if (data->interh.xstep < 0)
		data->interh.xstep *= -1;
	data->interh.xintersect = data->interh.firstx;
	data->interh.yintersect = data->interh.firsty;
	while (wallishited(data->interh.xintersect,
			data->interh.yintersect + 1, data) == 0)
	{
		data->interh.xintersect += data->interh.xstep;
		data->interh.yintersect += data->interh.ystep;
	}
	data->p.h_dist = distancebetweenpoints(data->p.pos_x,
			data->p.pos_y, data->interh.xintersect, data->interh.yintersect);
	data->p.h_rayx = data->interh.xintersect;
	data->p.h_rayy = data->interh.yintersect;
}

void	downleft_hintersect(struct s_data *data)
{
	data->interh.firsty = (floor(data->p.pos_y
				/ TILE_SIZE) * TILE_SIZE) + TILE_SIZE;
	data->interh.firstx = data->p.pos_x + ((data->interh.firsty
				- data->p.pos_y) / tan(data->p.rayangle));
	data->interh.ystep = TILE_SIZE;
	data->interh.xstep = data->interh.ystep / tan(data->p.rayangle);
	if (data->interh.xstep > 0)
		data->interh.xstep *= -1;
	data->interh.xintersect = data->interh.firstx;
	data->interh.yintersect = data->interh.firsty;
	while (wallishited(data->interh.xintersect,
			data->interh.yintersect + 1, data) == 0)
	{
		data->interh.xintersect += data->interh.xstep;
		data->interh.yintersect += data->interh.ystep;
	}
	data->p.h_dist = distancebetweenpoints(data->p.pos_x,
			data->p.pos_y, data->interh.xintersect, data->interh.yintersect);
	data->p.h_rayx = data->interh.xintersect;
	data->p.h_rayy = data->interh.yintersect;
}

void	upleft_hintersect(struct s_data *data)
{
	data->interh.firsty = (floor(data->p.pos_y
				/ TILE_SIZE) * TILE_SIZE);
	data->interh.firstx = data->p.pos_x + ((data->interh.firsty
				- data->p.pos_y) / tan(data->p.rayangle));
	data->interh.ystep = -TILE_SIZE;
	data->interh.xstep = data->interh.ystep / tan(data->p.rayangle);
	if (data->interh.xstep > 0)
		data->interh.xstep *= -1;
	data->interh.xintersect = data->interh.firstx;
	data->interh.yintersect = data->interh.firsty;
	while (wallishited(data->interh.xintersect,
			data->interh.yintersect - 1, data) == 0)
	{
		data->interh.xintersect += data->interh.xstep;
		data->interh.yintersect += data->interh.ystep;
	}
	data->p.h_rayx = data->interh.xintersect;
	data->p.h_rayy = data->interh.yintersect;
	data->p.h_dist = distancebetweenpoints(data->p.pos_x,
			data->p.pos_y, data->p.h_rayx, data->p.h_rayy);
}

void	horizontal_intersection(struct s_data *data)
{
	data->p.rayangle = normalizeangle(data->p.rayangle);
	data->p.rotationangle = normalizeangle(data->p.rotationangle);
	if ((data->p.rayangle > (270 * (M_PI / 180))
			&& data->p.rayangle < 2 * M_PI))
		upright_hintersect(data);
	else if ((data->p.rayangle > 0 && data->p.rayangle < M_PI / 2))
		downright_hintersect(data);
	else if ((data->p.rayangle > M_PI / 2 && data->p.rayangle < M_PI))
		downleft_hintersect(data);
	else if ((data->p.rayangle > M_PI && data->p.rayangle < (3 *(M_PI / 2))))
		upleft_hintersect(data);
}
