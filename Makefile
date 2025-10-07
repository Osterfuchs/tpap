CC = gcc
FLAGS =
WFLAGS = -Wall -Wpedantic -Wextra
NAME = tpap
SRCD = srcs
OBJD = objs

SRC = main.c

OBJ := $(addprefix ${OBJD}/,${SRC:.c=.o})
SRC := $(addprefix ${SRCD}/,${SRC})

${NAME}: ${OBJ}
	${CC} -o ${NAME} ${OBJ} ${FLAGS}

${OBJD}/%.o: ${SRCD}/%.c
	@mkdir -p ${OBJD}
	${CC} -o $@ -c ${FLAGS} ${WFLAGS} $<

debug:
	${CC} -g -o debug.out ${SRC} ${FLAGS}

run:
	make
	./${NAME}

clean:
	rm -rf ${OBJD}
	rm debug.out
