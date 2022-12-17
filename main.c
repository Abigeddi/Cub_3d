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

// void render_map(s_data *data)
// {
// 	 data.img.ptr = mlx_xpm_file_to_image(data.mlx_ptr, "./y.xpm", &data.img.width, &data.img.hight);
//     data.img.dataAdress = (int *)mlx_get_data_addr(data.img.ptr, &data.img.bpp, &data.img.size_line, &data.img.endian);
//     data.img2.ptr = mlx_xpm_file_to_image(data.mlx_ptr, "./n.xpm", &data.img2.width, &data.img2.hight);
//     data.img2.dataAdress = (int *)mlx_get_data_addr(data.img2.ptr, &data.img2.bpp, &data.img2.size_line, &data.img2.endian);
// }

// void render_player(s_data *data)
// {
// 	int i = -1;
// 	int j = 0;
//     while (++i< 10){
//         j = 0;
//         while (j < 10){
//             mlx_pixel_put(data->mlx_ptr, data->win_ptr, (data->p.pos_x + j), (data->p.pos_y + i), 65536 * 255);
//             j++;
//         }
//         // mlx_clear_window(data->mlx_ptr, data->win_ptr);
//     }
// }

// int key_hook(int key, struct s_data *data){
//     int i = -1;
//     int j = 0;
//     data->p.posLine_x += data->p.pos_x + 5;
//     data->p.posLine_y += data->p.pos_y + 5;
    
//     printf("***** %d\n", key);
   

//     if (key == 124 && data->p.pos_x < (20 * 30) && map[((int)data->p.pos_y / 30)][((int)data->p.pos_x /30 )] != 1){
//         if (map[(int)(data->p.pos_y) / 30][(((int)data->p.pos_x + 15 ) / 30)] == 0)
//         data->p.pos_x += 15;
//         // posLine_x += 15;
//         //data->p.turnDirection = 1;
//         data->p.rotationAngle = (data->p.rotationAngle + data->p.turnDirection) * data->p.rotationSpeed;

//         }
//     else if ( key == 123 && data->p.pos_x < (20 * 30) && map[((int)data->p.pos_y / 30)][((int)data->p.pos_x / 30)] != 1){
//         if (map[int(data->p.pos_y) / 30][(((int)data->p.pos_x  - 15)/ 30)] == 0)
//             data->p.pos_x -= 15;
//         // posLine_x -= 15;
//         //data->p.turnDirection = -1;
//         data->p.rotationAngle += data->p.turnDirection * data->p.rotationSpeed;
//         }
//     else if ( key == 125 && data->p.pos_y < (15 * 30) && map[((int)data->p.pos_y / 30)][((int)data->p.pos_x / 30)] != 1){
//         if (map[(int)(data->p.pos_y + 15) / 30][((int)data->p.pos_x / 30)] == 0)
//             data->p.pos_y += 15;
//         // posLine_y += 15;
//         //data->p.walkDirection = -1;
//         }
//     else if ( key == 126 && data->p.pos_y < (15 * 30) && map[((int)data->p.pos_y / 30)][((int)data->p.pos_x / 30)] != 1){
//         if (map[(int)(data->p.pos_y - 15) / 30][((int)data->p.pos_x / 30)] == 0)
//             data->p.pos_y -= 15;
//         // posLine_y -= 15;
//         //data->p.walkDirection = 1;
//         }
//     // mlx_clear_window(data->mlx_ptr, data->win_ptr);
//     i = -1;
//     while (++i < 30){
//         mlx_pixel_put(data->mlx_ptr, data->win_ptr, data->p.posLine_x, data->p.posLine_y, (65536 * 255));
//         data->p.posLine_x = (data->p.posLine_x * cos(data->p.rotationAngle)) - (data->p.posLine_y * sin(data->p.rotationAngle));
//         data->p.posLine_y = (data->p.posLine_x * sin(data->p.rotationAngle)) + (data->p.posLine_y * cos(data->p.rotationAngle));
//     }
//     data->p.turnDirection = 0;
//     data->p.walkDirection = 0;
//     return (0);
// }


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
    data->x = 0;
    data->y = 0;
    data->win_width = data->myMap.mapWidth * 30;
    data->win_hight = data->myMap.mapHeight * 30;
    data->p.moveSpeed = 4;
    // data->p.rotationAngle = 2 * M_PI;
    data->myMap.tile_size = 30;
    data->p.newPx = data->p.pos_x + cos(data->p.rotationAngle) * data->myMap.tile_size;
    data->p.newPy = data->p.pos_y + sin(data->p.rotationAngle) * data->myMap.tile_size;
    
    
    printf ("--x = %f\n",data->p.pos_x);
    printf ("--y = %f\n",data->p.pos_y);
    data->p.fieldAngle = 60 * (M_PI / 180);
    data->p.rotationSpeed = 40 * (M_PI / 180);
    data->p.wallStreapWidth = 10;
    data->p.raysNumber = data->win_width / data->p.wallStreapWidth;
    printf("--- %d\n", data->win_width);
    data->p.rayAngle = data->p.rotationAngle - (data->p.fieldAngle / 2);
    data->img.hight = 30;
    data->img.width = 30;
    data->mlx_ptr = mlx_init();
    data->win_ptr = mlx_new_window(data->mlx_ptr, data->win_width, data->win_hight, "test");
    data->img.ptr = mlx_xpm_file_to_image(data->mlx_ptr, "./pics/y.xpm", &data->img.width, &data->img.hight);
    data->img.dataAdress = (int *)mlx_get_data_addr(data->img.ptr, &data->img.bpp, &data->img.size_line, &data->img.endian);
    data->img2.ptr = mlx_xpm_file_to_image(data->mlx_ptr, "./pics/n.xpm", &data->img.width, &data->img.hight);
    data->img2.dataAdress = (int *)mlx_get_data_addr(data->img2.ptr, &data->img2.bpp, &data->img2.size_line, &data->img2.endian);
    data->img3.ptr = mlx_xpm_file_to_image(data->mlx_ptr, "./pics/j.xpm", &data->img.width, &data->img.hight);
    data->img3.dataAdress = (int *)mlx_get_data_addr(data->img3.ptr, &data->img3.bpp, &data->img3.size_line, &data->img3.endian);
}

void drawRays(struct s_data *data){
    
    int i = -1;
    printf("number rays = %d\n", data->p.raysNumber);
    printf("__---------------------____ROTAION : %f\n", data->p.rotationAngle);
    data->p.rayAngle = data->p.rotationAngle - (30 * (M_PI / 180));
    while (++i < data->p.raysNumber){

        vertical_inter(data);
        horizontal_inter(data);
        printf("pos p : x = %f && y = %f\n", data->p.pos_x, data->p.pos_y);
        printf("ver : x = %f && y= %f\n", data->ray.vertichitx, data->ray.vertichity);
        printf("hor : x = %f && y= %f\n", data->ray.horizhitx, data->ray.horizhity);
        if (data->ray.horizdistance > data->ray.verticdistance)
        {
            data->ray.distance = data->ray.verticdistance;
            data->p.rayX = data->ray.vertichitx;
            data->p.rayY = data->ray.vertichity;
        }
        else
            {
            data->ray.distance = data->ray.horizdistance;
            data->p.rayX = data->ray.horizhitx;
            data->p.rayY = data->ray.horizhity;
        }
            printf ("-----DISTANCE---%f\n",data->ray.distance );
        // horizontal_inter(data);
        // if ()
        // data->p.rayX = data->p.pos_x + (cos(data->p.rayAngle) * 200);
        // data->p.rayY = data->p.pos_y + (sin(data->p.rayAngle) * 200);

        DDA(data, 551);
        data->p.rayAngle += 2 * (M_PI / 180);
    }
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
    data->myMap.mapHeight = i;

}

int wallIsHited(double x, double y, struct s_data *data){
    int iMapX;
    int iMapY;

    // if (x < 0 || x > data->win_width || y < 0 || y > data->win_hight)
    //     return (5);
    iMapX = floor(x / 30);
    iMapY = floor(y / 30);
    if (data->myMap.map[iMapY][iMapX] == '0' || data->myMap.map[iMapY][iMapX] == 'N')
        return (0);
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
    printf ("x = %f\n",data.p.pos_x);
    printf ("y = %f\n",data.p.pos_y);
    check_width_hight(&data);
    init_data(&data);
    drawMyMap(&data);
    circleDraw(&data);
    DDA(&data, 1);
    drawRays(&data);

    // dda_Algo(&data, 1);
    // dda_Algo(&data, 2);
    mlx_hook(data.win_ptr, 2, 1L<<0, k_hook, &data);
    mlx_hook(data.win_ptr, 3, 1L<<1, release_k_hook, &data);
    mlx_loop(data.mlx_ptr);
    return (0);
}