# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/01/16 16:45:04 by rcargou           #+#    #+#              #
#    Updated: 2015/01/17 15:44:15 by rcargou          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rtv1

SRC = get_light.c main.c objects_init.c parsing.c plan_functions.c raytracer.c rt_mlx.c \
	  sphere_functions.c trente/trente.c snailfills.c anti_aliasing.c reflexion.c

HEADERS = object.h rtv1.h rc_lib/rc_math/rc_math.h rc_lib/libft/libft.h trente/trente.h \
		  rc_lib/rc_color/color.h mlx.h

LIB = rc_lib/libft/libft.a rc_lib/rc_math/librcmath.a rc_lib/rc_color/libcolor.a -lm \
	  -L./ libmlx_x86_64.a -lX11 -lXext -lm

All : $(NAME)

$(NAME) :
	@echo "Compiling libft..."
	@make re -C rc_lib/libft
	@echo "Success !"
	@echo "Compiling rc_math..."
	@make re -C rc_lib/rc_math
	@echo "Sucess !"
	@echo "Compiling rc_color..."
	@make re -C rc_lib/rc_color
	@echo "Sucess !"
	@echo "Compiling rtv1..."
	@gcc -o $(NAME) $(SRC) $(HEADERS) $(LIB)
	@echo "Optiomizing rtv1..."
	@gcc -o3 -o $(NAME) $(SRC) $(HEADERS) $(LIB)
	@echo "Goal \o/"

clean :

fclean :
	@rm $(NAME)

re : fclean All
