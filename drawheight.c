/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawheight.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-bakk < iel-bakk@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 18:54:11 by iel-bakk          #+#    #+#             */
/*   Updated: 2023/02/01 20:09:49 by iel-bakk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	draw_ceiling_and_floor(struct s_data *data, int c, int i)
{
	int	height;

	height = 0;
	while (height <= c)
	{
		my_mlx_pixel_put(&data->render, i, height, data->mymap->celling);
		height++;
	}
	height = data->win_hight - c;
	while (height < data->win_hight)
	{
		my_mlx_pixel_put(&data->render, i, height, data->mymap->floor);
		height++;
	}
}

t_xpm	*choose_xpm(t_data *data, int choice, int *oofx)
{
	if (choice == 1)
	{
		if (data->p.rayangle >= M_PI && data->p.rayangle <= 2 * M_PI)
			return (*oofx = (data->p.h_rayx / TILE_SIZE
					- ((int)data->p.h_rayx / TILE_SIZE))
				* data->mymap->north->width, data->mymap->north);
		else
			return (*oofx = (data->p.h_rayx / TILE_SIZE
					- ((int)data->p.h_rayx / TILE_SIZE))
				* data->mymap->south->width, data->mymap->south);
	}
	else
	{
		if (data->p.rayangle >= M_PI / 2 && data->p.rayangle <= 3 * M_PI / 2)
			return (*oofx = (data->p.v_rayy / TILE_SIZE
					- ((int)data->p.v_rayy / TILE_SIZE))
				* data->mymap->west->width, data->mymap->west);
		else
			return (*oofx = (data->p.v_rayy / TILE_SIZE
					- ((int)data->p.v_rayy / TILE_SIZE))
				* data->mymap->east->width, data->mymap->east);
	}
	return (NULL);
}

void	draw_height_helper(int *ceiling)
{
	if (*ceiling < 0)
		*ceiling = 0;
}

void	drawheight(struct s_data *data, int i, int intersect)
{
	t_draw_tool	tool;
	t_xpm		*xpm;

	xpm = choose_xpm(data, intersect, &tool.oofx);
	tool.height = 0;
	tool.ppdistance = (data->win_hight / 2) / tan(data->p.fieldangle / 2);
	tool.wstripheight = (TILE_SIZE / data->p.raysdistance[i]) * tool.ppdistance;
	tool.ceiling = (data->win_hight - tool.wstripheight) / 2;
	if (intersect == 1)
		tool.oofx = (data->p.h_rayx / TILE_SIZE
				- ((int)data->p.h_rayx / TILE_SIZE)) * xpm->width;
	else
		tool.oofx = (data->p.v_rayy / TILE_SIZE
				- ((int)data->p.v_rayy / TILE_SIZE)) * xpm->width;
	draw_height_helper(&tool.ceiling);
	tool.height = tool.ceiling;
	draw_ceiling_and_floor(data, tool.ceiling, i);
	while (tool.height < data->win_hight - tool.ceiling)
	{
		tool.tmp = tool.height + ((tool.wstripheight / 2)
				- (data->win_hight / 2));
		tool.oofy = tool.tmp * ((float)xpm->height / tool.wstripheight);
		tool.color = xpm->address[(xpm->width * tool.oofy) + tool.oofx];
		my_mlx_pixel_put(&data->render, i, tool.height++, tool.color);
	}
}
