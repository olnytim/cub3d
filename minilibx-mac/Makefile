#
#

NOM	=	libmlx.a
SRC	=	mlx_shaders.c mlx_new_window.m mlx_init_loop.m \
		mlx_new_image.m mlx_xpm.c mlx_int_str_to_wordtab.c \
		mlx_png.c mlx_mouse.m
#
OBJ	=	$(patsubst %.c, %.o, $(patsubst %.m, %.o, $(SRC)))
CFLAGS	+=	-O2

# add to match string put with X11 in size and position
# CFLAGS	+=	-DSTRINGPUTX11
CFLAGS	+=	-DGL_SILENCE_DEPRECATION

all:	$(NOM)
	@echo > /dev/null

$(NOM):	$(OBJ)
	@ar rcs $(NOM) $(OBJ)
	@ranlib $(NOM)

clean:
	@rm -f $(NOM) $(OBJ) *~
	@rm -f mlx_app

re: clean all
