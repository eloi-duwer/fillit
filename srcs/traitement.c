/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traitement.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuret <jjuret@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 11:01:24 by jjuret            #+#    #+#             */
/*   Updated: 2016/11/14 13:49:08 by jjuret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fillit.h"

int		master(t_piece *pieces, char **table, int pos)
{
	if (pieces == NULL)
		return (1);
	while (pieces->is_placed == 0)
	{
		if (pieces != NULL && check_place(table, pos, *pieces) == 0)
			pos++;
		else if (pieces != NULL)
			put_piece(table, pos, pieces);
		if (*g_size < (pos / *g_size))
			return (0);
	}
	if (master(pieces->next, table, 0) == 1)
		return (save_setup(table));
	del_piece(table, pieces);
	return (master(pieces, table, pos + 1));
}

void	put_piece(char **table, int pos, t_piece *target)
{
	int	i;
	int x;
	int y;

	i = 0;
	while (i < 4)
	{
		x = (pos % *g_size) + target->x_piece[i];
		y = (pos / *g_size) + target->y_piece[i];
		table[y][x] = target->count;
		i++;
	}
	target->is_placed = 1;
}

void	del_piece(char **table, t_piece *target)
{
	int	i;
	int	j;

	j = 0;
	while (j < 19)
	{
		i = 0;
		while (i < 19)
		{
			if (table[j][i] == target->count)
				table[j][i] = '.';
			i++;
		}
		j++;
	}
	target->is_placed = 0;
}

int		check_place(char **table, int pos, t_piece target)
{
	int	i;
	int x;
	int y;

	i = 0;
	while (i < 4)
	{
		x = (pos % *g_size) + target.x_piece[i];
		y = (pos / *g_size) + target.y_piece[i];
		if (x < 0 || y < 0)
			return (0);
		if (x >= g_size[0] || y >= g_size[0])
			return (0);
		if (table[y][x] != '.')
			return (0);
		i++;
	}
	return (1);
}

int		save_setup(char **table)
{
	int		i;
	int		j;

	j = 0;
	if (*g_oldsize == 0)
	{
		*g_oldsize = 1;
		while (j < 19)
		{
			i = 0;
			while (i < 19)
			{
				g_save[j][i] = table[j][i];
				i++;
			}
			j++;
		}
	}
	return (1);
}
