/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuhamma <smuhamma@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 13:41:34 by mbin-nas          #+#    #+#             */
/*   Updated: 2023/08/10 19:49:08 by smuhamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	my_check_rc(t_info *info)
{
	if (info->map.tab_map[info->raycast.rmap.y][info->raycast.rmap.x] != '0' &&
		info->map.tab_map[info->raycast.rmap.y][info->raycast.rmap.x] != '2' &&
		info->map.tab_map[info->raycast.rmap.y][info->raycast.rmap.x] != 'E' &&
		info->map.tab_map[info->raycast.rmap.y][info->raycast.rmap.x] != 'N' &&
		info->map.tab_map[info->raycast.rmap.y][info->raycast.rmap.x] != 'S' &&
		info->map.tab_map[info->raycast.rmap.y][info->raycast.rmap.x] != 'W')
		return (1);
	return (0);
}

int	tab_size(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

t_img	*fn_new_image(t_info *info, int width, int height)
{
	t_img	*img;

	img = malloc(sizeof(t_img));
	if (!img)
		return (NULL);
	img->img_ptr = mlx_new_image(info->mlx_ptr, width, height);
	if (!img->img_ptr)
		return (NULL);
	img->img_data = (int *)mlx_get_data_addr(img->img_ptr, &img->bpp,
			&img->size_line, &img->endian);
	if (!img->img_data)
		return (NULL);
	img->width = width;
	img->height = height;
	return (img);
}

t_textur	*fn_new_textur(t_info *info, char *file)
{
	t_textur	*textur;

	textur = malloc(sizeof(t_textur));
	if (!textur)
		return (NULL);
	textur->textur_ptr = mlx_xpm_file_to_image(info->mlx_ptr, file,
			&textur->width, &textur->height);
	if (!textur->textur_ptr)
		return (NULL);
	textur->textur_data = (int *)mlx_get_data_addr(textur->textur_ptr,
			&textur->bpp, &textur->size_line, &textur->endian);
	if (!textur->textur_data)
		return (NULL);
	return (textur);
}

int	look_for_alpha(char *s, int i)
{
	while (s[i])
	{
		if (ft_isalpha(s[i]))
			return (WRONG_INPUT);
		i++;
	}
	return (SUCCESS);
}
