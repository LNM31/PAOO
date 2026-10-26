cmake_minimum_required(VERSION 3.10)

project(catalog)

include_directories(inc)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-Wall -Wextra)

# cmake .. -DDEMO_INIT_ERROR=ON  -> compileaza si exemplul care NU foloseste
# lista de initializare, ca sa se vada eroarea de compilare.
option(DEMO_INIT_ERROR "Compileaza exemplul gresit de initializare (da eroare)" OFF)
if(DEMO_INIT_ERROR)
    add_definitions(-DDEMO_INIT_ERROR)
endif()

add_executable(${PROJECT_NAME}
    inc/catalog/student.hpp
    inc/catalog/bad_examples.hpp
    src/main.cpp
    src/student.cpp
    src/bad_examples.cpp
)
