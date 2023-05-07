/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-bakk < iel-bakk@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 22:15:31 by abigeddi          #+#    #+#             */
/*   Updated: 2023/02/05 19:07:14 by iel-bakk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_playerdirection(struct s_data *data, char c)
{
	if (c == 'N')
		data->p.rotationangle = (3 * M_PI) / 2;
	else if (c == 'E')
		data->p.rotationangle = (0 * M_PI);
	else if (c == 'W')
		data->p.rotationangle = (1 * M_PI);
	else if (c == 'S')
		data->p.rotationangle = (M_PI / 2);
}

int	if_frist_condition(char c)
{
	return (c != '1' && c != '0' && c != ' '
		&& c != 'N' && c != 'S'
		&& c != 'W' && c != 'E');
}

int	if_second_condition(char c)
{
	return (c == 'N' || c == 'S' || c == 'W' || c == 'E');
}

int	checkmap_element(struct s_data *data)
{
	int	i;
	int	j;
	int	counter;

	i = -1;
	j = 0;
	counter = 0;
	while (data->mymap->map[++i])
	{
		j = 0;
		while (data->mymap->map[i][j])
		{
			if (if_frist_condition(data->mymap->map[i][j]))
				return (0);
			if (if_second_condition(data->mymap->map[i][j]))
			{
				data->p.pos_x = (j * TILE_SIZE) + (TILE_SIZE / 2);
				data->p.pos_y = (i * TILE_SIZE) + (TILE_SIZE / 2);
				ft_playerdirection(data, data->mymap->map[i][j]);
				counter++;
			}
			j++;
		}
	}
	return (counter == 1);
}

int	check_horizontale(struct s_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->mymap->map[i] != NULL)
	{
		j = 0 ;
		while (data->mymap->map[i][j] != 0)
		{
			if (data->mymap->map[i][j] == ' ' && data->mymap->map[i + 1] != NULL
			&& (data->mymap->map[i + 1][j] != ' ' &&
			data->mymap->map[i + 1][j] != '1'))
				return (printf("%s", "ERROR:    MAP NON VALID "), 0);
			if (data->mymap->map[i][j] == '0' && i == 0)
				return (printf("%s", "ERROR: MAP NON VALID "), 0);
			if (data->mymap->map[i][j] == '0' &&
			(data->mymap->map[i + 1] == NULL
			|| data->mymap->map[i + 1][j] == ' '))
				return (printf("%s", "ERROR: MAP NON VALID "), 0);
			j++;
		}
		i++;
	}
	return (1);
}
