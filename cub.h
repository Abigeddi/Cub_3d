/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalazhar <aalazhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 01:46:54 by abigeddi          #+#    #+#             */
/*   Updated: 2022/12/19 21:55:32 by aalazhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
#define CUB_H
# include <mlx.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include <stddef.h>

struct s_player{
    double pos_x;
    double pos_y;
    double radius;
    double fieldAngle;
    double wallStreapWidth;
    double rayAngle;
    int raysNumber;
    int turnDirection;
    int walkDirection;
    double rotationAngle;
    double moveSpeed;
    double rotationSpeed;
    double newPx;
    double newPy;
    double newPPx;
    double newPPy;
    double rayX;
    double rayY;
    double h_dist;
    double v_dist;
    double distance;
    double v_rayx;
    double v_rayy;
    double h_rayx;
    double h_rayy;

};

struct s_img{
    void *ptr;
    int *dataAdress;
    int width;
    int hight;
    int bpp;
    int size_line;
    int endian;
};

typedef struct s_map{
    char    **componements;
    char    **map;
    int tile_size;
    int mapWidth;
    int mapHeight;
    int     n;
    int     s;
    int     w;
    int     e;
    int     f;
    int     c;
    int     i;
} t_map;

typedef struct s_ray
{
    // int xtile;
    // int ytile;
    // int xtylestep;
    // int ytylestep;
    // double xintercept;
    // double yintercept;
    // long xstep;
    // long ystep;
    double distance;
    int  ray_facingdown;
    int  ray_facingup;
    int  ray_facinright;
    int  ray_facinleft;
    double horizhitx;
    double horizhity;
    double vertichitx;
    double vertichity;
    char horizwallcontent;
    char vertiwallcontent;
    double verticdistance;
    double horizdistance;
    int horizwallhit;
    int vertiwallhit;
    int wallhit;
    
}t_ray;

struct s_data{
    long double x;
    long double y;
    int win_width;
    int win_hight;
    void *mlx_ptr;
    void *win_ptr;
    struct s_img img;
    struct s_img img2;
    struct s_img img3;
    struct s_player p;
    t_map myMap;
    t_ray ray;
} t_data;





char	**ft_free(char **copy, int j);
void	ft_putendl_fd(char *s, int fd);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*get_next_line(int fd);
void	check_file(char *s);
char	**store_map(char *map);
char	**ft_split(char const *s, char c);
// testing
char    **get_map(char *str);
int checkmap(char **map);

// jesus
t_map	*init_map(void);
t_map	*get_param(char **str);
int checkpath(char *str);
int check_map(char **str);
char **stor_tab(char **str);
int check_tab(struct s_data *data);
int checkmap_element(struct s_data *data);

// Hooks

int k_hook(int key, struct s_data *data);
int release_k_hook(int key, struct s_data *data);
int close_window(int key, struct s_data *data);

// draw

void dda_Algo(struct s_data *data, int indice);
int circleDraw(struct s_data *data);
int drawMyMap(struct s_data *data);
int wallIsHited(double x, double y, struct s_data *data);
void DDA(struct s_data *data, int indice);
void DDA2(struct s_data *data, int indice);
void drawRays(struct s_data *data);
// void horizontal_inter(struct s_data *data);
// void vertical_inter(struct s_data *data);

// libft

int	ft_atoi(const char *str);
int	ft_isdigit(int c);
int	ft_strncmp(const char *s1,const char *s2, int n);
void	ft_putendl_fd(char *s, int fd);
size_t	ft_strlen(const char *s);

void horizontal_intersection(struct s_data *data);
void vertical_intersection(struct s_data *data);
double distancebetweenpoints(double x1, double y1, double x2, double y2);
void normalizeAngle(struct s_data *data);
void ray_facing(struct s_data *data);
#endif