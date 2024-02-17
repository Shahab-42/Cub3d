/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuhamma <smuhamma@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:23:09 by smuhamma          #+#    #+#             */
/*   Updated: 2023/08/10 19:55:56 by smuhamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	write_colours(t_info *info, int fd, int height, int width)
{
	static unsigned char	rgb[3] = {0, 0, 0};
	int						i;
	int						j;

	i = 0;
	while (i < (int)info->height)
	{
		j = 0;
		while (j < (int)info->width)
		{
			rgb[0] = ((info->img->img_data[(height - i) * width + j]) >> 16);
			rgb[1] = ((info->img->img_data[(height - i) * width + j]) >> 8);
			rgb[2] = (info->img->img_data[(height - i) * width + j]);
			if ((write(fd, rgb + 2, 1)) < 0)
				return (WRITE_FAIL);
			if ((write(fd, rgb + 1, 1)) < 0)
				return (WRITE_FAIL);
			if ((write(fd, rgb, 1)) < 0)
				return (WRITE_FAIL);
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

static int	fn_save(t_info *info)
{
	t_save	save;

	save.height = info->height - 1;
	save.width = info->width;
	save.pad = (4 - ((int)info->width * 3) % 4) % 4;
	save.file_header = create_file_header(info, save.pad);
	save.img_header = create_img_header(save.height, save.width);
	save.fd = open(SCREEN_PATH, O_WRONLY | O_CREAT, RIGHTS);
	if (save.fd < 0)
		return (OPEN_ERR);
	info->error = write_headers(&save);
	if (info->error != SUCCESS)
		return (info->error);
	info->error = write_colours(info, save.fd, save.height, save.width);
	if (info->error != SUCCESS)
	{
		close(save.fd);
		return (info->error);
	}
	close(save.fd);
	return (SUCCESS);
}

int	launch_save(t_info *info)
{
	if (fn_display_screen(info) != SUCCESS)
		return (info->error);
	info->error = fn_save(info);
	if (info->error != SUCCESS)
		return (info->error);
	deal_exit(info);
	return (SUCCESS);
}
