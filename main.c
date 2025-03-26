#include "minilibx-linux/mlx.h"
#include <stdlib.h>
#include <stdio.h>
#define SIZE 20

typedef struct s_data{
    void *mlx;
    void *win;
} t_data;

int draw_something(int x, int y, t_data *data)
{
    int points = SIZE * 4;
    int i = 0 - (SIZE/2);
    int tempsize = SIZE;
    mlx_mouse_get_pos(data->mlx, data->win, &x, &y);
    mlx_clear_window(data->mlx, data->win);
    while(points--)
    {
        mlx_pixel_put(data->mlx, data->win, x + (SIZE/2), y + i, 0x00FF0000);
        i++;
    }

}
int close_x(t_data *data)
{
    mlx_destroy_window(data->mlx, data->win);
    mlx_destroy_display(data->mlx);
    exit(0);
}
int close_esc(int keycode, t_data *data)
{
    printf("%d \n", keycode); //-------------- what key
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
    int x;
    int y;

    data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, 800, 600, "MiniLibX Window"); 
    mlx_hook(data.win, 17, 0, close_x, &data);
    mlx_key_hook(data.win, close_esc, &data);
    mlx_hook(data.win, 6, 1L<<6, draw_something, &data);
    mlx_loop(data.mlx);
    return 0;
}
