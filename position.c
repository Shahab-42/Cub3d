/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbin-nas <mbin-nas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:22:33 by smuhamma          #+#    #+#             */
/*   Updated: 2023/08/10 19:14:16 by mbin-nas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	init_pos(t_info *info)
{
	if (info->map.player == 'N')
	{
		info->raycast.dir.y = -1;
		info->raycast.plane.x = -0.80;
	}
	if (info->map.player == 'S')
	{
		info->raycast.dir.y = 1;
		info->raycast.plane.x = 0.80;
	}
	if (info->map.player == 'E')
	{
		info->raycast.dir.x = 1;
		info->raycast.plane.y = -0.80;
	}
	if (info->map.player == 'W')
	{
		info->raycast.dir.x = -1;
		info->raycast.plane.y = 0.80;
	}
	return (SUCCESS);
}

int	init_info_pos(t_info *info)
{
	info->mlx_ptr = mlx_init();
	if (!info->mlx_ptr)
		return (MLX_FAIL);
	info->img = fn_new_image(info, info->width, info->height);
	if (info->img == NULL)
		return (IMG_FAIL);
	info->error = init_pos(info);
	if (info->error != SUCCESS)
		return (info->error);
	return (SUCCESS);
}
