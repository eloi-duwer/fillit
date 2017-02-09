/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_globals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 16:58:12 by eduwer            #+#    #+#             */
/*   Updated: 2016/11/14 15:52:29 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fillit.h"

int		ft_get_distance(t_piece *piece, int i, int j)
{
	int	coord1_x;
	int	coord2_x;
	int	coord1_y;
	int	coord2_y;

	coord1_x = piece->x_piece[i];
	coord2_x = piece->x_piece[j];
	coord1_y = piece->y_piece[i];
	coord2_y = piece->y_piece[j];
	return (ft_abs(coord1_x - coord2_x) + ft_abs(coord1_y - coord2_y));
}

void	supertest(t_piece *piece)
{
	int	nb_of_nearly_alone_pieces;
	int	nb_of_nearly_pieces;
	int	i;
	int j;

	i = 0;
	nb_of_nearly_alone_pieces = 0;
	while (i < 4)
	{
		nb_of_nearly_pieces = 0;
		j = 0;
		while (j < 4)
		{
			if (ft_get_distance(piece, i, j) == 1)
				nb_of_nearly_pieces++;
			j++;
		}
		if (nb_of_nearly_pieces == 1)
			nb_of_nearly_alone_pieces++;
		i++;
	}
	if (nb_of_nearly_alone_pieces == 4)
		ft_write_error();
}

int		ft_approx_sqrt(int i)
{
	int j;

	j = 1;
	while (j * j < i)
		j++;
	return (j);
}

int		ft_find_the_best_size(t_piece *piece)
{
	t_piece *pt_piece;
	int		i;

	pt_piece = piece;
	i = 0;
	while (pt_piece != NULL)
	{
		pt_piece = pt_piece->next;
		i++;
	}
	return (ft_approx_sqrt(4 * i));
}
