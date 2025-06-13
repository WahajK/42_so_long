/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakhan <muhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 14:48:24 by muhakhan          #+#    #+#             */
/*   Updated: 2025/06/13 16:54:58 by muhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <X11/keysym.h>

# define TILE_SIZE 64
# define OBSTACLE "textures/XPM/obstacle.xpm"
# define BACKGROUND "textures/XPM/mid_tile.xpm"
# define PLAYER_LEFT "textures/XPM/player_left.xpm"
# define PLAYER_RIGHT "textures/XPM/player_right.xpm"
# define PLAYER_UP "textures/XPM/player_up.xpm"
# define PLAYER_DOWN "textures/XPM/player_down.xpm"
# define ENEMY_LEFT "textures/XPM/enemy_left.xpm"
# define ENEMY_RIGHT "textures/XPM/enemy.xpm"
# define ENEMY_UP "textures/XPM/enemy_up.xpm"
# define ENEMY_DOWN "textures/XPM/enemy_down.xpm"
# define WATER "textures/XPM/water.xpm"
# define EXIT_INACTIVE "textures/XPM/exit_inactive.xpm"
# define EXIT_ACTIVE "textures/XPM/exit_active.xpm"
# define TOP_LEFT_TILE "textures/XPM/top_left_tile.xpm"
# define TOP_RIGHT_TILE "textures/XPM/top_right_tile.xpm"
# define TOP_TILE "textures/XPM/top_tile.xpm"
# define BOT_LEFT_TILE "textures/XPM/bot_left_tile.xpm"
# define BOT_RIGHT_TILE "textures/XPM/bot_right_tile.xpm"
# define BOT_TILE "textures/XPM/bot_tile.xpm"
# define LEFT_TILE "textures/XPM/left_tile.xpm"
# define RIGHT_TILE "textures/XPM/right_tile.xpm"
# define COLLECTIBLE "textures/XPM/collectible.xpm"

typedef struct s_enemy {
    int x;
    int y;
    int direction;
    int frame_index;
    void *frames[2][4];
} t_enemy;
typedef struct t_vars
{
	void	*mlx;
	void	*window;
	void	*player_down;
	void	*player_up;
	void	*player_right;
	void	*player_left;
	void	*enemy_down;
	void	*enemy_up;
	void	*enemy_right;
	void	*enemy_left;
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
}	t_vars;

void	continue_border(t_vars *map);
#endif