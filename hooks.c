/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguyout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 01:48:06 by mguyout           #+#    #+#             */
/*   Updated: 2017/10/27 08:02:31 by mguyout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int			ft_expose(t_fract *env)
{
	mlx_put_image_to_window(env->mlx.init, env->mlx.window,
			env->mlx.image, 0, 0);
	return (0);
}

int			ft_keyhook(int keycode, t_fract *env)
{
	if (keycode == 53)
		exit(0);
	else if (keycode == 123 || keycode == 124)
		keycode == 123 ? env->info.basex -= 0.006 : (env->info.basex += 0.006);
	else if (keycode == 126 || keycode == 125)
		keycode == 126 ? env->info.basey -= 0.006 : (env->info.basey += 0.006);
	else if (keycode == 49)
		env->info.pause = (env->info.pause == 0 ? 1 : 0);
	else if (keycode == 15)
	{
		env->info.basex = 0;
		env->info.basey = 0;
		env->info.zoom = 1;
	}
	else if (keycode == 13 || keycode == 1)
		keycode == 1 ? (ITT = ITT * 2 + 1) : (ITT /= 2);
	else
		return (0);
	ft_fractol(env);
	return (0);
}

void		ft_map(t_fract *env)
{
	if (ft_strcmp(env->info.type, "Mandelbrot") == 0)
		env->info.flag = 1;
	else if (ft_strcmp(env->info.type, "Julia") == 0)
		env->info.flag = 2;
	else if (ft_strcmp(env->info.type, "Burning_Ship") == 0)
		env->info.flag = 3;
	else
	{
		ft_putstr("Julia/Mandelbrot/Burning_Ship");
		exit(42);
	}
}
