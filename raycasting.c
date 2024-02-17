/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbin-nas <mbin-nas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 13:43:22 by mbin-nas          #+#    #+#             */
/*   Updated: 2023/08/10 19:23:35 by mbin-nas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
# @brief Initialize the raycast
* @param t_info_*info
* @param int_x 
*/
void	init_raycast(t_info *info, int x)
{
	info->raycast.camera = 2 * x / (double)(info->width) - 1;
	info->raycast.rpos.x = info->pos.x;
	info->raycast.rpos.y = info->pos.y;
	info->raycast.rdir.x = info->raycast.dir.x + info->raycast.plane.x
		* info->raycast.camera;
	info->raycast.rdir.y = info->raycast.dir.y + info->raycast.plane.y
		* info->raycast.camera;
	info->raycast.rmap.x = (int)info->raycast.rpos.x;
	info->raycast.rmap.y = (int)info->raycast.rpos.y;
	info->raycast.rdisd.x = fabs(1 / info->raycast.rdir.x);
	info->raycast.rdisd.y = fabs(1 / info->raycast.rdir.y);
	info->raycast.hit = 0;
}

/*
# @brief Will calculate the direction of the ray that has been sent out to the 
# grid intersection
* @example
* 1. (info->rc.rdir.x < 0): Throwing the ray direction towards left in the 
* x-axis. and vice versa for the else statement. 
* 2. (info->rc.rdir.y < 0): Throwing the ray direction upwards and vice versa. 
? @return
--> Calculates rc.rdist.x and rc.rdisty which represents the ray need to 
--> travel along the x-axis
--> and y-axis to intersect the grid lines from horizontal and vertical points. 
*/
void	direction_ray(t_info *info)
{
	if (info->raycast.rdir.x < 0)
	{
		info->raycast.step.x = -1;
		info->raycast.rdist.x = (info->raycast.rpos.x - info->raycast.rmap.x) 
			* info->raycast.rdisd.x;
	}
	else
	{
		info->raycast.step.x = 1;
		info->raycast.rdist.x = (info->raycast.rmap.x + 1.0
				- info->raycast.rpos.x) * info->raycast.rdisd.x;
	}
	if (info->raycast.rdir.y < 0)
	{
		info->raycast.step.y = -1;
		info->raycast.rdist.y = (info->raycast.rpos.y - info->raycast.rmap.y) 
			* info->raycast.rdisd.y;
	}
	else
	{
		info->raycast.step.y = 1;
		info->raycast.rdist.y = (info->raycast.rmap.y + 1.0
				- info->raycast.rpos.y) * info->raycast.rdisd.y;
	}
}

/*
# @brief The rays keeps going untill it hits a wall
* @example
* The ray keeps looping as it keeps hitting 0 which allows the user to increase 
* the step and dist.x of the ray which later entails calls the function to check 
* the ray whether it hit either of the conditions specified which leads to loop 
* exiting out of loop. 
--> rc.wall 0 and 2 means left and right,
	1 and 3 means up and down for the rays to move.
*/
void	hit_ray(t_info *info)
{
	while (info->raycast.hit == 0)
	{
		if (info->raycast.rdist.x < info->raycast.rdist.y)
		{
			info->raycast.rdist.x += info->raycast.rdisd.x;
			info->raycast.rmap.x += info->raycast.step.x;
			if (info->raycast.rdir.x < 0)
				info->raycast.wall = 0;
			else
				info->raycast.wall = 2;
		}
		else
		{
			info->raycast.rdist.y += info->raycast.rdisd.y;
			info->raycast.rmap.y += info->raycast.step.y;
			if (info->raycast.rdir.y < 0)
				info->raycast.wall = 1;
			else
				info->raycast.wall = 3;
		}
		if (my_check_rc(info) == 1)
			info->raycast.hit = 1;
	}
}

/*
# @brief It will calculate the size of the ray once hit the wall 
* @details
* - Checks which driection of the ray it hit the wall (x or y)
* - Calculates the [prependicular distance] to the wall along the direction ray
* - Using the info->height to calculate the raycast height in vertical sense
* - Calculates the wall slice where to start the wall from and where to end
* - Added the texxture.id to give different textures to the wall 
*/
void	size_ray(t_info *info)
{
	if (info->raycast.wall == 0 || info->raycast.wall == 2)
		info->raycast.dist = (info->raycast.rmap.x - info->raycast.rpos.x
				+ (1 - info->raycast.step.x) / 2) / info->raycast.rdir.x;
	else
		info->raycast.dist = (info->raycast.rmap.y - info->raycast.rpos.y + (1
					- info->raycast.step.y) / 2) / info->raycast.rdir.y;
	info->raycast.rh = ((info->height / info->raycast.dist));
	info->raycast.wstart = ((-info->raycast.rh)) / 2 + info->height / 2;
	if (info->raycast.wstart < 0)
		info->raycast.wstart = 0;
	info->raycast.wend = info->raycast.rh / 2 + info->height / 2;
	if (info->raycast.wend >= info->height)
		info->raycast.wend = info->height - 1;
	info->raycast.textur.id = (info->map.tab_map[info->raycast.rmap.y]
		[info->raycast.rmap.x] - '0') - 1;
}

void	wall_textur(t_info *info)
{
	double	wallx;

	if (info->raycast.wall == 0 || info->raycast.wall == 2)
		wallx = info->raycast.rpos.y + info->raycast.dist
			* info->raycast.rdir.y;
	else
		wallx = info->raycast.rpos.x + info->raycast.dist
			* info->raycast.rdir.x;
	wallx -= floor((wallx));
	info->raycast.textur.x = (int)(wallx * 64.0);
	if ((info->raycast.wall == 0 || info->raycast.wall == 2)
		&& info->raycast.rdir.x > 0)
		info->raycast.textur.x = 64 - info->raycast.textur.x - 1;
	if ((info->raycast.wall == 1 || info->raycast.wall == 3)
		&& info->raycast.rdir.y < 0)
		info->raycast.textur.x = 64 - info->raycast.textur.x - 1;
	if_and_elseforest(info);
	info->raycast.step_textur = 1.0 * 64 / info->raycast.rh;
	info->raycast.textur_pos = (info->raycast.wstart - info->height / 2
			+ info->raycast.rh / 2) * info->raycast.step_textur;
}
