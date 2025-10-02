cmake_minimum_required(VERSION 3.16)

# Glob all C sources in src/
file(GLOB LIBPCM_SRCS "src/*.c")

# Include directories for public headers
set(LIBPCM_INCLUDE_DIRS include)

# If inside ESP-IDF, register as a component
if(COMMAND idf_component_register)
    idf_component_register(
        SRCS ${LIBPCM_SRCS}
        INCLUDE_DIRS ${LIBPCM_INCLUDE_DIRS}
    )
else()
    # Standalone CMake project
    project(libpcm C)

    # Create static library
    add_library(libpcm STATIC ${LIBPCM_SRCS})
    target_include_directories(libpcm PUBLIC ${LIBPCM_INCLUDE_DIRS})
endif()
