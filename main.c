/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-bakk < iel-bakk@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 01:46:32 by abigeddi          #+#    #+#             */
/*   Updated: 2023/02/03 18:20:52 by iel-bakk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	wall_coalision(double x, double y, struct s_data *data)
{
	if (data->mymap->map[(int)floor((y + 0.2)
				/ TILE_SIZE)][(int)floor(x / TILE_SIZE)] == '1')
		return (1);
	if (data->mymap->map[(int)floor(y - 0.2)
			/ TILE_SIZE][(int)floor(x / TILE_SIZE)] == '1')
		return (1);
	if (data->mymap->map[(int)floor(y / TILE_SIZE)]
		[(int)floor((x + 0.2) / TILE_SIZE)] == '1')
		return (1);
	if (data->mymap->map[(int)floor(y / TILE_SIZE)]
		[(int)floor((x - 0.2) / TILE_SIZE)] == '1')
		return (1);
	return (0);
}

char	**get_map(char *str)
{
	char	**map;

	check_file(str);
	map = store_map(str);
	if (!map || *map == '\0')
		return (NULL);
	return (map);
}

void	check_width_hight(struct s_data *data)
{
	int		i;
	size_t	k;

	i = 0;
	k = 0;
	while (data->mymap->map[i])
	{
		if (k < ft_strlen(data->mymap->map[i]))
			data->mymap->mapwidth = ft_strlen(data->mymap->map[i]);
		i++;
	}
	data->mymap->mapheight = i;
}

int	wallishited(double x, double y, struct s_data *data)
{
	int	imapx;
	int	imapy;

	imapx = floor(x / TILE_SIZE);
	imapy = floor(y / TILE_SIZE);
	if (x >= 0 && x <= data->win_width && y >= 0
		&& (imapy <= data->mymap->mapheight && imapy >= 0))
	{
		if (data->mymap->map[imapy] && (data->mymap->map[imapy][imapx] == '0'
			|| data->mymap->map[imapy][imapx] == 'N'
			|| data->mymap->map[imapy][imapx] == 'S'
			|| data->mymap->map[imapy][imapx] == 'W'
			|| data->mymap->map[imapy][imapx] == 'E')
			&& (data->mymap->map[imapy][imapx] != '1'))
			return (0);
	}
	return (2);
}

int	main(int ac, char **av)
{
	struct s_data	data;

	if (ac != 2)
		return (printf("invalid arguments!!\n"), 1);
	init_data(&data, av[1]);
	mlx_hook(data.win_ptr, 2, 0, k_hook, &data);
	mlx_hook(data.win_ptr, 3, 0, release_k_hook, &data);
	mlx_hook(data.win_ptr, 17, 0, &free_last, &data);
	mlx_loop_hook(data.mlx_ptr, &play_game, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
