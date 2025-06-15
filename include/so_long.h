/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakhan <muhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 14:48:24 by muhakhan          #+#    #+#             */
/*   Updated: 2025/06/15 02:15:07 by muhakhan         ###   ########.fr       */
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
# define OBSTACLE1 "textures/XPM/obstacle1.xpm"
# define OBSTACLE2 "textures/XPM/obstacle2.xpm"
# define OBSTACLE3 "textures/XPM/obstacle3.xpm"
# define OBSTACLE4 "textures/XPM/obstacle4.xpm"
# define OBSTACLE5 "textures/XPM/obstacle5.xpm"
# define OBSTACLE6 "textures/XPM/obstacle6.xpm"
# define OBSTACLE7 "textures/XPM/obstacle7.xpm"
# define OBSTACLE8 "textures/XPM/obstacle8.xpm"
# define BACKGROUND "textures/XPM/mid_tile.xpm"
# define PLAYER_LEFT1 "textures/XPM/player1_l.xpm"
# define PLAYER_LEFT2 "textures/XPM/player2_l.xpm"
# define PLAYER_LEFT3 "textures/XPM/player3_l.xpm"
# define PLAYER_LEFT4 "textures/XPM/player4_l.xpm"
# define PLAYER_LEFT5 "textures/XPM/player5_l.xpm"
# define PLAYER_LEFT6 "textures/XPM/player6_l.xpm"
# define PLAYER_RIGHT1 "textures/XPM/player1_r.xpm"
# define PLAYER_RIGHT2 "textures/XPM/player2_r.xpm"
# define PLAYER_RIGHT3 "textures/XPM/player3_r.xpm"
# define PLAYER_RIGHT4 "textures/XPM/player4_r.xpm"
# define PLAYER_RIGHT5 "textures/XPM/player5_r.xpm"
# define PLAYER_RIGHT6 "textures/XPM/player6_r.xpm"
# define ENEMY_RIGHT1 "textures/XPM/goblin1_R.xpm"
# define ENEMY_RIGHT2 "textures/XPM/goblin2_R.xpm"
# define ENEMY_RIGHT3 "textures/XPM/goblin3_R.xpm"
# define ENEMY_RIGHT4 "textures/XPM/goblin4_R.xpm"
# define ENEMY_RIGHT5 "textures/XPM/goblin5_R.xpm"
# define ENEMY_RIGHT6 "textures/XPM/goblin6_R.xpm"
# define ENEMY_RIGHT7 "textures/XPM/goblin7_R.xpm"
# define ENEMY_UP "textures/XPM/enemy_up.xpm"
# define ENEMY_DOWN "textures/XPM/enemy_down.xpm"
# define WATER "textures/XPM/water.xpm"
# define EXIT_INACTIVE "textures/XPM/exit_inactive.xpm"
# define EXIT_ACTIVE "textures/XPM/exit_active.xpm"
# define TOP_LEFT1 "textures/XPM/top_left1.xpm"
# define TOP_LEFT2 "textures/XPM/top_left2.xpm"
# define TOP_LEFT3 "textures/XPM/top_left3.xpm"
# define TOP_LEFT4 "textures/XPM/top_left4.xpm"
# define TOP_LEFT5 "textures/XPM/top_left5.xpm"
# define TOP_LEFT6 "textures/XPM/top_left6.xpm"
# define TOP_LEFT7 "textures/XPM/top_left7.xpm"
# define TOP_LEFT8 "textures/XPM/top_left8.xpm"
# define TOP_RIGHT1 "textures/XPM/top_right1.xpm"
# define TOP_RIGHT2 "textures/XPM/top_right2.xpm"
# define TOP_RIGHT3 "textures/XPM/top_right3.xpm"
# define TOP_RIGHT4 "textures/XPM/top_right4.xpm"
# define TOP_RIGHT5 "textures/XPM/top_right5.xpm"
# define TOP_RIGHT6 "textures/XPM/top_right6.xpm"
# define TOP_RIGHT7 "textures/XPM/top_right7.xpm"
# define TOP_RIGHT8 "textures/XPM/top_right8.xpm"
# define TOP_1 "textures/XPM/top_1.xpm"
# define TOP_2 "textures/XPM/top_2.xpm"
# define TOP_3 "textures/XPM/top_3.xpm"
# define TOP_4 "textures/XPM/top_4.xpm"
# define TOP_5 "textures/XPM/top_5.xpm"
# define TOP_6 "textures/XPM/top_6.xpm"
# define TOP_7 "textures/XPM/top_7.xpm"
# define TOP_8 "textures/XPM/top_8.xpm"
# define LEFT1 "textures/XPM/left1.xpm"
# define LEFT2 "textures/XPM/left2.xpm"
# define LEFT3 "textures/XPM/left3.xpm"
# define LEFT4 "textures/XPM/left4.xpm"
# define LEFT5 "textures/XPM/left5.xpm"
# define LEFT6 "textures/XPM/left6.xpm"
# define LEFT7 "textures/XPM/left7.xpm"
# define LEFT8 "textures/XPM/left8.xpm"
# define RIGHT1 "textures/XPM/right1.xpm"
# define RIGHT2 "textures/XPM/right2.xpm"
# define RIGHT3 "textures/XPM/right3.xpm"
# define RIGHT4 "textures/XPM/right4.xpm"
# define RIGHT5 "textures/XPM/right5.xpm"
# define RIGHT6 "textures/XPM/right6.xpm"
# define RIGHT7 "textures/XPM/right7.xpm"
# define RIGHT8 "textures/XPM/right8.xpm"
# define BOT_LEFT1 "textures/XPM/bot_left1.xpm"
# define BOT_LEFT2 "textures/XPM/bot_left2.xpm"
# define BOT_LEFT3 "textures/XPM/bot_left3.xpm"
# define BOT_LEFT4 "textures/XPM/bot_left4.xpm"
# define BOT_LEFT5 "textures/XPM/bot_left5.xpm"
# define BOT_LEFT6 "textures/XPM/bot_left6.xpm"
# define BOT_LEFT7 "textures/XPM/bot_left7.xpm"
# define BOT_LEFT8 "textures/XPM/bot_left8.xpm"
# define BOT_RIGHT1 "textures/XPM/bot_right1.xpm"
# define BOT_RIGHT2 "textures/XPM/bot_right2.xpm"
# define BOT_RIGHT3 "textures/XPM/bot_right3.xpm"
# define BOT_RIGHT4 "textures/XPM/bot_right4.xpm"
# define BOT_RIGHT5 "textures/XPM/bot_right5.xpm"
# define BOT_RIGHT6 "textures/XPM/bot_right6.xpm"
# define BOT_RIGHT7 "textures/XPM/bot_right7.xpm"
# define BOT_RIGHT8 "textures/XPM/bot_right8.xpm"
# define BOT_1 "textures/XPM/bot_1.xpm"
# define BOT_2 "textures/XPM/bot_2.xpm"
# define BOT_3 "textures/XPM/bot_3.xpm"
# define BOT_4 "textures/XPM/bot_4.xpm"
# define BOT_5 "textures/XPM/bot_5.xpm"
# define BOT_6 "textures/XPM/bot_6.xpm"
# define BOT_7 "textures/XPM/bot_7.xpm"
# define BOT_8 "textures/XPM/bot_8.xpm"
# define COLLECTIBLE1 "textures/XPM/gold1.xpm"
# define COLLECTIBLE2 "textures/XPM/gold2.xpm"
# define COLLECTIBLE3 "textures/XPM/gold3.xpm"
# define COLLECTIBLE4 "textures/XPM/gold4.xpm"
# define COLLECTIBLE5 "textures/XPM/gold5.xpm"
# define COLLECTIBLE6 "textures/XPM/gold6.xpm"
# define COLLECTIBLE7 "textures/XPM/gold7.xpm"

typedef struct s_enemy
{
	int		x;
	int		y;
	int		direction;
	int		frame_index;
	void	*frames[2][7];
}	t_enemy;

typedef struct s_player
{
	int		x;
	int		y;
	int		direction;
	int		frame_index;
	void	*frames[2][6];
}	t_player;
typedef struct s_collectible
{
	int		flag;
	int		frame_index;
	void	*frames[7];
}	t_collectible;

typedef struct s_exit
{
	int		flag;
	void	*img[2];
}	t_exit;

typedef struct s_obstacle
{
	int		frame_index;
	void	*frames[8];
}	t_obstacle;

typedef struct s_border
{
	int		frame_index;
	void	*frames[8][8];
}	t_border;

typedef struct t_vars
{
	void			*mlx;
	void			*window;
	void			*water;
	void			*background;
	char			**map;
	int				x_count;
	int				y_count;
	int				c_count;
	int				e_count;
	int				p_count;
	int				ex_count;
	t_enemy			*enemies;
	t_exit			exit;
	t_player		player;
	t_collectible	collectibles;
	t_obstacle		obstacle;
	t_border		borders;
}	t_vars;

void	continue_border(t_vars *map);
#endif