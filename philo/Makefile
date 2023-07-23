NAME		=	philo

SRCS		=	main.c \
				process/action.c process/checker.c process/routine.c process/time.c \
				create/create_data.c create/create_mutex.c create/create_threads.c \
				kernel/parsing.c kernel/print.c utils/utils.c

OBJS		=	${SRCS:.c=.o}

CC			=	@clang

CFLAGS		=	-Wall -Werror -Wextra -g3 -pthread

RM			=	@rm -rf

RED		=	\033[0;31m

DEFAULT		=	\033[0m

PURPLE	= \033[38;5;213m

PHILO	= @printf "$(PURPLE)\033[5m ██████╗ ██╗  ██╗██╗██╗      ██████╗ ███████╗\n"
PHILO1	= printf "$(PURPLE)\033[5m ██╔══██╗██║  ██║██║██║     ██╔═══██╗██╔════╝\n"
PHILO2	= printf "$(PURPLE)\033[5m ██████╔╝███████║██║██║     ██║   ██║███████╗\n"
PHILO3	= printf "$(PURPLE)\033[5m ██╔═══╝ ██╔══██║██║██║     ██║   ██║╚════██║\n"
PHILO4	= printf "$(PURPLE)\033[5m ██║     ██║  ██║██║███████╗╚██████╔╝███████║\n"
PHILO5	= printf "$(PURPLE)\033[5m ╚═╝     ╚═╝  ╚═╝╚═╝╚══════╝ ╚═════╝ ╚══════╝\n"

PHIL = $(PHILO);$(PHILO1);$(PHILO2);$(PHILO3);$(PHILO4);$(PHILO5); \

.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME):	${OBJS}
		${CC} ${CFLAGS} ${OBJS} -o ${NAME}
		${PHIL}

all:		${NAME}

clean:		
		${RM} ${OBJS}

fclean:		clean
		${RM} ${NAME}
		@echo "${RED}Erased by the code destroyer${DEFAULT}"

re:			fclean
		@$(MAKE) all -j

.PHONY:		all clean fclean re