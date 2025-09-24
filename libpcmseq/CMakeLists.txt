cmake_minimum_required(VERSION 3.16)
project(libpcmseq C)

# Automatically collect all C source files in this directory
file(GLOB LIBPCMSEQ_SRCS "*.c")

# Include directories (public API)
set(LIBPCMSEQ_INCLUDE_DIRS include)

# Create a static library
add_library(libpcmseq STATIC ${LIBPCMSEQ_SRCS})

# Export public headers
target_include_directories(libpcmseq PUBLIC ${LIBPCMSEQ_INCLUDE_DIRS})
