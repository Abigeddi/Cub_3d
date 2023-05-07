/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-bakk < iel-bakk@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 20:50:02 by iel-bakk          #+#    #+#             */
/*   Updated: 2023/02/02 23:52:44 by iel-bakk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	free_table(char **table)
{
	int	i;

	i = 0;
	if (!table)
		return ;
	while (table[i])
	{
		free(table[i]);
		i++;
	}
	free(table);
}

void	free_map(t_map *map)
{
	if (!map)
		return ;
	if (map->componements)
	{
		free_table(map->componements);
		map->componements = NULL;
	}
	if (map->north)
		free(map->north);
	if (map->south)
		free(map->south);
	if (map->east)
		free(map->east);
	if (map->west)
		free(map->west);
	free(map);
	map = NULL;
}

void	init_tab(char **param, int size)
{
	int	i;

	i = 0;
	while (i < size)
		param[i++] = NULL;
}

int	free_last(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	free(data->p.raysdistance);
	free_table(data->mymap->map);
	free(data->mymap->north);
	free(data->mymap->south);
	free(data->mymap->east);
	free(data->mymap->west);
	exit(1);
	return (0);
}
