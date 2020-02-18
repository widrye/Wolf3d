/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widrye <widrye@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 16:49:55 by widrye            #+#    #+#             */
/*   Updated: 2020/02/18 18:34:19 by widrye           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

#include <stdio.h>
int		get_width(char *s)
{
	int w;

	w = 0;
	while (*s)
	{
		if (!ft_isdigit((int)*s) && !ft_isspace((int)*s) && *s != '-')
			return (-1);
		if (ft_isdigit(*s))
		{
			while (ft_isdigit(*s))
				s++;
			w++;
		}
		while (ft_isspace(*s) || *s == '-')
			s++;
	}
	return (w);
}

int		*fill_row(char *s, int *row, int w)
{
	int i;
	int v;
	int neg;

	i = 0;
	dprintf(1, "fill row\n");
	while (*s && i < w)
	{
		v = 0;
		neg = 1;
		if (!ft_isspace(*s) && !ft_isdigit(*s) && *s != '-')
			return (NULL);
		if (*s == '-' || ft_isspace(*s))
		{
			(*s == '-') ? neg = -1 : 0;
			s++;
		}
		while (ft_isdigit(*s))
		{
			v = v * 10 + (*s - 48);
			s++;
		}
		row[i++] = v * neg;
		(*s) ? s++ : 0;
	}
	return (row);
}

int    **lst_to_tab(t_list *lst, int **grid, int height, int assumed_wdth)
{
	int i;
	int	width;

	i = 0;
	dprintf(1, "lst to tab\n");
	while (lst && i < height)
	{
		width = get_width(lst->content);
		if (width != assumed_wdth)
			assumed_wdth = width;
		if (width <= 1 || !(grid[i] = (int *)malloc(sizeof(int) * assumed_wdth)))
			return (NULL);
		if (!(grid[i] = fill_row(lst->content, grid[i], assumed_wdth)))
			return (NULL);
		lst = lst->next;
		i++;
	}
	return (grid);
}

int    **init_mapgrid(int height, int width)
{
	int **grid;

	if (height < 5 || width < 5)
		return (NULL);
	if (!(grid = (int **)malloc(sizeof(char *) * height)))
		return (NULL);
	return (grid);
}

int    **fill_grid(t_list *lst, int height, t_world *w)
{
	int		assumed_wdth;
	t_list	*tmp;
	int		**map;

	tmp = lst;
	assumed_wdth = get_width(lst->content);
	if ((map = init_mapgrid(height, assumed_wdth)) == NULL)
		return (NULL);
	if ((map = lst_to_tab(lst, map, height, assumed_wdth)) == NULL)
	{
		ft_free_list(tmp);
		return (NULL);
	}
	w->line_nb = height;
	w->row_nb = assumed_wdth;
	ft_free_list(tmp);
	return (map);
}

int		**parse_file(const int fd, t_world *world)
{
	int		gnl_ret;
	int		i;
	char	*line;
	t_list	*lst;

	i = 0;
	lst = NULL;
	while ((gnl_ret = get_next_line(fd, &line)) != 0)
	{
		dprintf(1, "%s\n", line);
		if (gnl_ret == -1 || (lst = ft_lst_pb(&lst, line)) == NULL)
		{
			ft_free_list(lst);
			return (NULL);
		}
		i++;
	}
	return (fill_grid(lst, i, world));
	// return (get_nodes(fill_grid(lst, i)));
}
