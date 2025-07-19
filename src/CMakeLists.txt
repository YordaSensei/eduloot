cmake_minimum_required(VERSION 3.10)
project(eduloot)

include_directories(include)

# Only add working source files
add_executable(main 
    src/main.cpp
    src/User.cpp
    src/Parent.cpp
    src/Teacher.cpp
    # src/BuggyClass.cpp  # Don't include yet
)

set(HEADER_FILES
    include/User.h
    include/Parent.h
    include/Teacher.h
)