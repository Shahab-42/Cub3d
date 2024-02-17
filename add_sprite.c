/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_sprite.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbin-nas <mbin-nas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 13:37:29 by mbin-nas          #+#    #+#             */
/*   Updated: 2023/08/10 12:33:49 by mbin-nas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	add_sprite_part_two(t_info *info)
{
	int	d;
	int	y;

	y = info->sp.drawstart_y;
	if (info->sp.transy > 0 && info->sp.stripe > 0
		&& info->sp.stripe < info->width
		&& info->sp.transy < info->raycast.zbuffer[info->sp.stripe])
	{
		while (y < info->sp.drawend_y)
		{
			d = y * 256 - info->height * 128 + info->sp.sprite_height * 128;
			info->sp.sp_y = ((d * 64) / info->sp.sprite_height) / 256;
			info->colour = info->sprite->textur_data[info->sprite->width 
				* info->sp.sp_y + info->sp.sp_x];
			if (info->colour != PINK && info->colour != BLACK)
				put_pixel(info->img, info->colour, info->sp.stripe, y);
			y++;
		}
	}
}

static void	calc_end_start(t_info *info)
{
	if (info->sp.drawstart_y < 0)
		info->sp.drawstart_y = 0;
	info->sp.drawend_y = info->sp.sprite_height / 2 + info->height / 2;
	if (info->sp.drawend_y >= info->height)
		info->sp.drawend_y = info->height - 1;
	info->sp.sprite_width = abs((int)(info->height / (info->sp.transy)));
	info->sp.drawstart_x = -info->sp.sprite_width / 2 + info->sp.spritescreenx;
	if (info->sp.drawstart_x < 0)
		info->sp.drawstart_x = 0;
	info->sp.drawend_x = info->sp.sprite_width / 2 + info->sp.spritescreenx;
	if (info->sp.drawend_x >= info->width)
		info->sp.drawend_x = info->width - 1;
}

static void	sprite_calc(t_info *info, int i)
{
	double	inv;

	info->sp.spcamx = info->tab_sprite[info->raycast.sp_order[i]].pos_x
		- info->pos.x;
	info->sp.spcamy = info->tab_sprite[info->raycast.sp_order[i]].pos_y
		- info->pos.y;
	inv = 1.0 / (info->raycast.plane.x * info->raycast.dir.y
			- info->raycast.dir.x * info->raycast.plane.y);
	info->sp.transx = inv * (info->raycast.dir.y * info->sp.spcamx
			- info->raycast.dir.x * info->sp.spcamy);
	info->sp.transy = inv * (-info->raycast.plane.y * info->sp.spcamx
			+ info->raycast.plane.x * info->sp.spcamy);
	info->sp.spritescreenx = (int)((info->width / 2) * (1 + info->sp.transx
				/ info->sp.transy));
	info->sp.sprite_height = abs((int)(info->height / info->sp.transy));
	info->sp.drawstart_y = -info->sp.sprite_height / 2 + info->height / 2;
	calc_end_start(info);
}

void	add_sprite(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->kol_sprite)
	{
		sprite_calc(info, i);
		info->sp.stripe = info->sp.drawstart_x;
		while (info->sp.stripe < info->sp.drawend_x)
		{
			info->sp.sp_x = (int)(256 * (info->sp.stripe 
						- (-info->sp.sprite_width / 2 + info->sp.spritescreenx))
					* info->sprite->width / info->sp.sprite_width / 256);
			add_sprite_part_two(info);
			info->sp.stripe++;
		}
	}
}
