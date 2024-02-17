/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbin-nas <mbin-nas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 13:41:45 by mbin-nas          #+#    #+#             */
/*   Updated: 2023/08/10 16:19:03 by mbin-nas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	key_hit(int key, t_info *info)
{
	if (key == KEY_UP || key == KEY_W)
		info->move.up = 1;
	if (key == KEY_DOWN || key == KEY_S)
		info->move.down = 1;
	if (key == KEY_LEFT)
		info->move.left = 1;
	if (key == KEY_A)
		info->move.move_left = 1;
	if (key == KEY_RIGHT)
		info->move.right = 1;
	if (key == KEY_D)
		info->move.move_right = 1;
	if (key == KEY_ESCAPE)
		deal_exit(info);
	return (SUCCESS);
}

static int	key_release(int key, t_info *info)
{
	if (key == KEY_UP || key == KEY_W)
		info->move.up = 0;
	if (key == KEY_DOWN || key == KEY_S)
		info->move.down = 0;
	if (key == KEY_LEFT)
		info->move.left = 0;
	if (key == KEY_A)
		info->move.move_left = 0;
	if (key == KEY_RIGHT)
		info->move.right = 0;
	if (key == KEY_D)
		info->move.move_right = 0;
	return (SUCCESS);
}

static int	fn_run(t_info *info)
{
	free_img(info);
	info->img = fn_new_image(info, info->width, info->height);
	if (info->img == NULL)
		return (IMG_FAIL);
	player_move(info);
	fn_display_screen(info);
	mlx_put_image_to_window(info->mlx_ptr, info->win_ptr, info->img->img_ptr, 0,
		0);
	return (SUCCESS);
}

int	events(t_info *info)
{
	info->win_ptr = mlx_new_window(info->mlx_ptr, info->width,
			info->height, "Cub3D");
	if (!info->win_ptr)
		return (MLX_FAIL);
	mlx_hook(info->win_ptr, 17, STRUCTURENOTIFYMASK, deal_exit, info);
	mlx_hook(info->win_ptr, KEYPRESS, KEYPRESSMASK, key_hit, info);
	mlx_hook(info->win_ptr, KEYRELEASE, KEYRELEASEMASK, key_release, info);
	info->error = mlx_loop_hook(info->mlx_ptr, fn_run, info);
	if (info->error != SUCCESS)
		return (info->error);
	mlx_loop(info->mlx_ptr);
	return (SUCCESS);
}
