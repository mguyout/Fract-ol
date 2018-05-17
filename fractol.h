/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguyout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 05:40:46 by mguyout           #+#    #+#             */
/*   Updated: 2017/10/27 06:59:55 by mguyout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include "minilibx_macos/mlx.h"
# include "Libft/libft.h"
# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include <time.h>
# define HEIGHT env->info.hauteur
# define WIDTH env->info.largeur
# define TMPI env->calc.tmpi
# define TMPR env->calc.tmpr
# define ITT env->info.itt
# define C_R env->calc.c_r
# define C_I env->calc.c_i
# define Z_R env->calc.z_r
# define Z_I env->calc.z_i
# define I env->calc.i

typedef struct		s_info
{
	double			largeur;
	double			hauteur;
	double			basex;
	double			basey;
	double			zoom;
	double			time;
	double			time_tmp;
	char			*type;
	int				pause;
	int				color;
	int				itt;
	int				flag;
	int				j;
	int				menu;
}					t_info;

typedef struct		s_calc
{
	double			z_i;
	double			tmpi;
	double			tmpr;
	double			z_r;
	double			c_i;
	double			c_r;
	int				i;
}					t_calc;

typedef struct		s_mlx
{
	void			*init;
	void			*window;
	void			*image;
	char			*data;
	int				bpp;
	int				size_line;
	int				endian;
}					t_mlx;

typedef struct		s_choose
{
	void			*img;
	void			*win;
	char			*data;
	char			*file;
	int				bpp;
	int				sizel;
	int				endian;
	int				hauteur;
	int				largeur;
}					t_choose;

typedef struct		s_fract
{
	t_info			info;
	t_mlx			mlx;
	t_calc			calc;
	t_choose		texture;
}					t_fract;

void				mandel(int x, int y, t_fract *env);
void				ft_select(int x, int y, t_fract *env);
void				ft_fractol(t_fract *env);
void				ft_init(t_fract **env);
void				pixel_to_image(int x, int y, t_fract *env);
int					ft_keyhook(int keycode, t_fract *env);
int					ft_expose(t_fract *env);
void				ft_map(t_fract *env);
#endif
