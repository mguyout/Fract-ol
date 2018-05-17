/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguyout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 01:47:51 by mguyout           #+#    #+#             */
/*   Updated: 2017/10/27 07:00:23 by mguyout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		pixel_to_image(int x, int y, t_fract *env)
{
	int		pos;

	pos = (x * env->mlx.bpp / 8) + (y * env->mlx.size_line);
	env->mlx.data[pos] = env->info.color * I;
	env->mlx.data[pos + 1] = ((env->info.color * I) >> 8);
	env->mlx.data[pos + 2] = ((env->info.color * I) >> 16);
}

int			ft_posmouse(int x, int y, t_fract *env)
{
	if (env->info.pause == 0)
	{
		C_R = ((double)x / (double)WIDTH);
		C_I = ((double)y / (double)HEIGHT);
		ft_fractol(env);
	}
	else
		mlx_string_put(env->mlx.init, env->mlx.window,
			350, 50, 0x960018, "PAUSED");
	return (0);
}

int			ft_movehook(int keycode, int x, int y, t_fract *env)
{
	if (keycode == 5)
	{
		env->info.zoom *= pow(1.001, env->info.time_tmp);
		env->info.basex += (x - WIDTH / 2) / (WIDTH / 2 * env->info.zoom) / 8;
		env->info.basey += (x - HEIGHT / 2) / (HEIGHT / 2 * env->info.zoom) / 8;
	}
	else if (keycode == 4)
	{
		env->info.zoom /= pow(1.001, env->info.time_tmp);
		env->info.basex -= (x - WIDTH / 2) / (WIDTH / 2 * env->info.zoom) / 8;
		env->info.basey -= (y - HEIGHT / 2) / (HEIGHT / 2 * env->info.zoom) / 8;
	}
	else
		return (0);
	ft_fractol(env);
	return (0);
}

void		ft_init(t_fract **env)
{
	(*env)->info.hauteur = 700;
	(*env)->info.largeur = 700;
	(*env)->mlx.init = mlx_init();
	(*env)->mlx.window = mlx_new_window((*env)->mlx.init, (*env)->info.largeur,
			(*env)->info.hauteur, "Fractol");
	(*env)->mlx.image = mlx_new_image((*env)->mlx.init, (*env)->info.largeur,
			(*env)->info.hauteur);
	(*env)->info.basex = 0;
	(*env)->info.basey = 0;
	(*env)->info.zoom = 1;
	(*env)->info.itt = 50;
	(*env)->info.color = 420;
	(*env)->calc.c_r = 0;
	(*env)->info.menu = 0;
}

int			main(int argc, char **argv)
{
	t_fract	*env;

	if (!(env = (t_fract *)ft_memalloc(sizeof(t_fract))))
		return (0);
	if (argc == 2)
	{
		if (!(env->info.type = ft_memalloc(sizeof(char *) *
			ft_strlen(argv[1]))))
			return (0);
		ft_strcpy(env->info.type, argv[1]);
		ft_init(&env);
		ft_map(env);
		ft_fractol(env);
		mlx_expose_hook(env->mlx.window, ft_expose, env);
		mlx_hook(env->mlx.window, 2, 0, ft_keyhook, env);
		mlx_mouse_hook(env->mlx.window, ft_movehook, env);
		mlx_hook(env->mlx.window, 6, 0, ft_posmouse, env);
		mlx_loop(env->mlx.init);
	}
	else
		ft_putstr("Julia/Mandelbrot/Burning_Ship");
	return (0);
}
