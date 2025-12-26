#include "cub.h"

static int check_name(char *av, char *p)
{
	int i;

	i = 0;
	while (av[i])
	{
		if (ft_strncmp(&av[i], p, 4) == 0)
		{
			if (i == 0)
				break;
			if (!av[i + 4])
				return (0);
			else
				break;
		}
		i++;
	}
	return (1);
}

void error_textur(char *msg, char *s)
{
    write(2, "Error\n", 6);
    write(2, msg, ft_strlen(msg));
	write(2, " : ", 3);
	write(2, s, ft_strlen(s));
    write(2, "\n", 1);
	free_all(gc_instance());
    exit(1);
}

static int whitespace(char c)
{
    return (c == '\t' || c == ' ');
}
void print_error(char *msg)
{
    free_all(gc_instance());
    write(2, "Error\n", 6);
    write(2, msg, ft_strlen(msg));
    write(2, "\n", 1);
    exit(1);
}
static int  valide_elem(char c)
{
    if (c == '0' || c == 'N' || c == 'S' || c == 'W'
		|| c == 'E' || c == '1' || c == ' ' || c == '\t' || c == '\0')
        return (1);
    return (0);
}
void pos_player(t_game *game, int x, int y)
{
	if (game->flag_pos)
		print_error("Duplicate player");
	game->flag_pos = 1;
	game->position_player_x = x;
	game->position_player_y = y;
	printf("x[%d],y[%d]\n", game->position_player_x, game->position_player_y);//
}

int check_player(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	return (0);
}

int clcul_long(t_game *game, char **map)
{
	int lng;
	int	len;
	int j;
	
	len = 0;
	lng = ft_strlen(map[0]);
	while (map[len])
	{
		j = 0;
		while (map[len][j])
		{
			if (check_player(map[len][j]))
				pos_player(game, len, j);
			if (!valide_elem(map[len][j]))
				print_error("invalide element !");
			j++;
		}
		if (lng < ft_strlen(map[len]))
			lng = ft_strlen(map[len]);
		len++;
	}
	if (!game->flag_pos)
		print_error("NO player");
	game->length_map = len;
	return (lng);
}
void alloc_map(t_game *game, int len, int lng)
{
	int i;

	i = 0;
	game->map = malloc(sizeof(char *) * (len + 1));
	if (!game->map)
		print_error("malloc failed");
	gc_add_node_back(gc_instance(), gc_new_node(game->map));
	while (i < len)
		game->map[i++] = strdup_map(game->all_map[game->map_start++], lng);
	game->map[i] = NULL;

}
static void full_map(t_game *game)
{
    int i;
    int start;
	int lng;
    
    start = game->map_start;
	lng = clcul_long(game, &game->all_map[start]);
    while (game->length_map > 0)
    {
        i = 0;
        while (whitespace(game->all_map[start + game->length_map - 1][i]))
            i++;
        if (game->all_map[start + game->length_map - 1][i] != '\0')
            break;
        game->length_map--;
    }
	alloc_map(game, game->length_map, lng);
}

static int is_allowed (char c)
{
    if (c == '0' || c == 'N' || c == 'S' || c == 'W' || c == 'E')
        return (1);
    return (0);
}

static int is_invalid(char c)
{
    return (c == '\t' || c == ' ' || c == '\0');
}
int close_up_down(char *map)
{
    int i;

    i = 0;
    while(map[i])
    {
        if (is_allowed (map[i]))
            return (1);
        i++;
    }
    return (0);
}

int close_left(char **map)
{
    int i;
    int j;

    i = 1;
    while (map[i])
    {
        j = 0;
        if (map[i][0] == '\0')
            return (2);
        if (whitespace(map[i][j]))
        {
            while (whitespace(map[i][j]))
                j++;
			if (map[i][j] == '\0')
				return (2);
        }
        if (is_allowed(map[i][j]))
            return (1);
        i++;
    }
    return (0);
}
int close_right(char **map)
{
    int i;
    int j;

    i = 1;
    while (map[i])
    {
        j = ft_strlen(map[i]) - 1;
        if (whitespace(map[i][j]))
        { 
            while (whitespace(map[i][j]) && j > 0)
                j--;
        }
            if (is_allowed(map[i][j]))
                return(1);
        i++;
        
    }
    return (0);
}
int valid_way(char **map)
{
    int i;
    int j;

    i = 1;
    while (map[i + 1])
    {
        j = 1;
        while (map[i][j + 1])
        {
            if (is_allowed(map[i][j]))
            {      
                if (is_invalid(map[i][j-1]) || is_invalid(map[i][j+1])
                    || (is_invalid(map[i-1][j]) || is_invalid(map[i+1][j])))
                    return (1);
            }
            j++;
        }
        i++;
    }
    return (0);
}

static void is_map_last(t_game *game, int i)
{
    if(!game->textures[NO].flag || !game->textures[SO].flag 
        || !game->textures[WE].flag || !game->textures[EA].flag 
        || !game->floor_color.flage || !game->ceiling_color.flage)
    {
        print_error("Invalid file structure");
    }
    game->map_start = i;
}
int valid_number(char *line)
{
    int nmb;

    nmb = ft_atoi(line);
    if (nmb < 0 || nmb > 255)
        print_error("Color out of range");
    return (nmb);
}
int is_num(char *str)
{
    int i;
    char *s;
    
    s = ft_strtrim(str, " \t");
	if (!s[0])
		print_error("Invalid color format");
    i = 0;
    while (s[i])
    {
        if (s[i] < '0' || s[i] > '9')
            return (0);
        i++;
    }
    return (1);
}
int    parse_color(t_color *color, char *s)
{
    char **line;
    int i;

	if (!s || !s[0])
		print_error("Invalid color");
    i = 0;
	if (color->flage)
        print_error("Duplicate color");
    color->flage = 1;
    line = ft_split(s, ',');
    if (!line || !line[0]|| !line[1] || !line[2] || line[3]
		|| !line[0][0] || !line[1][0] || !line[2][0])
        print_error("Invalid color format");
    while (line[i])
    {
        if (!is_num(line[i]))
            print_error("Invalid color");
        i++;
    }
    color->r = valid_number(line[0]);
    color->g = valid_number(line[1]);
    color->b = valid_number(line[2]);
    color->value = (color->r << 16) | (color->g << 8) | color->b;
    return (1);
}
int check_texture_path(char *path)
{
    int fd;


    fd = open(path, O_RDONLY);
    if (fd == -1)
        return (1);
    close(fd);
    return (0);
}

void parse_textur(t_game *g, t_texture *t, char *map)
{
	(void)g;
    char *s;

	if (t->flag)
		print_error("Duplicate textur");
	t->flag = 1;
	if (!map || !map[0])
		print_error("Invalid textur format");
    s = ft_strtrim(map, " \t");
	if (!s[0])
		print_error("Invalid textur format");
	if (check_name(s, ".xpm"))
		print_error("Invalid textur name");
	
	if (check_texture_path(s))
    	error_textur("Invalid texture path", s);
    t->path = s;
    // //////////////////////////
    //  t->img = mlx_xpm_file_to_image(g->frame.mlx, (char *)t->path,
	// 	   &t->w, &t->h);
    // if (!t->img)
    // {
    //         printf("no texture found\n");
    //     t->flag = 0;
    //     return;
    // }
    // t->addr = mlx_get_data_addr(t->img,
    //     &t->bpp,
    //     &t->line_len,
    //     &t->endian);
	
    ///////////////////////////
    printf("main:320:t->path=\"%s\"\n", s);
}
int texture_color(t_game *game, char *m, char c, int i)
{
    if (ft_strncmp(m, "NO ", 3) == 0)
        parse_textur(game, &game->textures[NO], m + 3);
    else if (ft_strncmp(m, "SO ", 3) == 0)
        parse_textur(game, &game->textures[SO], m + 3);
    else if (ft_strncmp(m, "WE ", 3) == 0)
        parse_textur(game, &game->textures[WE], m + 3);
    else if (ft_strncmp(m, "EA ", 3) == 0)
        parse_textur(game, &game->textures[EA], m + 3);
    else if (ft_strncmp(m, "F ", 2) == 0)
        parse_color(&game->floor_color, m + 2);
    else if (ft_strncmp(m, "C ", 2) == 0)
        parse_color(&game->ceiling_color, m + 2);
    else if (c == '0' || c == '1')
        return (is_map_last(game, i), 0);
    else if (c != '\0')
        print_error("Unknown element");
    return (1);
}

static int  check_parse_file(t_game *game)
{
    int i;
    int j ;
    char c;

    i = 0;
    while (game->all_map[i])
    {
        j = 0;
        while (whitespace(game->all_map[i][j]))
            j++;
        c = game->all_map[i][j];
        if (!texture_color(game, &game->all_map[i][j], c, i))
            return (0);
        i++;
    }
    return (1);
}

void parse_cub_file(t_game *game)
{
    int len;
    int left;
    
    len = 0;
    if (check_parse_file(game))
        print_error("Invalid file structure");
    full_map(game);
    while (game->map[len])
        len++;
    left = close_left(game->map);
    if (left == 2)
        print_error("Invalid map : empty line");
    if (close_up_down(game->map[0]) || close_up_down(game->map[len - 1])
        || (left == 1) || close_right(game->map))
        print_error("Map is not closed");
    
    if (valid_way(game->map))
        print_error("Invalid map");
}

void    read_map(t_game *game, char **av)
{
    char *line;
    char *join;
    int fd;

    fd = open(av[1], O_RDONLY);
    if (fd < 0)
        print_error("Cannot open file");
    join = NULL;
    line = get_next_line(fd);
    while (line)
    {
        join = ft_strjoin(join, line);
        line = get_next_line(fd);
    }
    game->all_map = ft_split(join, '\n');
    if (!game->all_map)
        print_error("Empty file");
    parse_cub_file(game);
}
 
static void init(t_game *game)
{
	game->flag_pos = 0;
	game->textures[NO].path = NULL;
	game->textures[NO].flag = 0;
	game->textures[SO].path = NULL;
	game->textures[SO].flag = 0;
	game->textures[WE].path = NULL;
	game->textures[WE].flag = 0;
	game->textures[EA].path = NULL;
	game->textures[EA].flag = 0;
	game->floor_color.flage = 0;
	game->ceiling_color.flage = 0;
}
static void parse_cub(t_game *game, int ac, char **av)
{
	if (ac > 2 || ac < 2)
		print_error("Invalid arguments");
	if (check_name(av[1], ".cub"))
		print_error("hasna Invalid file extension");
	init(game);
	read_map(game, av);
}
static void     init_player(t_game *game, char **map)
{
        int     y = 0;
        int x = 0;
        while (map[y])
        {
                int x = 0;
                while (map[y][x])
                {
                    printf("%c", map[y][x]);
                    if (map[y][x] != '0' 
                        &&  map[y][x] != '1' && map[y][x] != ' ')
                        printf("diffrent [%c]\n", map[y][x]);
                    x++;
                }
                printf("\n");
                y++;
        }
        printf("Done ! ---------------\n");
        y = 0;
        while (map[y])
        {
                x = 0;
                while (map[y][x])
                {
                        char c = map[y][x];
                        if (map[y][x] == '\r')
                                map[y][x] = '\0';
                        printf("%c ", map[y][x]);
                        //printf("the player is at pos[%c] y[%d] x[%d]\n", map[y][x], y, x);
                        if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
                        {
                                game->player.posX = x + 0.5;
                                game->player.posY = y + 0.5;
                                map[y][x] = '0';
                                if (c == 'N')
                                {
                                        game->player.dirX = 0;
                                        game->player.dirY = -1;
                                        game->player.planeX = 0.66;
                                        game->player.planeY = 0;
                                }
                                else if (c == 'S')
                                {
                                        game->player.dirX = 0;
                                        game->player.dirY = 1;
                                        game->player.planeX = -0.66;
                                        game->player.planeY = 0;
                                }
                                else if (c == 'E')
                                {
                                        game->player.dirX = 1;
                                        game->player.dirY = 0;
                                        game->player.planeX = 0;
                                        game->player.planeY = 0.66;
                                }
                                else if (c == 'W')
                                {
                                        game->player.dirX = -1;
                                        game->player.dirY = 0;
                                        game->player.planeX = 0;
                                        game->player.planeY = -0.66;
                                }
                                return ;
                        }
                        x++;
                }
                printf("\n");
                y++;
        }
}

int game_loop(t_game *g)
{
//      printf("the player is at pos[%c] y[%f] x[%f]\n", g->map[(int)(g->player.posY)][(int)(g->player.posX)], g->player.posY, g->player.posX);
    key_move(g);              // reacts to pressed keys
   // clear_image(&g->frame);      // erase previous frame
    raycaster(g);                // redraw scene
    return 0;
}


void    my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
    *(unsigned int*)dst = color;
}

int main (int ac, char **av) 
{
	t_game g;
ac = 2;
av[0] = "./cub";
av[1] = "maps/l7al.cub";

	parse_cub(&g, ac, av);
    ft_bzero(&g.keys, sizeof(t_keys));
    // read_map(&g, av);
    init_player(&g, g.map);
    printf("posX= %f\nposY= %f\ndirX= %f\ndirY= %f\nplaneX= %f\nplaneY= %f\n", g.player.posX, g.player.posY, g.player.dirX, g.player.dirY, g.player.planeX, g.player.planeY);

g.frame.mlx = mlx_init();
    g.frame.win = mlx_new_window(g.frame.mlx, WIDTH, HEIGHT, "cub3d");
    g.frame.img = mlx_new_image(g.frame.mlx, WIDTH, HEIGHT);
    g.frame.addr = mlx_get_data_addr(g.frame.img, &g.frame.bpp, &g.frame.line_len, &g.frame.endian);
//ROT_SPEED 0.02
//# define MOVE_SPEED 6
        g.rot_speed = ROT_SPEED;
        g.move_speed = MOVE_SPEED;
     printf("the player is at pos[%c] y[%f] x[%f]\n", g.map[(int)(g.player.posY)][(int)(g.player.posX)], g.player.posY, g.player.posX);
   load_textures(&g);
     mlx_loop_hook(g.frame.mlx, game_loop, &g);
mlx_hook(g.frame.win, KeyPress, KeyPressMask, key_press, &g);
mlx_hook(g.frame.win, KeyRelease, KeyReleaseMask, key_release, &g);
mlx_hook(g.frame.win, 17, 0, ft_finish, &g);
mlx_loop(g.frame.mlx);
	free_all(gc_instance());
	return (0);
}
