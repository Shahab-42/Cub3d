/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuhamma <smuhamma@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:21:21 by smuhamma          #+#    #+#             */
/*   Updated: 2023/08/10 21:06:06 by smuhamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_data_part5(t_info *info, char *line, int i, int *flag_map)
{
	if (line[i] == 'C' && line[i + 1] == ' ' && *flag_map == 0 && \
		info->data.c == NULL)
	{
		info->data.c = ft_strtrim(line + i, " ");
		if (!info->data.c)
			return (MALLOC_FAIL);
	}
	else if (line[i] == 'C' && line[i + 1] == ' ' && (flag_map != 0 || \
		info->data.c != NULL))
		return (WRONG_INPUT);
	else if (line[i] != 'R' && (line[i] != 'N' && line[i + 1] != 'O') && \
		(line[i] != 'S' && line[i + 1] != 'O') && (line[i] != 'W' && line[i + 1]
			!= 'E') && (line[i] != 'E' && line[i + 1] != 'A') && line[i] != 'S'
		&& line[i] != 'F' && line[i] != 'C')
		return (WRONG_INPUT);
	return (SUCCESS);
}

static int	get_data_part4(t_info *info, char *line, int i, int *flag_map)
{
	if (line[i] == 'F' && line[i + 1] == ' ' && *flag_map == 0 && \
		info->data.f == NULL)
	{
		info->data.f = ft_strtrim(line + i, " ");
		if (!info->data.f)
			return (MALLOC_FAIL);
	}
	else if (line[i] == 'F' && line[i + 1] == ' ' && (flag_map != 0 || \
		info->data.f != NULL))
		return (WRONG_INPUT);
	info->error = get_data_part5(info, line, i, flag_map);
	if (info->error != SUCCESS)
		return (info->error);
	return (SUCCESS);
}

static	int	get_data_part3(t_info *info, char *line, int i, int *flag_map)
{
	if (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' '
		&& *flag_map == 0 && info->data.e == NULL)
	{
		info->data.e = ft_strdup(line + i);
		if (!info->data.e)
			return (MALLOC_FAIL);
	}
	else if (line[i] == 'E' && (flag_map != 0 || \
		info->data.e != NULL || line[i + 1] == ' ' || line[i + 1] != 'A'))
		return (WRONG_INPUT);
	if (line[i] == 'S' && line[i + 1] == ' ' && *flag_map == 0 && \
		info->data.sp == NULL)
	{
		(info->data.sp = ft_strdup(line + i));
		if (!info->data.sp)
			return (MALLOC_FAIL);
	}
	else if (line[i] == 'S' && line[i + 1] == ' ' && (flag_map != 0 || \
		info->data.sp != NULL))
		return (WRONG_INPUT);
	info->error = get_data_part4(info, line, i, flag_map);
	if (info->error != SUCCESS)
		return (info->error);
	return (SUCCESS);
}

static	int	get_data_part2(t_info *info, char *line, int i, int *flag_map)
{
	if (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' '
		&& *flag_map == 0 && info->data.s == NULL)
	{
		info->data.s = ft_strdup(line + i);
		if (!info->data.s)
			return (MALLOC_FAIL);
	}
	else if (line[i] == 'S' && line[i + 1] == 'O' && (*flag_map != 0 || \
		info->data.s != NULL || line[i + 2] != ' '))
		return (WRONG_INPUT);
	if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' '
		&& *flag_map == 0 && info->data.w == NULL)
	{
		info->data.w = ft_strdup(line + i);
		if (!info->data.w)
			return (MALLOC_FAIL);
	}
	else if (line[i] == 'W' && (flag_map != 0 || \
			info->data.w != NULL || line[i + 2] != ' ' || line[i + 1] != 'E'))
		return (WRONG_INPUT);
	info->error = get_data_part3(info, line, i, flag_map);
	if (info->error != SUCCESS)
		return (info->error);
	return (SUCCESS);
}

int	get_data(t_info *info, char *line, int i, int *flag_map)
{
	if (line[i] == 'R' && line[i + 1] == ' ' && *flag_map == 0
		&& info->data.r == NULL)
	{
		info->data.r = ft_strdup(line + i);
		if (!info->data.r)
			return (MALLOC_FAIL);
	}
	else if (line[i] == 'R' && (*flag_map != 0 || \
		info->data.r != NULL || line[i + 1] != ' '))
		return (WRONG_INPUT);
	if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' '
		&& *flag_map == 0 && info->data.n == NULL)
	{
		info->data.n = ft_strdup(line + i);
		if (!info->data.n)
			return (MALLOC_FAIL);
	}
	else if (line[i] == 'N' && (*flag_map != 0 || \
		info->data.n != NULL || line[i + 2] != ' ' || line[i + 1] != 'O'))
		return (WRONG_INPUT);
	info->error = get_data_part2(info, line, i, flag_map);
	if (info->error != SUCCESS)
		return (info->error);
	return (SUCCESS);
}
