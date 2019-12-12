/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   mouse_events.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: widrye <widrye@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/28 04:33:59 by widrye       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/28 06:32:42 by widrye      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/wolf.h"

int		mouse_released(int keycode, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	(void)keycode;
	data->mouse_pressed = 0;
	return (0);
}

int		mouse_pressed(int keycode, int x, int y, t_data *data)
{
	if (keycode == 1)
	{
		data->mouse_x = x;
		data->mouse_y = y;
		data->mouse_pressed = 1;
	}
	return (0);
}

int		check_mouse_events(t_data *data)
{
	int ret;

	if (data->mouse_pressed == 1 && data->pause == 3)
	{
		ret = texture_clicks(data, data->mouse_x, data->mouse_y);
		if (ret >= 0)
		{
			data->texturepack = ret;
			data->pause = 1;
		}
	}
	if (data->mouse_pressed == 1 && data->pause == 1)
		data->pause = menu_clicks(data, data->mouse_x, data->mouse_y);
	if (data->mouse_pressed == 1 && data->pause == 2)
		options_clicks(data, data->mouse_x, data->mouse_y);
	return (0);
}
