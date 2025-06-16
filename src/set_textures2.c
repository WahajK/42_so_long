/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_textures2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakhan <muhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 18:07:20 by muhakhan          #+#    #+#             */
/*   Updated: 2025/06/16 18:12:50 by muhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	set_borders2(t_vars *vars, int tile_size)
{
	void	*(*f)(void *, char *, int *, int *);

	f = mlx_xpm_file_to_image;
	vars->borders.frames[2][0] = f(vars->mlx, T_R1, &tile_size, &tile_size);
	vars->borders.frames[2][1] = f(vars->mlx, T_R2, &tile_size, &tile_size);
	vars->borders.frames[2][2] = f(vars->mlx, T_R3, &tile_size, &tile_size);
	vars->borders.frames[2][3] = f(vars->mlx, T_R4, &tile_size, &tile_size);
	vars->borders.frames[2][4] = f(vars->mlx, T_R5, &tile_size, &tile_size);
	vars->borders.frames[2][5] = f(vars->mlx, T_R6, &tile_size, &tile_size);
	vars->borders.frames[2][6] = f(vars->mlx, T_R7, &tile_size, &tile_size);
	vars->borders.frames[2][7] = f(vars->mlx, T_R8, &tile_size, &tile_size);
	vars->borders.frames[3][0] = f(vars->mlx, L1, &tile_size, &tile_size);
	vars->borders.frames[3][1] = f(vars->mlx, L2, &tile_size, &tile_size);
	vars->borders.frames[3][2] = f(vars->mlx, L3, &tile_size, &tile_size);
	vars->borders.frames[3][3] = f(vars->mlx, L4, &tile_size, &tile_size);
	vars->borders.frames[3][4] = f(vars->mlx, L5, &tile_size, &tile_size);
	vars->borders.frames[3][5] = f(vars->mlx, L6, &tile_size, &tile_size);
	vars->borders.frames[3][6] = f(vars->mlx, L7, &tile_size, &tile_size);
	vars->borders.frames[3][7] = f(vars->mlx, L8, &tile_size, &tile_size);
}

void	set_borders3(t_vars *vars, int tile_size)
{
	void	*(*f)(void *, char *, int *, int *);

	f = mlx_xpm_file_to_image;
	vars->borders.frames[4][0] = f(vars->mlx, R1, &tile_size, &tile_size);
	vars->borders.frames[4][1] = f(vars->mlx, R2, &tile_size, &tile_size);
	vars->borders.frames[4][2] = f(vars->mlx, R3, &tile_size, &tile_size);
	vars->borders.frames[4][3] = f(vars->mlx, R4, &tile_size, &tile_size);
	vars->borders.frames[4][4] = f(vars->mlx, R5, &tile_size, &tile_size);
	vars->borders.frames[4][5] = f(vars->mlx, R6, &tile_size, &tile_size);
	vars->borders.frames[4][6] = f(vars->mlx, R7, &tile_size, &tile_size);
	vars->borders.frames[4][7] = f(vars->mlx, R8, &tile_size, &tile_size);
	vars->borders.frames[5][0] = f(vars->mlx, B_L1, &tile_size, &tile_size);
	vars->borders.frames[5][1] = f(vars->mlx, B_L2, &tile_size, &tile_size);
	vars->borders.frames[5][2] = f(vars->mlx, B_L3, &tile_size, &tile_size);
	vars->borders.frames[5][3] = f(vars->mlx, B_L4, &tile_size, &tile_size);
	vars->borders.frames[5][4] = f(vars->mlx, B_L5, &tile_size, &tile_size);
	vars->borders.frames[5][5] = f(vars->mlx, B_L6, &tile_size, &tile_size);
	vars->borders.frames[5][6] = f(vars->mlx, B_L7, &tile_size, &tile_size);
	vars->borders.frames[5][7] = f(vars->mlx, B_L8, &tile_size, &tile_size);
}

void	set_borders4(t_vars *vars, int tile_size)
{
	void	*(*f)(void *, char *, int *, int *);

	f = mlx_xpm_file_to_image;
	vars->borders.frames[6][0] = f(vars->mlx, B_1, &tile_size, &tile_size);
	vars->borders.frames[6][1] = f(vars->mlx, B_2, &tile_size, &tile_size);
	vars->borders.frames[6][2] = f(vars->mlx, B_3, &tile_size, &tile_size);
	vars->borders.frames[6][3] = f(vars->mlx, B_4, &tile_size, &tile_size);
	vars->borders.frames[6][4] = f(vars->mlx, B_5, &tile_size, &tile_size);
	vars->borders.frames[6][5] = f(vars->mlx, B_6, &tile_size, &tile_size);
	vars->borders.frames[6][6] = f(vars->mlx, B_7, &tile_size, &tile_size);
	vars->borders.frames[6][7] = f(vars->mlx, B_8, &tile_size, &tile_size);
	vars->borders.frames[7][0] = f(vars->mlx, B_R1, &tile_size, &tile_size);
	vars->borders.frames[7][1] = f(vars->mlx, B_R2, &tile_size, &tile_size);
	vars->borders.frames[7][2] = f(vars->mlx, B_R3, &tile_size, &tile_size);
	vars->borders.frames[7][3] = f(vars->mlx, B_R4, &tile_size, &tile_size);
	vars->borders.frames[7][4] = f(vars->mlx, B_R5, &tile_size, &tile_size);
	vars->borders.frames[7][5] = f(vars->mlx, B_R6, &tile_size, &tile_size);
	vars->borders.frames[7][6] = f(vars->mlx, B_R7, &tile_size, &tile_size);
	vars->borders.frames[7][7] = f(vars->mlx, B_R8, &tile_size, &tile_size);
}

void	set_tiles(t_vars *vars)
{
	int		tile_size;
	void	*(*f)(void *, char *, int *, int *);

	tile_size = TILE_SIZE;
	f = mlx_xpm_file_to_image;
	set_obstacles(vars, tile_size);
	set_player(vars, tile_size);
	vars->background = f(vars->mlx, BG, &tile_size, &tile_size);
	if (vars->ex_count != 0)
		set_enemies(vars, tile_size);
	vars->water = f(vars->mlx, WATER, &tile_size, &tile_size);
	vars->exit.img[0] = f(vars->mlx, EXT_IN, &tile_size, &tile_size);
	vars->exit.img[1] = f(vars->mlx, EXT_AT, &tile_size, &tile_size);
	set_borders1(vars, tile_size);
	set_borders2(vars, tile_size);
	set_borders3(vars, tile_size);
	set_borders4(vars, tile_size);
	set_collectibles(vars, tile_size);
	check_missing_textures(vars);
}

void	set_enemy_frames(t_vars *vars, int count)
{
	int	i;
	int	j;

	i = 0;
	while (i < 2)
	{
		j = 0;
		while (j < 7)
		{
			vars->enemies[count].frames[i][j] = vars-> \
			en_frames[i][j];
			j++;
		}
		i++;
	}
}
