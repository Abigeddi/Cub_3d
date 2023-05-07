/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_intersect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-bakk < iel-bakk@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 18:41:52 by iel-bakk          #+#    #+#             */
/*   Updated: 2023/02/01 20:10:22 by iel-bakk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	upright_vintersect(struct s_data *data)
{
	data->interv.firstx = (floor(data->p.pos_x / TILE_SIZE)
			* TILE_SIZE) + TILE_SIZE;
	data->interv.firsty = data->p.pos_y + ((data->interv.firstx
				- data->p.pos_x) * tan(data->p.rayangle));
	data->interv.xstep = TILE_SIZE;
	data->interv.ystep = data->interv.xstep * tan(data->p.rayangle);
	if (data->interv.ystep > 0)
		data->interv.ystep *= -1;
	data->interv.xintersect = data->interv.firstx;
	data->interv.yintersect = data->interv.firsty;
	while (wallishited(data->interv.xintersect + 1,
			data->interv.yintersect, data) == 0)
	{
		data->interv.xintersect += data->interv.xstep;
		data->interv.yintersect += data->interv.ystep;
	}
	data->p.v_dist = distancebetweenpoints(data->p.pos_x, data->p.pos_y,
			data->interv.xintersect, data->interv.yintersect);
	data->p.v_rayx = data->interv.xintersect;
	data->p.v_rayy = data->interv.yintersect;
}

void	downright_vintersect(struct s_data *data)
{
	data->interv.firstx = (floor(data->p.pos_x / TILE_SIZE)
			* TILE_SIZE) + TILE_SIZE;
	data->interv.firsty = data->p.pos_y + ((data->interv.firstx
				- data->p.pos_x) * tan(data->p.rayangle));
	data->interv.xstep = TILE_SIZE;
	data->interv.ystep = data->interv.xstep * tan(data->p.rayangle);
	if (data->interv.ystep < 0)
		data->interv.ystep *= -1;
	data->interv.xintersect = data->interv.firstx;
	data->interv.yintersect = data->interv.firsty;
	while (wallishited(data->interv.xintersect + 1,
			data->interv.yintersect, data) == 0)
	{
		data->interv.xintersect += data->interv.xstep;
		data->interv.yintersect += data->interv.ystep;
	}
	data->p.v_dist = distancebetweenpoints(data->p.pos_x, data->p.pos_y,
			data->interv.xintersect, data->interv.yintersect);
	data->p.v_rayx = data->interv.xintersect;
	data->p.v_rayy = data->interv.yintersect;
}

void	downleft_vintersect(struct s_data *data)
{
	data->interv.firstx = (floor(data->p.pos_x / TILE_SIZE) * TILE_SIZE);
	data->interv.firsty = data->p.pos_y + ((data->interv.firstx
				- data->p.pos_x) * tan(data->p.rayangle));
	data->interv.xstep = -TILE_SIZE;
	data->interv.ystep = data->interv.xstep * tan(data->p.rayangle);
	if (data->interv.ystep < 0)
		data->interv.ystep *= -1;
	data->interv.xintersect = data->interv.firstx;
	data->interv.yintersect = data->interv.firsty;
	while (wallishited(data->interv.xintersect - 1,
			data->interv.yintersect, data) == 0)
	{
		data->interv.xintersect += data->interv.xstep;
		data->interv.yintersect += data->interv.ystep;
	}
	data->p.v_rayx = data->interv.xintersect;
	data->p.v_rayy = data->interv.yintersect;
	data->p.v_dist = distancebetweenpoints(data->p.pos_x,
			data->p.pos_y, data->p.v_rayx, data->p.v_rayy);
}

void	upleft_vintersect(struct s_data *data)
{
	data->interv.firstx = (floor(data->p.pos_x / TILE_SIZE) * TILE_SIZE);
	data->interv.firsty = data->p.pos_y + ((data->interv.firstx
				- data->p.pos_x) * tan(data->p.rayangle));
	data->interv.xstep = -TILE_SIZE;
	data->interv.ystep = data->interv.xstep * tan(data->p.rayangle);
	if (data->interv.ystep > 0)
		data->interv.ystep *= -1;
	data->interv.xintersect = data->interv.firstx;
	data->interv.yintersect = data->interv.firsty;
	while (wallishited(data->interv.xintersect - 1,
			data->interv.yintersect, data) == 0)
	{
		data->interv.xintersect += data->interv.xstep;
		data->interv.yintersect += data->interv.ystep;
	}
	data->p.v_rayx = data->interv.xintersect;
	data->p.v_rayy = data->interv.yintersect;
	data->p.v_dist = distancebetweenpoints(data->p.pos_x,
			data->p.pos_y, data->p.v_rayx, data->p.v_rayy);
}

void	vertical_intersection(struct s_data *data)
{
	data->p.rayangle = normalizeangle(data->p.rayangle);
	data->p.rotationangle = normalizeangle(data->p.rotationangle);
	if ((data->p.rayangle > (270 * (M_PI / 180))
			&& data->p.rayangle < 2 * M_PI))
		upright_vintersect(data);
	else if ((data->p.rayangle > 0 && data->p.rayangle < M_PI / 2))
		downright_vintersect(data);
	else if ((data->p.rayangle > M_PI / 2 && data->p.rayangle < M_PI))
		downleft_vintersect(data);
	else if ((data->p.rayangle > M_PI && data->p.rayangle < (3 *(M_PI / 2))))
		upleft_vintersect(data);
}
