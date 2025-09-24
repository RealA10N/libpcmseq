cmake_minimum_required(VERSION 3.16)
project(libpcmseq C)

# Glob all C sources in src/
file(GLOB LIBPCMSEQ_SRCS "src/*.c")

# Include directories for public headers
set(LIBPCMSEQ_INCLUDE_DIRS include)

# Create static library
add_library(libpcmseq STATIC ${LIBPCMSEQ_SRCS})
target_include_directories(libpcmseq PUBLIC ${LIBPCMSEQ_INCLUDE_DIRS})
