/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuhamma <smuhamma@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 21:18:16 by nhill             #+#    #+#             */
/*   Updated: 2023/08/10 20:48:30 by smuhamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "keycode.h"
# include "libft/libft.h"
# include "minilibx_opengl/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# define MAX_WIDTH 2560
# define MAX_HEIGHT 1440
# define FILE_HEADER_SIZE 14
# define IMG_HEADER_SIZE 40
# define BYTES_PER_PIX 3
# define COMPRESSION 24
# define SCREEN_PATH "screen.bmp"
# define RIGHTS 0644
// # define BUFFER_SIZE 1
# define PINK 9961608
# define BLACK 000000

typedef struct s_rgb
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	a;
}					t_rgb;

typedef union u_colour
{
	unsigned int	all;
	char			tab[4];
	t_rgb			rgb;
}					t_colour;

typedef enum e_error
{
	SUCCESS,
	INVALID_ARG,
	WRONG_MAP,
	WRONG_INPUT,
	MALLOC_FAIL,
	IMG_FAIL,
	OPEN_ERR,
	MLX_FAIL,
	WRITE_FAIL,
	WRONG_TEXTURE
}					t_error;

typedef struct s_pos
{
	double			x;
	double			y;
}					t_pos;

typedef struct s_pos_i
{
	int				x;
	int				y;
	int				id;
}					t_pos_i;

typedef struct s_map
{
	char			**tab_map;
	t_list			*list;
	int				kol_line;
	int				place_char;
	char			player;
	int				flag_n;
	int				k_total;
}					t_map;

typedef struct s_img
{
	void			*img_ptr;
	int				*img_data;
	int				bpp;
	int				size_line;
	int				endian;
	int				width;
	int				height;
}					t_img;

typedef struct s_data
{
	char			*r;
	char			*no;
	char			*n;
	char			*so;
	char			*s;
	char			*we;
	char			*w;
	char			*ea;
	char			*e;
	char			*spr;
	char			*sp;
	char			*f;
	char			*c;
}					t_data;

typedef struct s_textur
{
	void			*textur_ptr;
	int				*textur_data;
	int				bpp;
	int				size_line;
	int				endian;
	int				width;
	int				height;
}					t_textur;

typedef struct s_sprite
{
	double			pos_x;
	double			pos_y;
}					t_sprite;

typedef struct s_spdata
{
	double			sp_dist;
	double			spcamx;
	double			spcamy;
	double			transx;
	double			transy;
	int				spritescreenx;
	int				sprite_height;
	int				drawstart_y;
	int				drawend_y;
	int				sprite_width;
	int				drawstart_x;
	int				drawend_x;
	int				stripe;
	int				sp_x;
	int				sp_y;
}					t_spdata;

typedef struct s_move
{
	int				up;
	int				down;
	int				left;
	int				right;
	int				move_left;
	int				move_right;
}					t_move;

typedef struct s_rc
{
	t_pos			plane;
	t_pos			step;
	t_pos			dir;
	t_pos_i			textur;
	t_pos			rpos;
	t_pos			rdir;
	t_pos			rdisd;
	t_pos			rdist;
	t_pos_i			rmap;
	int				wall;
	int				wstart;
	int				wend;
	double			camera;
	int				hit;
	double			rh;
	double			step_textur;
	double			textur_pos;
	double			dist;
	double			speed;
	double			*zbuffer;
	int				*sp_order;
	double			*sp_distance;

}					t_rc;

typedef struct s_save
{
	int				height;
	int				width;
	unsigned char	*file_header;
	unsigned char	*img_header;
	int				fd;
	int				pad;
}					t_save;

typedef struct s_info
{
	void			*mlx_ptr;
	void			*win_ptr;
	double			width;
	double			height;
	int				flag_save;
	int				kol_sprite;
	t_map			map;
	t_img			*img;
	t_pos			pos;
	t_data			data;
	t_move			move;
	t_colour		colour_floor;
	t_colour		colour_ceiling;
	t_spdata		sp;
	t_sprite		*tab_sprite;
	t_textur		*textur1;
	t_textur		*textur2;
	t_textur		*textur3;
	t_textur		*textur4;
	t_textur		*sprite;
	unsigned int	colour;
	t_rc			raycast;
	int				error;
}					t_info;

int					get_next_line_new(int fd, char **line, int bytes);
int					tab_size(char **tab);
char				*ft_strdup_without_space(const char *s);
t_img				*fn_new_image(t_info *info, int width, int height);
t_textur			*fn_new_textur(t_info *info, char *file);
int					init_sprite(t_info *info);
int					launch_save(t_info *info);
int					get_map(t_info *info, char *file, int *i);
int					deal_exit(t_info *info);
int					re_errors(int error, t_info *info);
void				wall_textur(t_info *info);
void				size_ray(t_info *info);
void				hit_ray(t_info *info);
void				direction_ray(t_info *info);
void				init_raycast(t_info *info, int x);
int					init_info_pos(t_info *info);
int					path_fix_textures(t_info *info);
int					parse_map(t_info *info);
int					init_var(t_info *info, char *s);
int					init_save(t_info *info, int argc, char *s);
int					write_headers(t_save *save);
unsigned char		*create_img_header(int height, int width);
unsigned char		*create_file_header(t_info *info, int pad);
int					get_colour(t_colour *colour, char *s);
void				pixel_colour(t_info *info);
int					look_for_alpha(char *s, int i);
int					check_data(t_info *info);
void				add_sprite(t_info *info);
int					fn_display_screen(t_info *info);
int					get_data(t_info *info, char *line, int i, int *flag_map);
void				free_tab(t_info *info);
void				ft_tabdel(void **tab);
void				free_textur(t_info *info, t_textur *textur);
void				free_img(t_info *info);
int					path_fix_textures2(t_info *info);
int					get_start_path(char *s);
void				player_move(t_info *info);
int					events(t_info *info);
void				put_pixel(t_img *img, unsigned int colour, int p_x,
						int p_y);
void				fn_free_path(char *s);
void				if_and_elseforest(t_info *info);
int					closed_map(t_info *info);
int					init_var2(t_info *info, char *s);
int					my_check_rc(t_info *info);
int					check_resolut(t_info *info, char ***tab);
void				check_resolut2(t_info *info);
void				get_resolut2(char **tab, t_info *info);
void				ft_info_map_val(t_info *info, int i);

#endif
