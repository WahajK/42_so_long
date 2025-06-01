/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakhan <muhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 14:48:24 by muhakhan          #+#    #+#             */
/*   Updated: 2025/05/31 21:49:09 by muhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"

# define TILE_SIZE 32
typedef struct s_map
{
	void	*mlx;
	void	*window;
	void	*player;
	char	**map;
	int		row_count;
	int		col_count;
	int		player_pos[2];
	int		c_count;
	int		e_count;
	int		p_count;
	int		x_count;
}	t_map;

#endif