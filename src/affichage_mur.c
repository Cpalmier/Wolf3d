/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affichage_mur.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalmier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 17:27:02 by cpalmier          #+#    #+#             */
/*   Updated: 2019/03/01 20:13:02 by cpalmier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

static int		affichage_ciel(double h_percue, t_env *env, int x, float y)
{
	float	lim;
	float	pourcent_x;
	float	pourcent_y;
	int		i;
	int		j;

	y = -1;
	lim = (env->h_regard - (h_percue / 2));
	pourcent_x = (100. * x) / env->nb_colonne;
	while (++y < lim && y < 870.)
	{
		pourcent_y = (100. * y) / (870.);
		i = 4 * x + y * env->s_l;
		j = 4 * (int)(env->texture5.width * pourcent_x / 100)
			+ (int)(env->texture5.height * (pourcent_y + (100 - (env->h_regard
								* 100 / 870.))) / 100) * env->texture5.s_l;
		env->img_str[i] = env->texture5.img_str[j];
		env->img_str[i + 1] = env->texture5.img_str[j + 1];
		env->img_str[i + 2] = env->texture5.img_str[j + 2];
	}
	return (y - 1);
}

static void		affichage(double h_percue, t_env *env, int x, float a)
{
	float	y;
	float	lim;

	y = 0;
	y = affichage_ciel(h_percue, env, x, y);
	lim = (env->h_regard + (h_percue / 2));
	if (env->orientation == 1)
	{
		while (a >= 0. && a < 180. && ++y < lim && y < 870.)
			put_texture_img(env, h_percue, y, &env->texture1);
		while (!(a >= 0. && a < 180.) && ++y < lim && y < 870.)
			put_texture_img(env, h_percue, y, &env->texture2);
	}
	else if (env->orientation == 2)
	{
		while (a >= 90. && a < 270. && ++y < lim && y < 870.)
			put_texture_img(env, h_percue, y, &env->texture3);
		while (!(a >= 90. && a < 270.) && ++y < lim && y < 870.)
			put_texture_img(env, h_percue, y, &env->texture4);
	}
	y -= 2;
	while (++y < 870.)
		put_pxl_img(env, x, y, 7);
}

static double	verif_angle(double angle)
{
	if (angle < 0.)
	{
		while (angle < 0.)
			angle = angle + 360.;
	}
	else if (angle > 360.)
	{
		while (angle > 360.)
			angle = angle - 360.;
	}
	if (angle == 360.)
		angle = 0.;
	return (angle);
}

void			affichage_mur(t_env *env)
{
	double	a;
	double	dist;
	double	h_percue;
	int		x;

	a = env->d_regard + 30;
	a = verif_angle(a);
	x = 0;
	while (x < (env->nb_colonne))
	{
		env->angle = a;
		env->angle = verif_angle(env->angle);
		dist = detection_mur(env);
		dist = dist * cos((a - env->d_regard) * M_PI / 180);
		h_percue = env->d_ecran * (env->h_mur / dist);
		env->img_x = x;
		affichage(h_percue, env, x, env->angle);
		a -= (60. / (env->nb_colonne));
		x++;
	}
}
