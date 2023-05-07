/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_param_function_file.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-bakk < iel-bakk@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 18:50:12 by iel-bakk          #+#    #+#             */
/*   Updated: 2023/02/01 23:50:44 by iel-bakk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	north_param_checker(t_map *param, char **str, int *i)
{
	if (param->n)
		get_param_error(param, str, "Error\n: in map00000x000000NO");
	param->componements[0] = ft_strdup(str[*i]);
	param->n = 1;
	param->i = *i;
}

void	south_param_checker(t_map *param, char **str, int *i)
{
	if (param->s)
		get_param_error(param, str, "Error\n: in map00000x000000SO");
	param->componements[1] = ft_strdup(str[*i]);
	param->s = 1;
	param->i = *i;
}

void	west_param_checker(t_map *param, char **str, int *i)
{
	if (param->w)
		get_param_error(param, str, "Error\n: in map00000x000000WE");
	param->componements[2] = ft_strdup(str[*i]);
	param->w = 1;
	param->i = *i;
}

void	east_param_checker(t_map *param, char **str, int *i)
{
	if (param->e)
		get_param_error(param, str, "Error\n: in map00000x000000EA");
	param->componements[3] = ft_strdup(str[*i]);
	param->e = 1;
	param->i = *i;
}

void	floor_param_checker(t_map *param, char **str, int *i)
{
	if (param->f)
		get_param_error(param, str, "Error\n: in map00000x000000F");
	param->componements[4] = ft_strdup(str[*i]);
	param->f = 1;
	param->i = *i;
}
