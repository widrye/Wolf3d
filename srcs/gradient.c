/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   gradient.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: widrye <widrye@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/25 17:44:54 by ztrouill     #+#   ##    ##    #+#       */
/*   Updated: 2020/02/17 21:18:48 by widrye      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/wolf.h"

static int				get_light(int start, int end, double percentage)
{
	return ((int)((1 - percentage) * start + percentage * end));
}

#include <stdio.h>

int						get_color(int range, int n)
{
	t_vector		color;
	int				red;
	int				green;
	int				blue;
	double			percentage;


	color.x = GREY_DARK;
	color.y = GREY_LIGHT;
	percentage = (range) ? (double)n / (double)range : 1;
	red = get_light(((int)color.x >> 16) & 0xff, ((int)color.y >> 16)
			& 0xff, percentage);
	green = get_light(((int)color.x >> 8) & 0xff, ((int)color.y >> 8)
			& 0xff, percentage);
	blue = get_light((int)color.x & 0xff, (int)color.y
			& 0xff, percentage);
	return ((red << 16) | (green << 8) | blue);
}
