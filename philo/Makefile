SRCS    =    ./main.c ./cycle.c ./ft_atoi.c ./init.c

OBJ_SRC = 	${SRCS:.c=.o}

CC 		= 	gcc

NAME = philo

REM = rm -f

HEADER = ./philo.h

FLAGS = -Wall -Wextra -Werror -g -fsanitize=thread

.PHONY: all clean fclean re

%.o:	%.c ${HEADER}
			${CC} ${FLAGS} -c $< -o $@

${NAME}: ${OBJ_SRC}
			${CC} ${FLAGS} ${OBJ_SRC} -o ${NAME} 

all: ${NAME}

clean:
	${REM} ${OBJ_SRC}

fclean: clean
	${REM} ${OBJ_SRC} ${NAME}

re:         fclean all
