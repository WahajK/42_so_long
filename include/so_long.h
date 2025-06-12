/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakhan <muhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 14:48:24 by muhakhan          #+#    #+#             */
/*   Updated: 2025/06/12 15:40:35 by muhakhan         ###   ########.fr       */
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
# define OBSTACLE "textures/obs.xpm"
# define BACKGROUND "textures/mid_tile.xpm"
# define PLAYER_LEFT "textures/left.xpm"
# define PLAYER_RIGHT "textures/right.xpm"
# define PLAYER_UP "textures/up.xpm"
# define PLAYER_DOWN "textures/down.xpm"
# define WATER "textures/water.xpm"
# define EXIT_INACTIVE "textures/exit_inactive.xpm"
# define EXIT_ACTIVE "textures/exit_active.xpm"
# define TOP_LEFT_TILE "textures/top_left_t.xpm"
# define TOP_RIGHT_TILE "textures/top_right_t.xpm"
# define TOP_TILE "textures/top_t.xpm"
# define BOT_LEFT_TILE "textures/bot_left_t.xpm"
# define BOT_RIGHT_TILE "textures/bot_right_t.xpm"
# define BOT_TILE "textures/bot_t.xpm"
# define LEFT_TILE "textures/left_t.xpm"
# define RIGHT_TILE "textures/right_t.xpm"
# define COLLECTIBLE "textures/coll.xpm"

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
	void	*collectible;
	void	*top_left_tile;
	void	*top_right_tile;
	void	*top_tile;
	void	*bot_left_tile;
	void	*bot_right_tile;
	void	*bot_tile;
	void	*left_tile;
	void	*right_tile;
	void	*exit_inactive;
	void	*exit_active;
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

void	continue_border(t_map *map);
#endif