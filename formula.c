/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formula.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguyout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 01:47:40 by mguyout           #+#    #+#             */
/*   Updated: 2017/10/27 07:03:40 by mguyout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		ft_julia(int x, int y, t_fract *env)
{
	if (C_R == 0)
	{
		C_R = -0.7 + env->info.basex;
		C_I = 0.27 + env->info.basey;
	}
	Z_R = 1.5 * (x - WIDTH / 2) / (0.5 * env->info.zoom * WIDTH) +
		env->info.basex;
	Z_I = (y - HEIGHT / 2) / (0.5 * env->info.zoom * HEIGHT) +
		env->info.basey;
	I = -1;
	while (Z_R * Z_R + Z_I * Z_I < 4 && ++I < ITT)
	{
		TMPR = Z_R;
		TMPI = Z_I;
		Z_R = TMPR * TMPR - TMPI * TMPI + C_R;
		Z_I = 2 * TMPI * TMPR + C_I;
	}
}

void		ft_burningship(int x, int y, t_fract *env)
{
	if (env->info.basex == 0)
		env->info.basex = -0.5;
	C_R = 1.5 * (x - WIDTH / 2) / (0.5 * env->info.zoom * WIDTH) +
		env->info.basex;
	C_I = 1.5 * (y - HEIGHT / 2) / (0.5 * env->info.zoom * HEIGHT) +
		env->info.basey;
	Z_R = 0;
	Z_I = 0;
	I = -1;
	while (Z_R * Z_R + Z_I * Z_I < 4 && ++I < ITT)
	{
		TMPR = Z_R;
		TMPI = Z_I;
		Z_R = (TMPR * TMPR) - (TMPI * TMPI) + C_R;
		Z_I = 2 * fabs(TMPR * TMPI) + C_I;
	}
}

void		ft_mandelbrot(int x, int y, t_fract *env)
{
	if (env->info.basex == 0)
		env->info.basex = -0.5;
	C_R = 1.5 * (x - WIDTH / 2) / (0.5 * env->info.zoom * WIDTH) +
		env->info.basex;
	C_I = (y - HEIGHT / 2) / (0.5 * env->info.zoom * HEIGHT) +
		env->info.basey;
	Z_R = 0;
	Z_I = 0;
	I = -1;
	while (Z_R * Z_R + Z_I * Z_I < 4 && ++I < ITT)
	{
		TMPR = Z_R;
		TMPI = Z_I;
		Z_R = TMPR * TMPR - TMPI * TMPI + C_R;
		Z_I = 2 * TMPI * TMPR + C_I;
	}
}

void		ft_mapselect(int x, int y, t_fract *env)
{
	if (env->info.flag == 1)
		ft_mandelbrot(x, y, env);
	else if (env->info.flag == 2)
		ft_julia(x, y, env);
	else if (env->info.flag == 3)
		ft_burningship(x, y, env);
	else
	{
		ft_putstr("Julia/Mandelbrot/Burning_Ship");
		exit(42);
	}
}

void		ft_fractol(t_fract *env)
{
	int		x;
	int		y;

	env->mlx.data = mlx_get_data_addr(env->mlx.image, &env->mlx.bpp,
			&env->mlx.size_line, &env->mlx.endian);
	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			ft_mapselect(x, y, env);
			pixel_to_image(x, y, env);
		}
	}
	mlx_put_image_to_window(env->mlx.init, env->mlx.window,
			env->mlx.image, 0, 0);
	env->info.time_tmp = env->info.time / CLOCKS_PER_SEC * 10;
	env->info.time = clock();
}
