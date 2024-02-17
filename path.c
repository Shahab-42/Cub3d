/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbin-nas <mbin-nas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:22:28 by smuhamma          #+#    #+#             */
/*   Updated: 2023/08/10 19:11:49 by mbin-nas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_text(char *s)
{
	int		i;

	i = 0;
	while (ft_isalpha(s[i]))
		i++;
	while (s[i] != '.')
	{
		if (ft_isascii(s[i]) && s[i] != ' ' && s[i] != '\t')
			return (WRONG_INPUT);
		i++;
	}
	return (SUCCESS);
}

static int	check_text_path(t_info *info)
{
	if (check_text(info->data.n) == WRONG_INPUT)
		return (WRONG_INPUT);
	if (check_text(info->data.s) == WRONG_INPUT)
		return (WRONG_INPUT);
	if (check_text(info->data.w) == WRONG_INPUT)
		return (WRONG_INPUT);
	if (check_text(info->data.e) == WRONG_INPUT)
		return (WRONG_INPUT);
	if (check_text(info->data.sp) == WRONG_INPUT)
		return (WRONG_INPUT);
	return (SUCCESS);
}

int	get_start_path(char *s)
{
	int		i;

	i = 0;
	while (s[i] != '.')
		i++;
	return (i);
}

void	fn_free_path(char *s)
{
	free(s);
	s = NULL;
}

int	path_fix_textures2(t_info *info)
{
	int		i;

	if (check_text_path(info) == WRONG_INPUT)
		return (WRONG_INPUT);
	i = get_start_path(info->data.n);
	info->data.no = ft_strtrim(info->data.n + i, " ");
	if (!(info->data.no))
		return (MALLOC_FAIL);
	fn_free_path(info->data.n);
	i = get_start_path(info->data.s);
	info->data.so = ft_strtrim(info->data.s + i, " ");
	if (!(info->data.so))
		return (MALLOC_FAIL);
	fn_free_path(info->data.s);
	i = get_start_path(info->data.w);
	info->data.we = ft_strtrim(info->data.w + i, " ");
	if (!(info->data.we))
		return (MALLOC_FAIL);
	fn_free_path(info->data.w);
	return (SUCCESS);
}
