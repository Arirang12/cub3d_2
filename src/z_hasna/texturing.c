/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texturing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhassna <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 17:30:39 by zhassna           #+#    #+#             */
/*   Updated: 2025/12/21 17:30:41 by zhassna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	get_texture_addresses(t_game *game)
{
	game->textures[0].addr = mlx_get_data_addr(game->textures[0].img,
			&game->textures[0].bpp, &game->textures[0].line_len,
			&game->textures[0].endian);
	game->textures[1].addr = mlx_get_data_addr(game->textures[1].img,
			&game->textures[1].bpp, &game->textures[1].line_len,
			&game->textures[1].endian);
	game->textures[2].addr = mlx_get_data_addr(game->textures[2].img,
			&game->textures[2].bpp, &game->textures[2].line_len,
			&game->textures[2].endian);
	game->textures[3].addr = mlx_get_data_addr(game->textures[3].img,
			&game->textures[3].bpp, &game->textures[3].line_len,
			&game->textures[3].endian);
	return (1);
}

int	load_textures(t_game *game)
{
	printf("im in texturing\n");
	game->textures[0].img = mlx_xpm_file_to_image(game->frame.mlx,
			game->textures[0].path, &game->textures[0].w, &game->textures[0].h);
	game->textures[1].img = mlx_xpm_file_to_image(game->frame.mlx,
			game->textures[1].path, &game->textures[1].w, &game->textures[1].h);
	game->textures[2].img = mlx_xpm_file_to_image(game->frame.mlx,
			game->textures[2].path, &game->textures[2].w, &game->textures[2].h);
	game->textures[3].img = mlx_xpm_file_to_image(game->frame.mlx,
			game->textures[3].path, &game->textures[3].w, &game->textures[3].h);
	if (game->textures[0].img == NULL || game->textures[1].img == NULL
		|| game->textures[2].img == NULL || game->textures[3].img == NULL)
		return (0);
	if (!get_texture_addresses(game))
		return (0);
	printf("im in texturing 3\n");
	return (1);
}
