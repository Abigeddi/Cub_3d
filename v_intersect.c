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

void upRight_vIntersect(struct s_data *data){
    data->interV.firstX = floor(data->p.pos_x / 30) * 30 + 1;
    data->interV.firstY = data->p.pos_y + ((data->interV.firstX - data->p.pos_x) * tan(data->p.rayAngle)) - 1;
    data->interV.xstep = 30;
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
    data->interV.firstX = (floor(data->p.pos_x / 30) * 30) + 30 + 1;
    data->interV.firstY = data->p.pos_y + ((data->interV.firstX - data->p.pos_x) * tan(data->p.rayAngle)) + 1;
    data->interV.xstep = 30;
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
    data->interV.firstX = (floor(data->p.pos_x / 30) * 30) + 30 - 1;
    data->interV.firstY = data->p.pos_y + ((data->interV.firstX - data->p.pos_x) * tan(data->p.rayAngle)) + 1;
    data->interV.xstep = -30;
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
}
void upLeft_vIntersect(struct s_data *data){
    data->interV.firstX = (floor(data->p.pos_x / 30) * 30) - 1;
        data->interV.firstY = data->p.pos_y + ((data->interV.firstX - data->p.pos_x) * tan(data->p.rayAngle)) - 1;
        data->interV.xstep = -30;
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
    printf("vertical --------\n");
    printf("ray Angle = %f \n", data->p.rayAngle * (180 / M_PI));
    printf("rot Angle = %f \n", data->p.rotationAngle * (180 / M_PI));
    if ((data->p.rayAngle > (270 * (M_PI / 180)) && data->p.rayAngle <= 2 * M_PI))
        upRight_vIntersect(data);
    else if ((data->p.rayAngle > 0 && data->p.rayAngle <= M_PI / 2))
        downRight_vIntersect(data);
    else if ((data->p.rayAngle > M_PI / 2 && data->p.rayAngle <= M_PI))
        downLeft_vIntersect(data);
    else if ((data->p.rayAngle > M_PI && data->p.rayAngle <= (3 *(M_PI / 2))))
        upLeft_vIntersect(data);
}