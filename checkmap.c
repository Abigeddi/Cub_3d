/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkmap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abigeddi <abigeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 16:47:30 by abigeddi          #+#    #+#             */
/*   Updated: 2022/12/13 17:53:52 by abigeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
int check_nb(char **str)
{
	int i = 0;
	int j = 0;
	while (str[i])
	{
		if (ft_atoi(str[i]) < 0 || ft_atoi(str[i]) > 255)
				return (printf("ERROR: number lower or higher"),exit(1),0);
		j=0;
		while (str[i][j])
		{
			if (ft_isdigit(str[i][j]))
				j++;
			else
				return (printf("ERROR: syntaxe error colors"),exit(1),0);
		}
		i++;
	}
	return (1);
}
int check_colors(char *str)
{
	char **res;
	char **tmp;
	int i = 0;
	res = ft_split(str,' ');
	if (!res[i])
		return (printf("ERROR:"),exit(1),0);
	tmp = ft_split(res[1], ',');
	while (tmp[i])
		i++;
	if (i != 3)
		return (printf("ERROR: too few argument for rgb"),exit(1),0);
	if (!check_nb(tmp))
		return (exit(1),0);
	return (1);
}

int checkpath(char *str)
{
	char **res;
	int j = 0;
	int i = 0;
	res = ft_split(str,' ');
	while (res[i])
		i++;
	if (i != 2)
		return (printf ("too few for rgb"),exit (1),0);
	if (!res[0])
		return (printf("ERROR: not splited"),exit(1),0);
	j = ft_strlen(res[1]);
	return (ft_strncmp(&res[1][j - 4], ".xpm", 3));	

}

t_map	*get_param(char **str)
{
	int		i;
	int		j;
	t_map *param;

	i = 0;
	j = 0;
	param = init_map();
	while (str[i])
	{
		if (str[i][j] == 'N' && str[i][j + 1] == 'O')
		{
			if (param->n)
				return(free(param->componements), free(param),printf("Error in map00000x000000NO\n"), NULL);
			param->componements[0] = ft_strdup(str[i]);
			param->n = 1;
			param->i = i;
		}
		else if (str[i][j] == 'S' && str[i][j + 1] == 'O')
		{
			if (param->s)
				return(free(param->componements), free(param),printf("Error in map00000x000000SO\n"), NULL);
			param->componements[1] = ft_strdup(str[i]);
			param->s = 1;
			param->i = i;
		}
		else if (str[i][j] == 'W' && str[i][j + 1] == 'E')
		{
			if (param->w)
				return(free(param->componements), free(param),printf("Error in map00000x000000WE\n"), NULL);
			param->componements[2] = ft_strdup(str[i]);
			param->w = 1;
			param->i = i;
		}
		else if (str[i][j] == 'E' && str[i][j + 1] == 'A')
		{
			if (param->e)
				return(free(param->componements), free(param),printf("Error in map00000x000000EA\n"), NULL);
			param->componements[3] = ft_strdup(str[i]);
			param->e = 1;
			param->i = i;
		}
		else if (str[i][j] == 'F')
		{
			if (param->f)
				return(free(param->componements), free(param),printf("Error in map00000x000000F\n"), NULL);
			param->componements[4] = ft_strdup(str[i]);
			param->f = 1;
			param->i = i;
		}
		else if (str[i][j] == 'C')
		{
			if (param->c)
				return(free(param->componements), free(param),printf("Error in map00000x000000C\n"), NULL);
			param->componements[5] = ft_strdup(str[i]);
			param->c = 1;
			param->i = i + 1;
		}
		i++;
	}
	if (param->c == 0 || param->e == 0 || param->f == 0 || param->n == 0 || param->s == 0 || param->w == 0)
		return(free(param->componements), free(param),printf("Error  : less information\n"), NULL);
	return (param);
}

t_map	*init_map(void)
{
	t_map	*param;
	param = (t_map *)malloc(sizeof(t_map));
	if (!param)
		return(printf("ERROR !!\n"), NULL);
	param->c = 0;
	param->n = 0;
	param->e = 0;
	param->w = 0;
	param->f = 0;
	param->s = 0;
	param->i = 0;
	param->componements = (char **)malloc(sizeof(char *) * 6);
	if (!param->componements)
	{
		free(param);
		return(printf("ERROR !!\n"), NULL);
	}
	return (param);
}

int checkmap(char **map)
{
	int	i;
	int	j;
	t_map *param;
	
	i = 0;
	j = 0;
	param = get_param(map);
	if (!param)
		exit(1);
	
	// printf("i == %d\n", param->i);
	while (i < 4)
	{
		if (checkpath (param->componements[i]) == 1)
			i++;
		else
			return (printf ("ERROR : invalid texture link "),exit(1),0);
	}
	while (i < 6)
	{
		if (check_colors(param->componements[i]))
			i++;
		else 
			return (printf ("ERROR : colors aarguments wrong"),exit(1),0);
	}
	// i = 0;
	// while (i < 6)
	// 	printf ("%s", param->componements[i++]);
	i = 0;
	return (1);
	// i = 0;
	// while (map[i][0] != '1' && map[i][0] !=' ')
	// 	i++;
	// while (map[i][j])
    // {
    //     printf("%s\n", );
    //     i++;
    // }
}

char	**store_map(char *map)
{
	int		fd;
	char	*line;
	char	*all_lines;
	char	**res;

	line = "";
	all_lines = NULL;
	fd = open(map, O_RDONLY);
	if (fd < 0)
		return (write(2, "Error: invalid file descriptor\n", 31), exit(1), NULL);
	while (line)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		all_lines = ft_strjoin(all_lines, line);
		free (line);
	}
	free (line);
	close (fd);
	if (all_lines[0] == '\0')
		return (write(2, "Error:no map readed\n", 22), exit(1), NULL);
	res = ft_split(all_lines, '\n');
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

