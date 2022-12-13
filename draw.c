#include "cub.h"

// void dda_Algo(struct s_data *data, int indice){

//     double dx;
//     double dy;
//     double choice;
//     double y2 = 0;
//     double x2 = 0;
//     double var; 
//     double var2; 
//     double step = 0;
//     int i = -1;

//     if (indice == 1)
//         choice = data->p.rotationAngle;
//     else
//         choice = data->p.rayAngle;

//     x2 = data->p.pos_x + cos(choice);
//     y2 = data->p.pos_y + sin(choice);
//     dx = fabs(x2 - data->p.pos_x);
//     dy = fabs(y2 - data->p.pos_y);
//     if (dx >= dy)
//         step = dx;
//     else
//         step = dy;
//     var = dx / step;
//     var2 = dy / step;
//     double inc_x = data->p.pos_x;
//     double inc_y = data->p.pos_y;
//     printf("%f | %f", inc_x, inc_y);
//     if (x2 == inc_x && y2 < inc_y)
//     {
//         while (++i < 47){
//             mlx_pixel_put(data->mlx_ptr, data->win_ptr, inc_x, inc_y, (65536 * 255));
//             // inc_x += var;
//             inc_y -= var2;
//         }
//     }
//     else if (x2 == inc_x && y2 > inc_y)
//     {
//         while (++i < 47){
//             mlx_pixel_put(data->mlx_ptr, data->win_ptr, inc_x, inc_y, (65536 * 255));
//             // inc_x += var;
//             inc_y += var2;
//         }
//     }
//     else if (x2 > inc_x && y2 == inc_y)
//     {
//         while (++i < 47){
//             mlx_pixel_put(data->mlx_ptr, data->win_ptr, inc_x, inc_y, (65536 * 255));
//             inc_x += var;
//             // inc_y -= var2;
//         }
//     }
//     else if (x2 > inc_x && y2 > inc_y)
//     {
//         while (++i < 47){
//             mlx_pixel_put(data->mlx_ptr, data->win_ptr, inc_x, inc_y, (65536 * 255));
//             inc_x += var;
//             inc_y += var2;
//         }
//     }
//     else if (x2 < inc_x && y2 > inc_y)
//     {
//         while (++i < 47){
//             mlx_pixel_put(data->mlx_ptr, data->win_ptr, inc_x, inc_y, (65536 * 255));
//             inc_x -= var;
//             inc_y += var2;

//         }
//     }
//     else if (x2 < inc_x && y2 < inc_y)
//     {
//         while (++i < 47){
//             mlx_pixel_put(data->mlx_ptr, data->win_ptr, inc_x, inc_y, (65536 * 255));
//             inc_x -= var;
//             inc_y -= var2;
//         }
//     }
//     else if (x2 > inc_x && y2 < inc_y)
//     {
//         while (++i < 47){
//             mlx_pixel_put(data->mlx_ptr, data->win_ptr, inc_x, inc_y, (65536 * 255));
//             inc_x += var;
//             inc_y -= var2;
//         }
//     }
//     // data->p.rotationAngle += 15 *(M_PI / 180); 
// }

void DDA(struct s_data *data, int indice)
{
    int dx;
    int dy;
    // calculate dx & dy
    if (indice == 1){
        dx = data->p.newPx - data->p.pos_x;
        dy = data->p.newPy - data->p.pos_y;
    }
    else if (indice == 2){
        dx = data->p.newPPx - data->p.pos_x;
        dy = data->p.newPPy - data->p.pos_y;
    }
    else {
        dx = data->p.rayX - data->p.pos_x;
        dy = data->p.rayY - data->p.pos_y;
    }
    // printf("-- posx = %f\n, posy = %f\n", data->p.newPx, data->p.newPy);
    

 
    // calculate steps required for generating pixels
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
 
    // calculate increment in x & y for each steps
    double Xinc = dx / (double)steps;
    double Yinc = dy / (double)steps;
 
    // Put pixel for each step
    double X = data->p.pos_x;
    double Y = data->p.pos_y;
    for (int i = 0; i <= steps; i++) {
        mlx_pixel_put(data->mlx_ptr, data->win_ptr, X, Y, (65536 * 255 * indice));// put pixel at (X,Y)
        X += Xinc; // increment in x at each step
        Y += Yinc; // increment in y at each step // for visualization of line-
                    // generation step by step
    }
}

int circleDraw(struct s_data *data){
    int i = 0;
    int j = 0;
    int r = 4;
    // printf("width = %f\n", data->p.pos_x);
    // printf("height = %f\n", data->p.pos_y);
    while (i < data->win_hight)
    {
        j = 0;
        while (j < data->win_width){
            if ((j - data->p.pos_x) * (j - data->p.pos_x) + (i - data->p.pos_y) * (i - data->p.pos_y) <= r * r )
                mlx_pixel_put(data->mlx_ptr, data->win_ptr, j, i, 0xFF0000);
            j++;
        }
        i++;
    }
    return (0);
}

int drawMyMap(struct s_data *data){
    int j = 0;
    int i = -1;
    
    while (++i < data->myMap.mapHeight){
        j = 0;
        while (j < data->myMap.mapWidth){
            if (data->myMap.map[i][j] == '0' || data->myMap.map[i][j] == 'N')
                mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img2.ptr, (data->x + (j * 30)), (data->y + (i * 30)));
            else if (data->myMap.map[i][j] == ' ')
                mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img3.ptr, (data->x + (j * 30)), (data->y + (i * 30)));
            else if (data->myMap.map[i][j] == '1')
                mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.ptr, (data->x + (j * 30)), (data->y + (i * 30)));
            j++;
        }
    }
    return (0);
}