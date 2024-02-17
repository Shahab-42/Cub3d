/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbin-nas <mbin-nas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 18:36:43 by mbin-nas          #+#    #+#             */
/*   Updated: 2023/08/10 18:39:57 by mbin-nas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	init_texture(t_info *info)
{
	info->textur1 = fn_new_textur(info, info->data.no);
	if (info->textur1 == NULL)
		return (WRONG_TEXTURE);
	info->textur2 = fn_new_textur(info, info->data.so);
	if (info->textur2 == NULL)
		return (WRONG_TEXTURE);
	info->textur3 = fn_new_textur(info, info->data.we);
	if (info->textur3 == NULL)
		return (WRONG_TEXTURE);
	info->textur4 = fn_new_textur(info, info->data.ea);
	if (info->textur4 == NULL)
		return (WRONG_TEXTURE);
	info->sprite = fn_new_textur(info, info->data.spr);
	if (info->sprite == NULL)
		return (WRONG_TEXTURE);
	return (SUCCESS);
}

int	init_var(t_info *info, char *s)
{
	info->error = init_var2(info, s);
	if (info->error != SUCCESS)
		return (info->error);
	info->raycast.zbuffer = malloc(sizeof(double) * info->width);
	if (!(info->raycast.zbuffer))
		return (MALLOC_FAIL);
	(info->error = init_texture(info));
	if (info->error != SUCCESS)
		return (info->error);
	return (SUCCESS);
}
