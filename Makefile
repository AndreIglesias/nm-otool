#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/20 17:00:07 by ciglesia          #+#    #+#              #
#    Updated: 2021/06/14 01:51:58 by ciglesia         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME		=	ft_nm

#****************** INC *******************#
# General
INC			=	./include/

# Libft
SUB_MAKE	=	./lib/libft/
INCFT		=	./lib/libft/include/

INCLUDE		=	-O3 -I $(INCFT) -I $(INC)

INC_LIB		=	-L$(SUB_MAKE) -lft

#***************** SRC* *******************#

DIRSRC		=	./src/
DIRDIS		=	$(DIRSRC)/display/

SRC			=	main.c
DISPLAY		=	print_header.c

SRCS		=	$(SRC) $(DISPLAY)

#***************** DEPS ******************#

DIROBJ		=	./depo/

OAUX		=	$(SRCS:%=$(DIROBJ)%)
DEPS		=	$(OAUX:.c=.d)
OBJS		=	$(OAUX:.c=.o)

ifdef FLAGS
	ifeq ($(FLAGS), no)
CFLAGS		=
	endif
	ifeq ($(FLAGS), debug)
CFLAGS		=	-Wall -Wextra -Werror -ansi -pedantic -g
	endif
else
CFLAGS		=	-Wall -Wextra -Werror
endif

CC			=	/usr/bin/clang
RM			=	/bin/rm -f
ECHO		=	/bin/echo -e
BOLD		=	"\e[1m"
BLINK		=	 "\e[5m"
RED			=	 "\e[38;2;255;0;0m"
GREEN		=	 "\e[92m"
BLUE		=	 "\e[34m"
YELLOW		=	 "\e[33m"
E0M			=	 "\e[0m"

#************************ DEPS COMPILATION *************************

%.o		:		../$(DIRSRC)/%.c
				@printf $(GREEN)"Generating minishell objects... %-33.33s\r" $@
				@$(CC) $(CFLAGS) $(INCLUDE) -MMD -o $@ -c $<

%.o		:		../$(DIRDIS)/%.c
				@printf $(GREEN)"Generating minishell objects... %-33.33s\r" $@
				@$(CC) $(CFLAGS) $(INCLUDE) -MMD -o $@ -c $<

#************************ MAIN COMPILATION *************************

$(NAME)	:		ftlib $(OBJS)
				@printf $(E0M)"\n"
				@$(CC)  $(INCLUDE) $(CFLAGS) -o $(NAME) $(OBJS) $(INC_LIB)
				@$(ECHO) $(GREEN) $(BOLD)
				@$(ECHO) "88          88"
				@$(ECHO) "88          \"\""
				@$(ECHO) "88"
				@$(ECHO) "88,dPPYba,  88 8b,dPPYba,  ,adPPYYba, 8b,dPPYba, 8b       d8"
				@$(ECHO) "88P'    \"8a 88 88P'   \`\"8a \"\"     \`Y8 88P'   \"Y8 \`8b     d8'"
				@$(ECHO) "88       d8 88 88       88 ,adPPPPP88 88          \`8b   d8'"
				@$(ECHO) "88b,   ,a8\" 88 88       88 88,    ,88 88           \`8b,d8'"
				@$(ECHO) "8Y\"Ybbd8\"'  88 88       88 \`\"8bbdP\"Y8 88             Y88'"
				@$(ECHO) "                                                    d8'"
				@$(ECHO) "                                                   d8'"
				@$(ECHO) $(E0M)
				@$(ECHO) $(BOLD)$(GREEN)'> Compiled'$(E0M)

clean	:
				@($(RM) $(OBJS))
				@($(RM) $(DEPS))
				@(cd $(SUB_MAKE) && $(MAKE) clean)
				@$(ECHO) $(RED)'> Directory cleaned'$(E0M)

all		:		$(NAME)

fclean	:		clean
				@$(RM) $(NAME)
				@(cd $(SUB_MAKE) && $(MAKE) fclean)
				@$(ECHO) $(RED)'> Executable removed'$(E0M)

re		:		fclean all

ftlib	:
				@(cd $(SUB_MAKE) && $(MAKE))

.PHONY	:		all clean re

-include $(DEPS)
