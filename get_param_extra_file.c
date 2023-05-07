/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_param_extra_file.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-bakk < iel-bakk@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 19:59:37 by iel-bakk          #+#    #+#             */
/*   Updated: 2023/02/01 23:49:45 by iel-bakk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ceiling_param_checker(t_map *param, char **str, int *i)
{
	if (param->c)
		get_param_error(param, str, "Error\n: in map00000x000000C");
	param->componements[5] = ft_strdup(str[*i]);
	param->c = 1;
	param->i = *i + 1;
}
