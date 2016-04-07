cmake_minimum_required(VERSION 2.8.11)

project(F_Tool)



include_directories(
    C:/Development/Tools/FormattingTool/F_Tool/
    C:/Development/Tools/FormattingTool/F_Tool/

)

# Linker options
set(CMAKE_LDFLAGS "${CMAKE_LDFLAGS}  ")

# Library path
set(CMAKE_LDFLAGS "${CMAKE_LDFLAGS} -L\".\" ")

# Define the CXX sources
set ( CXX_SRCS
    main.cpp
)

set_source_files_properties(
    ${CXX_SRCS} PROPERTIES COMPILE_FLAGS 
    " -g -O0 -Wall")

add_executable(F_Tool ${CXX_SRCS} ${C_SRCS})

