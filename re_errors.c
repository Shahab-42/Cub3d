/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbin-nas <mbin-nas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:22:52 by smuhamma          #+#    #+#             */
/*   Updated: 2023/08/10 19:42:54 by mbin-nas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	deal_exit(t_info *info)
{
	free_tab(info);
	free_img(info);
	free_textur(info, info->textur1);
	free_textur(info, info->textur2);
	free_textur(info, info->textur3);
	free_textur(info, info->textur4);
	free_textur(info, info->sprite);
	if (info->win_ptr)
		mlx_destroy_window(info->mlx_ptr, info->win_ptr);
	if (info->mlx_ptr)
		free(info->mlx_ptr);
	exit(0);
}

int	re_errors(int error, t_info *info)
{
	if (error == INVALID_ARG)
		perror("Error\nInvalid argument passed to cub3d");
	if (error == WRONG_INPUT)
		perror("Error\nInvalid resolution or colour passed to cub3d");
	if (error == WRONG_MAP)
		perror("Error\nInvalid map for cub3d");
	if (error == MALLOC_FAIL)
		perror("Error\nMemory allocation fail");
	if (error == OPEN_ERR)
		perror("Error\nFile could not be opened");
	if (error == IMG_FAIL)
		perror("Error\nImage could not be allocated");
	if (error == MLX_FAIL)
		perror("Error\nMlx fail");
	if (error == WRITE_FAIL)
		perror("Error\nCould not write to object");
	if (error == WRONG_TEXTURE)
		perror("Error\nWrong path for texture");
	deal_exit(info);
	return (error);
}

int	check_resolut(t_info *info, char ***tab)
{
	int	i;

	i = 0;
	while (!ft_isdigit(info->data.r[i]))
	{
		if (info->data.r[i] == '-')
			return (WRONG_INPUT);
		i++;
	}
	info->error = look_for_alpha(info->data.r, i);
	if (info->error != SUCCESS)
		return (info->error);
	*tab = ft_split(info->data.r + i, ' ');
	if (!(*tab))
		return (MALLOC_FAIL);
	return (SUCCESS);
}

void	check_resolut2(t_info *info)
{
	if (info->width > MAX_WIDTH)
		info->width = MAX_WIDTH;
	if (info->height > MAX_HEIGHT)
		info->height = MAX_HEIGHT;
}
