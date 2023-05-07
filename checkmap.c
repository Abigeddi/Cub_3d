/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkmap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-bakk < iel-bakk@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 16:47:30 by abigeddi          #+#    #+#             */
/*   Updated: 2023/02/02 16:48:59 by iel-bakk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	check_nb(char **str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (ft_atoi(str[i]) < 0 || ft_atoi(str[i]) > 255)
			return (printf("ERROR: number lower or higher"), exit(1), 0);
		j = 0;
		while (str[i][j])
		{
			if (ft_isdigit(str[i][j]))
				j++;
			else
				return (printf("ERROR: syntaxe error colors"), exit(1), 0);
		}
		i++;
	}
	return (1);
}

int	checkpath(char *str)
{
	char	**res;
	int		j;
	int		i;

	i = 0;
	j = 0;
	res = ft_split(str, ' ');
	while (res[i])
		i++;
	if (i != 2)
		return (printf ("too few for rgb"), exit (1), 0);
	if (!res[0])
		return (printf("ERROR: not splited"), exit(1), 0);
	j = ft_strlen(res[1]);
	return (ft_strncmp(&res[1][j - 4], ".xpm", 3));
}

void	get_param_error(t_map *param, char **str, char *msg)
{
	if (str)
	{
		free_table(str);
		str = NULL;
	}
	if (param)
	{
		free_map(param);
		param = NULL;
	}
	printf("%s\n", msg);
	exit(EXIT_FAILURE);
}

void	get_param(t_map	*param, char **str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i][j] == 'N' && str[i][j + 1] == 'O')
			north_param_checker(param, str, &i);
		else if (str[i][j] == 'S' && str[i][j + 1] == 'O')
			south_param_checker(param, str, &i);
		else if (str[i][j] == 'W' && str[i][j + 1] == 'E')
			west_param_checker(param, str, &i);
		else if (str[i][j] == 'E' && str[i][j + 1] == 'A')
			east_param_checker(param, str, &i);
		else if (str[i][j] == 'F')
			floor_param_checker(param, str, &i);
		else if (str[i][j] == 'C')
			ceiling_param_checker(param, str, &i);
		i++;
	}
	param->componements[6] = NULL;
	if (param->c == 0 || param->e == 0 || param->f == 0
		|| param->n == 0 || param->s == 0 || param->w == 0)
		get_param_error(NULL, str, "Error : need more informations please");
}

t_map	*init_map(void)
{
	t_map	*param;

	param = (t_map *)malloc(sizeof(t_map));
	if (!param)
		return (printf("ERROR !!\n"), NULL);
	param->c = 0;
	param->n = 0;
	param->e = 0;
	param->w = 0;
	param->f = 0;
	param->s = 0;
	param->i = 0;
	param->celling = 0;
	param->floor = 0;
	param->north = new_image_struct();
	param->east = new_image_struct();
	param->south = new_image_struct();
	param->west = new_image_struct();
	param->map = NULL;
	param->componements = (char **)malloc(sizeof(char *) * 7);
	if (!param->componements)
		return (free(param), printf("ERROR !!\n"), NULL);
	init_tab(param->componements, 7);
	return (param);
}
