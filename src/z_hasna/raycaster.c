/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhassna <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 17:19:40 by zhassna           #+#    #+#             */
/*   Updated: 2025/12/21 17:20:05 by zhassna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	dda(t_game *g, t_box *box)
{
	box->hit = 0;
	box->side = 0;
	while (!box->hit)
	{
		if (box->sideDistX < box->sideDistY)
		{
			box->sideDistX += box->deltaDistX;
			box->mapX += box->stepX;
			box->side = 0;
		}
		else
		{
			box->sideDistY += box->deltaDistY;
			box->mapY += box->stepY;
			box->side = 1;
		}
		if (box->mapX < 0 || box->mapX >= MAP_W || box->mapY < 0
			|| box->mapY >= MAP_H)
			box->hit = 1;
		if (g->map[box->mapY][box->mapX] == '1')
			box->hit = 1;
	}
	distance(g, box);
}

void	perform_dda(t_game *g, t_box *box)
{
	if (box->rayDirY < 0)
	{
		box->stepY = -1;
		box->sideDistY = (g->player.posY - box->mapY) * box->deltaDistY;
	}
	else
	{
		box->stepY = 1;
		box->sideDistY = (box->mapY + 1.0 - g->player.posY) * box->deltaDistY;
	}
	dda(g, box);
}

void	ray_setup(t_game *g, t_box *box)
{
	box->mapX = (int)g->player.posX;
	box->mapY = (int)g->player.posY;
	box->rayDirX = g->player.dirX + g->player.planeX * box->cameraX;
	box->rayDirY = g->player.dirY + g->player.planeY * box->cameraX;
	if (box->rayDirX == 0)
		box->deltaDistX = 1e30;
	else
		box->deltaDistX = fabs(1 / box->rayDirX);
	if (box->rayDirY == 0)
		box->deltaDistY = 1e30;
	else
		box->deltaDistY = fabs(1 / box->rayDirY);
	if (box->rayDirX < 0)
	{
		box->stepX = -1;
		box->sideDistX = (g->player.posX - box->mapX) * box->deltaDistX;
	}
	else
	{
		box->stepX = 1;
		box->sideDistX = (box->mapX + 1.0 - g->player.posX) * box->deltaDistX;
	}
	perform_dda(g, box);
}

int	raycaster(t_game *g)
{
	t_box	box;
	int		x;
	int		y;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		box.cameraX = 2.0 * x / (double)WIDTH - 1.0;
		ray_setup(g, &box);
		while (y < HEIGHT)
		{
			if (y < box.drawStart)
				my_mlx_pixel_put(&g->frame, x, y, g->ceiling_color.value);
			else if (y > box.drawEnd)
				my_mlx_pixel_put(&g->frame, x, y, g->floor_color.value);
			else
				get_texture_color(g, &box, x, y);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(g->frame.mlx, g->frame.win, g->frame.img, 0, 0);
	return (0);
}
