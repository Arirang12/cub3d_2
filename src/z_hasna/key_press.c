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

int	ft_finish(t_game *g)
{
	(void)g;
	exit(0);
	return (0);
}

int	key_press(int keycode, t_game *g)
{
	if (keycode == KEY_ESC)
		ft_finish(g);
	if (keycode == KEY_W)
		g->keys.w = 1;
	else if (keycode == KEY_S)
		g->keys.s = 1;
	else if (keycode == KEY_A)
		g->keys.a = 1;
	else if (keycode == KEY_D)
		g->keys.d = 1;
	else if (keycode == KEY_LEFT)
		g->keys.left = 1;
	else if (keycode == KEY_RIGHT)
		g->keys.right = 1;
	return (0);
}

int	key_release(int keycode, t_game *g)
{
	if (keycode == KEY_W)
		g->keys.w = 0;
	else if (keycode == KEY_S)
		g->keys.s = 0;
	else if (keycode == KEY_A)
		g->keys.a = 0;
	else if (keycode == KEY_D)
		g->keys.d = 0;
	else if (keycode == KEY_LEFT)
		g->keys.left = 0;
	else if (keycode == KEY_RIGHT)
		g->keys.right = 0;
	return (0);
}

void	turn_left_right(t_game *g)
{
	double	old_dirx;
	double	old_planex;

	if (g->keys.right)
	{
		old_dirx = g->player.dirX;
		g->player.dirX = g->player.dirX * cos(g->rot_speed) - g->player.dirY
			* sin(g->rot_speed);
		g->player.dirY = old_dirx * sin(g->rot_speed) + g->player.dirY
			* cos(g->rot_speed);
		old_planex = g->player.planeX;
		g->player.planeX = g->player.planeX * cos(g->rot_speed)
			- g->player.planeY * sin(g->rot_speed);
		g->player.planeY = old_planex * sin(g->rot_speed) + g->player.planeY
			* cos(g->rot_speed);
	}
	if (g->keys.left)
	{
		old_dirx = g->player.dirX;
		g->player.dirX = g->player.dirX * cos(-g->rot_speed) - g->player.dirY
			* sin(-g->rot_speed);
		g->player.dirY = old_dirx * sin(-g->rot_speed) + g->player.dirY
			* cos(-g->rot_speed);
		old_planex = g->player.planeX;
		g->player.planeX = g->player.planeX * cos(-g->rot_speed)
			- g->player.planeY * sin(-g->rot_speed);
		g->player.planeY = old_planex * sin(-g->rot_speed) + g->player.planeY
			* cos(-g->rot_speed);
	}
}

int	key_move(t_game *g)
{
	double	sx;
	double	sy;

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
	if (g->keys.a)
	{
		sx = g->player.dirY;
		sy = -g->player.dirX;
		if (g->map[(int)(g->player.posY)][(int)(g->player.posX + sx
				* g->move_speed)] == '0')
			g->player.posX += sx * g->move_speed;
		if (g->map[(int)(g->player.posY + sy
				* g->move_speed)][(int)(g->player.posX)] == '0')
			g->player.posY += sy * g->move_speed;
	}
	if (g->keys.d)
	{
		sx = -g->player.dirY;
		sy = g->player.dirX;
		if (g->map[(int)(g->player.posY)][(int)(g->player.posX + sx
				* g->move_speed)] == '0')
			g->player.posX += sx * g->move_speed;
		if (g->map[(int)(g->player.posY + sy
				* g->move_speed)][(int)(g->player.posX)] == '0')
			g->player.posY += sy * g->move_speed;
	}
	turn_left_right(g);
	return (0);
}
