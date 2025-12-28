/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhassna <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 16:01:10 by zhassna           #+#    #+#             */
/*   Updated: 2025/12/21 17:31:13 by zhassna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	turn_left_right(t_game *g, double angle)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = g->player.dirX;
	old_planex = g->player.planeX;
	g->player.dirX = g->player.dirX * cos(angle) - g->player.dirY * sin(angle);
	g->player.dirY = old_dirx * sin(angle) + g->player.dirY * cos(angle);
	g->player.planeX = g->player.planeX * cos(angle) - g->player.planeY
		* sin(angle);
	g->player.planeY = old_planex * sin(angle) + g->player.planeY * cos(angle);
}

void	key_a_d(t_game *g, double sx, double sy)
{
	if (g->map[(int)(g->player.posY)][(int)(g->player.posX + sx
			* g->move_speed)] == '0')
		g->player.posX += sx * g->move_speed;
	if (g->map[(int)(g->player.posY + sy
			* g->move_speed)][(int)(g->player.posX)] == '0')
		g->player.posY += sy * g->move_speed;
}

void	key_move2(t_game *g)
{
	if (g->keys.a)
		key_a_d(g, g->player.dirY, -g->player.dirX);
	if (g->keys.d)
		key_a_d(g, -g->player.dirY, g->player.dirX);
	if (g->keys.right)
		turn_left_right(g, g->rot_speed);
	if (g->keys.left)
		turn_left_right(g, -g->rot_speed);
}

int	key_move(t_game *g)
{
	if (g->keys.w)
	{
		if (g->map[(int)(g->player.posY)][(int)(g->player.posX + g->player.dirX
				* g->move_speed)] == '0')
			g->player.posX += g->player.dirX * g->move_speed;
		if (g->map[(int)(g->player.posY + g->player.dirY
				* g->move_speed)][(int)(g->player.posX)] == '0')
			g->player.posY += g->player.dirY * g->move_speed;
	}
	if (g->keys.s)
	{
		if (g->map[(int)(g->player.posY)][(int)(g->player.posX - g->player.dirX
				* g->move_speed)] == '0')
			g->player.posX -= g->player.dirX * g->move_speed;
		if (g->map[(int)(g->player.posY - g->player.dirY
				* g->move_speed)][(int)(g->player.posX)] == '0')
			g->player.posY -= g->player.dirY * g->move_speed;
	}
	key_move2(g);
	return (0);
}
