/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuhamma <smuhamma@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 19:07:50 by mbin-nas          #+#    #+#             */
/*   Updated: 2023/08/10 20:22:12 by smuhamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	path_fix_textures(t_info *info)
{
	int	i;

	path_fix_textures2(info);
	i = get_start_path(info->data.e);
	info->data.ea = ft_strtrim(info->data.e + i, " ");
	if (!(info->data.ea))
		return (MALLOC_FAIL);
	fn_free_path(info->data.e);
	i = get_start_path(info->data.sp);
	info->data.spr = ft_strtrim(info->data.sp + i, " ");
	if (!(info->data.spr))
		return (MALLOC_FAIL);
	fn_free_path(info->data.sp);
	return (SUCCESS);
}

void	if_and_elseforest(t_info *info)
{
	if ((info->raycast.wall == 0 || info->raycast.wall == 2)
		&& info->raycast.rdir.x >= 0)
		info->raycast.textur.id = 1;
	else if ((info->raycast.wall == 0 || info->raycast.wall == 2)
		&& info->raycast.rdir.x < 0) 
		info->raycast.textur.id = 0;
	else if ((info->raycast.wall == 1 || info->raycast.wall == 3)
		&& info->raycast.rdir.y < 0)
		info->raycast.textur.id = 2;
	else
		info->raycast.textur.id = 3;
}

void	ft_info_map_val(t_info *info, int i)
{
	info->map.tab_map[i] = 0;
	info->map.kol_line = i;
}
