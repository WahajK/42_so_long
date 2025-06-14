/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakhan <muhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 14:52:20 by muhakhan          #+#    #+#             */
/*   Updated: 2025/06/14 19:57:27 by muhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	destructor_map(char **map);

int	check_extension(char *fname)
{
	if (ft_strncmp(&fname[ft_strlen(fname) - 4], ".ber", 4) != 0)
		return (1);
	return (0);
}

int	char_count(char *line, char ch)
{
	int	i;

	i = 0;
	while (*line)
		if (*line++ == ch)
			i++;
	return (i);
}

char	*trim(char *arr)
{
	if (!arr)
		return (NULL);
	if (arr[ft_strlen(arr) - 1] == '\n')
		arr[ft_strlen(arr) - 1] = 0;
	return (arr);
}

int	illegal_char(int row, char *str, t_vars *map)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '0' || str[i] == '1' || str[i] == 'P'
			|| str[i] == 'E' || str[i] == 'C' || str[i] == 'X')
		{
			if (str[i] == 'P')
			{
				map->player.x = row;
				map->player.y = i;
			}
		}
		else
			return (1);
		i++;
	}
	return (0);
}

int	set_counts(t_vars *map, char *fname)
{
	int		fd;
	char	*str;
	int		flag[2];

	ft_bzero(flag, sizeof(int) * 2);
	fd = open(fname, O_RDONLY);
	if (fd < 0)
		return (1);
	str = trim(get_next_line(fd));
	map->x_count = ft_strlen(str);
	while (str && ++flag[0])
	{
		if ((int) ft_strlen(str) != map->x_count
			|| illegal_char(flag[0] - 1, str, map))
			flag[1] = 1;
		map->c_count += char_count(str, 'C');
		map->p_count += char_count(str, 'P');
		map->e_count += char_count(str, 'E');
		map->ex_count += char_count(str, 'X');
		free(str);
		str = trim(get_next_line(fd));
	}
	if (!map->c_count || map->p_count != 1 || map->e_count != 1 || flag[1])
		return (close (fd), 1);
	return (map->y_count = flag[0], close (fd), 0);
}

int	read_map(char *fname, t_vars *map)
{
	int		fd;
	int		i;
	char	*temp;

	if (set_counts(map, fname))
		return (1);
	fd = open(fname, O_RDONLY);
	if (fd < 0)
		return (1);
	map->map = malloc((map->y_count + 1) * sizeof(char *));
	if (!map->map)
		return (close(fd), 1);
	temp = get_next_line(fd);
	i = 0;
	while (temp)
	{
		map->map[i++] = trim(temp);
		temp = get_next_line(fd);
	}
	map->map[i] = NULL;
	close(fd);
	return (0);
}

void	print_vars(t_vars *map)
{
	int	i;

	i = 0;
	while (map->map[i])
	{
		ft_printf("%s\n", map->map[i++]);
	}
}

char	**dup_map(int rc, char **map)
{
	char	**arr;
	int		i;

	arr = malloc(sizeof(char *) * (rc + 1));
	i = 0;
	while (map[i])
	{
		arr[i] = ft_strdup(map[i]);
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

void	solve_maze(char **map, int *flags, int px, int py)
{
	if (map[px][py] == 'V' || map[px][py] == '1')
		return ;
	if (map[px][py] == 'E')
		flags[0] = 1;
	if (map[px][py] == 'C')
		flags[1] = 1;
	map[px][py] = 'V';
	solve_maze(map, flags, px + 1, py);
	solve_maze(map, flags, px - 1, py);
	solve_maze(map, flags, px, py + 1);
	solve_maze(map, flags, px, py - 1);
}

int	check_escape(t_vars *map)
{
	char	**map_copy;
	int		flags[2];

	ft_bzero(flags, sizeof(int) * 2);
	map_copy = dup_map(map->y_count, map->map);
	solve_maze(map_copy, flags, map->player.x, map->player.y);
	if (!flags[0] || !flags[1])
		return (destructor_map(map_copy), 1);
	return (destructor_map(map_copy), 0);
}

int	check_borders(t_vars *map)
{
	int	i;

	i = 0;
	while (i < map->x_count)
		if (map->map[0][i++] != '1')
			return (1);
	i = 0;
	while (i < map->y_count)
		if (map->map[i++][0] != '1')
			return (1);
	i = 0;
	while (i < map->y_count)
		if (map->map[i++][map->x_count - 1] != '1')
			return (1);
	i = 0;
	while (i < map->x_count)
		if (map->map[map->y_count - 1][i++] != '1')
			return (1);
	return (0);
}

int	validate_map(t_vars *map)
{
	if (check_borders(map) || check_escape(map))
		return (1);
	return (0);
}

void	destructor_map(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
		free(map[i++]);
	free(map);
}

void	destroy_enemy_images(t_vars *var)
{
	int	i;
	int	j;

	i = 0;
	while (i < 1)
	{
		j = 0;
		while (j < 7)
			mlx_destroy_image(var->mlx, var->enemies->frames[i][j++]);
		i++;
	}
}

void	destroy_collectible_images(t_vars *var)
{
	int	i;

	i = 0;
	while (i < 7)
		mlx_destroy_image(var->mlx, var->collectibles->frames[i++]);
}

void	free_player_images(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	while (i < 2)
	{
		j = 0;
		while (j < 6)
			mlx_destroy_image(vars->mlx, vars->player.LRframes[i][j++]);
		i++;
	}
}

void	destroy_images(t_vars *map)
{
	if (map->obstacle)
		mlx_destroy_image(map->mlx, map->obstacle);
	if (map->background)
		mlx_destroy_image(map->mlx, map->background);
	free_player_images(map);
	if (map->ex_count != 0)
		destroy_enemy_images(map);
	if (map->water)
		mlx_destroy_image(map->mlx, map->water);
	if (map->exit.img)
	{
		mlx_destroy_image(map->mlx, map->exit.img[0]);
		mlx_destroy_image(map->mlx, map->exit.img[1]);
	}
	if (map->bot_left_tile)
		mlx_destroy_image(map->mlx, map->bot_left_tile);
	if (map->bot_right_tile)
		mlx_destroy_image(map->mlx, map->bot_right_tile);
	if (map->bot_tile)
		mlx_destroy_image(map->mlx, map->bot_tile);
	if (map->top_left_tile)
		mlx_destroy_image(map->mlx, map->top_left_tile);
	if (map->top_right_tile)
		mlx_destroy_image(map->mlx, map->top_right_tile);
	if (map->top_tile)
		mlx_destroy_image(map->mlx, map->top_tile);
	if (map->left_tile)
		mlx_destroy_image(map->mlx, map->left_tile);
	if (map->right_tile)
		mlx_destroy_image(map->mlx, map->right_tile);
	if (map->collectibles)
		destroy_collectible_images(map);
}

void	destructor(t_vars *map)
{
	destructor_map(map->map);
	destroy_images(map);
	if (map->window)
		mlx_destroy_window(map->mlx, map->window);
	if (map->mlx)
	{
		mlx_destroy_display(map->mlx);
		free(map->mlx);
	}
	free(map->enemies);
	free(map->collectibles);
	exit(0);
}

void	start_game_window(t_vars *map)
{
	int	size_x;
	int	size_y;

	map->mlx = mlx_init();
	if (!map->mlx)
		destructor(map);
	mlx_get_screen_size(map->mlx, &size_x, &size_y);
	if ((map->x_count + 2) * TILE_SIZE > size_x
		|| (map->y_count + 2) * TILE_SIZE > size_y)
		return (ft_printf("Screen too big\n"), destructor(map));
	map->window = mlx_new_window(map->mlx, (map->x_count + 2) * TILE_SIZE \
		, (map->y_count + 2) * TILE_SIZE, "Meow");
	if (!map->window)
		destructor(map);
}

void	set_tiles(t_vars *map)
{
	int		tile_size;
	void	*(*f)(void *, char *, int *, int *);

	tile_size = TILE_SIZE;
	f = mlx_xpm_file_to_image;
	map->obstacle = f(map->mlx, OBSTACLE, &tile_size, &tile_size);
	map->background = f(map->mlx, BACKGROUND, &tile_size, &tile_size);
	map->player.LRframes[0][0] = f(map->mlx, PLAYER_RIGHT1, &tile_size, &tile_size);
	map->player.LRframes[0][1] = f(map->mlx, PLAYER_RIGHT2, &tile_size, &tile_size);
	map->player.LRframes[0][2] = f(map->mlx, PLAYER_RIGHT3, &tile_size, &tile_size);
	map->player.LRframes[0][3] = f(map->mlx, PLAYER_RIGHT4, &tile_size, &tile_size);
	map->player.LRframes[0][4] = f(map->mlx, PLAYER_RIGHT5, &tile_size, &tile_size);
	map->player.LRframes[0][5] = f(map->mlx, PLAYER_RIGHT6, &tile_size, &tile_size);
	map->player.LRframes[1][0] = f(map->mlx, PLAYER_LEFT1, &tile_size, &tile_size);
	map->player.LRframes[1][1] = f(map->mlx, PLAYER_LEFT2, &tile_size, &tile_size);
	map->player.LRframes[1][2] = f(map->mlx, PLAYER_LEFT3, &tile_size, &tile_size);
	map->player.LRframes[1][3] = f(map->mlx, PLAYER_LEFT4, &tile_size, &tile_size);
	map->player.LRframes[1][4] = f(map->mlx, PLAYER_LEFT5, &tile_size, &tile_size);
	map->player.LRframes[1][5] = f(map->mlx, PLAYER_LEFT6, &tile_size, &tile_size);
	if (map->ex_count != 0)
	{
		map->enemies->frames[0][0] = f(map->mlx, ENEMY_RIGHT1, &tile_size, &tile_size);
		map->enemies->frames[0][1] = f(map->mlx, ENEMY_RIGHT2, &tile_size, &tile_size);
		map->enemies->frames[0][2] = f(map->mlx, ENEMY_RIGHT3, &tile_size, &tile_size);
		map->enemies->frames[0][3] = f(map->mlx, ENEMY_RIGHT4, &tile_size, &tile_size);
		map->enemies->frames[0][4] = f(map->mlx, ENEMY_RIGHT5, &tile_size, &tile_size);
		map->enemies->frames[0][5] = f(map->mlx, ENEMY_RIGHT6, &tile_size, &tile_size);
		map->enemies->frames[0][6] = f(map->mlx, ENEMY_RIGHT7, &tile_size, &tile_size);
	}
	map->water = f(map->mlx, WATER, &tile_size, &tile_size);
	map->exit.img[0] = f(map->mlx, EXIT_INACTIVE, &tile_size, &tile_size);
	map->exit.img[1] = f(map->mlx, EXIT_ACTIVE, &tile_size, &tile_size);
	map->bot_left_tile = f(map->mlx, BOT_LEFT_TILE, &tile_size, &tile_size);
	map->bot_right_tile = f(map->mlx, BOT_RIGHT_TILE, &tile_size, &tile_size);
	map->bot_tile = f(map->mlx, BOT_TILE, &tile_size, &tile_size);
	map->top_left_tile = f(map->mlx, TOP_LEFT_TILE, &tile_size, &tile_size);
	map->top_right_tile = f(map->mlx, TOP_RIGHT_TILE, &tile_size, &tile_size);
	map->top_tile = f(map->mlx, TOP_TILE, &tile_size, &tile_size);
	map->left_tile = f(map->mlx, LEFT_TILE, &tile_size, &tile_size);
	map->right_tile = f(map->mlx, RIGHT_TILE, &tile_size, &tile_size);
	map->collectibles->frames[0] = f(map->mlx, COLLECTIBLE1, &tile_size, &tile_size);
	map->collectibles->frames[1] = f(map->mlx, COLLECTIBLE2, &tile_size, &tile_size);
	map->collectibles->frames[2] = f(map->mlx, COLLECTIBLE3, &tile_size, &tile_size);
	map->collectibles->frames[3] = f(map->mlx, COLLECTIBLE4, &tile_size, &tile_size);
	map->collectibles->frames[4] = f(map->mlx, COLLECTIBLE5, &tile_size, &tile_size);
	map->collectibles->frames[5] = f(map->mlx, COLLECTIBLE6, &tile_size, &tile_size);
	map->collectibles->frames[6] = f(map->mlx, COLLECTIBLE7, &tile_size, &tile_size);
}

void	draw_image(t_vars *map, void *img, int x, int y)
{
	mlx_put_image_to_window(map->mlx, map->window, \
		img, TILE_SIZE * x, TILE_SIZE * y);
}

void	draw_water(t_vars *map)
{
	int	i;

	i = 0;
	while (i < map->x_count + 2)
		draw_image(map, map->water, i++, 0);
	i = 0;
	while (i < map->y_count + 2)
		draw_image(map, map->water, 0, i++);
	i = 0;
	while (i < map->x_count + 2)
		draw_image(map, map->water, i++, map->y_count + 1);
	i = 0;
	while (i < map->x_count + 2)
		draw_image(map, map->water, map->x_count + 1, i++);
}

void	draw_border(t_vars *map)
{
	int	i;

	i = 1;
	while (i < map->x_count + 1)
	{
		if (i == 1)
			draw_image(map, map->top_left_tile, i++, 1);
		else if (i == map->x_count)
			draw_image(map, map->top_right_tile, i++, 1);
		else
			draw_image(map, map->top_tile, i++, 1);
	}
	i = 1;
	while (i < map->x_count + 1)
	{
		if (i == 1)
			draw_image(map, map->bot_left_tile, i++, map->y_count);
		else if (i == map->x_count)
			draw_image(map, map->bot_right_tile, i++, map->y_count);
		else
			draw_image(map, map->bot_tile, i++, map->y_count);
	}
	continue_border(map);
}

void	continue_border(t_vars *map)
{
	int	i;

	i = 2;
	while (i < map->y_count)
		draw_image(map, map->left_tile, 1, i++);
	i = 2;
	while (i < map->y_count)
		draw_image(map, map->right_tile, map->x_count, i++);
}

void	check_and_draw(t_vars *map, int i, int j)
{
	if (map->map[i][j] == '1')
		draw_image(map, map->obstacle, j + 1, i + 1);
	else if (map->map[i][j] == 'P')
	{
		if (map->player.direction == 0)
			draw_image(map, map->player.LRframes[0][map->player.LRframe_index], j + 1, i + 1);
		else if (map->player.direction == 1)
			draw_image(map, map->player.LRframes[1][map->player.LRframe_index], j + 1, i + 1);
		else if (map->player.direction == 2)
			draw_image(map, map->player.LRframes[0][map->player.LRframe_index], j + 1, i + 1);
		else if (map->player.direction == 3)
			draw_image(map, map->player.LRframes[0][map->player.LRframe_index], j + 1, i + 1);
	}
	else if (map->map[i][j] == 'X')
		draw_image(map, map->enemies->frames[map->enemies->direction][map->enemies->frame_index], j + 1, i + 1);
	else if (map->map[i][j] == 'E')
		draw_image(map, map->exit.img[map->exit.flag], j + 1, i + 1);
	else if (map->map[i][j] == 'C')
		draw_image(map, map->collectibles->frames[map->collectibles->frame_index], j + 1, i + 1);
	else
		draw_image(map, map->background, j + 1, i + 1);
}

void	render_map(t_vars *map)
{
	int	i;
	int	j;

	draw_water(map);
	draw_border(map);
	i = 1;
	while (map->map[i + 1])
	{
		j = 1;
		while (map->map[i][j + 1])
		{
			check_and_draw(map, i, j);
			j++;
		}
		i++;
	}
}

void	move_player(t_vars *map, int x, int y)
{
	int	new_x;
	int	new_y;

	new_x = map->player.x + x;
	new_y = map->player.y + y;
	if (map->map[new_x][new_y] == 'C')
		map->c_count--;
	if (map->map[new_x][new_y] != '1' && (map->map[new_x][new_y] != 'E'))
	{
		if (map->map[new_x][new_y] != 'E')
			map->map[map->player.x][map->player.y] = '0';
		map->player.x = new_x;
		map->player.y = new_y;
		map->map[new_x][new_y] = 'P';
		render_map(map);
	}
}

int	handle_key(int keysym, t_vars *map)
{
	if (keysym == XK_w)
	{
		map->player.direction = 2;
		move_player(map, -1, 0);
	}
	if (keysym == XK_s)
	{
		map->player.direction = 3;
		move_player(map, 1, 0);
	}
	if (keysym == XK_a)
	{
		map->player.direction = 1;
		move_player(map, 0, -1);
	}
	if (keysym == XK_d)
	{
		map->player.direction = 0;
		move_player(map, 0, 1);
	}
	if (keysym == XK_Escape)
		destructor(map);
	return (0);
}

int	handle_exit(t_vars *map)
{
	destructor(map);
	return (0);
}

int	update_game(t_vars *vars)
{
	static int	frame = 0;

	frame++;
	if (frame % 300 == 0 && !vars->collectibles->flag)
	{
		vars->collectibles->frame_index++;
		if (vars->collectibles->frame_index >= 7)
		{
			vars->collectibles->frame_index = 6;
			vars->collectibles->flag = 1;
		}
	}
	if (frame % 300 == 0)
	{
		vars->enemies->frame_index++;
		if (vars->player.direction == 0 || vars->player.direction == 1)
			vars->player.LRframe_index++;
		if (vars->player.LRframe_index >= 6)
			vars->player.LRframe_index = 0;
		if (vars->enemies->frame_index >= 7)
			vars->enemies->frame_index = 0;
	}
	if (frame % 30 == 0)
	{
		if (vars->c_count == 0)
			vars->exit.flag = 1;
		render_map(vars);
	}
}

void	init_vars(t_vars *vars)
{
	vars->enemies = malloc(sizeof(t_enemy) * vars->ex_count);
	vars->collectibles = malloc(sizeof(t_collectible) * vars->c_count);
}

int	main(int argc, char *argv[])
{
	t_vars	vars;

	ft_bzero(&vars, sizeof(t_vars));
	if (argc != 2)
		return (ft_printf("Invalid number of arguments\n"), 1);
	if (check_extension(argv[1]) || read_map(argv[1], &vars))
		return (ft_printf("Invalid map or file\n"), 1);
	if (validate_map(&vars))
		return (destructor(&vars), ft_printf("Invalid map\n"), 1);
	init_vars(&vars);
	start_game_window(&vars);
	set_tiles(&vars);
	mlx_hook(vars.window, 2, 1L << 0, &handle_key, &vars);
	mlx_hook(vars.window, 17, 0, &handle_exit, &vars);
	mlx_loop_hook(vars.mlx, &update_game, &vars);
	mlx_loop(vars.mlx);
	return (0);
}