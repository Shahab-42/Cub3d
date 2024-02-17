/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbin-nas <mbin-nas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 13:37:35 by mbin-nas          #+#    #+#             */
/*   Updated: 2023/08/10 12:39:09 by mbin-nas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_rgb(char *s, int i)
{
	i++;
	while ((ft_isdigit(s[i]) != 1))
	{
		if (s[i] != ' ')
			return (WRONG_INPUT);
		i++;
	}
	return (SUCCESS);
}

static int	check_data_c(t_info *info)
{
	int		i;
	int		fl;

	i = 1;
	fl = 0;
	while (info->data.c[i])
	{
		if (!ft_isdigit(info->data.c[i]) && (info->data.c[i] != ' ')
			&& (info->data.c[i] != ','))
			return (WRONG_INPUT);
		if (ft_isdigit(info->data.c[i]))
			fl = 1;
		if (info->data.c[i] == ',')
		{
			if (fl == 0)
				return (WRONG_INPUT);
			if (check_rgb(info->data.c, i) != SUCCESS)
				return (WRONG_INPUT);
		}
		i++;
	}
	return (SUCCESS);
}

static int	check_data_f(t_info *info)
{
	int		i;
	int		fl;

	i = 1;
	fl = 0;
	while (info->data.f[i])
	{
		if (!ft_isdigit(info->data.f[i]) 
			&& (info->data.f[i] != ' ') && (info->data.f[i] != ','))
			return (WRONG_INPUT);
		if (ft_isdigit(info->data.f[i]))
			fl = 1;
		if (info->data.f[i] == ',')
		{
			if (fl == 0)
				return (WRONG_INPUT);
			if (check_rgb(info->data.f, i) != SUCCESS)
				return (WRONG_INPUT);
		}
		i++;
	}
	if (check_data_c(info) != SUCCESS)
		return (WRONG_INPUT);
	return (SUCCESS);
}

int	check_data(t_info *info)
{
	int		i;

	if (!info->data.r || !info->data.n || !info->data.s || !info->data.w 
		|| !info->data.e || !info->data.sp || !info->data.f || !info->data.c 
		|| !info->map.list)
		return (WRONG_INPUT);
	i = 1;
	while (info->data.r[i])
	{
		if (ft_isalpha(info->data.r[i]))
			return (WRONG_INPUT);
		i++;
	}
	if (check_data_f(info) != SUCCESS)
		return (WRONG_INPUT);
	return (SUCCESS);
}
