/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbin-nas <mbin-nas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 13:39:51 by mbin-nas          #+#    #+#             */
/*   Updated: 2023/08/10 16:11:00 by mbin-nas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(t_img *img, unsigned int colour, int p_x, int p_y)
{
	if (p_y >= img->height || p_x >= img->width || p_x < 0 || p_y < 0)
		return ;
	img->img_data[p_y * img->width + p_x] = colour;
}

static int	display_col(t_info *info, int x)
{
	int		y;

	y = 0;
	while (y < info->raycast.wstart)
		put_pixel(info->img, info->colour_ceiling.all, x, y++);
	while (y >= info->raycast.wstart && y <= info->raycast.wend)
	{
		info->raycast.textur.y = (int)info->raycast.textur_pos & (64 - 1);
		info->raycast.textur_pos += info->raycast.step_textur;
		pixel_colour(info);
		put_pixel(info->img, info->colour, x, y);
		y++;
	}
	while (y < info->height)
		put_pixel(info->img, info->colour_floor.all, x, y++);
	return (SUCCESS);
}

int	fn_display_screen(t_info *info)
{
	int	x;

	x = 0;
	while (x < info->width - 1)
	{
		init_raycast(info, x);
		direction_ray(info);
		hit_ray(info);
		size_ray(info);
		wall_textur(info);
		info->error = display_col(info, x++);
		if (info->error != SUCCESS)
			return (info->error);
		info->raycast.zbuffer[x] = info->raycast.dist;
	}
	info->error = init_sprite(info);
	if (info->error != SUCCESS)
		return (info->error);
	return (SUCCESS);
}
