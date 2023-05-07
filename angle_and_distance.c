/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angle_and_distance.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-bakk < iel-bakk@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 16:45:15 by iel-bakk          #+#    #+#             */
/*   Updated: 2023/01/31 16:54:24 by iel-bakk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

double	normalizeangle(double angle)
{
	if (angle < 0)
		angle = (2 * M_PI) + angle;
	if (angle > 2 * M_PI)
		angle = angle - (2 * M_PI);
	return (angle);
}

double	distancebetweenpoints(double x1, double y1, double x2, double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}
