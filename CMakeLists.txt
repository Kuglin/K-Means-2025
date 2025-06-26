cmake_minimum_required(VERSION 3.10)
project(KMeansImageSegmentation)

set(CMAKE_CXX_STANDARD 17)

# Inclui os diretórios de headers
include_directories(include)
include_directories(include/utils)

# Busca o OpenCV
find_package(OpenCV REQUIRED)

# Adiciona os arquivos fonte
add_executable(KMeansImageSegmentation
    src/main.cpp
    src/kmeans.cpp
    src/image_processing.cpp
    src/utils/distance.cpp
    src/utils/convergence.cpp # Adiciona este arquivo
)

# Linka o OpenCV
target_link_libraries(KMeansImageSegmentation ${OpenCV_LIBS})