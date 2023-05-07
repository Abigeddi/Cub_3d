/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tab_and_vertical.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-bakk < iel-bakk@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 17:15:46 by iel-bakk          #+#    #+#             */
/*   Updated: 2023/02/02 21:13:53 by iel-bakk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	check_vertical(struct s_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->mymap->map[i])
	{
		j = 0 ;
		while (data->mymap->map[i][j])
		{
			if (data->mymap->map[i][j] == ' ' &&
			(data->mymap->map[i][j + 1] != ' '
			&& data->mymap->map[i][j + 1] != '1'
			&& data->mymap->map[i][j + 1] != '\0'))
				return (printf("%s", "ERROR: MAP NON VALID "), 0);
			if (data->mymap->map[i][j] == '0' &&
			(data->mymap->map[i][j + 1] == ' ' &&
			data->mymap->map[i][j + 1] == '\0'))
				return (printf("%s", "ERROR: MAP NON VALID "), 0);
			j++;
		}
		i++;
	}
	return (1);
}

int	check_tab(struct s_data *data)
{
	if (!checkmap_element(data))
		return (printf("%s\n", "ERROR: UNKNOWN ELEMENT IN THE MAP"), 0);
	if (!check_horizontale(data))
		return (printf("%s", "ERROR: MAP NON VALID "), 0);
	if (!check_vertical(data))
		return (printf("%s", "ERROR: MAP NON VALID "), 0);
	return (1);
}
