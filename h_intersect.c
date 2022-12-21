#include "cub.h"

void upRight_hIntersect(struct s_data *data){
    data->interH.firstY = floor(data->p.pos_y / 30) * 30 - 1;
    data->interH.firstX = data->p.pos_x + ((data->interH.firstY - data->p.pos_y) / tan(data->p.rayAngle)) + 1;
    data->interH.ystep = -30;
    data->interH.xstep = data->interH.ystep / tan(data->p.rayAngle);
    if (data->interH.xstep < 0)
        data->interH.xstep *= -1;
    data->interH.xIntersect = data->interH.firstX;
    data->interH.yIntersect = data->interH.firstY;
    while (wallIsHited(data->interH.xIntersect, data->interH.yIntersect, data) == 0){
        data->interH.xIntersect += data->interH.xstep;
        data->interH.yIntersect += data->interH.ystep;
    }
    data->p.h_rayx = data->interH.xIntersect;
    data->p.h_rayy = data->interH.yIntersect;
    data->p.h_dist = distancebetweenpoints(data->p.pos_x, data->p.pos_y, data->p.h_rayx, data->p.h_rayy);
}

void downRight_hIntersect(struct s_data *data){
    data->interH.firstY = (floor(data->p.pos_y / 30) * 30) + 30 + 1;
    data->interH.firstX = data->p.pos_x + ((data->interH.firstY - data->p.pos_y) / tan(data->p.rayAngle)) + 1;
    data->interH.ystep = 30;
    data->interH.xstep = data->interH.ystep / tan(data->p.rayAngle);
    if (data->interH.xstep < 0)
        data->interH.xstep *= -1;
    data->interH.xIntersect = data->interH.firstX;
    data->interH.yIntersect = data->interH.firstY;
    while (wallIsHited(data->interH.xIntersect, data->interH.yIntersect, data) == 0){
        data->interH.xIntersect += data->interH.xstep;
        data->interH.yIntersect += data->interH.ystep;
    }
    data->p.h_dist = distancebetweenpoints(data->p.pos_x, data->p.pos_y, data->interH.xIntersect, data->interH.yIntersect);
    data->p.h_rayx = data->interH.xIntersect;
    data->p.h_rayy = data->interH.yIntersect;
}

void downLeft_hIntersect(struct s_data *data){
    data->interH.firstY = (floor(data->p.pos_y / 30) * 30) + 30 + 1;
    data->interH.firstX = data->p.pos_x + ((data->interH.firstY - data->p.pos_y) / tan(data->p.rayAngle)) - 1;
    data->interH.ystep = 30;
    data->interH.xstep = data->interH.ystep / tan(data->p.rayAngle);
    if (data->interH.xstep > 0)
        data->interH.xstep *= -1;
    data->interH.xIntersect = data->interH.firstX;
    data->interH.yIntersect = data->interH.firstY;
    while (wallIsHited(data->interH.xIntersect, data->interH.yIntersect, data) == 0){
        data->interH.xIntersect += data->interH.xstep;
        data->interH.yIntersect += data->interH.ystep;
    }
    data->p.h_dist = distancebetweenpoints(data->p.pos_x, data->p.pos_y, data->interH.xIntersect, data->interH.yIntersect);
    data->p.h_rayx = data->interH.xIntersect;
    data->p.h_rayy = data->interH.yIntersect;
    printf("horizontal -------- \n");

    printf("h ray x = %f \n", data->interH.xIntersect);
    printf("h ray y = %f \n", data->interH.yIntersect);

}

void upLeft_hIntersect(struct s_data *data){
    data->interH.firstY = (floor(data->p.pos_y / 30) * 30) - 1;
    data->interH.firstX = data->p.pos_x + ((data->interH.firstY - data->p.pos_y) / tan(data->p.rayAngle)) - 1;
    data->interH.ystep = -30;
    data->interH.xstep = data->interH.ystep / tan(data->p.rayAngle);
    if (data->interH.xstep > 0)
        data->interH.xstep *= -1;
    data->interH.xIntersect = data->interH.firstX;
    data->interH.yIntersect = data->interH.firstY;
    while (wallIsHited(data->interH.xIntersect, data->interH.yIntersect, data) == 0){
        data->interH.xIntersect += data->interH.xstep;
        data->interH.yIntersect += data->interH.ystep;
    }
    data->p.h_rayx = data->interH.xIntersect;
    data->p.h_rayy = data->interH.yIntersect;
    data->p.h_dist = distancebetweenpoints(data->p.pos_x, data->p.pos_y, data->p.h_rayx, data->p.h_rayy);
}

void horizontal_intersection(struct s_data *data){

    printf("ray Angle = %f \n", data->p.rayAngle * (180 / M_PI));
    printf("rot Angle = %f \n", data->p.rotationAngle * (180 / M_PI));
    data->p.rayAngle =  normalizeAngle(data->p.rayAngle);
    data->p.rotationAngle =  normalizeAngle(data->p.rotationAngle);
    if ((data->p.rayAngle > (270 * (M_PI / 180)) && data->p.rayAngle <= 2 * M_PI))
        upRight_hIntersect(data);
    else if ((data->p.rayAngle > 0 && data->p.rayAngle <= M_PI / 2))
        downRight_hIntersect(data);
    else if ((data->p.rayAngle > M_PI / 2 && data->p.rayAngle <= M_PI))
        downLeft_hIntersect(data);
    else if ((data->p.rayAngle > M_PI && data->p.rayAngle <= (3 *(M_PI / 2))))
        upLeft_hIntersect(data);
}