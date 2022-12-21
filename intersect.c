#include "cub.h"

double normalizeAngle(double angle){
    // data->p.rayAngle = data->p.rayAngle / (2 * M_PI);
    // if (data->p.rayAngle < 0)
    //     data->p.rayAngle = (2 * M_PI) + data->p.rayAngle;
    // if (data->p.rotationAngle < 0)
    //     data->p.rotationAngle = data->p.rotationAngle + (2 * M_PI);
    // if (data->p.rotationAngle > (2 * M_PI))
    //     data->p.rotationAngle = data->p.rotationAngle - (2 * M_PI);
    // if (data->p.rayAngle < 0)
    //     data->p.rayAngle = data->p.rayAngle + (2 * M_PI);
    // if (data->p.rayAngle > (2 * M_PI))
    //     data->p.rayAngle = data->p.rayAngle - (2 * M_PI);
    if (angle < 0)
        angle = (2 * M_PI) + angle;
    if (angle > 2 * M_PI)
        angle = angle - (2 * M_PI);
    return (angle);
}

double distancebetweenpoints(double x1, double y1, double x2, double y2)
{
    return (sqrt((x2 -x1) * (x2 -x1) + (y2 - y1) * (y2 - y1)));
}

// int playerFaceSide(struct s_data *data){
//     int fDown = 0;
//     int fUp = 0;
//     int fRight = 0;
//     int fLeft = 0;

//     if (data->p.rayAngle > 0 && data->p.rayAngle < M_PI)
//         fDown = 1;
//     else if (data->p.rayAngle <= (2 * M_PI) && data->p.rayAngle > M_PI)
//         fUp = 1;
//     if (data->p.rayAngle < (M_PI / 2) || data->p.rayAngle > (3 * (M_PI / 2)))
//         fRight = 1;
//     else if (data->p.rayAngle > (M_PI / 2) || data->p.rayAngle < (3 * (M_PI / 2)))
//         fLeft = 1;
//     return (0);
// }

void ray_facing(struct s_data *data)
{
    data->ray.ray_facingdown = 0;
    data->ray.ray_facingup = 0;
    data->ray.ray_facinright = 0;
    data->ray.ray_facinleft = 0;
    
    // normalize_angle(data);
    if ( (data->p.rayAngle > ((1.5) * M_PI) && data->p.rayAngle < (M_PI * (2))) ||  (data->p.rayAngle > 0 && data->p.rayAngle < (0.5) * M_PI))
        data->ray.ray_facinright = 1;
    else
        data->ray.ray_facinleft = 1;
    if (data->p.rayAngle > 0 && data->p.rayAngle < M_PI)
        data->ray.ray_facingdown = 1;
    else
        data->ray.ray_facingup = 1;
        
}

void horizontal_intersection(struct s_data *data){

    double xstep; // delta-x
    double ystep; // delta-y 

    double xIntersect;
    double yIntersect;
    printf("hroo===========\n");
    // double distance;

    /* get the first intersection point */
    double firstX = 0.0;
    double firstY = 0.0;
    // int fDown = 0;
    // int fUp = 0;
    // int fRight = 0;
    // int fLeft = 0;

    // if (data->p.rayAngle > 0 && data->p.rayAngle < M_PI)
    //     fDown = 1;
    // else
    //     fUp = 1;
    
    // if ((data->p.rayAngle > ((1.5) * M_PI) && data->p.rayAngle < (M_PI * (2))) ||  (data->p.rayAngle > 0 && data->p.rayAngle < (0.5) * M_PI))
    //     fRight = 1;
    // else
    //     fLeft = 1;
    // if ((data->p.rayAngle * (180 / M_PI)) == 360)
    //     data->p.rayAngle = 0;
    printf("ray Angle = %f \n", data->p.rayAngle * (180 / M_PI));
    printf("rot Angle = %f \n", data->p.rotationAngle * (180 / M_PI));
    data->p.rayAngle =  normalizeAngle(data->p.rayAngle);
    
    
    if ((data->p.rayAngle > (270 * (M_PI / 180)) && data->p.rayAngle <= 2 * M_PI)){
        firstY = floor(data->p.pos_y / 30) * 30 - 1;
        firstX = data->p.pos_x + ((firstY - data->p.pos_y) / tan(data->p.rayAngle)) + 1;
        ystep = -30;
        // if(data->p.rayAngle == 0)
        //     xstep = 0;
        xstep = ystep / tan(data->p.rayAngle);
        printf("xstep = %f\n", xstep);
        printf("ystep = %f\n", ystep);
        if (xstep < 0)
            xstep *= -1;
        // ystep *= -1;
        xIntersect = firstX;
        yIntersect = firstY;

        while (wallIsHited(xIntersect, yIntersect, data) == 0){
            xIntersect += xstep;
            yIntersect += ystep;
        }
        data->p.h_rayx = xIntersect;
        data->p.h_rayy = yIntersect;
        if (data->p.h_rayy == 0){
            data->p.h_rayy += 30;
        }
        data->p.h_dist = distancebetweenpoints(data->p.pos_x, data->p.pos_y, data->p.h_rayx, data->p.h_rayy);
        printf("intercX = %f\n", xIntersect);
        printf("intercY = %f\n", yIntersect);
    }
    if ((data->p.rayAngle > 0 && data->p.rayAngle <= M_PI / 2)){
        firstY = (floor(data->p.pos_y / 30) * 30) + 30 + 1;
        firstX = data->p.pos_x + ((firstY - data->p.pos_y) / tan(data->p.rayAngle)) + 1;
        ystep = 30;
        xstep = ystep / tan(data->p.rayAngle);
        if (xstep < 0)
            xstep *= -1;
        // ystep *= -1;
        printf("xstep = %f\n", xstep);
        printf("ystep = %f\n", ystep);
        xIntersect = firstX;
        yIntersect = firstY;

        while (wallIsHited(xIntersect, yIntersect, data) == 0){
            xIntersect += xstep;
            yIntersect += ystep;
        }
        data->p.h_dist = distancebetweenpoints(data->p.pos_x, data->p.pos_y, xIntersect, yIntersect);
        data->p.h_rayx = xIntersect;
        data->p.h_rayy = yIntersect;
        printf("intercX = %f\n", xIntersect);
        printf("intercY = %f\n", yIntersect);
    }
    if ((data->p.rayAngle > M_PI / 2 && data->p.rayAngle <= M_PI)){
        firstY = (floor(data->p.pos_y / 30) * 30) + 30 + 1;
        firstX = data->p.pos_x + ((firstY - data->p.pos_y) / tan(data->p.rayAngle)) - 1;
        ystep = 30;
        xstep = ystep / tan(data->p.rayAngle);
        if (xstep > 0)
            xstep *= -1;
        printf("xstep = %f\n", xstep);
        printf("ystep = %f\n", ystep);
        xIntersect = firstX;
        yIntersect = firstY;

        while (wallIsHited(xIntersect, yIntersect, data) == 0){
            xIntersect += xstep;
            yIntersect += ystep;
        }
        data->p.h_dist = distancebetweenpoints(data->p.pos_x, data->p.pos_y, xIntersect, yIntersect);
        data->p.h_rayx = xIntersect;
        data->p.h_rayy = yIntersect;
        printf("intercX = %f\n", xIntersect);
        printf("intercY = %f\n", yIntersect);
    }

    if ((data->p.rayAngle > M_PI && data->p.rayAngle <= (3 *(M_PI / 2)))){
        firstY = (floor(data->p.pos_y / 30) * 30) - 1;
        firstX = data->p.pos_x + ((firstY - data->p.pos_y) / tan(data->p.rayAngle)) - 1;
        printf("first-x = %f\n", firstX);
        printf("first-Y = %f\n", firstY);
        ystep = -30;
        xstep = ystep / tan(data->p.rayAngle);
        if (xstep > 0)
            xstep *= -1;
        printf("xstep = %f\n", xstep);
        printf("ystep = %f\n", ystep);
        xIntersect = firstX;
        yIntersect = firstY;

        while (wallIsHited(xIntersect, yIntersect, data) == 0){
            xIntersect += xstep;
            yIntersect += ystep;
        }
        data->p.h_rayx = xIntersect;
        data->p.h_rayy = yIntersect;
        if (data->p.h_rayy == 0){
            data->p.h_rayy += 30;
        }
        data->p.h_dist = distancebetweenpoints(data->p.pos_x, data->p.pos_y, data->p.h_rayx, data->p.h_rayy);
        printf("intercX = %f\n", xIntersect);
        printf("intercY = %f\n", yIntersect);
    }
    printf("last point : X %f , Y %f\n", data->p.h_rayx, data->p.h_rayy);
    // firstY = floor(data->p.pos_y / 30) * 30;
    // // if (data->p.rayAngle > 0 && data->p.rayAngle < M_PI)
    // if (data->ray.ray_facingdown)
    //     firstY += 30;
    // firstX = data->p.pos_x + ((firstY - data->p.pos_y) / tan(data->p.rayAngle));
    // ystep = 30;
    // if (data->ray.ray_facingup)
    //     ystep *= -1;
    // xstep = ystep / tan(data->p.rayAngle);
    // // if (data->p.rayAngle > (270 * (M_PI / 180)) && data->p.rayAngle < (90 * (M_PI / 180)))
    // // if (xstep > 0 && ((data->p.rayAngle > (270 * (M_PI / 180)) && data->p.rayAngle < (360 * (M_PI / 180))) || (data->p.rayAngle > (0 * (M_PI / 180)) && data->p.rayAngle < (90 * (M_PI / 180)))))
    // if (data->ray.ray_facinright && xstep > 0)
    //     xstep *= -1;
    // // if (xstep < 0 && ((data->p.rayAngle > (90 * (M_PI / 180)) && data->p.rayAngle < (180 * (M_PI / 180))) || (data->p.rayAngle > (180 * (M_PI / 180)) && data->p.rayAngle < (270 * (M_PI / 180)))))
    // if (data->ray.ray_facinleft && xstep < 0)
    //     xstep *= -1;



    // if (fDown)
    // if ((data->p.rayAngle > 0 &&  data->p.rayAngle < M_PI))
    //     firstY += 30;

    /* find delta-x and delta-y */
    // ystep = 30;
    // xstep = ystep / tan(data->p.rayAngle);
    // xstep *= -1;
    // printf("xstep = %f\n", xstep);
    // if (data->p.rayAngle > (M_PI / 2) && data->p.rayAngle < M_PI)
    //     xstep *= -1;
    // if (data->p.rayAngle > M_PI && data->p.rayAngle < (3 * (M_PI / 2))){
    //     xstep *= -1;
    //     ystep *= -1;
    // }
    // else if (data->p.rayAngle > (3 * (M_PI / 2)) && data->p.rayAngle < 2 * M_PI)
    //     ystep *= -1;

    // if (fUp)
    //     ystep *= -1;


    // if (fLeft && xstep > 0)
    //     xstep *= -1;
    // if (fRight && xstep < 0)
    //     xstep *= -1;

    // xIntersect = firstX;
    // yIntersect = firstY;

    // while (wallIsHited(xIntersect, yIntersect, data) == 0){
    //     xIntersect += xstep;
    //     yIntersect += ystep;
    // }
    // // if (wallIsHited(xIntersect, yIntersect, data) == 1)
    // distance = distancebetweenpoints(data->p.pos_x, data->p.pos_y, xIntersect, yIntersect);
    // data->ray.horizhitx = xIntersect;
    // data->ray.horizhity = yIntersect;
    printf("first-x = %f\n", firstX);
    printf("first-Y = %f\n", firstY);
}

void vertical_intersection(struct s_data *data){
    double xstep = 0; // delta-x
    double ystep = 0; // delta-y 

    double xIntersect;
    double yIntersect;

    // double distance;
    double firstX = 0.0;
    double firstY = 0.0;
    data->p.rayAngle =  normalizeAngle(data->p.rayAngle);
    printf("vertical --------\n");
    printf("ray Angle = %f \n", data->p.rayAngle * (180 / M_PI));
    printf("rot Angle = %f \n", data->p.rotationAngle * (180 / M_PI));
    if ((data->p.rayAngle > (270 * (M_PI / 180)) && data->p.rayAngle <= 2 * M_PI)){
        firstX = floor(data->p.pos_x / 30) * 30 + 1;
        firstY = data->p.pos_y + ((firstX - data->p.pos_x) * tan(data->p.rayAngle)) - 1;
        xstep = 30;
        ystep = xstep * tan(data->p.rayAngle);
        
        // if(data->p.rayAngle == 0)
        //     xstep = 0;
        if (ystep > 0)
            ystep *= -1;
        // if (xstep < 0)
        //     xstep *= -1;
        // ystep *= -1;
        xIntersect = firstX;
        yIntersect = firstY;

        while (wallIsHited(xIntersect, yIntersect, data) == 0){
            xIntersect += xstep;
            yIntersect += ystep;
        }
        data->p.v_dist = distancebetweenpoints(data->p.pos_x, data->p.pos_y, xIntersect, yIntersect);
        data->p.v_rayx = xIntersect;
        data->p.v_rayy = yIntersect;
        printf("intercX = %f\n", xIntersect);
        printf("intercY = %f\n", yIntersect);
    }
    else if ((data->p.rayAngle > 0 && data->p.rayAngle <= M_PI / 2)){
        firstX = (floor(data->p.pos_x / 30) * 30) + 30 + 1;
        firstY = data->p.pos_y + ((firstX - data->p.pos_x) * tan(data->p.rayAngle)) + 1;
        xstep = 30;
        ystep = xstep * tan(data->p.rayAngle);
        // printf("xstep = %f\n", xstep);
        // printf("ystep = %f\n", ystep);
        if (ystep < 0)
            ystep *= -1;
        // ystep *= -1;
        xIntersect = firstX;
        yIntersect = firstY;

        while (wallIsHited(xIntersect, yIntersect, data) == 0){
            xIntersect += xstep;
            yIntersect += ystep;
        }
        data->p.v_dist = distancebetweenpoints(data->p.pos_x, data->p.pos_y, xIntersect, yIntersect);
        data->p.v_rayx = xIntersect;
        data->p.v_rayy = yIntersect;
        printf("intercX = %f\n", xIntersect);
        printf("intercY = %f\n", yIntersect);
    }
    else if ((data->p.rayAngle > M_PI / 2 && data->p.rayAngle <= M_PI)){
        firstX = (floor(data->p.pos_x / 30) * 30) + 30 - 1;
        firstY = data->p.pos_y + ((firstX - data->p.pos_x) * tan(data->p.rayAngle)) + 1;
        xstep = -30;
        ystep = xstep * tan(data->p.rayAngle);
        // printf("xstep = %f\n", xstep);
        // printf("ystep = %f\n", ystep);
        if (ystep < 0)
            ystep *= -1;
        xIntersect = firstX;
        yIntersect = firstY;

        while (wallIsHited(xIntersect, yIntersect, data) == 0){
            xIntersect += xstep;
            yIntersect += ystep;
        }
        data->p.v_rayx = xIntersect;
        data->p.v_rayy = yIntersect;
        // if (data->p.v_rayx < data->p.pos_x){
        //     data->p.v_rayx += 30;
        // }
        data->p.v_dist = distancebetweenpoints(data->p.pos_x, data->p.pos_y, data->p.v_rayx, data->p.v_rayy);
        // printf("intercX = %f\n", xIntersect);
        // printf("intercY = %f\n", yIntersect);
    }
    else if ((data->p.rayAngle > M_PI && data->p.rayAngle <= (3 *(M_PI / 2)))){
        firstX = (floor(data->p.pos_x / 30) * 30) - 1;
        firstY = data->p.pos_y + ((firstX - data->p.pos_x) * tan(data->p.rayAngle)) - 1;
        xstep = -30;
        ystep = xstep * tan(data->p.rayAngle);
        if (ystep > 0)
            ystep *= -1;
        // printf("xstep = %f\n", xstep);
        // printf("ystep = %f\n", ystep);
        xIntersect = firstX;
        yIntersect = firstY;

        while (wallIsHited(xIntersect, yIntersect, data) == 0){
            xIntersect += xstep;
            yIntersect += ystep;
        }
        data->p.v_rayx = xIntersect;
        data->p.v_rayy = yIntersect;
        // if (data->p.v_rayx < data->p.pos_x){
        //     data->p.v_rayx += 30;
        // }
        data->p.v_dist = distancebetweenpoints(data->p.pos_x, data->p.pos_y, data->p.v_rayx, data->p.v_rayy);
        // printf("intercX = %f\n", xIntersect);
        // printf("intercY = %f\n", yIntersect);
    }
    printf("first-x = %f\n", firstX);
    printf("first-Y = %f\n", firstY);
    printf("xstep = %f\n", xstep);
    printf("ystep = %f\n", ystep);
    printf("last point : X %f , Y %f\n", data->p.v_rayx, data->p.v_rayy);
    // xIntersect = firstX;
    // yIntersect = firstY;

    // while (wallIsHited(xIntersect, yIntersect, data) == 0){
    //     xIntersect += xstep;
    //     yIntersect += ystep;
    // }
    // if (wallIsHited(xIntersect, yIntersect, data) == 1)
    // distance = distancebetweenpoints(data->p.pos_x, data->p.pos_y, xIntersect, yIntersect);
    // data->ray.vertichitx = xIntersect;
    // data->ray.vertichity = yIntersect;

    // // double xstep; // delta-x
    // // double ystep; // delta-y 

    // // double xIntersect;
    // // double yIntersect;

    // // double distance;

    // // /* get the first intersection point */
    // // double firstX = 0.0;
    // // double firstY = 0.0;

    // // firstX = floor(data->p.pos_x / 30) * 30;
    // // if (data->p.rayAngle > (270 * (M_PI / 180)) && data->p.rayAngle < M_PI / 2)
    // //     firstX += 30;
    // // firstY = data->p.pos_y + ((firstX - data->p.pos_x) * tan(data->p.rayAngle));
    // // xstep = 30;
    // // if (data->p.rayAngle > M_PI / 2 && data->p.rayAngle < (270 * (M_PI / 180)))
    // //     xstep *= -1;
    // // ystep = xstep * tan(data->p.rayAngle);
    // // // if (data->p.rayAngle > (270 * (M_PI / 180)) && data->p.rayAngle < (90 * (M_PI / 180)))
    // // if (ystep > 0 && (((data->p.rayAngle > M_PI) && data->p.rayAngle < (270 * (M_PI / 180))) || (data->p.rayAngle > (270 * (M_PI / 180)) && data->p.rayAngle < (360 * (M_PI / 180)))))
    // //     ystep *= -1;
    // // if (ystep < 0 && ((data->p.rayAngle > 0 && data->p.rayAngle < (M_PI / 2)) || ((data->p.rayAngle > (M_PI / 2)) && data->p.rayAngle < M_PI)))
    // //     ystep *= -1;
    // // xIntersect = firstX;
    // // yIntersect = firstY;
    // // // if ()

    // // while (wallIsHited(xIntersect, yIntersect, data) == 0){

    // //     xIntersect += xstep;
    // //     yIntersect += ystep;
    // // }
    // // // if (wallIsHited(xIntersect, yIntersect, data) == 1)
    // //     distance = distancebetweenpoints(data->p.pos_x, data->p.pos_y, xIntersect, yIntersect);
    // // data->p.rayX = xIntersect;
    // // data->p.rayY = yIntersect;
}