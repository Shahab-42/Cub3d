/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbin-nas <mbin-nas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 13:37:39 by mbin-nas          #+#    #+#             */
/*   Updated: 2023/08/10 16:05:34 by mbin-nas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	pixel_textur(t_textur *textur, t_info *info)
{
	info->colour = textur->textur_data[64 * info->raycast.textur.y 
		+ info->raycast.textur.x];
}

void	pixel_colour(t_info *info)
{
	if (info->raycast.textur.id == 0)
		pixel_textur(info->textur3, info);
	else if (info->raycast.textur.id == 1)
		pixel_textur(info->textur4, info);
	else if (info->raycast.textur.id == 2)
		pixel_textur(info->textur1, info);
	else if (info->raycast.textur.id == 3)
		pixel_textur(info->textur2, info);
}

static int	check_tab(char *tab)
{
	int		i;
	int		size;

	i = 0;
	size = ft_strlen(tab);
	while (i < size && tab[i] == ' ')
		i++;
	while (i < size && ft_isdigit(tab[i]))
		i++;
	while (i < size)
	{
		if (ft_isdigit(tab[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	check_colour(char **tab)
{
	int		r;
	int		g;
	int		b;
	int		i;

	i = -1;
	if (tab_size(tab) == 3)
	{
		while (++i < 3)
		{
			if (check_tab(tab[i]) == 0)
				return (WRONG_INPUT);
		}
		r = ft_atoi(tab[0]);
		g = ft_atoi(tab[1]);
		b = ft_atoi(tab[2]);
	}
	else
	{
		ft_tabdel((void **)tab);
		return (WRONG_INPUT);
	}
	if (r > 255 || r < 0 || g > 255 || g < 0 || b > 255 || b < 0)
		return (WRONG_INPUT);
	return (SUCCESS);
}

int	get_colour(t_colour *colour, char *s)
{
	int		i;
	char	**tab;

	i = 0;
	while (!ft_isdigit(s[i]) && s[i] != '-')
		i++;
	if (look_for_alpha(s, i) != SUCCESS)
		return (WRONG_INPUT);
	tab = ft_split(s + i, ',');
	if (!tab)
		return (MALLOC_FAIL);
	if (check_colour(tab) == WRONG_INPUT)
		return (WRONG_INPUT);
	colour->rgb.r = ft_atoi(tab[0]);
	colour->rgb.g = ft_atoi(tab[1]);
	colour->rgb.b = ft_atoi(tab[2]);
	colour->rgb.a = 0x00;
	ft_tabdel((void **)tab);
	return (SUCCESS);
}
