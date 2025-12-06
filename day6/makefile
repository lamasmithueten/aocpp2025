CC           = g++

CFLAGS       = -O3 -march=native -mtune=native -ffast-math -flto=auto -Wall

OUTPUT_PART1 = part1
OUTPUT_PART2 = part2

DAY          = 6

SRC_PART1    = day$(DAY).cpp
SRC_PART2    = day$(DAY)_part2.cpp


INPUT        = input.txt
TEST         = test.txt

all: $(OUTPUT_PART1) $(OUTPUT_PART2)

1: $(OUTPUT_PART1)
2: $(OUTPUT_PART2)

$(OUTPUT_PART1): $(SRC_PART1)
	$(CC) $(CFLAGS) -o $(OUTPUT_PART1) $(SRC_PART1)

$(OUTPUT_PART2): $(SRC_PART2)
	$(CC) $(CFLAGS) -o $(OUTPUT_PART2) $(SRC_PART2)


clean:
	rm -rf $(OUTPUT_PART1) $(OUTPUT_PART2) a.out

test:
	bash -c	"time ./$(OUTPUT_PART1) $(TEST)"
	bash -c	"time ./$(OUTPUT_PART2) $(TEST)"
	

time:
	bash -c	"time ./$(OUTPUT_PART1) $(INPUT)"
	bash -c	"time ./$(OUTPUT_PART2) $(INPUT)"

pretty:	
	find . -name "*.h" -exec clang-format -i {} \;
	find . -name "*.cpp" -exec clang-format -i {} \;
