#include "cub.h"

int k_hook(int key, struct s_data *data){
    printf ("%d\n", key);
    double moveStep = 0;

    if (key == 124){
        data->p.turnDirection = 1;
        data->p.rotationAngle += (4 * (M_PI / 180));
        data->p.rayAngle += data->p.fieldAngle / data->p.raysNumber;
        data->p.newPx = data->p.pos_x + cos(data->p.rotationAngle) * 30;
        data->p.newPy = data->p.pos_y + sin(data->p.rotationAngle) * 30;
        // data->p.rayAngle += 2 * (M_PI / 180) * data->p.turnDirection;
        mlx_clear_window(data->mlx_ptr, data->win_ptr);
        drawMyMap(data);
        circleDraw(data); 
        DDA(data, 1);
        drawRays(data);
    }
    else if (key == 123){
        data->p.turnDirection = 1;
        data->p.rotationAngle -= (4 * (M_PI / 180));
        data->p.rayAngle += data->p.fieldAngle / data->p.raysNumber;
        data->p.newPx = data->p.pos_x + cos(data->p.rotationAngle) * 30;
        data->p.newPy = data->p.pos_y + sin(data->p.rotationAngle) * 30;
        // data->p.rayAngle += 2 * (M_PI / 180) * data->p.turnDirection; 
        mlx_clear_window(data->mlx_ptr, data->win_ptr);
        drawMyMap(data);
        circleDraw(data); 
        DDA(data, 1);
        drawRays(data);
    }
    else if (key == 125){
        data->p.walkDirection = -1;
        moveStep = data->p.walkDirection * data->p.moveSpeed;
        printf("move = %f\n", moveStep);
        data->p.newPx = (data->p.pos_x + cos(data->p.rotationAngle) * moveStep);
        data->p.newPy = (data->p.pos_y + sin(data->p.rotationAngle) * moveStep) ;
        data->p.newPPx = (data->p.newPx + cos(data->p.rotationAngle) * 30);
        data->p.newPPy = (data->p.newPy + sin(data->p.rotationAngle) * 30) ;
        if (wallIsHited(data->p.newPx, data->p.newPy, data) == 0){
            data->p.pos_x = data->p.newPx;
            data->p.pos_y = data->p.newPy;
        }
        mlx_clear_window(data->mlx_ptr, data->win_ptr);
        drawMyMap(data);
        circleDraw(data); 
        DDA(data, 2);
        drawRays(data);

        // }
    }
    else if (key == 126){
        data->p.walkDirection = +1;
        moveStep = data->p.walkDirection * data->p.moveSpeed;
        data->p.newPx = (data->p.pos_x + cos(data->p.rotationAngle) * moveStep);
        data->p.newPy = (data->p.pos_y + sin(data->p.rotationAngle) * moveStep) ;
        data->p.newPPx = (data->p.newPx + cos(data->p.rotationAngle) * 30);
        data->p.newPPy = (data->p.newPy + sin(data->p.rotationAngle) * 30) ;
        printf("move = %d\n", wallIsHited(data->p.newPx, data->p.newPy, data));
        if (wallIsHited(data->p.newPx, data->p.newPy, data) == 0){
            data->p.pos_x = data->p.newPx;
            data->p.pos_y = data->p.newPy;
        }
        mlx_clear_window(data->mlx_ptr, data->win_ptr);
        drawMyMap(data);
        circleDraw(data); 
        DDA(data, 2);
        drawRays(data);

    }

    return (0);

}

int release_k_hook(int key, struct s_data *data){
    if (key == 124)
        data->p.turnDirection = 0;
    else if (key == 123)
        data->p.turnDirection = 0;
    else if (key == 125)
        data->p.walkDirection = 0;
    else if (key == 126)
        data->p.walkDirection = 0;
    return (1);
}