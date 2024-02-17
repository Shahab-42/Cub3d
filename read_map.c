/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuhamma <smuhamma@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:22:58 by smuhamma          #+#    #+#             */
/*   Updated: 2023/08/10 20:48:03 by smuhamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	add_to_list_map(t_info *info, char *line, int *i, t_list *tmp)
{
	tmp->content = ft_strdup(line + *i);
	if (!tmp->content)
		return (MALLOC_FAIL);
	tmp->next = 0;
	ft_lstadd_back(&info->map.list, tmp);
	return (SUCCESS);
}

static int	stock_data(char *line, t_info *info, int *i, int *flag_map)
{
	t_list	*tmp;

	if (ft_isalpha(line[*i]))
	{
		info->error = get_data(info, line, *i, flag_map);
		if (info->error != SUCCESS)
			return (info->error);
	}
	else if (ft_isdigit(line[*i]))
	{
		(*flag_map)++;
		*i = 0;
		tmp = malloc(sizeof(t_list));
		if (!tmp)
			return (MALLOC_FAIL);
		info->error = add_to_list_map(info, line, i, tmp);
		if (info->error != SUCCESS)
			return (info->error);
	}
	return (SUCCESS);
}

static	int	info_error(t_info *info, char *line)
{
	if (info->error != SUCCESS)
	{
		free(line);
		return (info->error);
	}
	return (info->error);
}

static int	fn_read(t_info *info, int fd)
{
	char	*line;
	int		i[3];

	i[1] = 1;
	i[2] = 0;
	while (i[1] != 0)
	{
		i[1] = get_next_line_new(fd, &line, 1);
		i[0] = 0;
		while ((line[i[0]] == ' ' || line[i[0]] == '\t') && line[i[0]])
			i[0]++;
		info->error = stock_data(line, info, &i[0], &i[2]);
		if (info_error(info, line) != SUCCESS)
			return (info->error);
		free(line);
	}
	info->error = check_data(info);
	if (info->error != SUCCESS)
		return (info->error);
	info->error = path_fix_textures(info);
	if (info->error != SUCCESS)
		return (info->error);
	return (SUCCESS);
}

int	get_map(t_info *info, char *file, int *i)
{
	t_list	*tmp;

	i[1] = open(file, O_RDONLY);
	if (i[1] < 0)
		return (OPEN_ERR);
	info->error = fn_read(info, i[1]);
	if (info->error != SUCCESS)
		return (info->error);
	close(i[1]);
	info->map.tab_map = (char **)malloc(sizeof(char *)
			* ft_lstsize(info->map.list) + 1);
	if (!info->map.tab_map)
		return (MALLOC_FAIL);
	i[0] = 0;
	tmp = info->map.list;
	while (tmp)
	{
		info->map.tab_map[i[0]] = ft_strdup(tmp->content);
		if (!info->map.tab_map[i[0]])
			return (MALLOC_FAIL);
		tmp = tmp->next;
		i[0]++;
	}
	ft_info_map_val(info, i[0]);
	return (SUCCESS);
}
