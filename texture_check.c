/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-bakk < iel-bakk@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:51:56 by iel-bakk          #+#    #+#             */
/*   Updated: 2023/02/05 16:51:26 by iel-bakk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	get_rgb(char *rgb)
{
	char	**colors;
	char	**first_split;
	int		red;
	int		green;
	int		blue;

	first_split = ft_split(rgb, ' ');
	if (first_split[2] != NULL)
		return (printf("ERROR: Invalid\n"), 0);
	if (check_color(first_split[1]))
		return (free_table(first_split), printf("not valid rgb\n"), exit(1), 0);
	colors = ft_split(first_split[1], ',');
	red = ft_atoi(colors[0]);
	green = ft_atoi(colors[1]);
	blue = ft_atoi(colors[2]);
	if (red < 0 || red > 255 || green < 0
		|| green > 255 || blue < 0 || blue > 255)
		return (free_table(first_split),
			free_table(colors), printf("Invalid RGB color\n"), exit (1), 1);
	free_table(colors);
	free_table(first_split);
	return ((int)combine_rgb(red, green, blue));
}

int	check_north(char **texture)
{
	char	**north;
	int		len;

	north = ft_split(texture[0], ' ');
	if (!north)
		return (1);
	len = 0;
	while (north[len])
		len++;
	if (len != 2)
		return (free_table(north), 1);
	free(texture[0]);
	texture[0] = NULL;
	texture[0] = ft_strdup(north[1]);
	free_table(north);
	return (0);
}

int	check_south(char **texture)
{
	char	**south;
	int		len;

	south = ft_split(texture[1], ' ');
	if (!south)
		return (1);
	len = 0;
	while (south[len])
		len++;
	if (len != 2)
		return (free_table(south), 1);
	free(texture[1]);
	texture[1] = NULL;
	texture[1] = ft_strdup(south[1]);
	free_table(south);
	return (0);
}

int	check_west(char **texture)
{
	char	**west;
	int		len;

	west = ft_split(texture[2], ' ');
	if (!west)
		return (1);
	len = 0;
	while (west[len])
		len++;
	if (len != 2)
		return (free_table(west), 1);
	free(texture[2]);
	texture[2] = NULL;
	texture[2] = ft_strdup(west[1]);
	free_table(west);
	return (0);
}

int	check_east(char **texture)
{
	char	**east;
	int		len;

	east = ft_split(texture[3], ' ');
	if (!east)
		return (1);
	len = 0;
	while (east[len])
		len++;
	if (len != 2)
		return (free_table(east), 1);
	free(texture[3]);
	texture[3] = NULL;
	texture[3] = ft_strdup(east[1]);
	free_table(east);
	return (0);
}
