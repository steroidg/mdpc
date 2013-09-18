cmake_minimum_required(VERSION 2.8)

# Set the name of the prank project
project(mdpc)

# setup version numbers
set(VERSION_MAJOR 0)
set(VERSION_MINOR 0)
set(VERSION_PATCH 1)

# find the libraries we want
find_package(SDL REQUIRED)
find_package(SDL_image REQUIRED)
find_package(SDL_ttf REQUIRED)

# use the constants defined for packages to setup compiler options
include_directories(${SDL_INCLUDE_DIR})

# easy way to just grab all files named .hpp and .cpp
FILE( GLOB allHeaders *.hpp )
FILE( GLOB allSrcs *.cpp )

# define the target executable
add_executable( mdpc
    ${allHeaders}
    ${allSrcs}
    )

# link against the sdl libraries
target_link_libraries( mdpc ${SDL_LIBRARY} ${SDLIMAGE_LIBRARY} ${SDLTTF_LIBRARY})


# set any compiler options
set_target_properties( mdpc PROPERTIES LINKER_LANGUAGE CXX)
