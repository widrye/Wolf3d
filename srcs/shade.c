/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   shade.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: widrye <widrye@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/28 05:55:06 by widrye       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/28 05:57:47 by widrye      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/wolf.h"

int			darken_color(int rgb)
{
	int r;
	int g;
	int b;
	int ret;

	r = (rgb >> 16 & 0xff) / 2;
	g = (rgb >> 8 & 0xff) / 2;
	b = (rgb & 0xff) / 2;
	ret = 0;
	ret += r << 16;
	ret += g << 8;
	ret += b;
	return (ret);
}

void		shade_area(t_data *data, int x, int y)
{
	int tmp;

	tmp = x;
	if (x < 0 || y < 0)
		return ;
	while (y < HEIGHT)
	{
		x = tmp;
		while (x < WIDTH)
		{
			data->image.image_str[y * WIDTH + x] =
			darken_color(data->image.image_str[y * WIDTH + x]);
			x++;
		}
		y++;
	}
}
