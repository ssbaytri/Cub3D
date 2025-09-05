CC = cc  
flags = -Wall -Wextra -Werror -O3  #-fsanitize=address -g
lib = mlx/build/libglfw3.a mlx/build/libmlx42.a -framework Cocoa -framework OpenGL -framework IOKit
NAME = cub3D
src = $(shell find . -name "*.c")
obj = $(src:.c=.o)



all: $(NAME)


$(NAME): $(obj)
	
	
	@echo "\033[0;32mCompiling...\033[0m"
	@make -C libft
	@$(CC) $(flags) $(obj) -o $(NAME) $(lib) ./libft/libft.a
	@echo "\033[0;32mCompilation successful! ✅\033[0m"

%.o: %.c cub.h
	@$(CC) $(flags) -c $< -o $@

clean:
	@echo "\033[0;32mCleaning objects...\033[0m"
	@rm -rf $(obj)
	@make -C libft clean
	@echo "\033[0;32mCleaning objects successful! ✅\033[0m"

fclean: clean
	@echo "\033[0;32mCleaning executable...\033[0m"
	@rm -rf $(NAME)
	@make -C libft fclean
	@echo "\033[0;32mCleaning executable successful! ✅\033[0m"

re: fclean all
42: all clean ; clear

.PHONY: all clean fclean