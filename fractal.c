#include "minilibx-linux/mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define SIZE 500
#define RED 0x00FF0000
// #define SHIFT 1
#define WIDTH 1600
#define HEIGHT 1200


// typedef struct s_img
// {
//     void	*img;
// 	char	*addr;
// 	int		bits_per_pixel;
// 	int		endian;
// 	int		line_length;
// }				t_img;

typedef struct	s_data {
    void    *mlx;
    void    *win;
    void	*img;
    char	*addr;
    int		bits_per_pixel;
    int		line_length;
    int		endian;
}				t_data;

int close_x(t_data *data)
{
    mlx_destroy_image(data->mlx, data->img);
    mlx_destroy_window(data->mlx, data->win);
    mlx_destroy_display(data->mlx);
    exit(0);
}
int close_esc(int keycode, t_data *data)
{
    printf("%d\n", keycode); //-------------- what key
    if(keycode == 65307)
    {
        mlx_destroy_image(data->mlx, data->img);
        mlx_destroy_window(data->mlx, data->win);
        mlx_destroy_display(data->mlx);
        exit(0);
    }
}
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
int draw_square(int x_zero, int y_zero, t_data *data)
{
    // t_data data;
    // static int colorshift;
    // int points = SIZE * 4;
    // int tempsize = SIZE;
    int i = 0;
    // mlx_mouse_get_pos(data->mlx, data->win, &x_zero, &y_zero);
    // mlx_destroy_image(data->mlx, data->img);
    // mlx_clear_window(data->mlx, data->win);
    memset(data->addr, 0, WIDTH * HEIGHT * (data->bits_per_pixel / 8));
    
    while(i <= (SIZE/2)) //RB
    {
        my_mlx_pixel_put(data, x_zero + (SIZE/2), y_zero + i, RED);
        i++;
        // colorshift++;
    }
    i = 0;
    while(i <= (SIZE/2)) //RT
    {
        my_mlx_pixel_put(data, x_zero + (SIZE/2), y_zero - i, RED);
        i++;
        // colorshift++;
    }
    i = 0;
    while(i <= (SIZE/2)) //BR
    {
        my_mlx_pixel_put(data, x_zero + i, y_zero + (SIZE/2), RED);
        i++;
        // colorshift++;
    }
    i = 0;
    while(i <= (SIZE/2)) //BL
    {
        my_mlx_pixel_put(data, x_zero - i, y_zero + (SIZE/2), RED);
        i++;
        // colorshift++;
    }
    i = 0;
    while(i <= (SIZE/2)) //TL
    {
        my_mlx_pixel_put(data, x_zero - i, y_zero - (SIZE/2), RED);
        i++;
        // colorshift++;
    }
    i = 0;
    while(i <= (SIZE/2)) //TR
    {
        my_mlx_pixel_put(data, x_zero + i, y_zero - (SIZE/2), RED);
        i++;
        // colorshift++;
    }
    i = 0;
    while(i <= (SIZE/2)) //LT
    {
        my_mlx_pixel_put(data, x_zero - (SIZE/2), y_zero - i, RED);
        i++;
        // colorshift++;
    }
    i = 0;
    while(i <= (SIZE/2)) //LB
    {
        my_mlx_pixel_put(data, x_zero - (SIZE/2), y_zero + i, RED);
        i++;
        // colorshift++;
    }
    // printf("%d\n", RED + (colorshift * SHIFT));
    // if(colorshift > 150000)
    //     colorshift = -colorshift;
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
    return (0);
}
int main()
{
    t_data data;
    
    data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "MiniLibX Window"); 
	data.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
    
    // // my_mlx_pixel_put(&data, 5, 5, 0x00FF0000);
    draw_square(WIDTH/2, HEIGHT/2, &data);
    mlx_hook(data.win, 6, 1L<<6, draw_square, &data);

    mlx_hook(data.win, 17, 0, close_x, &data);
    mlx_key_hook(data.win, close_esc, &data);

	mlx_loop(data.mlx);
    // mlx_hook(data.win, 6, 1L<<6, draw_square, &data);
    // mlx_loop(data.mlx);
    return 0;
}
