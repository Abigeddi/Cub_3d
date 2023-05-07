/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkmap_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-bakk < iel-bakk@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 20:21:35 by iel-bakk          #+#    #+#             */
/*   Updated: 2023/02/03 18:08:55 by iel-bakk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	store_map_helper(char **line, char **all_lines, char **tmp, int fd)
{
	int	nl;

	nl = 0;
	*all_lines = ft_strjoin(*all_lines, *line);
	free(*line);
	while (*line)
	{
		*line = get_next_line(fd);
		if (*line == NULL)
			break ;
		if (nl == 2 && *line[0] == '1')
			return ;
		if (*line[0] == '1')
			nl = 1;
		if (*line[0] == '\n' && nl == 1)
			nl = 2;
		*tmp = *all_lines;
		*all_lines = ft_strjoin(*all_lines, *line);
		free(*tmp);
		free (*line);
	}
}

char	**store_map(char *map)
{
	int		fd;
	char	*line;
	char	*all_lines;
	char	**res;
	char	*tmp;

	all_lines = NULL;
	line = NULL;
	fd = open(map, O_RDONLY);
	if (fd < 0)
		return (write(2, "Error: invalid file descriptor\n", 31), NULL);
	line = get_next_line(fd);
	if (!line || *line == '\0')
		return (close(fd), NULL);
	store_map_helper(&line, &all_lines, &tmp, fd);
	free (line);
	close (fd);
	if (all_lines[0] == '\0')
		return (write(2, "Error: in map\n", 14), close(fd), exit(1), NULL);
	res = ft_split(all_lines, '\n');
	free(all_lines);
	return (res);
}

int	check_file_type(char *s, char *type)
{
	int	i;

	i = 0;
	while (type[i])
	{
		if (type[i] != s[i])
			return (0);
		i++;
	}
	if (s[i] == '\0')
		return (1);
	return (0);
}

void	check_file(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '.')
		{
			if (check_file_type(s + i, ".cub"))
				return ;
		}
		i++;
	}
	write(2, "ERROR: invalid file type\n", 26);
	exit(1);
}

t_xpm	*new_image_struct(void)
{
	t_xpm	*image;

	image = (t_xpm *)malloc(sizeof(t_xpm));
	if (image == NULL)
		return (NULL);
	image->address = NULL;
	image->ptr = NULL;
	return (image);
}
