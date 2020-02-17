/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   drawline.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: widrye <widrye@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/26 09:02:14 by widrye       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/17 21:12:52 by widrye      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/wolf.h"

void					pixelit(t_data *data, int64_t y, int64_t x, int rgba)
{
	if (y < 0 || x < 0 || y >= HEIGHT || x >= WIDTH)
		return ;
	data->image.image_str[(y * WIDTH) + x] = rgba;
}

void					draw_floor(t_data *data)
{
	int y;

	y = data->world.line_pos[1][data->world.x];
	while (y < HEIGHT - 1)
	{
		pixelit(data, y, data->world.x,
		get_color(HEIGHT - data->world.line_pos[1]
		[data->world.x], y - data->world.line_pos[1][data->world.x]));
		y++;
	}
}
