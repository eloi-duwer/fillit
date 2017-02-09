/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   little_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 12:52:49 by eduwer            #+#    #+#             */
/*   Updated: 2016/11/14 15:24:10 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fillit.h"

void		ft_write_error(void)
{
	write(1, "error\n", 6);
	exit(1);
}

char		**ft_init_tab(void)
{
	int		x;
	int		y;
	char	**tab;

	x = 0;
	tab = (char **)malloc(sizeof(char *) * 20);
	while (x < 20)
	{
		y = 0;
		tab[x] = (char *)malloc(sizeof(char) * 20);
		while (y < 20)
		{
			tab[x][y] = '.';
			y++;
		}
		x++;
	}
	return (tab);
}

int			ft_abs(int i)
{
	if (i < 0)
		return (-i);
	return (i);
}

int			get_min_distance(int pos, int *tab)
{
	int	min_distance;
	int	i;
	int x_pos;
	int y_pos;
	int distance;

	x_pos = pos % 5;
	y_pos = pos / 5;
	i = 0;
	min_distance = 99;
	while (i < 4)
	{
		distance = (ft_abs(x_pos - tab[i] % 5)) + (ft_abs(y_pos - tab[i] / 5));
		if (distance <= min_distance && distance > 0)
			min_distance = distance;
		i++;
	}
	return (min_distance);
}

void		ft_verif_coords(char *buff, t_piece *piece)
{
	int	tab_pos[4];
	int	nb_diese;
	int	pos;
	int	distance;

	pos = 0;
	nb_diese = 0;
	distance = -1;
	while (pos < 20)
	{
		if (buff[pos] == '#')
			tab_pos[nb_diese++] = pos;
		pos++;
	}
	pos = 0;
	while (pos < 4)
	{
		if (get_min_distance(tab_pos[pos], tab_pos) > 1)
			ft_write_error();
		pos++;
	}
	supertest(piece);
}
