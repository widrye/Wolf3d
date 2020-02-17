/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widrye <widrye@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 21:35:48 by widrye            #+#    #+#             */
/*   Updated: 2020/02/17 21:38:19 by widrye           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

void		pick_texture(t_data *data, int y, t_vector t)
{
	if (data->rays.side == 0 && data->rays.dir_x < 0)
		data->image.image_str[(int)((y * WIDTH) + data->world.x)] =
			data->texture.wall[1 + 4 * data->texturepack].image_str[(int)
			((((int)t.y % data->texture.size) * data->texture.size) +
			((int)t.x % data->texture.size))];
	if (data->rays.side == 0 && data->rays.dir_x > 0)
		data->image.image_str[(int)((y * WIDTH) + data->world.x)] =
			data->texture.wall[2 + 4 * data->texturepack].image_str[(int)
			((((int)t.y % data->texture.size) * data->texture.size) +
			((int)t.x % data->texture.size))];
	if (data->rays.side == 1 && data->rays.dir_y < 0)
		data->image.image_str[(int)((y * WIDTH) + data->world.x)] =
			data->texture.wall[3 + 4 * data->texturepack].image_str[(int)
			((((int)t.y % data->texture.size) * data->texture.size) +
			((int)t.x % data->texture.size))];
	if (data->rays.side == 1 && data->rays.dir_y > 0)
		data->image.image_str[(int)((y * WIDTH) + data->world.x)] =
			data->texture.wall[4 + 4 * data->texturepack].image_str[(int)
			((((int)t.y % data->texture.size) * data->texture.size) +
			((int)t.x % data->texture.size))];
	if (data->rays.wall == 2 || data->rays.wall == 3)
		data->image.image_str[(int)((y * WIDTH) + data->world.x)] =
			data->texture.wall[0].image_str[(int)
			((((int)t.y % data->texture.size) * data->texture.size) +
			((int)t.x % data->texture.size))];
}

double		init_t_walls(t_data *data, int *y)
{
	double x;

	*y = data->world.line_pos[0][data->world.x] - 1;
	if (data->rays.side == 0)
		x = data->player.pos_y + data->rays.dist_from_wall * data->rays.dir_y;
	else
		x = data->player.pos_x + data->rays.dist_from_wall * data->rays.dir_x;
	x = x * (double)data->texture.size;
	return (x);
}

void		texture_wall(t_data *data)
{
	int			y;
	int			d;
	t_vector	t;

	t.x = init_t_walls(data, &y);
	while (++y < data->world.line_pos[1][data->world.x] - 1)
	{
		d = (int)fabs(y - (HEIGHT * 0.5) + (data->world.line_height * 0.5));
		t.y = ((d * data->texture.size) / data->world.line_height);
		pick_texture(data, y, t);
	}
}

static void	dump_end_screen(t_data *data)
{
	mlx_put_image_to_window(data->mlx_ptr, data->window_ptr,
							data->image.image_ptr, 0, 0);
	if (data->end == 1)
		mlx_string_put(data->mlx_ptr, data->window_ptr,
		WIDTH / 2 - 100, HEIGHT / 2, CYAN, "Bravo tu es tres fort");
	else
		mlx_string_put(data->mlx_ptr, data->window_ptr,
		WIDTH / 2 - 100, HEIGHT / 2, RED, "Oh non tu as perdu");
}

void		apply_end_screen(t_data *data)
{
	int x;
	int x2;
	int y;
	int y2;

	y = (HEIGHT >= END_SCREEN_HEIGHT) ? abs(END_SCREEN_HEIGHT - HEIGHT) / 2 : 0;
	y2 = (HEIGHT < END_SCREEN_HEIGHT) ? abs(END_SCREEN_HEIGHT - HEIGHT) / 2 : 0;
	while (y < HEIGHT && y2 < END_SCREEN_HEIGHT)
	{
		x = (WIDTH >= END_SCREEN_WIDTH) ? abs(END_SCREEN_WIDTH - WIDTH) / 2 : 0;
		x2 = (WIDTH < END_SCREEN_WIDTH) ? abs(END_SCREEN_WIDTH - WIDTH) / 2 : 0;
		while (x < WIDTH && x2 < END_SCREEN_WIDTH)
		{
			data->image.image_str[y * WIDTH + x] =
			data->texture.end_screen[data->end].
			image_str[y2 * END_SCREEN_WIDTH + x2];
			x++;
			x2++;
		}
		y++;
		y2++;
	}
	dump_end_screen(data);
}
