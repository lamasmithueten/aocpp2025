CC           = g++
NVCC          = nvcc

CFLAGS       = -O3 -march=native -mtune=native -ffast-math -flto=auto -Wall -fopenmp
CFLAGS_NVCC   = -O3 -Wno-deprecated-gpu-targets -use_fast_math -Xcompiler -march=native

OUTPUT_PART1 = part1
OUTPUT_PART2 = part2
OUTPUT_PART2_PARALLEL = part2_parallel
OUTPUT_NVCC   = part2_cuda


DAY          = 7

SRC_PART1    = day$(DAY).cpp
SRC_PART2    = day$(DAY)_part2.cpp
SRC_PART2_PARALLEL    = day$(DAY)_part2_parallel.cpp
SRC_NVCC      = day$(DAY)_part2.cu



INPUT        = input.txt
TEST         = test.txt

all: $(OUTPUT_PART1) $(OUTPUT_PART2) $(OUTPUT_PART2_PARALLEL) $(OUTPUT_NVCC)

1: $(OUTPUT_PART1)
2: $(OUTPUT_PART2)
parallel: $(OUTPUT_PART2)
cuda: $(OUTPUT_NVCC)

$(OUTPUT_PART1): $(SRC_PART1)
	$(CC) $(CFLAGS) -o $(OUTPUT_PART1) $(SRC_PART1)

$(OUTPUT_PART2): $(SRC_PART2)
	$(CC) $(CFLAGS) -o $(OUTPUT_PART2) $(SRC_PART2)

$(OUTPUT_PART2_PARALLEL): $(SRC_PART2_PARALLEL)
	$(CC) $(CFLAGS) -o $(OUTPUT_PART2_PARALLEL) $(SRC_PART2_PARALLEL)

$(OUTPUT_NVCC): $(SRC_NVCC) 
	$(NVCC) $(CFLAGS_NVCC) -o $(OUTPUT_NVCC) $(SRC_NVCC) 

clean:
	rm -rf $(OUTPUT_PART1) $(OUTPUT_PART2) $(OUTPUT_PART2_PARALLEL) $(OUTPUT_NVCC) a.out

test:
	bash -c	"time ./$(OUTPUT_PART1) $(TEST)"
	bash -c	"time ./$(OUTPUT_PART2) $(TEST)"
	bash -c	"time ./$(OUTPUT_PART2_PARALLEL) $(TEST)"
	bash -c	"time ./$(OUTPUT_NVCC) $(TEST)"
	

time:
	bash -c	"time ./$(OUTPUT_PART1) $(INPUT)"
	bash -c	"time ./$(OUTPUT_PART2) $(INPUT)"
	bash -c	"time ./$(OUTPUT_PART2_PARALLEL) $(INPUT)"
	bash -c	"time ./$(OUTPUT_NVCC) $(INPUT)"

pretty:	
	find . -name "*.h" -exec clang-format -i {} \;
	find . -name "*.cpp" -exec clang-format -i {} \;
	find . -name "*.cu" -exec clang-format -i {} \;
