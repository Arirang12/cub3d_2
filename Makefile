CC = cc

NAME = cub
# BNAME = so_long_bonus
CFLAGS = -Wall -Wextra -Werror -g

MLXF = -Lminilibx-linux -lmlx_Linux -lX11 -lXext -lm

SRC = src/main.c src/z_omaima/get_next_line.c  src/z_omaima/ft_splite.c \
		src/z_omaima/read_map_utils.c src/z_omaima/garbage_collector.c \
		src/z_hasna/key_press.c src/z_hasna/raycaster.c \
		src/z_hasna/texturing.c src/z_hasna/raycaster_utils.c \
		src/z_hasna/key_press_utils.c
# CSRC = so_long_free.c so_long_check_map.c so_long_line_map.c ft_splite.c so_long_utils.c so_long_utils1.c get_next_line.c
# BSRC = bonus/so_long_bonus_event.c  bonus/so_long_bonus_map.c  bonus/so_long_main_bonus.c  bonus/so_long_minilibx_bonus.c

OBJ = $(SRC:.c=.o)
# COBJ = $(CSRC:.c=.o)
# BOBJ = $(BSRC:.c=.o)
# $(CC) $(CFLAGS) $(OBJ) $(COBJ) $(MLXF) -o $(NAME) $(COBJ)
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(MLXF)  -o $(NAME)
	echo "ALL IS GOOD :/\:"

# bonus: $(BNAME)

# $(BNAME): $(BOBJ) $(COBJ)
# 	$(CC) $(CFLAGS) $(BOBJ) $(COBJ) $(MLXF) -o $(BNAME)
# 	echo "tmika l bonus"

clean:
	rm -f $(OBJ)

# 	rm -f $(OBJ) $(BOBJ) $(COBJ)

fclean: clean
	rm -f $(NAME) 

# 	rm -f $(NAME) $(BNAME) 

re: fclean all
# ree: fclean bonus

.PHONY: all bonus clean fclean re ree
