/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-bakk < iel-bakk@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 16:42:37 by iel-bakk          #+#    #+#             */
/*   Updated: 2023/02/02 22:22:22 by iel-bakk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	init_data_helper(struct s_data *data)
{
	data->win_width = (data->mymap->mapwidth * TILE_SIZE) + 100;
	data->win_hight = (data->mymap->mapheight * TILE_SIZE) + 100;
	data->p.movespeed = 2;
	data->p.turndirection = 0;
	data->p.walkdirection = 0;
	data->p.slidedirection = 0;
	data->mymap->tile_size = TILE_SIZE;
	data->p.newpx = data->p.pos_x + cos(data->p.rotationangle) * 30;
	data->p.newpy = data->p.pos_y + sin(data->p.rotationangle) * 30;
	data->p.fieldangle = 60 * (M_PI / 180);
	data->p.rotationspeed = 2 * (M_PI / 180);
	data->p.wallstreapwidth = 1;
	data->p.raysnumber = data->win_width / data->p.wallstreapwidth;
	data->p.rayangle = data->p.rotationangle - (data->p.fieldangle / 2);
	data->img.hight = TILE_SIZE;
	data->img.width = TILE_SIZE;
}

void	init_data(struct s_data *data, char *param)
{
	data->mlx_ptr = mlx_init();
	data->mymap = texture_init(param, data);
	if (!check_tab(data))
		exit (1);
	check_width_hight(data);
	init_data_helper(data);
	data->p.raysdistance = malloc(sizeof(double) * data->p.raysnumber);
	if (!data->p.raysdistance)
		return ;
	data->p.wallstreaphight = 0;
	data->p.distanceprojectplane = 0;
	data->win_ptr = mlx_new_window(data->mlx_ptr,
			data->win_width, data->win_hight, "test");
}

void	get_texture_info(struct s_data *data, t_map *map)
{
	int	check;

	check = check_texture(map->componements, map, data->mlx_ptr);
	if (check)
	{
		free_map(map);
		free_table(map->map);
		printf("Error\n:Invalid textures\n");
		exit (1);
	}
}

t_map	*texture_init(char *file, struct s_data *data)
{
	t_map	*map;
	char	**tmp;

	tmp = NULL;
	map = init_map();
	tmp = get_map(file);
	if (!tmp || *tmp == '\0')
		return (printf("Invalid arguments"), exit(0), NULL);
	get_param(map, tmp);
	map->map = stor_tab(tmp);
	free_table(tmp);
	get_texture_info(data, map);
	return (map);
}
