#include "cub.h"

double normalizeAngle(double angle){
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

void upRight_vIntersect(struct s_data *data){
    data->interV.firstX = floor(data->p.pos_x / TILE_SIZE) * TILE_SIZE  + TILE_SIZE + 1;
    data->interV.firstY = data->p.pos_y + ((data->interV.firstX - data->p.pos_x) * tan(data->p.rayAngle)) - 1;
    data->interV.xstep = TILE_SIZE;
    data->interV.ystep = data->interV.xstep * tan(data->p.rayAngle);
    if (data->interV.ystep > 0)
        data->interV.ystep *= -1;
    data->interV.xIntersect = data->interV.firstX;
    data->interV.yIntersect = data->interV.firstY;
    while (wallIsHited(data->interV.xIntersect, data->interV.yIntersect, data) == 0){
        data->interV.xIntersect += data->interV.xstep;
        data->interV.yIntersect += data->interV.ystep;
    }
    data->p.v_dist = distancebetweenpoints(data->p.pos_x, data->p.pos_y, data->interV.xIntersect, data->interV.yIntersect);
    data->p.v_rayx = data->interV.xIntersect;
    data->p.v_rayy = data->interV.yIntersect;
}

void downRight_vIntersect(struct s_data *data){
    data->interV.firstX = (floor(data->p.pos_x / TILE_SIZE) * TILE_SIZE) + TILE_SIZE + 1;
    data->interV.firstY = data->p.pos_y + ((data->interV.firstX - data->p.pos_x) * tan(data->p.rayAngle)) + 1;
    data->interV.xstep = TILE_SIZE;
    data->interV.ystep = data->interV.xstep * tan(data->p.rayAngle);
    if (data->interV.ystep < 0)
        data->interV.ystep *= -1;
    data->interV.xIntersect = data->interV.firstX;
    data->interV.yIntersect = data->interV.firstY;
    while (wallIsHited(data->interV.xIntersect, data->interV.yIntersect, data) == 0){
        data->interV.xIntersect += data->interV.xstep;
        data->interV.yIntersect += data->interV.ystep;
    }
    data->p.v_dist = distancebetweenpoints(data->p.pos_x, data->p.pos_y, data->interV.xIntersect, data->interV.yIntersect);
    data->p.v_rayx = data->interV.xIntersect;
    data->p.v_rayy = data->interV.yIntersect;
}
void downLeft_vIntersect(struct s_data *data){
    data->interV.firstX = (floor(data->p.pos_x / TILE_SIZE) * TILE_SIZE) - 1;
    data->interV.firstY = data->p.pos_y + ((data->interV.firstX - data->p.pos_x) * tan(data->p.rayAngle)) + 1;
    data->interV.xstep = -TILE_SIZE;
    data->interV.ystep = data->interV.xstep * tan(data->p.rayAngle);
    if (data->interV.ystep < 0)
        data->interV.ystep *= -1;
    data->interV.xIntersect = data->interV.firstX;
    data->interV.yIntersect = data->interV.firstY;
    while (wallIsHited(data->interV.xIntersect, data->interV.yIntersect, data) == 0){
        data->interV.xIntersect += data->interV.xstep;
        data->interV.yIntersect += data->interV.ystep;
    }
    data->p.v_rayx = data->interV.xIntersect;
    data->p.v_rayy = data->interV.yIntersect;
    data->p.v_dist = distancebetweenpoints(data->p.pos_x, data->p.pos_y, data->p.v_rayx, data->p.v_rayy);
    printf("vertical -------- \n");

    printf("v ray x = %f \n", data->interV.xIntersect);
    printf("v ray y = %f \n", data->interV.yIntersect);
}
void upLeft_vIntersect(struct s_data *data){
    data->interV.firstX = (floor(data->p.pos_x / TILE_SIZE) * TILE_SIZE) - 1;
        data->interV.firstY = data->p.pos_y + ((data->interV.firstX - data->p.pos_x) * tan(data->p.rayAngle)) - 1;
        data->interV.xstep = -TILE_SIZE;
        data->interV.ystep = data->interV.xstep * tan(data->p.rayAngle);
        if (data->interV.ystep > 0)
            data->interV.ystep *= -1;
        data->interV.xIntersect = data->interV.firstX;
        data->interV.yIntersect = data->interV.firstY;

        while (wallIsHited(data->interV.xIntersect, data->interV.yIntersect, data) == 0){
            data->interV.xIntersect += data->interV.xstep;
            data->interV.yIntersect += data->interV.ystep;
        }
        data->p.v_rayx = data->interV.xIntersect;
        data->p.v_rayy = data->interV.yIntersect;
        data->p.v_dist = distancebetweenpoints(data->p.pos_x, data->p.pos_y, data->p.v_rayx, data->p.v_rayy);
}

void vertical_intersection(struct s_data *data){

    data->p.rayAngle =  normalizeAngle(data->p.rayAngle);
    data->p.rotationAngle =  normalizeAngle(data->p.rotationAngle);
    if ((data->p.rayAngle > (270 * (M_PI / 180)) && data->p.rayAngle <= 2 * M_PI))
        upRight_vIntersect(data);
    else if ((data->p.rayAngle > 0 && data->p.rayAngle <= M_PI / 2))
        downRight_vIntersect(data);
    else if ((data->p.rayAngle > M_PI / 2 && data->p.rayAngle <= M_PI))
        downLeft_vIntersect(data);
    else if ((data->p.rayAngle > M_PI && data->p.rayAngle <= (3 *(M_PI / 2))))
        upLeft_vIntersect(data);
}