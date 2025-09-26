cmake_minimum_required(VERSION 3.16)

# Glob all C sources in src/
file(GLOB LIBPCMSEQ_SRCS "src/*.c")

# Include directories for public headers
set(LIBPCMSEQ_INCLUDE_DIRS include)

# If inside ESP-IDF, register as a component
if(COMMAND idf_component_register)
    idf_component_register(
        SRCS ${LIBPCMSEQ_SRCS}
        INCLUDE_DIRS ${LIBPCMSEQ_INCLUDE_DIRS}
    )
else()
    # Standalone CMake project
    project(libpcmseq C)

    # Create static library
    add_library(libpcmseq STATIC ${LIBPCMSEQ_SRCS})
    target_include_directories(libpcmseq PUBLIC ${LIBPCMSEQ_INCLUDE_DIRS})
endif()
