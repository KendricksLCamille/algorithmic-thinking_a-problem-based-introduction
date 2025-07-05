cmake_minimum_required(VERSION 3.30)

# Set the project and language
project(algorithmic_thinking_a_problem_based_introduction C)

# Specify the C compiler (adjust path as needed)
set(CMAKE_C_COMPILER "/usr/local/gcc-15.1.0/bin/gcc-15.1.0")

# Enforce C23 standard
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)  # Strict C compliance

# Define the executable target
add_executable(${PROJECT_NAME} main.c
        Ch1_Hash_Tables.h)

# Common compile options
if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
    # Enable all warnings, extra, pedantic, and treat warnings as errors
    target_compile_options(${PROJECT_NAME} PRIVATE
            -Wall
            -Wextra
            -Wpedantic
            -Werror
            -D_FORTIFY_SOURCE=2
            -fstack-protector-strong
    )

    # Enable Address Sanitizer for runtime detection of memory errors
    target_compile_options(${PROJECT_NAME} PRIVATE
            -fsanitize=address
            -fno-omit-frame-pointer
    )
    target_link_options(${PROJECT_NAME} PRIVATE
            -fsanitize=address
    )

    # Enable static analysis with fanalyzer
    target_compile_options(${PROJECT_NAME} PRIVATE
            -fanalyzer
            -Warray-bounds
    )
endif()