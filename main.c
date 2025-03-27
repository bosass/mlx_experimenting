#include "minilibx-linux/mlx.h"
#include <stdlib.h>
#include <stdio.h>
#define SIZE 500
#define RED 0x00000000
#define SHIFT 1
#define WIDTH 1600
#define HEIGHT 1200

typedef struct s_data{
    void *mlx;
    void *win;
} t_data;

// int *colorshift()
// {
//     int* color = 0x00445500;
//     return((int *)color);
// }
int draw_square(int x_zero, int y_zero, t_data *data)
{
    static int colorshift;
    int points = SIZE * 4;
    int i = 0;
    int tempsize = SIZE;
    mlx_mouse_get_pos(data->mlx, data->win, &x_zero, &y_zero);
    mlx_clear_window(data->mlx, data->win);
    while(i <= (SIZE/2)) //RB
    {
        mlx_pixel_put(data->mlx, data->win, x_zero + (SIZE/2), y_zero + i, RED + (colorshift * SHIFT));
        i++;
        colorshift++;
    }
    i = 0;
    while(i <= (SIZE/2)) //RT
    {
        mlx_pixel_put(data->mlx, data->win, x_zero + (SIZE/2), y_zero - i, RED + (colorshift * SHIFT));
        i++;
        colorshift++;
    }
    i = 0;
    while(i <= (SIZE/2)) //BR
    {
        mlx_pixel_put(data->mlx, data->win, x_zero + i, y_zero + (SIZE/2), RED + (colorshift * SHIFT));
        i++;
        colorshift++;
    }
    i = 0;
    while(i <= (SIZE/2)) //BL
    {
        mlx_pixel_put(data->mlx, data->win, x_zero - i, y_zero + (SIZE/2), RED + (colorshift * SHIFT));
        i++;
        colorshift++;
    }
    i = 0;
    while(i <= (SIZE/2)) //TL
    {
        mlx_pixel_put(data->mlx, data->win, x_zero - i, y_zero - (SIZE/2), RED + (colorshift * SHIFT));
        i++;
        colorshift++;
    }
    i = 0;
    while(i <= (SIZE/2)) //TR
    {
        mlx_pixel_put(data->mlx, data->win, x_zero + i, y_zero - (SIZE/2), RED + (colorshift * SHIFT));
        i++;
        colorshift++;
    }
    i = 0;
    while(i <= (SIZE/2)) //LT
    {
        mlx_pixel_put(data->mlx, data->win, x_zero - (SIZE/2), y_zero - i, RED + (colorshift * SHIFT));
        i++;
        colorshift++;
    }
    i = 0;
    while(i <= (SIZE/2)) //LB
    {
        mlx_pixel_put(data->mlx, data->win, x_zero - (SIZE/2), y_zero + i, RED + (colorshift * SHIFT));
        i++;
        colorshift++;
    }
    printf("%d\n", RED + (colorshift * SHIFT));
    if(colorshift > 150000)
        colorshift = -colorshift;
}
int close_x(t_data *data)
{
    mlx_destroy_window(data->mlx, data->win);
    mlx_destroy_display(data->mlx);
    exit(0);
}
int close_esc(int keycode, t_data *data)
{
    printf("%d\n", keycode); //-------------- what key
    if(keycode == 65307)
    {
        mlx_destroy_window(data->mlx, data->win);
        mlx_destroy_display(data->mlx);
        exit(0);
    }
}

int main()
{
    t_data data;

    data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "MiniLibX Window"); 
    mlx_hook(data.win, 17, 0, close_x, &data);
    mlx_key_hook(data.win, close_esc, &data);
    mlx_hook(data.win, 6, 1L<<6, draw_square, &data);
    mlx_loop(data.mlx);
    return 0;
}
