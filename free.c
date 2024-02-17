/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbin-nas <mbin-nas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 13:41:52 by mbin-nas          #+#    #+#             */
/*   Updated: 2023/08/10 16:20:38 by mbin-nas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_img(t_info *info)
{
	if (info->img)
	{
		mlx_destroy_image(info->mlx_ptr, info->img->img_ptr);
		free(info->img);
		info->img = NULL;
	}
}

void	free_textur(t_info *info, t_textur *textur)
{
	if (textur)
	{
		mlx_destroy_image(info->mlx_ptr, textur->textur_ptr);
		free(textur);
		textur = NULL;
	}
}

void	ft_tabdel(void **tab)
{
	int		i;

	i = 0;
	if (tab)
	{
		while (tab[i])
			free(tab[i++]);
		free(tab);
	}
}

void	free_tab(t_info *info)
{
	if (info->raycast.zbuffer)
		free(info->raycast.zbuffer);
	if (info->map.tab_map)
		ft_tabdel((void *)info->map.tab_map);
	if (info->data.r)
		free(info->data.r);
	if (info->data.no)
		free(info->data.no);
	if (info->data.so)
		free(info->data.so);
	if (info->data.we)
		free(info->data.we);
	if (info->data.ea)
		free(info->data.ea);
	if (info->data.f)
		free(info->data.f);
	if (info->data.c)
		free(info->data.c);
	if (info->data.spr)
		free(info->data.spr);
}
