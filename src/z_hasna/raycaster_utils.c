/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhassna <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 17:22:04 by zhassna           #+#    #+#             */
/*   Updated: 2025/12/21 17:23:49 by zhassna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

static int	get_texcolor(t_game *g, int tex, int tx, int ty)
{
	char	*pixel;

	if (!g->textures[tex].flag)
	{
		printf("Error: Texture %d not loaded properly.\n", tex);
		return (0xFFFFFF);
	}
	pixel = g->textures[tex].addr + (ty * g->textures[tex].line_len + tx
			* (g->textures[tex].bpp / 8));
	return (*(unsigned int *)pixel);
}

void	get_texture_color(t_game *g, t_box *box, int x, int y)
{
	box->texY = (int)box->texPos;
	if (box->texY < 0)
		box->texY = 0;
	if (box->texY >= g->textures[box->texNum].h)
		box->texY = g->textures[box->texNum].h - 1;
	box->texPos += box->step;
	if (g->textures[box->texNum].flag)
		box->color = get_texcolor(g, box->texNum, box->texX, box->texY);
	else
	{
		if (box->texNum == 0)
			box->color = 0xFF0000;
		else if (box->texNum == 1)
			box->color = 0x00FF00;
		else if (box->texNum == 2)
			box->color = 0x0000FF;
		else
			box->color = 0xFFFF00;
	}
	if (box->side == 1)
		box->color = (box->color >> 1) & 0x7F7F7F;
	my_mlx_pixel_put(&g->frame, x, y, box->color);
}

void	texture(t_game *g, t_box *box)
{
	if (box->side == 0 && box->rayDirX > 0)
		box->texNum = 3;
	else if (box->side == 0 && box->rayDirX < 0)
		box->texNum = 2;
	else if (box->side == 1 && box->rayDirY > 0)
		box->texNum = 1;
	else
		box->texNum = 0;
	if (box->side == 0)
		box->wallX = g->player.posY + box->perpWallDist * box->rayDirY;
	else
		box->wallX = g->player.posX + box->perpWallDist * box->rayDirX;
	box->wallX -= floor(box->wallX);
	box->texX = (int)(box->wallX * g->textures[box->texNum].w);
	if (box->side == 0 && box->rayDirX > 0)
		box->texX = g->textures[box->texNum].w - box->texX - 1;
	if (box->side == 1 && box->rayDirY < 0)
		box->texX = g->textures[box->texNum].w - box->texX - 1;
	box->step = 1.0 * g->textures[box->texNum].h / box->lineHeight;
	box->texPos = (box->drawStart - HEIGHT / 2 + box->lineHeight / 2)
		* box->step;
}

void	distance(t_game *g, t_box *box)
{
	if (box->side == 0)
		box->perpWallDist = (box->mapX - g->player.posX + (1 - box->stepX)
				/ 2.0) / box->rayDirX;
	else
		box->perpWallDist = (box->mapY - g->player.posY + (1 - box->stepY)
				/ 2.0) / box->rayDirY;
	box->lineHeight = (int)(HEIGHT / box->perpWallDist);
	box->drawStart = -box->lineHeight / 2 + HEIGHT / 2;
	box->drawEnd = box->lineHeight / 2 + HEIGHT / 2;
	if (box->drawStart < 0)
		box->drawStart = 0;
	if (box->drawEnd >= HEIGHT)
		box->drawEnd = HEIGHT - 1;
	texture(g, box);
}
