/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuret <jjuret@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 16:26:03 by jjuret            #+#    #+#             */
/*   Updated: 2016/11/14 15:49:38 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct		s_piece
{
	int				is_placed;
	int				x_piece[4];
	int				y_piece[4];
	char			count;
	struct s_piece	*next;
}					t_piece;

int					g_size[1];
int					g_oldsize[1];
char				g_save[20][20];

void				ft_reduce(t_piece *piece);
t_piece				*ft_fill_piece(int fd, t_piece *piece, int *ret);
t_piece				ft_get_all_pieces(int fd);
int					master(t_piece *pieces, char **table, int pos);
void				put_piece(char **table, int pos, t_piece *target);
void				del_piece(char **tab, t_piece *target);
int					check_place(char **table, int pos, t_piece target);
void				ft_reduce(t_piece *piece);
void				ft_print_tab(void);
void				ft_write_error(void);
void				ft_verif(char *buff, int nb_diese, int ret);
char				**ft_init_tab(void);
int					save_setup(char **table);
int					ft_find_the_best_size(t_piece *piece);
void				ft_verif_coords(char *buff, t_piece *piece);
int					get_min_distance(int pos, int *tab);
int					ft_abs(int i);
void				supertest(t_piece *piece);
int					ft_get_distance(t_piece *piece, int i, int j);
int					ft_approx_sqrt(int i);

#endif
