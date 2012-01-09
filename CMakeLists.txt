# Homotopic Paths 2D

cmake_minimum_required( VERSION 2.8 )
project ( HP2D )

message ( STATUS "Creating Makefile for Homotopic Paths 2D" )
set( CMAKE_CXX_FLAGS "-L /usr/local/lib" )

set( SRC_FILES 
				 Vertex.cpp
				 Grid2D.cpp
				 HP2D.cpp
				 SDL_Functions.cpp
				 testSDL.cpp )

set ( HDR_FILES 
				 Vertex.h
				 Grid2D.h
				 HP2D.h
				 testSDL.h )

set( SDL_LIBS SDL
			  SDL_image )


add_executable ( testSDL ${SRC_FILES} ${HDR_FILES} )
target_link_libraries ( testSDL ${SDL_LIBS}  )
