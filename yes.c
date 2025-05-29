#define _USE_MATH_DEFINES
#include "minilibx-linux/mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#define SIZE 50
#define RED 0x00FF0000
// #define SHIFT 1
#define WIDTH 800
#define HEIGHT 800
#define ITERATIONS 420
#define ESC 4
#define INCOLOR 0x00010101
#define COLORSHIFT 10
#define WHITE 0x00FFFFFF
#define BLUE 0x000000FF
#define LYL 0x005D10A1
#define PINK 0x00ed11d7
#define BLACK 0


// typedef struct s_fractal
// {
//     double shiftx;
//     double shifty;
//     double zoom;
// }              t_fractal;


typedef struct	s_data {
    void    *mlx;
    void    *win;
    void	*img;
    char	*addr;
    char    *ftype;
    double  jrl;
    double  jim;
    int		bits_per_pixel;
    int		line_length;
    int		endian;
    double shiftx;
    double shifty;
    double zoom;
}		        t_data;

typedef struct s_complex{
    double x;
    double y;
}              t_complex;

typedef struct s_color{
    unsigned int r;
    unsigned int g;
    unsigned int b;
}              t_color;

t_complex csqr(t_complex c)
{
    t_complex out;
    
    out.x = (c.x * c.x) - (c.y * c.y);
    out.y = c.y * c.x * 2;
    return (out);
}

t_complex cadd(t_complex c1, t_complex c2)
{
    t_complex out;

    out.x = c1.x + c2.x;
    out.y = c1.y + c2.y;
    return (out);
}
double chyp(t_complex c)
{
    return(c.x * c.x + (c.y * c.y));
}

double map(double unscaled_num, double new_min, double new_max, double old_max)
{
    return (new_max - new_min) * unscaled_num / old_max + new_min;
}
int intmap(int unscaled_num, int new_min, int new_max, int old_max)
{
    return (new_max - new_min) * unscaled_num / old_max + new_min;
}

// int close_x(t_data *data)
// {
//     mlx_destroy_image(data->mlx, data->img);
//     mlx_destroy_window(data->mlx, data->win);
//     mlx_destroy_display(data->mlx);
//     exit(0);
// }

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
    {
        dst = data->addr + (y * data->line_length + 
            x * (data->bits_per_pixel / 8));
        *(unsigned int*)dst = color;
    }
}

unsigned int mandelbrot(int x, int y, t_data *data)
{
    t_complex c;
    t_complex z;
    unsigned int i;

    c.x = map(x, -data->zoom + data->shiftx, 
        data->zoom + data->shiftx, WIDTH);
    c.y = map(y, data->zoom + data->shifty, 
        -data->zoom + data->shifty, HEIGHT);
    z = c;
    i = 0;
    while(i < ITERATIONS)
    {
        if(chyp(c) >= ESC)
            return (i);
        c = cadd(csqr(c), z);
        i++;
    }
    return (0);
}
unsigned int mandelbrot_in(int x, int y, t_data *data)
{
    t_complex c;
    t_complex z;
    unsigned int i;

    c.x = map(x, -data->zoom + data->shiftx, 
        data->zoom + data->shiftx, WIDTH);
    c.y = map(y, data->zoom + data->shifty, 
        -data->zoom + data->shifty, HEIGHT);
    z = c;
    i = 0;
    double out = 0;
    while(i < ITERATIONS)
    {
        if(chyp(c) >= ESC)
            return (0);
        else if(chyp(c) > out)
            out = chyp(c);
        c = cadd(csqr(c), z);
        i++;
    }
    i = map(out, 0, ITERATIONS, 4);
    return (i);
}
t_color unbox(unsigned int color)     // c = ((color.r << 16) | (color.g << 8) | color.b); to box
{
    t_color out;

    out.r = (color >> 16) & 0xFF;
    out.g = (color >> 8) & 0xFF;
    out.b = color & 0xFF;
    return (out);
}
unsigned int ft_color(unsigned int c, int x, int y)
{
    if (c == 0)
        return 0;
    return(c * ((y - x) * 50));
}
unsigned int ft_color_in(unsigned int c, int x, int y)
{
    if (c == 0)
        return 0;
    return(c * ((y - x) * 50));
}
void render_mandelbrot(t_data *data)
{
    int x;
    int y;
    unsigned int color;

    x = 0;
    y = 0;
    while(y < HEIGHT)
    {
        x = 0;
        while(x < WIDTH)
        {
            color = ft_color(mandelbrot(x, y, data), x, y);
            if(!color)
                color = ft_color(mandelbrot_in(x, y, data), y, x);
            my_mlx_pixel_put(data, x, y, color);
            x++;
        }
        y++;
    }
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}
unsigned int julia(int x, int y, t_data *data)
{
    t_complex c;
    t_complex z;
    unsigned int i;

    c.x = map(x, -data->zoom + data->shiftx, 
        data->zoom + data->shiftx, WIDTH);
    c.y = map(y, data->zoom + data->shifty, 
        -data->zoom + data->shifty, HEIGHT);
    z.x = data->jrl;
    z.y = data->jim;
    i = 0;
    while(i < ITERATIONS)
    {
        if(chyp(c) >= ESC)
            return (i);
        c = cadd(csqr(c), z);
        i++;
    }
    return (i);
}
void render_julia(t_data *data)
{
    int x;
    int y;
    unsigned int color;

    x = 0;
    y = 0;
    while(y < HEIGHT)
    {
        x = 0;
        while(x < WIDTH)
        {
            color = julia(x, y, data) * 13;
            my_mlx_pixel_put(data, x, y, color);
            x++;
        }
        y++;
    }
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}
t_complex absc(t_complex n)
{
    if (n.x < 0)
        n.x = -n.x;
    if (n.y < 0)
        n.y = -n.y;
    return(n);
}
double absv(double n)
{
    if (n < 0)
        return(-n);
    return (n);
}

int burn(int x, int y, t_data *data)
{
    t_complex c;
    t_complex z;
    unsigned int i;

    c.x = map(x, -data->zoom + data->shiftx, 
        data->zoom + data->shiftx, WIDTH);
    c.y = map(y, -data->zoom - data->shifty, 
        data->zoom - data->shifty, HEIGHT);
    z = c;
    i = 0;
    while(i < ITERATIONS)
    {
        if(chyp(c) >= ESC)
            return (i);
        c.x = absv(c.x);
        c.y = absv(c.y);
        c = cadd(csqr(c), z);
        i++;
    }
    return (0);
}
void render_burn(t_data *data)
{
    int x;
    int y;
    unsigned int color;

    x = 0;
    y = 0;
    while(y < HEIGHT)
    {
        x = 0;
        while(x < WIDTH)
        {
            color = burn(x, y, data) * 13;
            my_mlx_pixel_put(data, x, y, color);
            x++;
        }
        y++;
    }
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

void render(t_data *data)
{
    if (!strncmp(data->ftype, "mandelbrot", 10))
        render_mandelbrot(data);
    if (!strncmp(data->ftype, "julia", 5))
        render_julia(data);
    if (!strncmp(data->ftype, "burn", 4))
        render_burn(data);
    // render_julia(data, -0.7, 0.27015);
}
int clean_exit(t_data *data)
{
    mlx_destroy_image(data->mlx, data->img);
    mlx_destroy_window(data->mlx, data->win);
    mlx_destroy_display(data->mlx);
    exit(0);
}
int xddkey(int keycode, t_data *data)
{
    // printf("%d\n", keycode); //-------------- what key  left:65361 right:65363 up:65362 down:65364
    if(keycode == 65307)
    {
        clean_exit(data);
    }
    else if (keycode == 65361) //left
        data->shiftx -= data->zoom / 4;
    else if (keycode == 65363) //right
        data->shiftx += data->zoom / 4;
    else if (keycode == 65362) //up
        data->shifty += data->zoom / 4;
    else if (keycode == 65364) //down
        data->shifty -= data->zoom / 4;
    render(data);
    return (0);
}

int xddmouse(int button, int x, int y, t_data *data)
{

    // printf("%d\n", button);
    if (button == 4)
        data->zoom *= 0.6;
    else if(button == 5)
        data->zoom = data->zoom / 0.6;
    render(data);
    (void)x;
    (void)y;
    return (0);
}
double powerof(int x)
{
    double i;

    i = 1;
    while(x > 1)
    {
        i = i * 10;
        x--;
    }
    return (i);
}
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((s1[i] == s2[i]) && (s1[i] != '\0') && (i < n - 1))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
int	ft_atoi(const char *str)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	while ((*str == 32) || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		sign *= -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + *str - '0';
		str++;
	}
	return (result * sign);
}

double	ft_atof(const char *str)
{
	double	result;
    int i;
    int sign;

    i = 0;
    sign = 1;
	result = ft_atoi(str);
    if (*str == '-')
    {
        result  = -result;
        sign = -1;
    }

    while (*str != '.' && *str != ',')
        str++;
    str++;
    while ((*str >= '0' && *str <= '9') )
	{
		result = result * 10 + *str - '0';
		str++;
        i++;
	}
    result = (result) / powerof(i + 1) * sign;
	return (result);
}
void friendly_reminder(void)
{
    write(1, "use one of these parameters:\nmandelbrot\njulia <n> <n>\nburn\n", 59);
    exit (0);
}
void params(t_data *data, int ac, char **av)
{
    
    if(ac >= 2)
    {
        if(!strncmp(av[1], "mandelbrot", 10))
            data->ftype = "mandelbrot";
        else if(!strncmp(av[1], "burn", 4))
            data->ftype = "burn";
        else if(!strncmp(av[1], "julia", 5))
        {
            if (ac >= 4)
            {
                data->ftype = "julia";
                data->jrl = atof(av[2]);
                data->jim = atof(av[3]);
            }
            else
                friendly_reminder();
        }
        else
            friendly_reminder();
    }
    else
        friendly_reminder();
}

int main(int ac, char **av)
{
    t_data data;

    params(&data, ac, av);
    data.zoom = 1.5;
    
    data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "sas"); 
	data.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	data.addr = mlx_get_data_addr(data.img,
         &data.bits_per_pixel, &data.line_length, &data.endian);
    
    render(&data);

    mlx_hook(data.win, 17, 0, clean_exit, &data);
    mlx_key_hook(data.win, xddkey, &data);
    mlx_mouse_hook(data.win, xddmouse, &data);

	mlx_loop(data.mlx);
    return 0;
}