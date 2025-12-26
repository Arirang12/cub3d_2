#ifndef CUB_H
# define CUB_H

# include "mlx.h"
# include <X11/keysym.h>
# include <X11/X.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
# include <limits.h>
#include <stdio.h>
#include <math.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# if BUFFER_SIZE >= 2147483647
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif


# define KEY_RIGHT 65363
# define KEY_LEFT 65361
# define KEY_W 119
# define KEY_S 115
# define KEY_A 97
# define KEY_D 100
# define KEY_ESC 65307
//# define PI 3.14159265359
# define ROT_SPEED 0.03
# define MOVE_SPEED 0.02
//# define FOV 60
//# define WALL_HEIGHT 250
# define TILE_SIZE 100
#define WIDTH 1000
#define HEIGHT 1000
#define MAP_W 25
#define MAP_H 14
#define NO 0
#define SO 1
#define WE 2
#define EA 3

typedef struct s_box
{
	double	cameraX;
	double	rayDirX;
	double	rayDirY;
	int		mapX;
	int		mapY;
	double	deltaDistX;
	double	deltaDistY;
	int		stepX;
	int		stepY;
	double	sideDistX;
	double	sideDistY;
	int		hit;
	int		side;
	double	perpWallDist;
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
	double	wallX;
	double	step;
	double	texPos;
	int		color;
	int		texNum;
	int		texX;
	int		texY;
}			t_box;

typedef struct s_garbage_collector
{
	int							already_free;
	void						*ptr;
	struct s_garbage_collector	*next;
}								t_garbage_collector;

typedef struct s_keys
{
    int w;
    int a;
    int s;
    int d;
    int left;
    int right;
}   t_keys;

typedef struct s_color
{
    int flage;
    int r;
    int g;
    int b;
    int value;
} t_color;

typedef struct s_texture
{
    void *img;
char *addr;
int w;
int h;
int bpp;
int line_len;
int endian;
    int flag;
    char *path;
} t_texture;

typedef struct s_img {
    void    *mlx;
    void    *win;
    void    *img;
    char    *addr;
    int     bpp;
    int     line_len;
    int     endian;
}   t_img;

typedef struct s_player {
    double posX; // position in map
    double posY;
    double dirX; // direction vector
    double dirY;
    double planeX; // camera plane
    double planeY;
}   t_player;


typedef struct s_game
{
    t_img frame;
    char    **all_map;
    char    **map;
	int		length_map;
    int     map_start;
	int	position_player_x;
	int	position_player_y;
	int flag_pos;
	t_texture	textures[4];
  //  t_textur    north_texture;//chamal
  //  t_textur    south_texture;//janob
  //  t_textur    west_texture;//4arb
  //  t_textur    east_texture;//char9
    t_color    floor_color;//ardia
    t_color    ceiling_color;//sa9f
    t_player player;

     double	rot_speed;
    double	move_speed;
    t_keys	keys;
} t_game;

/////////////////hasna////////////////
int ft_handler (int keycode, t_game *g);
int key_move(t_game *g);
int     ft_moving(char direction, t_game *g);
int     ft_finish(t_game *g);
///this one below must be declared as static later !!
void    my_mlx_pixel_put(t_img *img, int x, int y, int color);
int raycaster(t_game *g);
int key_press(int keycode, t_game *g);
int key_release(int keycode, t_game *g);
//int     get_texture_addresses(t_cube *cube);
int     load_textures(t_game *game);
void	get_texture_color(t_game *g, t_box *box, int x, int y);
void	texture(t_game *g, t_box *box);
void	distance(t_game *g, t_box *box);

char	*strdup_map(char *s1, int len);
void print_error(char *msg);
int valid_number(char *line);
int    parse_color(t_color *color, char *s);
int close_window(void *param);
void    parse_cub_file(t_game *game);
void    read_map(t_game *game, char **av);
char	*get_next_line(int fd);
char	*ft_remember(char *remb);
char	*ft_get_line(char *remb);
char	*ft_read_buffer(char *remb, int fd);
char	*ft_strjoin(char *s1, char *s2);
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *s, size_t n);
int	ft_strncmp(char *s1, char *s2, size_t n);
char	*ft_strdup(char *s1);
int ft_strlen(char *s1);
int	ft_atoi(char *str);
char	*ft_strtrim(char *s1, char *set);
char	*ft_substr(char *s, int start, int len);
void	*ft_free(char **a, int j);
char	**ft_split(char *s, char c);
t_garbage_collector	**gc_instance(void);
void	is_already_free(t_garbage_collector **gc, void *ptr);
void	free_all(t_garbage_collector **lst);
void	gc_add_node_back(t_garbage_collector **lst, t_garbage_collector *new);
t_garbage_collector	*gc_last_node(t_garbage_collector *lst);
t_garbage_collector	*gc_new_node(void *ptr);

#endif
