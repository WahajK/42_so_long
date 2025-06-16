/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakhan <muhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 18:05:25 by muhakhan          #+#    #+#             */
/*   Updated: 2025/06/16 18:06:52 by muhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	set_obstacles(t_vars *vars, int tile_size)
{
	void	*(*f)(void *, char *, int *, int *);

	f = mlx_xpm_file_to_image;
	vars->obstacle.frames[0] = f(vars->mlx, OBS1, &tile_size, &tile_size);
	vars->obstacle.frames[1] = f(vars->mlx, OBS2, &tile_size, &tile_size);
	vars->obstacle.frames[2] = f(vars->mlx, OBS3, &tile_size, &tile_size);
	vars->obstacle.frames[3] = f(vars->mlx, OBS4, &tile_size, &tile_size);
	vars->obstacle.frames[4] = f(vars->mlx, OBS5, &tile_size, &tile_size);
	vars->obstacle.frames[5] = f(vars->mlx, OBS6, &tile_size, &tile_size);
	vars->obstacle.frames[6] = f(vars->mlx, OBS7, &tile_size, &tile_size);
	vars->obstacle.frames[7] = f(vars->mlx, OBS8, &tile_size, &tile_size);
}

void	set_player(t_vars *vars, int tile_size)
{
	void	*(*f)(void *, char *, int *, int *);

	f = mlx_xpm_file_to_image;
	vars->player.frames[0][0] = f(vars->mlx, P_R1, &tile_size, &tile_size);
	vars->player.frames[0][1] = f(vars->mlx, P_R2, &tile_size, &tile_size);
	vars->player.frames[0][2] = f(vars->mlx, P_R3, &tile_size, &tile_size);
	vars->player.frames[0][3] = f(vars->mlx, P_R4, &tile_size, &tile_size);
	vars->player.frames[0][4] = f(vars->mlx, P_R5, &tile_size, &tile_size);
	vars->player.frames[0][5] = f(vars->mlx, P_R6, &tile_size, &tile_size);
	vars->player.frames[1][0] = f(vars->mlx, P_L1, &tile_size, &tile_size);
	vars->player.frames[1][1] = f(vars->mlx, P_L2, &tile_size, &tile_size);
	vars->player.frames[1][2] = f(vars->mlx, P_L3, &tile_size, &tile_size);
	vars->player.frames[1][3] = f(vars->mlx, P_L4, &tile_size, &tile_size);
	vars->player.frames[1][4] = f(vars->mlx, P_L5, &tile_size, &tile_size);
	vars->player.frames[1][5] = f(vars->mlx, P_L6, &tile_size, &tile_size);
}

void	set_enemies(t_vars *vars, int tile_size)
{
	void	*(*f)(void *, char *, int *, int *);

	f = mlx_xpm_file_to_image;
	vars->en_frames[0][0] = f(vars->mlx, E_R1, &tile_size, &tile_size);
	vars->en_frames[0][1] = f(vars->mlx, E_R2, &tile_size, &tile_size);
	vars->en_frames[0][2] = f(vars->mlx, E_R3, &tile_size, &tile_size);
	vars->en_frames[0][3] = f(vars->mlx, E_R4, &tile_size, &tile_size);
	vars->en_frames[0][4] = f(vars->mlx, E_R5, &tile_size, &tile_size);
	vars->en_frames[0][5] = f(vars->mlx, E_R6, &tile_size, &tile_size);
	vars->en_frames[0][6] = f(vars->mlx, E_R7, &tile_size, &tile_size);
	vars->en_frames[1][0] = f(vars->mlx, E_L1, &tile_size, &tile_size);
	vars->en_frames[1][1] = f(vars->mlx, E_L2, &tile_size, &tile_size);
	vars->en_frames[1][2] = f(vars->mlx, E_L3, &tile_size, &tile_size);
	vars->en_frames[1][3] = f(vars->mlx, E_L4, &tile_size, &tile_size);
	vars->en_frames[1][4] = f(vars->mlx, E_L5, &tile_size, &tile_size);
	vars->en_frames[1][5] = f(vars->mlx, E_L6, &tile_size, &tile_size);
	vars->en_frames[1][6] = f(vars->mlx, E_L7, &tile_size, &tile_size);
}

void	set_collectibles(t_vars *vars, int tile_size)
{
	void	*(*f)(void *, char *, int *, int *);

	f = mlx_xpm_file_to_image;
	vars->collectibles.frames[0] = f(vars->mlx, COL1, &tile_size, &tile_size);
	vars->collectibles.frames[1] = f(vars->mlx, COL2, &tile_size, &tile_size);
	vars->collectibles.frames[2] = f(vars->mlx, COL3, &tile_size, &tile_size);
	vars->collectibles.frames[3] = f(vars->mlx, COL4, &tile_size, &tile_size);
	vars->collectibles.frames[4] = f(vars->mlx, COL5, &tile_size, &tile_size);
	vars->collectibles.frames[5] = f(vars->mlx, COL6, &tile_size, &tile_size);
	vars->collectibles.frames[6] = f(vars->mlx, COL7, &tile_size, &tile_size);
}

void	set_borders1(t_vars *vars, int tile_size)
{
	void	*(*f)(void *, char *, int *, int *);

	f = mlx_xpm_file_to_image;
	vars->borders.frames[0][0] = f(vars->mlx, T_L1, &tile_size, &tile_size);
	vars->borders.frames[0][1] = f(vars->mlx, T_L2, &tile_size, &tile_size);
	vars->borders.frames[0][2] = f(vars->mlx, T_L3, &tile_size, &tile_size);
	vars->borders.frames[0][3] = f(vars->mlx, T_L4, &tile_size, &tile_size);
	vars->borders.frames[0][4] = f(vars->mlx, T_L5, &tile_size, &tile_size);
	vars->borders.frames[0][5] = f(vars->mlx, T_L6, &tile_size, &tile_size);
	vars->borders.frames[0][6] = f(vars->mlx, T_L7, &tile_size, &tile_size);
	vars->borders.frames[0][7] = f(vars->mlx, T_L8, &tile_size, &tile_size);
	vars->borders.frames[1][0] = f(vars->mlx, T_1, &tile_size, &tile_size);
	vars->borders.frames[1][1] = f(vars->mlx, T_2, &tile_size, &tile_size);
	vars->borders.frames[1][2] = f(vars->mlx, T_3, &tile_size, &tile_size);
	vars->borders.frames[1][3] = f(vars->mlx, T_4, &tile_size, &tile_size);
	vars->borders.frames[1][4] = f(vars->mlx, T_5, &tile_size, &tile_size);
	vars->borders.frames[1][5] = f(vars->mlx, T_6, &tile_size, &tile_size);
	vars->borders.frames[1][6] = f(vars->mlx, T_7, &tile_size, &tile_size);
	vars->borders.frames[1][7] = f(vars->mlx, T_8, &tile_size, &tile_size);
}
