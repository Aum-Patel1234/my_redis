cmake_minimum_required(VERSION 4.0)
project(my_redis)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Output directory for binaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

# Automatically collect all .c and .cpp files in src/ and its subdirectories
# file(GLOB_RECURSE SERVER_SOURCES src/server/*.c src/server/*.cpp)
# file(GLOB_RECURSE CLIENT_SOURCES src/client/*.c src/client/*.cpp)
file(GLOB_RECURSE SERVER_SOURCES src/server*.c src/server*.cpp)
file(GLOB_RECURSE CLIENT_SOURCES src/client*.c src/client*.cpp)

# Alternatively, if you don't want separate folders, but all files in src/ (including subdirs)
# file(GLOB_RECURSE SOURCES src/*.c src/*.cpp)

# Create server executable
# add_executable(server ${SERVER_SOURCES})
add_executable(server_c src/server.c)

# Build C++ version of server
add_executable(server_cpp src/server.cpp)

# Create client executable
add_executable(client ${CLIENT_SOURCES})
