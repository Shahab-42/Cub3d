/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuhamma <smuhamma@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:21:48 by smuhamma          #+#    #+#             */
/*   Updated: 2023/08/10 20:20:54 by smuhamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_save(t_info *info, int argc, char *s)
{
	if (argc == 3 && (ft_strncmp(s, "--save", ft_strlen(s)) == 0))
		info->flag_save = 1;
	else if (argc == 3)
		return (INVALID_ARG);
	return (SUCCESS);
}

static int	check_tab2(char *tab)
{
	int		i;
	int		size;

	i = 0;
	size = ft_strlen(tab);
	while (i < size)
	{
		if (!ft_isdigit(tab[i]) && tab[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

static int	get_resolution(t_info *info)
{
	char	**tab;
	int		l;

	l = -1;
	info->error = check_resolut(info, &tab);
	if (info->error != SUCCESS)
		return (info->error);
	if (tab_size(tab) == 2)
	{
		while (++l < 2)
			if (!check_tab2(tab[l]))
				return (WRONG_INPUT);
		if (tab[0])
			info->width = ft_atoi(tab[0]);
		if (tab[1])
			info->height = ft_atoi(tab[1]);
	}
	else
		return (WRONG_INPUT);
	ft_tabdel((void **)tab);
	if (!info->width || !info->height || info->width < 0 || info->height < 0)
		return (WRONG_INPUT);
	check_resolut2(info);
	return (SUCCESS);
}

int	init_var2(t_info *info, char *s)
{
	int	i[2];

	i[0] = 0;
	i[1] = 0;
	info->raycast.speed = 0.05;
	info->error = get_map(info, s, i);
	if (info->error != SUCCESS)
		return (info->error);
	info->error = parse_map(info);
	if (info->error != SUCCESS)
		return (info->error);
	info->error = get_colour(&info->colour_floor, info->data.f);
	if (info->error != SUCCESS)
		return (info->error);
	info->error = get_colour(&info->colour_ceiling, info->data.c);
	if (info->error != SUCCESS)
		return (info->error);
	info->error = get_resolution(info);
	if (info->error != SUCCESS)
		return (info->error);
	info->error = init_info_pos(info);
	if (info->error != SUCCESS)
		return (info->error);
	return (SUCCESS);
}
