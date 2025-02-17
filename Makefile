# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/10 18:38:23 by motero            #+#    #+#              #
#    Updated: 2024/02/08 05:22:55 by olimarti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

#=============================================================================#
#                                 HEADERS                                     #
#=============================================================================#

LIBS_DIR = libs/

HDR_NAME = cub3D.h parsing.h structures.h colors.h mlx_engine.h settings.h
HDR_DIR = includes/
HDRS = $(addprefix $(HDR_DIR), $(HDR_NAME))
HDR_INC = -I includes

#================================================================flx=============#
#                                 LIBRARIES                                     #
#=============================================================================#

LIBFT_DIR = $(LIBS_DIR)libft/
LIBFT_HDIR = $(LIBFT_DIR)includes/
LIBFT_HDIR_INC = -I $(LIBFT_HDIR)
LIB_BINARY = -L$(LIBFT_DIR) -lft
LIBFT = $(LIBFT_HDIR)/libft.a
HDR_INC += $(LIBFT_HDIR_INC)

#=============================================================================#
#                                 MiniLIBX                                    #
#=============================================================================#

MINILIBX_HDIR = $(LIBS_DIR)minilibx-linux/
MINILIBX_HDIR_INC = -I $(MINILIBX_HDIR)
MINILIBX_BINARY = -Lmlx_linux -lmlx_Linux -L$(MINILIBX_HDIR) -Imlx_linux -lXext -lX11 -lm -lz
MINILIBX = $(MINILIBX_HDIR)libmlx.a
HDR_INC += $(MINILIBX_HDIR_INC)


#=============================================================================#
#                               SOURCES                                       #
#=============================================================================#

SRCS_DIR_project = sources/

SRCS_RAW_NAME_DIRECTORIES = $(wildcard $(SRCS_DIR_project)* )
SRCS_NAME_DIRECTORIES = $(patsubst sources/%,%,$(SRCS_RAW_NAME_DIRECTORIES))

SRCS_ALL = $(wildcard $(SRCS_RAW_NAME_DIRECTORIES)/)
SRCS_RAW_ALL = $(shell find $(SRCS_DIR_project) -type f -name "*.c")
SRCS_ALL = $(patsubst sources/%,%,$(SRCS_RAW_ALL))
SRCS_NAME_project = $(SRCS_ALL)
#SRCS_NAME_project = \

SRCS_PROJECT = $(addprefix $(SRCS_DIR_project), $(SRCS_NAME_project))

#=============================================================================#
#                             		GNL                                       #
#=============================================================================#

GNL_DIR = $(LIBS_DIR)gnl/
GNL_HDIR = $(GNL_DIR)
GNL_HDIR_INC = -I $(GNL_HDIR)
GNL_NAME = get_next_line.c \
			get_next_line_utils.c
GNL = $(addprefix $(GNL_DIR), $(GNL_NAME))
GNL_OBJ = $(GNL:.c=.o)
HDR_INC += $(GNL_HDIR_INC)



#=============================================================================#
#                                OBJECTS                                      #
#=============================================================================#

OBJS_PATH = objs/
OBJS_NAME = $(SRCS_NAME_project:.c=.o)
OBJS = $(addprefix $(OBJS_PATH), $(OBJS_NAME))

#=============================================================================#
#                          COMPILATOR & FLAGS                                 #
#=============================================================================#

CC = cc
CFLAGS = -Wall -Wextra -flto -O3 #-O3 -pg -g3# -fsanitize=address -fsanitize=leak#-g #-fpie #-fsanitize=leak -fsanitize=address
LIBA = ar rc
LIBS = ranlib

ifneq ($(no_error), true)
	CFLAGS += -Werror
endif

ifeq ($(little_endian), true)
	CFLAGS += -D LITTLE_ENDIAN
endif


RM = rm -Rf

#=============================================================================#
#                                 Profiler                                    #
#=============================================================================#

PROFILE = project_prof

OBJS_PATH_PROFILER = objs_prof/
OBJS_NAME_PROFILER = $(SRCS_NAME_project:.c=.o)
OBJS_PROFILER = $(addprefix $(OBJS_PATH_PROFILER), $(OBJS_NAME_PROFILER))

PROFILER_FLAG = -pg

#=============================================================================#
#                                 Fsanitize                                    #
#=============================================================================#

SANITIZE = project_sanitize

OBJS_PATH_SANITIZE = objs_sanitize/
OBJS_NAME_SANITIZE = $(SRCS_NAME_project:.c=.o)
OBJS_SANITIZE = $(addprefix $(OBJS_PATH_SANITIZE), $(OBJS_NAME_SANITIZE))

SANITIZE_FLAG = -g3 -fsanitize=address -fno-omit-frame-pointer

#=============================================================================#
#                                 Valgrind                                    #
#=============================================================================#

VALGND = project_valgrind

OBJS_PATH_VALGND = objs_valgrind/
OBJS_NAME_VALGND = $(SRCS_NAME_project:.c=.o)
OBJS_VALGND = $(addprefix $(OBJS_PATH_VALGND), $(OBJS_NAME_VALGND))

VALGND_FLAG = -g3

#=============================================================================#
#                                 Callgrind                                    #
#=============================================================================#

CALLGND = project_callgrind

OBJS_PATH_CALLGND = objyRatio
OBJS_PATH_GDB = objs_gdb/
OBJS_NAME_GDB = $(SRCS_NAME_project:.c=.o)
OBJS_GDB = $(addprefix $(OBJS_PATH_GDB), $(OBJS_NAME_GDB))

GDB_FLAG = -g

#=============================================================================#
#                                COLOURS                                      #
#=============================================================================#

RED = \033[0;31m
GREEN = \033[0;32m
BLUE = \033[0;34m
YELLOW = \033[0;33m
NONE = \033[0m

bold := $(shell tput bold)
normal := $(shell tput sgr0)

#=============================================================================#
#                                RULES                                        #
#=============================================================================#

bonus : all

all: check_libft check_mlx project ${NAME} ${HDRS}
		@echo "\n $(GREEN) $(bold) \|/ \|/ \|/ \|/ \|/ \|/ \|/ \|/ \|/ \|/ \|/ \|/ \|/"
		@echo "\t \t[ $(GREEN)✔$(NONE)] $(bold)Project is ready [ $(GREEN)✔$(NONE)]"
		@echo "$(GREEN) $(bold) /|\ /|\ /|\ /|\ /|\ /|\ /|\ /|\ /|\ /|\ /|\ /|\ /|\ \n"

check_libft:
		@echo "\n[ $(BLUE)$(bold)CHECKING LIBFT$(NONE)]"
		@echo "============================================="
		@make -sC $(LIBFT_DIR)

check_mlx:
		@echo "\n[ $(BLUE)$(bold)CHECKING MINILIBX$(NONE)]"
		@echo "============================================="
		@make -sC $(MINILIBX_HDIR)

project:
		@echo "\n == $(bold)$(YELLOW)CHECKING PROJECT$(normal)=="
		@echo "==============================================="

run:
	make
	clear
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes -s ./$(NAME)

$(OBJS_PATH):
		@mkdir -p $(addprefix $(OBJS_PATH), $(SRCS_NAME_DIRECTORIES))
		@echo "\t [ $(GREEN)✔$(NONE)] $@directories"

$(OBJS_PATH)%.o: $(SRCS_DIR_project)%.c $(HDRS)
		@mkdir -p $(@D)
		@$(CC) $(CFLAGS) $(HDR_INC) -o $@ -c $<
		@echo "\t[ $(GREEN)✔$(NONE) ] $@ objet project"

$(NAME): $(GNL_OBJ) $(OBJS_PATH) $(OBJS) $(HDRS)
		@echo $(SRCS_ALL)
		@$(CC) $(CFLAGS) $(GNL_OBJ) $(OBJS) $(LIB_BINARY) $(MINILIBX_BINARY) $(HDR_INC) -o $@
		@echo "\t[ $(GREEN)✔$(NONE) ] project"

malloc_test: $(OBJS_PATH) ${GNL_OBJ} $(OBJS)
		@make -C libft
		$(CC) $(CFLAGS) -fsanitize=undefined -rdynamic -o $@ ${OBJS} ${GNL_OBJ} $(LIB_BINARY) -L. -lmallocator

#=============================================================================#
#                                RULES   PROFILER                             #
#=============================================================================#

#To xecute as follows :make sanitizer var="1 2 3"

prof: fclean check_libft project ${PROFILE} ${HDRS} run_prof execute_profiler

execute_profiler :
		@gprof -b ${PROFILE} gmon.out > analysis.txt
		@echo "\t[ $(GREEN) Profling done!$(NONE) ]"
		@echo "========================================"
		@cat analysis.txt

run_prof: project_prof
	@echo "\n[ $(BLUE)$(bold)Executing binary$(NONE) ]"
	./project_prof $(var)

$(OBJS_PATH_PROFILER):
		@mkdir -p $@
		@echo "\t [ $(GREEN)✔$(NONE)] $@directory"

$(OBJS_PATH_PROFILER)%.o: $(SRCS_DIR_project)%.c $(HDRS) $(LIBFT)
		@mkdir -p $(@D)
		@$(CC) $(CFLAGS) $(PROFILER_FLAG) $(HDR_INC) $(LIBFT_HDIR_INC) -o $@ -c $<
		@echo "\t[ $(GREEN)✔$(NONE) ] $@ objet project_prof"

$(PROFILE) : $(OBJS_PATH_PROFILER) $(OBJS_PROFILER) $(LIBFT) $(HDRS)
		@echo " \n[$(bold)$(YELLOW) PROFILER COMPILATION $(NONE)]"
		$(CC) $(CFLAGS) $(PROFILER_FLAG) $(OBJS_PROFILER) $(LIB_BINARY) -o $@
		@echo "\t[ $(GREEN)✔$(NONE) ] project_prof"

#=============================================================================#
#                                RULES   SANITIZER                            #
#=============================================================================#

#to launch as folows  : make sanitizer var="1 2 3"
sanitizer: fclean check_libft project ${SANITIZE} ${HDRS} run_san

run_san: project_sanitize
	@echo "\n\[ $(BLUE)$(bold)===EXECUTING BINARY====$(NONE)]\n"		@echo "\t [ $(GREEN)✔$(NONE)] $@directories"
$(SANITIZE) : $(OBJS_PATH_SANITIZE) $(OBJS_SANITIZE) $(LIBFT) $(HDRS)
		@echo "\n [$(GREEN)$(bold)FSANITIZE COMPILATION$(NONE) ]"
		@$(CC) $(CFLAGS) $(SANITIZE_FLAG) $(OBJS_SANITIZE) $(LIB_BINARY) -o $@
		@echo "\t[ $(GREEN)✔$(NONE) ] project_sanitize"

#make run_sanitize with good run

#=============================================================================#
#                                RULES  VALGRIND                              #
#=============================================================================#

#to launch as folows  : make valgnd var="1 2 3"
valgnd: fclean check_libft project ${VALGND} ${HDRS} run_valgnd

run_valgnd: project_valgrind
	@echo "\n [ $(BLUE)$(bold) Executing binary with valgrind$(NONE)]\n"
	@valgrind ./project_valgrind $(var)

$(OBJS_PATH_VALGND):
		@mkdir -p $@
		@echo "\t [ $(GREEN)✔$(NONE)] $@directory"

$(OBJS_PATH_VALGND)%.o: $(SRCS_DIR_project)%.c $(HDRS) $(LIBFT)
		@mkdir -p $(@D)
		@$(CC) $(CFLAGS) $(VALGND_FLAG) $(HDR_INC) $(LIBFT_HDIR_INC) -o $@ -c $<
		@echo "\t[ $(GREEN)✔$(NONE) ] $@ objet project_valgrind"

$(VALGND) : $(OBJS_PATH_VALGND) $(OBJS_VALGND) $(LIBFT) $(HDRS)
		@echo "\n[$(GREEN)$(bold)VALGND COMPILATION"
		@$(CC) $(CFLAGS) $(VALGND_FLAG) $(OBJS_VALGND) $(LIB_BINARY) -o $@
		@echo "\t[ $(GREEN)✔$(NONE) ] project_valgrind"


#=============================================================================#
#                                RULES  CALLLGRIND                              #
#=============================================================================#

#to launch as folows  : make valgnd var="1 2 3"
callgnd: fclean check_libft project ${VALGND} ${HDRS} run_callgnd

run_callgnd: project_callgrind
	@echo "\n [ $(BLUE)$(bold) Executing binary with callgrind$(NONE)]\n"
	@valgrind --tool=callgrind --dump-instr=yes --collect-jumps=yes  ./project_callgrind $(var)
	@kcachegrind callgrind.out.*

$(OBJS_PATH_CALLGND):
		@mkdir -p $@
		@echo "\t [ $(GREEN)✔$(NONE)] $@directory"

$(OBJS_PATH_CALLGND)%.o: $(SRCS_DIR_project)%.c $(HDRS) $(LIBFT)
		@mkdir -p $(@D)
		@$(CC) $(CFLAGS) $(CALLGND_FLAG) $(HDR_INC) $(LIBFT_HDIR_INC) -o $@ -c $<
		@echo "\t[ $(GREEN)✔$(NONE) ] $@ objet project_callgrind"

$(CALLGND) : $(OBJS_PATH_CALLGND) $(OBJS_CALLGND) $(LIBFT) $(HDRS)
		@echo "\n[$(GREEN)$(bold)CALLGND COMPILATION]"
		@$(CC) $(CFLAGS) $(CALLGND_FLAG) $(LIB_BINARY) $(OBJS_CALLGND) -o $@
		@echo "\t[ $(GREEN)✔$(NONE) ] project_callgrind"

#=============================================================================#
#                                RULES   GDB                                  #
#=============================================================================#

#to launch as folows  : make BDG
bdg: fclean check_libft project ${BDG} ${HDRS} run_bdg

run_bdg: project_gdb
	@echo "\n\[ $(BLUE)$(bold)===EXECUTING BINARY====$(NONE)]\n"
	gdb project_gdb $(var)

$(OBJS_PATH_GDB):
		@mkdir -p $@
		@echo "\t [ $(GREEN)✔$(NONE)] $@directory"

$(OBJS_PATH_GDB)%.o: $(SRCS_DIR_project)%.c $(HDRS) $(LIBFT)
		@mkdir -p $(@D)
		@$(CC) $(CFLAGS) $(GDB_FLAG) $(HDR_INC) $(LIBFT_HDIR_INC) -o $@ -c $<
		@echo "\t[ $(GREEN)✔$(NONE) ] $@ objet project_gdb"

$(BDG) : $(OBJS_PATH_GDB) $(OBJS_GDB) $(LIBFT) $(HDRS)
		@echo "\n [$(GREEN)$(bold)BDG COMPILATION$(NONE) ]"
		@$(CC) $(CFLAGS) $(GDB_FLAG) $(OBJS_GDB) $(LIB_BINARY)  -o $@
		@echo "\t[ $(GREEN)✔$(NONE) ] project_gdb"

#=============================================================================#
#                                COMMANDS                                     #
#=============================================================================#

clean:
		@echo "[ $(RED)$(bold)STARTING CLEAN$(NONE) ]"
		@echo "==================================="
		@${RM} $(OBJS_PATH) $(OBJS_PATH_PROFILER) $(OBJS_PATH_SANITIZE) $(OBJS_PATH_VALGND) $(OBJS_CALLGND) $(OBJS_PATH_GDB) $(GNL_OBJ)
		@rm -rf analysis.txt gmon.out callgrind.out.* ${PROFILE}
		@echo "\t[ $(RED)✗$(NONE) ] $(OBJ_DIR) directory"
		@make -sC $(LIBFT_DIR) clean

fclean: clean
		@rm -f ${NAME} ${PROFILE} ${SANITIZE} ${VALGND} ${CALLGND} ${BDG}
		@echo "\t[ $(RED)✗$(NONE) ] $(NAME) executable"
		@make -sC $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
