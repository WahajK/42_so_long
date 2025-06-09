/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakhan <muhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 14:48:24 by muhakhan          #+#    #+#             */
/*   Updated: 2025/06/07 00:49:05 by muhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"

# define TILE_SIZE 64
# define OBSTACLE "textures/back_obs.xpm"
# define BACKGROUND "textures/mid_tile.xpm"
# define PLAYER "textures/player_right_tile.xpm"
# define WATER "textures/water.xpm"
typedef struct s_map
{
	void	*mlx;
	void	*window;
	void	*player_down;
	void	*player_up;
	void	*player_right;
	void	*player_left;
	void	*water;
	void	*obstacle;
	void	*background;
	char	**map;
	int		x_count;
	int		y_count;
	int		player_pos[2];
	int		c_count;
	int		e_count;
	int		p_count;
	int		ex_count;
}	t_map;

#endif