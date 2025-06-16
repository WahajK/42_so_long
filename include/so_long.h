/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakhan <muhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 14:48:24 by muhakhan          #+#    #+#             */
/*   Updated: 2025/06/16 18:05:19 by muhakhan         ###   ########.fr       */
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
# define OBS1 "textures/XPM/obstacle1.xpm"
# define OBS2 "textures/XPM/obstacle2.xpm"
# define OBS3 "textures/XPM/obstacle3.xpm"
# define OBS4 "textures/XPM/obstacle4.xpm"
# define OBS5 "textures/XPM/obstacle5.xpm"
# define OBS6 "textures/XPM/obstacle6.xpm"
# define OBS7 "textures/XPM/obstacle7.xpm"
# define OBS8 "textures/XPM/obstacle8.xpm"
# define BG "textures/XPM/mid_tile.xpm"
# define P_L1 "textures/XPM/player1_l.xpm"
# define P_L2 "textures/XPM/player2_l.xpm"
# define P_L3 "textures/XPM/player3_l.xpm"
# define P_L4 "textures/XPM/player4_l.xpm"
# define P_L5 "textures/XPM/player5_l.xpm"
# define P_L6 "textures/XPM/player6_l.xpm"
# define P_R1 "textures/XPM/player1_r.xpm"
# define P_R2 "textures/XPM/player2_r.xpm"
# define P_R3 "textures/XPM/player3_r.xpm"
# define P_R4 "textures/XPM/player4_r.xpm"
# define P_R5 "textures/XPM/player5_r.xpm"
# define P_R6 "textures/XPM/player6_r.xpm"
# define E_R1 "textures/XPM/goblin1_R.xpm"
# define E_R2 "textures/XPM/goblin2_R.xpm"
# define E_R3 "textures/XPM/goblin3_R.xpm"
# define E_R4 "textures/XPM/goblin4_R.xpm"
# define E_R5 "textures/XPM/goblin5_R.xpm"
# define E_R6 "textures/XPM/goblin6_R.xpm"
# define E_R7 "textures/XPM/goblin7_R.xpm"
# define E_L1 "textures/XPM/goblin1_L.xpm"
# define E_L2 "textures/XPM/goblin2_L.xpm"
# define E_L3 "textures/XPM/goblin3_L.xpm"
# define E_L4 "textures/XPM/goblin4_L.xpm"
# define E_L5 "textures/XPM/goblin5_L.xpm"
# define E_L6 "textures/XPM/goblin6_L.xpm"
# define E_L7 "textures/XPM/goblin7_L.xpm"
# define WATER "textures/XPM/water.xpm"
# define EXT_IN "textures/XPM/exit_inactive.xpm"
# define EXT_AT "textures/XPM/exit_active.xpm"
# define T_L1 "textures/XPM/top_left1.xpm"
# define T_L2 "textures/XPM/top_left2.xpm"
# define T_L3 "textures/XPM/top_left3.xpm"
# define T_L4 "textures/XPM/top_left4.xpm"
# define T_L5 "textures/XPM/top_left5.xpm"
# define T_L6 "textures/XPM/top_left6.xpm"
# define T_L7 "textures/XPM/top_left7.xpm"
# define T_L8 "textures/XPM/top_left8.xpm"
# define T_R1 "textures/XPM/top_right1.xpm"
# define T_R2 "textures/XPM/top_right2.xpm"
# define T_R3 "textures/XPM/top_right3.xpm"
# define T_R4 "textures/XPM/top_right4.xpm"
# define T_R5 "textures/XPM/top_right5.xpm"
# define T_R6 "textures/XPM/top_right6.xpm"
# define T_R7 "textures/XPM/top_right7.xpm"
# define T_R8 "textures/XPM/top_right8.xpm"
# define T_1 "textures/XPM/top_1.xpm"
# define T_2 "textures/XPM/top_2.xpm"
# define T_3 "textures/XPM/top_3.xpm"
# define T_4 "textures/XPM/top_4.xpm"
# define T_5 "textures/XPM/top_5.xpm"
# define T_6 "textures/XPM/top_6.xpm"
# define T_7 "textures/XPM/top_7.xpm"
# define T_8 "textures/XPM/top_8.xpm"
# define L1 "textures/XPM/left1.xpm"
# define L2 "textures/XPM/left2.xpm"
# define L3 "textures/XPM/left3.xpm"
# define L4 "textures/XPM/left4.xpm"
# define L5 "textures/XPM/left5.xpm"
# define L6 "textures/XPM/left6.xpm"
# define L7 "textures/XPM/left7.xpm"
# define L8 "textures/XPM/left8.xpm"
# define R1 "textures/XPM/right1.xpm"
# define R2 "textures/XPM/right2.xpm"
# define R3 "textures/XPM/right3.xpm"
# define R4 "textures/XPM/right4.xpm"
# define R5 "textures/XPM/right5.xpm"
# define R6 "textures/XPM/right6.xpm"
# define R7 "textures/XPM/right7.xpm"
# define R8 "textures/XPM/right8.xpm"
# define B_L1 "textures/XPM/bot_left1.xpm"
# define B_L2 "textures/XPM/bot_left2.xpm"
# define B_L3 "textures/XPM/bot_left3.xpm"
# define B_L4 "textures/XPM/bot_left4.xpm"
# define B_L5 "textures/XPM/bot_left5.xpm"
# define B_L6 "textures/XPM/bot_left6.xpm"
# define B_L7 "textures/XPM/bot_left7.xpm"
# define B_L8 "textures/XPM/bot_left8.xpm"
# define B_R1 "textures/XPM/bot_right1.xpm"
# define B_R2 "textures/XPM/bot_right2.xpm"
# define B_R3 "textures/XPM/bot_right3.xpm"
# define B_R4 "textures/XPM/bot_right4.xpm"
# define B_R5 "textures/XPM/bot_right5.xpm"
# define B_R6 "textures/XPM/bot_right6.xpm"
# define B_R7 "textures/XPM/bot_right7.xpm"
# define B_R8 "textures/XPM/bot_right8.xpm"
# define B_1 "textures/XPM/bot_1.xpm"
# define B_2 "textures/XPM/bot_2.xpm"
# define B_3 "textures/XPM/bot_3.xpm"
# define B_4 "textures/XPM/bot_4.xpm"
# define B_5 "textures/XPM/bot_5.xpm"
# define B_6 "textures/XPM/bot_6.xpm"
# define B_7 "textures/XPM/bot_7.xpm"
# define B_8 "textures/XPM/bot_8.xpm"
# define COL1 "textures/XPM/gold1.xpm"
# define COL2 "textures/XPM/gold2.xpm"
# define COL3 "textures/XPM/gold3.xpm"
# define COL4 "textures/XPM/gold4.xpm"
# define COL5 "textures/XPM/gold5.xpm"
# define COL6 "textures/XPM/gold6.xpm"
# define COL7 "textures/XPM/gold7.xpm"

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
	int				x_count;
	int				y_count;
	int				c_count;
	int				e_count;
	int				p_count;
	int				ex_count;
	int				steps;
	char			**map;
	void			*mlx;
	void			*water;
	void			*window;
	void			*background;
	void			*en_frames[2][7];	
	t_exit			exit;
	t_player		player;
	t_border		borders;
	t_enemy			*enemies;
	t_obstacle		obstacle;
	t_collectible	collectibles;
}	t_vars;

int	check_extension(char *fname);
int	char_count(char *line, char ch);
int	illegal_char(int row, char *str, t_vars *vars);
int	set_counts(t_vars *vars, char *fname);
int	read_map(char *fname, t_vars *vars);
int	check_escape(t_vars *vars);
int	check_borders(t_vars *vars);
int	validate_map(t_vars *vars);
int	destructor(t_vars *vars, char *msg);
int	handle_key(int keysym, t_vars *vars);
int	update_game(t_vars *vars);
int	handle_exit(t_vars *vars);
char	*trim(char *arr);
char	**dup_map(int rc, char **map);
void	solve_maze(char **map, int *flags, int px, int py);
void	destructor_map(char **map);
void	destroy_enemy_images(t_vars *var);
void	destroy_collectible_images(t_vars *var);
void	free_player_images(t_vars *vars);
void	destroy_obstacle_images(t_vars *vars);
void	destroy_borders(t_vars *vars);
void	destroy_images(t_vars *vars);
void	start_game_window(t_vars *vars);
void	set_obstacles(t_vars *vars, int tile_size);
void	set_player(t_vars *vars, int tile_size);
void	set_enemies(t_vars *vars, int tile_size);
void	set_collectibles(t_vars *vars, int tile_size);
void	set_borders1(t_vars *vars, int tile_size);
void	set_borders2(t_vars *vars, int tile_size);
void	set_borders3(t_vars *vars, int tile_size);
void	set_borders4(t_vars *vars, int tile_size);
void	check_obstacles_player(t_vars *vars);
void	check_missing_textures(t_vars *vars);
void	set_tiles(t_vars *vars);
void	draw_image(t_vars *vars, void *img, int x, int y);
void	draw_water(t_vars *vars);
void	draw_border(t_vars *vars);
void	continue_border(t_vars *vars);
void	draw_player(t_vars *vars, int i, int j);
void	draw_enemies(t_vars *vars, int i, int j);
void	check_and_draw(t_vars *vars, int i, int j);
void	render_map(t_vars *vars);
void	move_player(t_vars *vars, int x, int y);
void	animate_collectible(t_vars *vars, int frame);
void	animate_player_obs(t_vars *vars, int frame);
void	move_enemies(t_vars *vars);
void	set_enemy_frames(t_vars *vars, int count);
void	init_enemies(t_vars *vars);
#endif