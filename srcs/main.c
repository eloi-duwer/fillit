/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuret <jjuret@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 16:01:14 by jjuret            #+#    #+#             */
/*   Updated: 2016/11/16 13:24:23 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fillit.h"

void		ft_reduce(t_piece *piece)
{
	int x;
	int y;
	int i;

	x = piece->x_piece[0];
	y = piece->y_piece[0];
	i = 0;
	while (i < 4)
	{
		piece->x_piece[i] -= x;
		piece->y_piece[i] -= y;
		i++;
	}
}

void		ft_verif(char *buff, int nb_diese, int ret)
{
	int i;

	i = 0;
	if (ret < 20 || nb_diese != 4)
		ft_write_error();
	while (i < 20)
	{
		if (i % 5 < 4)
		{
			if (buff[i] != '.' && buff[i] != '#')
				ft_write_error();
		}
		else
		{
			if (buff[i] != '\n')
				ft_write_error();
		}
		i++;
	}
	if (buff[20] != '\0' && buff[20] != '\n')
		ft_write_error();
}

t_piece		*ft_fill_piece(int fd, t_piece *piece, int *ret)
{
	int		pos;
	int		nb_diese;
	char	buff[20];

	if ((*ret = read(fd, buff, 21)) != 0)
	{
		pos = 0;
		nb_diese = 0;
		while (pos < 20)
		{
			if (buff[pos] == '#')
			{
				piece->x_piece[nb_diese] = pos % 5;
				piece->y_piece[nb_diese] = pos / 5;
				nb_diese++;
			}
			pos++;
		}
		ft_verif(buff, nb_diese, *ret);
		ft_reduce(piece);
		ft_verif_coords(buff, piece);
		return (piece);
	}
	ft_write_error();
	return (NULL);
}

t_piece		ft_get_all_pieces(int fd)
{
	t_piece first_piece;
	t_piece *new_piece;
	t_piece *curr_piece;
	char	i;
	int		ret;

	ret = 0;
	ft_fill_piece(fd, &first_piece, &ret);
	first_piece.count = 'A';
	first_piece.next = NULL;
	new_piece = &first_piece;
	i = 'B';
	while (ret != 20)
	{
		curr_piece = (t_piece *)malloc(sizeof(t_piece));
		curr_piece = ft_fill_piece(fd, curr_piece, &ret);
		curr_piece->count = i;
		curr_piece->is_placed = 0;
		new_piece->next = curr_piece;
		new_piece = new_piece->next;
		new_piece->next = NULL;
		i++;
	}
	return (first_piece);
}

int			main(int argc, char **argv)
{
	int		fd;
	t_piece first_piece;
	char	**tab;
	int		ret;

	ret = 0;
	if (argc != 2)
	{
		write(1, "usage : ./fillit \"[file name]\"\n", 31);
		return (0);
	}
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		ft_write_error();
	first_piece = ft_get_all_pieces(fd);
	close(fd);
	tab = ft_init_tab();
	g_oldsize[0] = 0;
	g_size[0] = ft_find_the_best_size(&first_piece);
	while (master(&first_piece, tab, 0) == 0)
		(*g_size)++;
	ft_print_tab();
	return (0);
}
