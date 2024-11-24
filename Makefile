BIN_NAME	= bcgstab

SRCS		= main.cpp\
			  src/ParallelOperations.cpp

HEADERS		= include/Mat.h

OBJ			= $(SRCS:.cpp=.o)

CC			= g++ -O0 -fsanitize=address -fopenmp

CFLAGS		= -Iinclude -I/usr/include/eigen3/Eigen/

LDFLAGS		= -fsanitize=address -lgtest -pthread

all: $(BIN_NAME) clean

clean:
	@rm -rf *.o src/*.o

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_NAME): $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) -o $@