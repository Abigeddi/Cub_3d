/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalazhar <aalazhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 17:59:27 by abigeddi          #+#    #+#             */
/*   Updated: 2022/12/17 23:17:29 by aalazhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"


void normalize_angle(struct s_data *data)
{
    if (data->p.rotationAngle < 0)
        data->p.rotationAngle = data->p.rotationAngle + (2 * M_PI);
    if (data->p.rotationAngle > (2 * M_PI))
        data->p.rotationAngle = data->p.rotationAngle - (2 * M_PI);
    if (data->p.rayAngle < 0)
        data->p.rayAngle = data->p.rayAngle + (2 * M_PI);
    if (data->p.rayAngle > (2 * M_PI))
        data->p.rayAngle = data->p.rayAngle - (2 * M_PI);
        
}

void ray_facing(struct s_data *data)
{
    data->ray.ray_facingdown = 0;
    data->ray.ray_facingup = 0;
    data->ray.ray_facinright = 0;
    data->ray.ray_facinleft = 0;
    
    normalize_angle(data);
    if ( (data->p.rayAngle > ((1.5) * M_PI) && data->p.rayAngle < (M_PI * (2))) ||  (data->p.rayAngle > 0 && data->p.rayAngle < (0.5) * M_PI))
        data->ray.ray_facinright = 1;
    else
        data->ray.ray_facinleft = 1;
    if (data->p.rayAngle > 0 && data->p.rayAngle < M_PI)
        data->ray.ray_facingdown = 1;
    else
        data->ray.ray_facingup = 1;
        
}
double distancebetweenpoints(double x1, double y1, double x2, double y2)
{
    return (sqrt((x2 -x1) * (x2 -x1) + (y2 - y1) * (y2 - y1)));
}
void horizontal_inter(struct s_data *data)
{
    double  xtile , ytile;
    int xtocheck ,ytocheck;
    double xintercept,yintercept;
    long xstep,ystep;
        
        ray_facing(data);
        // printf ("------rayangle------- %f\n", data->p.rayAngle);
        // printf ("--------------UP--------%d\n" , data->ray.ray_facingup);
        // printf ("--------------DOWN--------%d\n" , data->ray.ray_facingdown);
        // printf ("---------------LEFT-------%d\n" , data->ray.ray_facinleft);
        // printf ("--------------RIGHT--------%d\n" , data->ray.ray_facinright);
        
        yintercept =  floor((data->p.pos_y / data->myMap.tile_size)) * data->myMap.tile_size;
        if (data->ray.ray_facingdown == 1)
            yintercept += data->myMap.tile_size;
        xintercept =  data->p.pos_x + ((yintercept - data->p.pos_y  ) / tan(data->p.rayAngle));
        ystep = data->myMap.tile_size;
        if (data->ray.ray_facingup == 1)
            ystep *= -1;
        xstep = data->myMap.tile_size / tan(data->p.rayAngle);
        // if (data->ray.ray_facinleft == 1 && xstep > 0)
        //     xstep *= -1;
        // if (data->ray.ray_facinright == 1 && xstep < 0)
        //     xstep *= -1;
        
        
        xtile = xintercept;
        ytile = yintercept;
        // mlx_pixel_put(data->mlx_ptr, data->win_ptr, xtile, ytile, ( 255));
        
        while (xtile >= 0 && xtile <= data->win_width && ytile >= 0 && ytile <= data->win_hight)
        {
            xtocheck = (int) (xtile  / data->myMap.tile_size);
            ytocheck = (int) (ytile  / data->myMap.tile_size);
            if (data->ray.ray_facingup == 1)
                ytocheck = (int) ((ytile  / data->myMap.tile_size)) - 1;
                // ytocheck = floor((ytile - 1) / data->myMap.tile_size);
            // printf("i = %d &&  j = %d\n", xtocheck, ytocheck);
            // printf("x_stp = %ld &&  y_stp = %ld\n", xstep, ystep);
            // printf ("------c[%d][%d]\n",ytocheck, xtocheck);
            // // printf("%c----\n", data->myMap.map[1][7]);
            // printf("=== %c\n",   data->myMap.map[ytocheck][xtocheck]);
            printf("*************\n");
            printf("xtocheck = %d\n", xtocheck);
            printf("ytocheck = %d\n", ytocheck);
            printf("*************\n");
            if (data->myMap.map[ytocheck][xtocheck] == '1')
            {
                data->ray.horizhitx = xtile;
                data->ray.horizhity = ytile;
                data->ray.horizwallhit = 1;
                data->ray.horizwallcontent = data->myMap.map[ytocheck][xtocheck];
                break ;  
            }
            else
            {
                xtile += xstep;
                ytile += ystep;  
            }
            
        }
        if (data->ray.horizwallhit == 1)
            data->ray.horizdistance = distancebetweenpoints(data->p.pos_x,data->p.pos_y,data->ray.horizhitx,data->ray.horizhity);
    
}


void vertical_inter(struct s_data *data)
{
    double  xtile , ytile;
    int xtocheck ,ytocheck;
    double xintercept,yintercept;
    long xstep,ystep;
    // data->ray.wallhit = 0;
        
        ray_facing(data);
        // printf(" vertical inet -- \n");
        xintercept =  floor((data->p.pos_x / data->myMap.tile_size)) * data->myMap.tile_size;
        if (data->ray.ray_facinright == 1)
            xintercept += data->myMap.tile_size;
        yintercept =  data->p.pos_y + ((xintercept - data->p.pos_x  ) * tan(data->p.rayAngle));
        xstep = data->myMap.tile_size;
        if (data->ray.ray_facinleft == 1)
            xstep *= -1;
        ystep = data->myMap.tile_size * tan(data->p.rayAngle);
        if (data->ray.ray_facingup == 1 && ystep > 0)
            ystep *= -1;
        if (data->ray.ray_facingdown == 1 && ystep < 0)
            ystep *= -1;
        
        
        xtile = xintercept;
        ytile = yintercept;
        // mlx_pixel_put(data->mlx_ptr, data->win_ptr, xtile, ytile, ( 255));
        while (xtile >= 0 && xtile <= data->win_width && ytile >= 0 && ytile <= data->win_hight)
        {
            xtocheck = (int) (xtile  / data->myMap.tile_size);
            ytocheck = (int) (ytile  / data->myMap.tile_size);
            if (data->ray.ray_facinleft == 1)
                xtocheck = (int) ((xtile  / data->myMap.tile_size) - 1);
            if (data->myMap.map[ytocheck][xtocheck] == '1')
            {
                data->ray.vertichitx = xtile;
                data->ray.vertichity = ytile;
                data->ray.vertiwallhit = 1;
                data->ray.vertiwallcontent = data->myMap.map[ytocheck][xtocheck];
                break ;  
            }
            else
            {
                xtile += xstep;
                ytile += ystep;  
            }
            
        }
        if (data->ray.vertiwallhit == 1)
            data->ray.verticdistance = distancebetweenpoints(data->p.pos_x,data->p.pos_y,data->ray.vertichitx,data->ray.vertichity);
    // printf("ver distenc %ld\n", data->ray.verticdistance);
}
