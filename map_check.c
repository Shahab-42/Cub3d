/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbin-nas <mbin-nas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:22:04 by smuhamma          #+#    #+#             */
/*   Updated: 2023/08/10 18:45:32 by mbin-nas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_symbol(t_info *info, int i, int j)
{
	if (info->map.tab_map[i][j] != '1' && info->map.tab_map[i][j] != '0'
	&& info->map.tab_map[i][j] != '2' && info->map.tab_map[i][j] != 'N'
	&& info->map.tab_map[i][j] != 'S' && info->map.tab_map[i][j] != 'E'
	&& info->map.tab_map[i][j] != 'W')
		return (0);
	return (1);
}

static int	if_space_inside(t_info *info, int i, int j)
{
	if (check_symbol(info, i, j - 1) == 0)
		return (WRONG_MAP);
	else if (check_symbol(info, i, j + 1) == 0)
		return (WRONG_MAP);
	else if (check_symbol(info, i - 1, j) == 0)
		return (WRONG_MAP);
	else if (check_symbol(info, i + 1, j) == 0)
		return (WRONG_MAP);
	else if (check_symbol(info, i + 1, j - 1) == 0)
		return (WRONG_MAP);
	else if (check_symbol(info, i + 1, j + 1) == 0)
		return (WRONG_MAP);
	else if (check_symbol(info, i - 1, j - 1) == 0)
		return (WRONG_MAP);
	else if (check_symbol(info, i - 1, j + 1) == 0)
		return (WRONG_MAP);
	return (SUCCESS);
}

static int	case_null1(t_info *info, int i, int *j)
{
	while (info->map.tab_map[i][*j] != '1' &&
	info->map.tab_map[i][*j])
	{
		if (info->map.tab_map[i][*j] != ' ')
			return (WRONG_MAP);
		(*j)++;
	}
	return (SUCCESS);
}

static int	cases(t_info *info, int i, int *j)
{
	if (j == 0)
	{
		info->error = case_null1(info, i, j);
		if (info->error != SUCCESS)
			return (info->error);
	}
	if ((i == 0) || (i == info->map.kol_line - 1))
	{
		if (info->map.tab_map[i][*j] != '1' &&
		info->map.tab_map[i][*j] != ' ')
			return (WRONG_MAP);
	}
	if ((info->map.tab_map[i][*j] == '0' || info->map.tab_map[i][*j] == 'N'
		|| info->map.tab_map[i][*j] == 'S' || info->map.tab_map[i][*j] == 'E'
		|| info->map.tab_map[i][*j] == 'W') && i != 0 &&
		i != info->map.kol_line && *j != 0)
	{
		info->error = if_space_inside(info, i, *j);
		if (info->error != SUCCESS)
			return (info->error);
	}
	return (SUCCESS);
}

int	closed_map(t_info *info)
{
	int		j;
	int		i;
	int		j_prev;

	i = 0;
	j = 0;
	while (i < info->map.kol_line)
	{
		j_prev = j;
		j = 0;
		while (info->map.tab_map[i][j])
		{
			info->error = cases(info, i, &j);
			if (info->error != SUCCESS)
				return (info->error);
			j++;
		}
		i++;
	}
	return (SUCCESS);
}
