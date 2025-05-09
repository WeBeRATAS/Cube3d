/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 09:17:43 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/04/16 13:26:15 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../inc/libft/libft.h"
# include "../inc/minilibx/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <math.h>
# include <string.h>
# include <errno.h>

    /* --- Constantes --- */
# define WIN_TITLE "Cub3D"
# define MOVE_SPEED 0.1
# define COLLISION_MARGIN 0.1 // Evita quedarse pegado
# define SUCCESS 1
# define ERROR 0

/* COLORS */
# define RESET	"\e[0m"
# define BLACK	"\e[30m"
# define RED	"\e[31m"
# define GREEN	"\e[32m"
# define YELLOW	"\e[33m"
# define BLUE	"\e[34m"
# define PURPLE	"\e[35m"
# define CYAN	"\e[36m"
# define WHITE	"\e[37m"

  /* --- Estructuras --- */
typedef struct s_texture
{
	void    *img_ptr;
	char    *addr;
	int     bits_per_pixel;
	int     line_length;
	int     endian;
	int     width;
	int     height;
	char    *path; // Guardar la ruta original de texturas
} t_texture;

typedef struct s_color
{
	int r;
	int g;
	int b;
	int combined; // Color combinado para mlx (ej: 0xRRGGBB)
	int is_set;   // Flag para saber si ya se parseó
} t_color;

typedef struct s_map
{
	char    **grid;
	int     width;
	int     height;
} t_map;

typedef struct s_list
{
    void			*content;
    struct s_list	*next;
} t_list;

typedef struct s_player
{
	double  pos_x;
	double  pos_y;
	double  dir_x; // Vector de dirección
	double  dir_y;
	double  plane_x; // Plano de la cámara (perpendicular a dir)
	double  plane_y;
	char    start_direction; // 'N', 'S', 'E', 'W'
	int     found; // Flag para asegurar que solo hay un jugador
} t_player;

typedef struct s_config
{
	int         win_width;
	int         win_height;
	int         res_set; // Flag para saber si la resolución se parseo
	t_texture   north_tex;
	t_texture   south_tex;
	t_texture   west_tex;
	t_texture   east_tex;
	t_color     floor_color;
	t_color     ceiling_color;
	t_map       map;
	t_player    player;
	int         elements_found; // Bitmask o contador para elementos obligatorios
} t_config;

typedef struct s_mlx_vars
{
	void        *mlx_ptr;
	void        *win_ptr;
	void        *img_ptr; // Buffer de imagen para dibujar
	char        *addr;    // Dirección del buffer
	int         bits_per_pixel;
	int         line_length;
	int         endian;
	t_config    config; // Contiene toda la configuración parseada
} t_mlx_vars;

/* PARSING*/
int		parser_scene(char **av, t_mlx_vars *vars);
int		parse_scene_file(char *filename, t_config *config);
int		add_map_line(char *line, t_list **map_list);
int		is_map_line(char *line, char **tokens);

/* VALIDATE*/
void	validate_scene_elements(t_config *config);
void	process_map_data(t_list **map_list, t_config *config);
void	transfer_config_to_vars(t_config *config, t_mlx_vars *vars);

/* UTILS*/
void	exit_error(char *message, char *details, t_mlx_vars *vars);
void	free_config(t_config *config);
int		ft_lstsize(t_list *lst);
void	ft_lstclear(t_list **lst, void (*del)(void *));
t_list	*ft_lstnew(void *content);
void	ft_lstadd_back(t_list **lst, t_list *new);
int		is_config_identifier(char *token);
int		is_empty_line(char *line);
void	free_split(char **tokens);





#endif
