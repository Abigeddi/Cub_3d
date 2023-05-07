/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-bakk < iel-bakk@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 01:46:54 by abigeddi          #+#    #+#             */
/*   Updated: 2023/02/05 19:03:59 by iel-bakk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <mlx.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include <stddef.h>

# define TILE_SIZE 32
# define BUFFER_SIZE 1

typedef struct s_player{
	double	pos_x;
	double	pos_y;
	double	radius;
	double	fieldangle;
	double	wallstreapwidth;
	double	rayangle;
	int		raysnumber;
	int		turndirection;
	int		walkdirection;
	int		slidedirection;
	double	rotationangle;
	double	movespeed;
	double	rotationspeed;
	double	newpx;
	double	newpy;
	double	newppx;
	double	newppy;
	double	rayx;
	double	rayy;
	double	h_dist;
	double	v_dist;
	double	v_rayx;
	double	v_rayy;
	double	h_rayx;
	double	h_rayy;
	double	*raysdistance;
	double	distanceprojectplane;
	double	wallstreaphight;
}	t_player;

typedef struct s_inter
{
	double	xstep;
	double	ystep;
	double	xintersect;
	double	yintersect;
	double	firstx;
	double	firsty;
}	t_inter;

typedef struct s_img
{
	void	*ptr;
	int		*dataadress;
	int		width;
	int		hight;
	int		bpp;
	int		size_line;
	int		endian;
}	t_img;

typedef struct s_draw_tool
{
	int	ppdistance;
	int	wstripheight;
	int	height;
	int	ceiling;
	int	color;
	int	tmp;
	int	oofx;
	int	oofy;
}	t_draw_tool;

typedef struct s_xpm
{
	void	*ptr;
	int		*address;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		endian;
	int		size_line;
}	t_xpm;

typedef struct s_map
{
	char	**componements;
	char	**map;
	int		tile_size;
	int		mapwidth;
	int		mapheight;
	int		n;
	int		s;
	int		w;
	int		e;
	int		f;
	int		c;
	int		i;
	int		floor;
	int		celling;
	t_xpm	*north;
	t_xpm	*south;
	t_xpm	*west;
	t_xpm	*east;
}	t_map;

typedef struct s_rect{
	double	top;
	double	left;
	double	right;
	double	down;
}	t_rect;

typedef struct s_j_img{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		offset;
}	t_j_img;

typedef struct s_data{
	int					win_width;
	int					win_hight;
	void				*mlx_ptr;
	void				*win_ptr;
	t_map				*mymap;
	struct s_img		img;
	struct s_img		img2;
	struct s_img		img3;
	struct s_player		p;
	struct s_inter		interh;
	struct s_inter		interv;
	struct s_rect		rect;
	t_j_img				render;
}	t_data;

typedef struct s_dda{
	int		dx;
	int		dy;
	int		steps;
	int		i;
	double	xinc;
	double	yinc;
	double	x;
	double	y;
}	t_dda;

// init data functions

void			init_data(struct s_data *data, char *param);
void			init_data_helper(struct s_data *data);

// parsing and string manipulation functions

char			**ft_free(char **copy, int j);
void			ft_putendl_fd(char *s, int fd);
char			*ft_substr(char const *s, unsigned int start, size_t len);
size_t			ft_strlen(const char *s);
char			*ft_strdup(const char *s);
char			*ft_strjoin(char *s1, char *s2);
char			*get_next_line(int fd);
void			check_file(char *s);
char			**store_map(char *map);
char			**ft_split(char const *s, char c);
char			**get_map(char *str);
int				checkmap(char **map);
// jesus

t_map			*init_map(void);
void			get_param(t_map *param, char **str);
int				checkpath(char *str);
int				check_map(char **str);
char			**stor_tab(char **str);
int				check_tab(struct s_data *data);
int				checkmap_element(struct s_data *data);

// Hooks

int				k_hook(int key, struct s_data *data);
int				release_k_hook(int key, struct s_data *data);
int				close_window(int key, struct s_data *data);
void			call_mouvement(t_data *data);

// draw

void			dda_Algo(struct s_data *data, int indice);
int				circledraw(struct s_data *data);
int				drawmymap(struct s_data *data);
int				wallishited(double x, double y, struct s_data *data);
void			dda(struct s_data *data, int indice);
void			dda2(struct s_data *data, int indice);
void			drawrays(struct s_data *data);

// libft

int				ft_atoi(const char *str);
int				ft_isdigit(int c);
int				ft_strncmp(const char *s1, const char *s2, int n);
void			ft_putendl_fd(char *s, int fd);
size_t			ft_strlen(const char *s);

void			horizontal_intersection(struct s_data *data);
void			vertical_intersection(struct s_data *data);
double			distancebetweenpoints(double x1, double y1,
					double x2, double y2);
double			normalizeangle(double angle);
void			ray_facing(struct s_data *data);

// horiz intersection
int				check_horizontale(struct s_data *data);
void			upright_hintersect(struct s_data *data);
void			downright_hintersect(struct s_data *data);
void			downleft_hintersect(struct s_data *data);
void			upleft_hintersect(struct s_data *data);

// verti intersection

void			upright_vintersect(struct s_data *data);
void			downright_vintersect(struct s_data *data);
void			downleft_vintersect(struct s_data *data);
void			upleft_vintersect(struct s_data *data);

// jesus render tests

void			create_image(t_j_img *img, void *mlx, int width, int height);
void			my_mlx_pixel_put(t_j_img *data, int x, int y, int color);
void			drawheight(struct s_data *data, int i, int intersect);

//keys functions

void			right_left_arrow(struct s_data *data);
void			left_arrow(struct s_data *data);
// void			a_key(struct s_data *data, double *movestep);
void			sliding_key(struct s_data *data);
// void			w_key(struct s_data *data, double *movestep);
void			front_back_key(struct s_data *data);

// text functions

int				check_texture(char **texture, t_map *map, void *mlx);
int				check_north(char **texture);
int				check_south(char **texture);
int				check_west(char **texture);
int				check_east(char **texture);
t_xpm			*new_image_struct(void);
t_map			*texture_init(char *file, struct s_data *data);
void			check_width_hight(struct s_data *data);
unsigned long	combine_rgb(int red, int green, int blue);
int				get_rgb(char *rgb);
int				check_color(char *color);
int				checkmap_element(struct s_data *data);
int				if_second_condition(char c);
int				if_frist_condition(char c);
void			ft_playerdirection(struct s_data *data, char c);
void			get_xpm_void_address(char **texture, t_map *map, void *mlx);
void			get_xpm_int_address(t_map *map);
void			north_param_checker(t_map *param, char **str, int *i);
void			south_param_checker(t_map *param, char **str, int *i);
void			west_param_checker(t_map *param, char **str, int *i);
void			east_param_checker(t_map *param, char **str, int *i);
void			floor_param_checker(t_map *param, char **str, int *i);
void			ceiling_param_checker(t_map *param, char **str, int *i);
void			get_param_error(t_map *param, char **str, char *msg);
void			store_map_helper(char **line, char **all_lines, char **tmp,
					int fd);
int				check_nb(char **str);

// free	functions

void			free_table(char **table);
void			free_map(t_map *map);
void			init_tab(char **param, int size);
int				wall_coalision(double x, double y, struct s_data *data);
int				play_game(void *param);
int				free_last(t_data *data);
#endif