#include "cub.h"

void normalizeAngle(struct s_data *data){
    // data->p.rayAngle = data->p.rayAngle / (2 * M_PI);
    // if (data->p.rayAngle < 0)
    //     data->p.rayAngle = (2 * M_PI) + data->p.rayAngle;
    if (data->p.rotationAngle < 0)
        data->p.rotationAngle = data->p.rotationAngle + (2 * M_PI);
    if (data->p.rotationAngle > (2 * M_PI))
        data->p.rotationAngle = data->p.rotationAngle - (2 * M_PI);
    if (data->p.rayAngle < 0)
        data->p.rayAngle = data->p.rayAngle + (2 * M_PI);
    if (data->p.rayAngle > (2 * M_PI))
        data->p.rayAngle = data->p.rayAngle - (2 * M_PI);
}

double distancebetweenpoints(double x1, double y1, double x2, double y2)
{
    return (sqrt((x2 -x1) * (x2 -x1) + (y2 - y1) * (y2 - y1)));
}

int playerFaceSide(struct s_data *data){
    int fDown = 0;
    int fUp = 0;
    int fRight = 0;
    int fLeft = 0;

    if (data->p.rayAngle > 0 && data->p.rayAngle < M_PI)
        fDown = 1;
    else if (data->p.rayAngle <= (2 * M_PI) && data->p.rayAngle > M_PI)
        fUp = 1;
    if (data->p.rayAngle < (M_PI / 2) || data->p.rayAngle > (3 * (M_PI / 2)))
        fRight = 1;
    else if (data->p.rayAngle > (M_PI / 2) || data->p.rayAngle < (3 * (M_PI / 2)))
        fLeft = 1;
    return (0);
}

void horizontal_intersection(struct s_data *data){

    double xstep; // delta-x
    double ystep; // delta-y 

    double xIntersect;
    double yIntersect;

    double distance;

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
    // if (data->p.rayAngle > 1.5 * M_PI && data->p.rayAngle < 2 * M_PI){
    //     firstY = floor(data->p.pos_y / 30) * 30;
    //     firstX = data->p.pos_x + ((firstY - data->p.pos_y) / tan(data->p.rayAngle));
    //     ystep = 30;
    //     xstep = ystep / tan(data->p.rayAngle);
    // }
    // if (data->p.rayAngle > 0 && data->p.rayAngle < M_PI / 2){
    //     firstY = floor(data->p.pos_y / 30) * 30;
    //     firstY += 30;
    //     firstX = data->p.pos_x + ((firstY - data->p.pos_y) / tan(data->p.rayAngle));
    //     ystep = 30 * -1;
    //     xstep = ystep / tan(data->p.rayAngle);
    // }
    // if (data->p.rayAngle > M_PI / 2 && data->p.rayAngle < M_PI){
    //     firstY = floor(data->p.pos_y / 30) * 30;
    //     firstY += 30;
    //     firstX = data->p.pos_x + ((firstY - data->p.pos_y) / tan(data->p.rayAngle));
    //     ystep = 30 * -1;
    //     xstep = ystep / tan(data->p.rayAngle);
    //     xstep *= -1;
    // }
    firstY = floor(data->p.pos_y / 30) * 30;
    if (data->p.rayAngle > 0 && data->p.rayAngle < M_PI)
        firstY += 30;
    firstX = data->p.pos_x + ((firstY - data->p.pos_y) / tan(data->p.rayAngle));
    ystep = 30;
    if (data->p.rayAngle > M_PI && data->p.rayAngle < (M_PI * 2))
        ystep *= -1;
    xstep = ystep / tan(data->p.rayAngle);
    // if (data->p.rayAngle > (270 * (M_PI / 180)) && data->p.rayAngle < (90 * (M_PI / 180)))
    if (xstep > 0 && ((data->p.rayAngle > (270 * (M_PI / 180)) && data->p.rayAngle < (360 * (M_PI / 180))) || (data->p.rayAngle > (0 * (M_PI / 180)) && data->p.rayAngle < (90 * (M_PI / 180)))))
        xstep *= -1;
    if (xstep < 0 && ((data->p.rayAngle > (90 * (M_PI / 180)) && data->p.rayAngle < (180 * (M_PI / 180))) || (data->p.rayAngle > (180 * (M_PI / 180)) && data->p.rayAngle < (270 * (M_PI / 180)))))
        xstep *= -1;



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

    xIntersect = firstX;
    yIntersect = firstY;

    while (wallIsHited(xIntersect, yIntersect, data) == 0){
        xIntersect -= xstep;
        yIntersect += ystep;
    }
    // if (wallIsHited(xIntersect, yIntersect, data) == 1)
        distance = distancebetweenpoints(data->p.pos_x, data->p.pos_y, xIntersect, yIntersect);
    data->p.rayX = xIntersect;
    data->p.rayY = yIntersect;

}

void vertical_intersection(struct s_data *data){

    double xstep; // delta-x
    double ystep; // delta-y 

    double xIntersect;
    double yIntersect;

    double distance;

    /* get the first intersection point */
    double firstX = 0.0;
    double firstY = 0.0;

    firstX = floor(data->p.pos_x / 30) * 30;
    if (data->p.rayAngle > (270 * (M_PI / 180)) && data->p.rayAngle < M_PI / 2)
        firstX += 30;
    firstY = data->p.pos_y + ((firstX - data->p.pos_x) * tan(data->p.rayAngle));
    xstep = 30;
    if (data->p.rayAngle > M_PI / 2 && data->p.rayAngle < (270 * (M_PI / 180)))
        xstep *= -1;
    ystep = xstep * tan(data->p.rayAngle);
    // if (data->p.rayAngle > (270 * (M_PI / 180)) && data->p.rayAngle < (90 * (M_PI / 180)))
    if (ystep > 0 && (((data->p.rayAngle > M_PI) && data->p.rayAngle < (270 * (M_PI / 180))) || (data->p.rayAngle > (270 * (M_PI / 180)) && data->p.rayAngle < (360 * (M_PI / 180)))))
        ystep *= -1;
    if (ystep < 0 && ((data->p.rayAngle > 0 && data->p.rayAngle < (M_PI / 2)) || ((data->p.rayAngle > (M_PI / 2)) && data->p.rayAngle < M_PI)))
        ystep *= -1;
    xIntersect = firstX;
    yIntersect = firstY;
    // if ()

    while (wallIsHited(xIntersect, yIntersect, data) == 0){

        xIntersect += xstep;
        yIntersect += ystep;
    }
    // if (wallIsHited(xIntersect, yIntersect, data) == 1)
        distance = distancebetweenpoints(data->p.pos_x, data->p.pos_y, xIntersect, yIntersect);
    data->p.rayX = xIntersect;
    data->p.rayY = yIntersect;
}