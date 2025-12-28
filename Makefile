CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g -I src
LIBS = -lm

TARGET_PSO = pso
SRCS_PSO = main.c src/map.c src/pso.c src/logger.c src/utils.c
OBJS_PSO = $(SRCS_PSO:.c=.o)

TARGET_GEN = generator
SRCS_GEN = src/map_generator.c src/utils.c src/generator_utils.c
OBJS_GEN = $(SRCS_GEN:.c=.o)

TARGET_UNIT = test_unit
SRCS_UNIT = src/test_unit.c src/map.c src/pso.c src/logger.c src/utils.c src/generator_utils.c
OBJS_UNIT = $(SRCS_UNIT:.c=.o)

TARGET_FUNC = test_func
SRCS_FUNC = src/test_functional.c src/map.c src/pso.c src/logger.c src/utils.c src/generator_utils.c
OBJS_FUNC = $(SRCS_FUNC:.c=.o)

all: $(TARGET_PSO)

$(TARGET_PSO): $(OBJS_PSO)
	$(CC) $(CFLAGS) $(OBJS_PSO) -o $(TARGET_PSO) $(LIBS)

$(TARGET_GEN): $(OBJS_GEN)
	$(CC) $(CFLAGS) $(OBJS_GEN) -o $(TARGET_GEN) $(LIBS)

$(TARGET_UNIT): $(OBJS_UNIT)
	$(CC) $(CFLAGS) $(OBJS_UNIT) -o $(TARGET_UNIT) $(LIBS)

$(TARGET_FUNC): $(OBJS_FUNC)
	$(CC) $(CFLAGS) $(OBJS_FUNC) -o $(TARGET_FUNC) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

unit: $(TARGET_UNIT)
	./$(TARGET_UNIT)

func: $(TARGET_FUNC)
	./$(TARGET_FUNC)

gen: $(TARGET_GEN)

test: unit func

clean:
	rm -f $(TARGET_PSO) $(TARGET_GEN) $(TARGET_UNIT) $(TARGET_FUNC) *.o src/*.o results.csv *.tmp