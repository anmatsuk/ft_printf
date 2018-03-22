NAME = libftprintf.a
FILES = ft_char.c \
		ft_integer.c \
		ft_printf.c \
		ft_helper.c \
		ft_string.c \
		utils.c \
		ft_unsigned_integer.c \
		ft_octal.c \
		ft_p.c \
		conversation_utils.c
OBJECTS = $(FILES:%.c=%.o)
HDR = ft_printf.h
LIBFT = ./libft/libft.a

.PHONY: all clean fclean re

all: $(NAME)

$(LIBFT):
	@make -C ./libft

$(NAME): $(LIBFT)
	@gcc -Wall -Wextra -Werror -c $(FILES) -I./libft
	@cp $(LIBFT) $(NAME)
	@ar rc $(NAME) $(OBJECTS)
	@ranlib $(NAME)
clean:
	@/bin/rm -f $(OBJECTS)
	@make clean -C ./libft

fclean:
	@/bin/rm -f $(OBJECTS)
	@/bin/rm -f $(NAME)
	@make fclean -C ./libft

test:
	gcc main.c $(LIBFT) -I./libft $(FILES)


re: fclean all 

