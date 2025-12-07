#include <cuda_runtime.h>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

__global__ void countPathsKernel(char *matrix, unsigned long long *dp,
                                 unsigned long long *partialSums, int rows,
                                 int cols, int goalRow, int goalCol) {
  int startCol = blockIdx.x * blockDim.x + threadIdx.x;
  if (startCol >= cols)
    return;

  unsigned long long *threadDP = dp + startCol * rows * cols;

  threadDP[(rows - 1) * cols + startCol] = 1;

  for (int i = rows - 2; i >= 0; --i) {
    for (int j = 0; j < cols; ++j) {
      if (i + 1 < rows) {
        char below = matrix[(i + 1) * cols + j];
        if (below == '^') {
          unsigned long long left =
              (j - 1 >= 0) ? threadDP[(i + 1) * cols + (j - 1)] : 0;
          unsigned long long right =
              (j + 1 < cols) ? threadDP[(i + 1) * cols + (j + 1)] : 0;
          threadDP[i * cols + j] = left + right;
        } else {
          threadDP[i * cols + j] = threadDP[(i + 1) * cols + j];
        }
      }
    }
  }

  partialSums[startCol] = threadDP[goalRow * cols + goalCol];
}

unsigned long long countAllPathsCUDA(std::vector<std::string> &matrix) {
  int rows = matrix.size();
  if (rows == 0)
    return 0;
  int cols = matrix[0].size();

  std::pair<int, int> goal;
  bool found = false;
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      if (matrix[i][j] == 'S') {
        goal = {i, j};
        found = true;
        break;
      }
    }
    if (found)
      break;
  }

  char *flatMatrix = new char[rows * cols];
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      flatMatrix[i * cols + j] = matrix[i][j];
    }
  }

  char *d_matrix;
  unsigned long long *d_dp;
  unsigned long long *d_partialSums;
  unsigned long long *h_partialSums = new unsigned long long[cols];

  cudaError_t err;
  err = cudaMalloc(&d_matrix, rows * cols * sizeof(char));
  if (err != cudaSuccess) {
    std::cerr << "Error allocating d_matrix: " << cudaGetErrorString(err)
              << std::endl;
    return 0;
  }

  err = cudaMalloc(&d_dp, cols * rows * cols * sizeof(unsigned long long));
  if (err != cudaSuccess) {
    std::cerr << "Error allocating d_dp: " << cudaGetErrorString(err)
              << std::endl;
    cudaFree(d_matrix);
    return 0;
  }

  err = cudaMalloc(&d_partialSums, cols * sizeof(unsigned long long));
  if (err != cudaSuccess) {
    std::cerr << "Error allocating d_partialSums: " << cudaGetErrorString(err)
              << std::endl;
    cudaFree(d_matrix);
    cudaFree(d_dp);
    return 0;
  }

  err = cudaMemcpy(d_matrix, flatMatrix, rows * cols * sizeof(char),
                   cudaMemcpyHostToDevice);
  if (err != cudaSuccess) {
    std::cerr << "Error copying d_matrix: " << cudaGetErrorString(err)
              << std::endl;
    cudaFree(d_matrix);
    cudaFree(d_dp);
    cudaFree(d_partialSums);
    return 0;
  }

  err = cudaMemset(d_dp, 0, cols * rows * cols * sizeof(unsigned long long));
  if (err != cudaSuccess) {
    std::cerr << "Error initializing d_dp: " << cudaGetErrorString(err)
              << std::endl;
    cudaFree(d_matrix);
    cudaFree(d_dp);
    cudaFree(d_partialSums);
    return 0;
  }

  err = cudaMemset(d_partialSums, 0, cols * sizeof(unsigned long long));
  if (err != cudaSuccess) {
    std::cerr << "Error initializing d_partialSums: " << cudaGetErrorString(err)
              << std::endl;
    cudaFree(d_matrix);
    cudaFree(d_dp);
    cudaFree(d_partialSums);
    return 0;
  }

  int blockSize = 256;
  int gridSize = (cols + blockSize - 1) / blockSize;
  countPathsKernel<<<gridSize, blockSize>>>(d_matrix, d_dp, d_partialSums, rows,
                                            cols, goal.first, goal.second);

  err = cudaGetLastError();
  if (err != cudaSuccess) {
    std::cerr << "Error launching kernel: " << cudaGetErrorString(err)
              << std::endl;
    cudaFree(d_matrix);
    cudaFree(d_dp);
    cudaFree(d_partialSums);
    delete[] flatMatrix;
    delete[] h_partialSums;
    return 0;
  }

  err = cudaMemcpy(h_partialSums, d_partialSums,
                   cols * sizeof(unsigned long long), cudaMemcpyDeviceToHost);
  if (err != cudaSuccess) {
    std::cerr << "Error copying d_partialSums: " << cudaGetErrorString(err)
              << std::endl;
    cudaFree(d_matrix);
    cudaFree(d_dp);
    cudaFree(d_partialSums);
    delete[] flatMatrix;
    delete[] h_partialSums;
    return 0;
  }

  unsigned long long totalPaths = 0;
  for (int i = 0; i < cols; ++i) {
    totalPaths += h_partialSums[i];
  }

  cudaFree(d_matrix);
  cudaFree(d_dp);
  cudaFree(d_partialSums);
  delete[] flatMatrix;
  delete[] h_partialSums;

  return totalPaths;
}

int main(int argc, char **argv) {
  std::ifstream file(argv[1]);
  std::string line;
  std::vector<std::string> manifold;
  std::vector<std::vector<std::pair<int, int>>> paths;
  std::vector<std::pair<int, int>> path;

  while (std::getline(file, line)) {
    manifold.push_back(line);
  }

  unsigned long long totalPaths = countAllPathsCUDA(manifold);
  std::cout << "Sum: " << totalPaths << '\n';

  return 0;
}
