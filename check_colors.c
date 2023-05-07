/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-bakk < iel-bakk@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 20:29:05 by iel-bakk          #+#    #+#             */
/*   Updated: 2023/02/01 20:29:36 by iel-bakk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	check_colors(char *str)
{
	char	**res;
	char	**tmp;
	int		i;

	i = 0;
	res = ft_split(str, ' ');
	if (!res[i])
		return (printf("ERROR:"), exit(1), 0);
	tmp = ft_split(res[1], ',');
	while (tmp[i])
		i++;
	if (i != 3)
		return (printf("ERROR: too few argument for rgb"), exit(1), 0);
	if (!check_nb(tmp))
		return (exit(1), 0);
	return (1);
}
