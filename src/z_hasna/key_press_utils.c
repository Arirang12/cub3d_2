/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhassna <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 23:42:39 by zhassna           #+#    #+#             */
/*   Updated: 2025/12/26 23:43:29 by zhassna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	ft_finish(t_game *g)
{
	//(void)g;
	//Free memory
	if (g->textures[0].img)
		mlx_destroy_image(g->frame.mlx, g->textures[0].img);
	if (g->textures[1].img)
		mlx_destroy_image(g->frame.mlx, g->textures[1].img);
	if (g->textures[2].img)
		mlx_destroy_image(g->frame.mlx, g->textures[2].img);
	if (g->textures[3].img)
		mlx_destroy_image(g->frame.mlx, g->textures[3].img);
	// return (0);
	if (g->frame.img)
		mlx_destroy_image(g->frame.mlx, g->frame.img);
	if (g->frame.win)
		mlx_destroy_window(g->frame.mlx, g->frame.win);
	if (g->frame.mlx)
	{
		mlx_destroy_display(g->frame.mlx);
		free(g->frame.mlx);
	}
	printf(">>>>>>>>>>>>Exiting the game. Goodbye!\n");
	print_error("Duplicate player");
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
