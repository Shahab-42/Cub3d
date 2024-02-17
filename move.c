/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbin-nas <mbin-nas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 14:06:56 by mbin-nas          #+#    #+#             */
/*   Updated: 2023/08/10 18:48:26 by mbin-nas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
# @brief Rotates the player with the advance (angle of rotation)
# @brief Info is the list containing the raycasting information 
? @param  t_info_*info  @param  int_advance
* @example Plane is storing the camera plane and Dir is storing x component of
* of the direction vector and to presever the original direction. 
*/
static void	player_rotate(t_info *info, int advance)
{
	double	dir_vec;
	double	plane;

	dir_vec = info->raycast.dir.x;
	plane = info->raycast.plane.x;
	info->raycast.dir.x = info->raycast.dir.x * cos(advance * 0.05)
		- info->raycast.dir.y * sin(advance * 0.05);
	info->raycast.dir.y = dir_vec * sin(advance * 0.05)
		+ info->raycast.dir.y * cos(advance * 0.05);
	info->raycast.plane.x = info->raycast.plane.x * cos(advance * 0.05)
		- info->raycast.plane.y * sin(advance * 0.05);
	info->raycast.plane.y = plane * sin(advance * 0.05)
		+ info->raycast.plane.y * cos(advance * 0.05);
}

static void	up_down(t_info *info)
{
	if (info->move.up == 1)
	{
		if (info->map.tab_map[(int)(info->pos.y)][(int)(info->pos.x + \
		info->raycast.dir.x * info->raycast.speed)] == '0')
			info->pos.x += info->raycast.dir.x * info->raycast.speed;
		if (info->map.tab_map[(int)(info->pos.y + info->raycast.dir.y * \
			info->raycast.speed)][(int)(info->pos.x)] == '0')
			info->pos.y += info->raycast.dir.y * info->raycast.speed;
	}
	if (info->move.down == 1)
	{
		if (info->map.tab_map[(int)(info->pos.y)][(int)(info->pos.x - \
		info->raycast.dir.x * info->raycast.speed)] == '0')
			info->pos.x -= info->raycast.dir.x * info->raycast.speed;
		if (info->map.tab_map[(int)(info->pos.y - info->raycast.dir.y * \
			info->raycast.speed)][(int)(info->pos.x)] == '0')
			info->pos.y -= info->raycast.dir.y * info->raycast.speed;
	}
}

/*
* @brief Movements of the player left and right 
* @param t_info_info
* @return Should move the player left and right 
*/
static void	move_left_right(t_info *info)
{
	if (info->move.move_right == 1)
	{
		if (info->map.tab_map[(int)(info->pos.y - info->raycast.dir.x * \
				info->raycast.speed)][(int)(info->pos.x)] == '0')
			info->pos.y -= info->raycast.dir.x * info->raycast.speed;
		if (info->map.tab_map[(int)(info->pos.y)][(int)(info->pos.x
			+ info->raycast.dir.y * info->raycast.speed)] == '0')
			info->pos.x += info->raycast.dir.y * info->raycast.speed;
	}
	if (info->move.move_left == 1)
	{
		if (info->map.tab_map[(int)(info->pos.y + info->raycast.dir.x * \
			info->raycast.speed)][(int)(info->pos.x)] == '0')
			info->pos.y -= -info->raycast.dir.x * info->raycast.speed;
		if (info->map.tab_map[(int)(info->pos.y)][(int)(info->pos.x -
			info->raycast.dir.y * info->raycast.speed)] == '0')
			info->pos.x -= info->raycast.dir.y * info->raycast.speed;
	}
}

/*
# @brief Calls the other functions to move the player
? @param t_info_*info
. @return Returns the movement of the player
*/
void	player_move(t_info *info)
{
	if (info->move.up == 1 || info->move.down == 1)
		up_down(info);
	if (info->move.move_right == 1 || info->move.move_left == 1)
		move_left_right(info);
	if (info->move.left == 1)
		player_rotate(info, 1);
	if (info->move.right == 1)
		player_rotate(info, -1);
}
