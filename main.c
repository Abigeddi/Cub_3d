// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   main.c                                             :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: abigeddi <abigeddi@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2022/11/26 01:46:32 by abigeddi          #+#    #+#             */
// /*   Updated: 2022/12/03 14:17:37 by abigeddi         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "cub.h"

char    **get_map(char *str)
{
    char   **map;

    map = (char **)malloc(sizeof(char *));
    if (!map)
        return (NULL);
    check_file(str);
    map = store_map(str);
    if (!map)
        return (NULL);
    return (map);
}

void init_data(struct s_data *data){
    // data->win_width = data->myMap.mapWidth * TILE_SIZE;
    // data->win_hight = data->myMap.mapHeight * TILE_SIZE;
    data->win_width = 1200;
    data->win_hight = 1200;
    // printf("%d\n", data->win_width);
    // printf("%d\n", data->win_hight);
    // exit(1);
    data->p.moveSpeed = 4;
    data->p.turnDirection = 0;
    data->p.walkDirection = 0;
    data->myMap.tile_size = TILE_SIZE;
    data->p.newPx = data->p.pos_x + cos(data->p.rotationAngle) * 30;
    data->p.newPy = data->p.pos_y + sin(data->p.rotationAngle) * 30;
    data->p.fieldAngle = 60 * (M_PI / 180);
    data->p.rotationSpeed = 4 * (M_PI / 180);
    data->p.wallStreapWidth = 1;
    data->p.raysNumber = data->win_width / data->p.wallStreapWidth;
    data->p.rayAngle = data->p.rotationAngle - (data->p.fieldAngle / 2);
    data->img.hight = TILE_SIZE;
    data->img.width = TILE_SIZE;
    data->p.raysDistance = malloc(sizeof(double) * data->p.raysNumber);
    if (!data->p.raysDistance)
        return;
    data->p.wallStreapHight = 0;
    data->p.distanceProjectPlane = 0;
    data->mlx_ptr = mlx_init();
    data->win_ptr = mlx_new_window(data->mlx_ptr, data->win_width, data->win_hight, "test");
    data->img.ptr = mlx_xpm_file_to_image(data->mlx_ptr, "./pics/g.xpm", &data->img.width, &data->img.hight);
    data->img.dataAdress = (int *)mlx_get_data_addr(data->img.ptr, &data->img.bpp, &data->img.size_line, &data->img.endian);
    data->img2.ptr = mlx_xpm_file_to_image(data->mlx_ptr, "./pics/w.xpm", &data->img.width, &data->img.hight);
    data->img2.dataAdress = (int *)mlx_get_data_addr(data->img2.ptr, &data->img2.bpp, &data->img2.size_line, &data->img2.endian);
    data->img3.ptr = mlx_xpm_file_to_image(data->mlx_ptr, "./pics/r.xpm", &data->img.width, &data->img.hight);
    data->img3.dataAdress = (int *)mlx_get_data_addr(data->img3.ptr, &data->img3.bpp, &data->img3.size_line, &data->img3.endian);
}

void rectangleDraw(struct s_data *data, int i){
    int k = 0;
    int j = 0;

    double dis = 0;
    // printf("-hight- %f\n", data->p.wallStreapHight);
    // printf("-width- %f\n", data->p.wallStreapWidth);
    dis = (data->p.wallStreapHight / 2) - (data->win_hight / 2);
    while (k < data->p.wallStreapHight){
        j  = 0;

        while (j < data->p.wallStreapWidth){

            if (dis <  0)
                dis *= -1;
            // printf("x -- %d\n", j + i);
            // printf("y -- %f\n", dis );
            mlx_pixel_put(data->mlx_ptr, data->win_ptr, j + i  , k + dis , 0xFEB913);
            j++;
        }
        k++;
    }
}
void render3D(struct s_data *data ,int i){

    double d_ray = 0;

    d_ray = data->p.raysDistance[i];
    
    data->p.distanceProjectPlane = (data->win_width / 2) / fabs(tan(data->p.fieldAngle / 2));
    data->p.wallStreapHight = (TILE_SIZE / d_ray) * data->p.distanceProjectPlane;
}

void drawRays(struct s_data *data){
    
    int i = -1;
    double limit;
    double tmp;
    data->p.rayAngle = data->p.rotationAngle - (data->p.fieldAngle / 2);
    tmp = data->p.rayAngle * (180 / M_PI);
    limit = data->p.fieldAngle * (180 / M_PI) + tmp; 
    while (++i < data->p.raysNumber){
        vertical_intersection(data);
        horizontal_intersection(data);
        if (data->p.v_dist > data->p.h_dist){
            data->p.rayY = data->p.h_rayy;
            data->p.rayX = data->p.h_rayx;
            data->p.raysDistance[i] = data->p.h_dist;
            // printf(" *-- %f --", data->p.raysDistance[i]);
        }
        else {
            data->p.rayX = data->p.v_rayx;
            data->p.rayY = data->p.v_rayy;
            data->p.raysDistance[i] = data->p.v_dist;
            // printf(" 5-- %f --", data->p.raysDistance[i]);
        }
        DDA(data, 551);
        data->p.rayAngle += data->p.fieldAngle / data->p.raysNumber;

        render3D(data, i);
        rectangleDraw(data, i);
    }
    printf("\n");
}

void check_width_hight(struct s_data *data){
    int i = 0;
    size_t k = 0;

    while (data->myMap.map[i])
    {
        if ( k < ft_strlen(data->myMap.map[i]))
            data->myMap.mapWidth = ft_strlen(data->myMap.map[i]);
        i++;
    }
    // printf("nb elemts: %d\n", i);
    data->myMap.mapHeight = i;
}

int wallIsHited(double x, double y, struct s_data *data){
    int iMapX;
    int iMapY;

    iMapX = floor(x / TILE_SIZE);
    iMapY = floor(y / TILE_SIZE);
    if (x >= 0 && x <= data->win_width && y >= 0 && (iMapY <= data->myMap.mapHeight && iMapY >= 0)){

        if (data->myMap.map[iMapY] && (data->myMap.map[iMapY][iMapX] == '0' || data->myMap.map[iMapY][iMapX] == 'N' || data->myMap.map[iMapY][iMapX] == 'S' || data->myMap.map[iMapY][iMapX] == 'W' || data->myMap.map[iMapY][iMapX] == 'E'))
            return (0);
        // if (data->myMap.map[iMapY][iMapX] == '0')
    }
    // printf("okhh3\n");
    return (2);
}

int main(int ac, char **av)
{
    struct s_data data;
    char **tmp;
    int     i;

    i = 0;
    if (ac != 2)
        return (printf("invalid arguments!!\n"), 1);
    tmp = get_map(av[1]);
    if (!tmp)
        return (printf("Invalid map!!\n"));
    if (!checkmap(tmp))
        return (printf("ERROR : colors or xpm links invalid"),exit (1),0);
	data.myMap.map = stor_tab(tmp);
    free (tmp);
	if (!check_tab(&data))
		return (printf("ERROR : invalid map"),exit (1),0);
    check_width_hight(&data);
    init_data(&data);
    drawMyMap(&data);
    circleDraw(&data);
    // DDA(&data, 1);
    drawRays(&data);
    // render3D(&data, 0);
    // rectangleDraw(&data, 0);
    mlx_hook(data.win_ptr, 3, 1L<<1, release_k_hook, &data);
    mlx_hook(data.win_ptr, 2, 1L<<0, k_hook, &data);
    mlx_key_hook(data.win_ptr, close_window, &data);
    mlx_loop(data.mlx_ptr);
    return (0);
}