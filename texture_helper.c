/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-bakk < iel-bakk@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 18:35:18 by iel-bakk          #+#    #+#             */
/*   Updated: 2023/02/02 21:17:44 by iel-bakk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	get_xpm_void_address(char **texture, t_map *map, void *mlx)
{
	map->north->ptr = mlx_xpm_file_to_image(mlx, texture[0],
			&map->north->width, &map->north->height);
	map->south->ptr = mlx_xpm_file_to_image(mlx, texture[1],
			&map->south->width, &map->south->height);
	map->west->ptr = mlx_xpm_file_to_image(mlx, texture[2],
			&map->west->width, &map->west->height);
	map->east->ptr = mlx_xpm_file_to_image(mlx, texture[3],
			&map->east->width, &map->east->height);
}

void	get_xpm_int_address(t_map *map)
{
	map->north->address = (int *)mlx_get_data_addr(map->north->ptr,
			&map->north->bits_per_pixel, &map->north->size_line,
			&map->north->endian);
	map->south->address = (int *)mlx_get_data_addr(map->south->ptr,
			&map->south->bits_per_pixel, &map->south->size_line,
			&map->south->endian);
	map->west->address = (int *)mlx_get_data_addr(map->west->ptr,
			&map->west->bits_per_pixel, &map->west->size_line,
			&map->west->endian);
	map->east->address = (int *)mlx_get_data_addr(map->east->ptr,
			&map->east->bits_per_pixel, &map->east->size_line,
			&map->east->endian);
}

int	check_texture(char **texture, t_map *map, void *mlx)
{
	if (check_north(texture) || check_south(texture)
		|| check_east(texture) || check_west(texture))
		return (1);
	get_xpm_void_address(texture, map, mlx);
	if (!map->south->ptr || !map->north->ptr
		|| !map->west->ptr || !map->east->ptr)
		return (1);
	get_xpm_int_address(map);
	if (!map->south->address || !map->north->address
		|| !map->west->address || !map->east->address)
		return (printf("3\n"), free_table(texture), 1);
	map->celling = get_rgb(texture[4]);
	map->floor = get_rgb(texture[5]);
	free_table(texture);
	return (0);
}

unsigned long	combine_rgb(int red, int green, int blue)
{
	return (((red & 0xff) << 16) + ((green & 0xff) << 8) + (blue & 0xff));
}

int	check_color(char *color)
{
	int	i;

	i = 0;
	if (!color || !*color)
		return (1);
	while (color[i])
	{
		if (color[i] && color[i] == ',' && i > 0
			&& color[i + 1] && ft_isdigit(color[i + 1]))
			i++;
		else if (color[i] && ft_isdigit(color[i]))
			i++;
		else
			return (1);
	}
	return (0);
}
