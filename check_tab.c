/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalazhar <aalazhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 22:15:31 by abigeddi          #+#    #+#             */
/*   Updated: 2022/12/22 00:37:43 by aalazhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void ft_playerdirection(struct s_data *data, char c)
{
    if (c =='N')
        data->p.rotationAngle = (3 * M_PI) / 2;
    else if (c =='E')
        data->p.rotationAngle = (0 * M_PI);
    else if (c =='W')
        data->p.rotationAngle = (1 * M_PI);
    else if (c == 'S')
        data->p.rotationAngle = (M_PI) / 2;    
}

int checkmap_element(struct s_data *data)
{
    int i;
    int j;
    int counter;

    i = 0;
    j = 0;
    counter = 0;
    while (data->myMap.map[i])
    {
        j = 0;
        while(data->myMap.map[i][j])
        {
            if (data->myMap.map[i][j] != '1' && data->myMap.map[i][j] != '0' && data->myMap.map[i][j] != ' ' && data->myMap.map[i][j] != 'F' &&
                data->myMap.map[i][j] != 'N' && data->myMap.map[i][j] != 'S' && data->myMap.map[i][j] != 'W' && data->myMap.map[i][j] != 'E')
                    return (0);
            if (data->myMap.map[i][j] == 'N' || data->myMap.map[i][j] == 'S' || data->myMap.map[i][j] == 'W' || data->myMap.map[i][j] == 'E'){
                data->p.pos_x = (j * TILE_SIZE) + (TILE_SIZE / 2);
                data->p.pos_y = (i * TILE_SIZE) + (TILE_SIZE / 2);
                ft_playerdirection(data, data->myMap.map[i][j]);
                counter++;
            }
            j++;
        }
        i++;
    }
    if (counter != 1)
        return (0);
    return (1);
}

int check_horizontale(struct s_data *data)
{
	int i = 0;
	int j = 0 ;

	while (data->myMap.map[i] != NULL)
	{
		j = 0 ;
		while(data->myMap.map[i][j] != 0)
		{
			if (data->myMap.map[i][j] == ' ' && data->myMap.map[i + 1] != NULL && (data->myMap.map[i + 1][j] != ' ' && data->myMap.map[i + 1][j] != '1'))
				return (printf("%s","ERROR:    MAP NON VALID "), 0);
			if (data->myMap.map[i][j] == '0' && i == 0)
				return (printf("%s","ERROR: MAP NON VALID "), 0);
			if (data->myMap.map[i][j] == '0' && (data->myMap.map[i + 1] == NULL || data->myMap.map[i + 1][j] == ' '))
				return (printf("%s","ERROR: MAP NON VALID "), 0);
			j++;
		}
		i++;
	}
	return (1);
}

int check_vertical(struct s_data *data)
{
	int	i;
	int 	j;

	i = 0;
	while (data->myMap.map[i])
	{
		j = 0 ;
		while (data->myMap.map[i][j])
		{
			if (data->myMap.map[i][j] == ' ' && (data->myMap.map[i][j + 1] != ' ' && data->myMap.map[i][j + 1] != '1' && data->myMap.map[i][j + 1] != '\0'))
				return (printf("%s","ERROR: MAP NON VALID "), 0);
			if (data->myMap.map[i][j] == '0' && (data->myMap.map[i][j + 1] == ' ' && data->myMap.map[i][j + 1] == '\0'))
				return (printf("%s","ERROR: MAP NON VALID "), 0);
			j++;
		}
		i++;
	}
	return (1);
}

int check_tab(struct s_data *data)
{
    if (!checkmap_element(data))
        return (printf("%s\n","ERROR: UNKNOWN WLWMWNT IN THE MAP"), 0);
    if (!check_horizontale(data))
        return (printf("%s","ERROR: MAP NON VALID "), 0);
    if (!check_vertical(data))
        return (printf("%s","ERROR: MAP NON VALID "),0);
    return (1);
}