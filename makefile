CC     = g++

CFLAGS = -O3 -march=native -mtune=native -ffast-math -flto -Wall

OUTPUT = benchmark

SRC    = benchmark.cpp

all: $(OUTPUT) 

$(OUTPUT): $(SRC)
	$(CC) $(CFLAGS) -o $(OUTPUT) $(SRC)

clean:
	rm -rf $(OUTPUT) a.out

pretty:	
	find . -name "*.h" -exec clang-format -i {} \;
	find . -name "*.cpp" -exec clang-format -i {} \;
