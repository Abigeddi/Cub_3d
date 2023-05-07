/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-bakk < iel-bakk@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 16:58:45 by abigeddi          #+#    #+#             */
/*   Updated: 2023/02/02 21:29:30 by iel-bakk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

char	*fct2(char *s, int size)
{
	char	*rs;
	int		i;

	i = 0;
	rs = malloc(sizeof (char) * (size + 1));
	if (!rs)
		return (printf("%s\n", "ERROR : allocation failed"), exit(1), NULL);
	while (s[i])
	{
		rs[i] = s[i];
		i++;
	}
	while (i < size)
	{
		rs[i] = ' ';
		i++;
	}
	rs[i] = '\0';
	return (rs);
}

char	**fct(char **str, int start, int end, int size)
{
	int		i;
	char	**tmp;
	int		s;

	i = 0;
	tmp = (char **)malloc(sizeof(char *) * (end - start + 1));
	if (!tmp)
		return (printf("%s\n", "ERROR : allocation failed"), exit(1), NULL);
	s = start;
	while (i < end - start)
		tmp[i++] = fct2(str[s++], size);
	tmp[i] = NULL;
	return (tmp);
}

char	**stor_tab(char **str)
{
	int		i;
	int		j;
	size_t	k;

	i = 0;
	k = 0;
	while (str[i] && str[i][0] != '0' && str[i][0] != '1' && str[i][0] != ' ')
		i++;
	j = i;
	while (str[i] != NULL)
	{
		if (ft_strlen(str[i]) > k)
			k = ft_strlen(str[i]);
		i++;
	}
	return (fct(str, j, i, k));
}
