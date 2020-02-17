/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   texture.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: widrye <widrye@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/08 12:07:17 by ztrouill     #+#   ##    ##    #+#       */
/*   Updated: 2020/02/09 06:11:13 by widrye      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/wolf.h"

void				texellit(t_data *data, int64_t y, int64_t x)
{
	int i;

	i = 0;
	if (y < 0 || x < 0 || y >= HEIGHT || x >= WIDTH)
		return ;
	if (data->texture.y < 0 || data->texture.x < 0 ||
		data->texture.y >= data->texture.size ||
		data->texture.x >= data->texture.size)
		return ;
	if (data->texture.i)
		i = data->texture.i + data->texturepack * 4;
	data->image.image_str[(y * WIDTH) + x] = data->texture.wall[i].
	image_str[((int)data->texture.y * data->texture.size) +
	(int)data->texture.x];
}

void				compute_texture_pos(t_data *data)
{
	if (data->rays.side == 0)
	{
		data->texture.i = 1;
		data->texture.map_x = data->player.pos_y + data->rays.dist_from_wall * data->rays.dir_y;
	}
	else
	{
		data->texture.i = 2;
		data->texture.map_x = data->player.pos_x + data->rays.dist_from_wall * data->rays.dir_x;
	}
	data->texture.map_x -= floor(data->texture.map_x);
	data->texture.x = ceil(data->texture.map_x * data->texture.size) - 1;
	if (data->rays.side == 0 && data->rays.dir_x > 0)
	{
		data->texture.i = 3;
		data->texture.x = data->texture.size - data->texture.x - 1;
	}
	if (data->rays.side == 1 && data->rays.dir_y < 0)
	{
		data->texture.i = 4;
		data->texture.x = data->texture.size - data->texture.x - 1;
	}
}

static void			dump_end_screen(t_data *data)
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

void				apply_end_screen(t_data *data)
{
	int				x;
	int				x2;
	int				y;
	int				y2;

	y = (HEIGHT >= END_SCREEN_HEIGHT) ? abs(END_SCREEN_HEIGHT - HEIGHT) / 2 : 0;
	y2 = (HEIGHT < END_SCREEN_HEIGHT) ? abs(END_SCREEN_HEIGHT - HEIGHT) / 2 : 0;
	while (y < HEIGHT && y2 < END_SCREEN_HEIGHT)
	{
		x = (WIDTH >= END_SCREEN_WIDTH) ? abs(END_SCREEN_WIDTH - WIDTH) / 2 : 0;
		x2 = (WIDTH < END_SCREEN_WIDTH) ? abs(END_SCREEN_WIDTH - WIDTH) / 2 : 0;
		while (x < WIDTH && x2 < END_SCREEN_WIDTH)
		{
			data->image.image_str[y * WIDTH + x] = data->texture.end_screen
			[data->end].image_str[y2 * END_SCREEN_WIDTH + x2];
			x++;
			x2++;
		}
		y++;
		y2++;
	}
	dump_end_screen(data);
}
