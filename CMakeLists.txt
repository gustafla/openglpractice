cmake_minimum_required (VERSION 3.1)
project (openglpractice)

# C++11
set (CMAKE_CXX_STANDARD 11)

# Flags
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

if (EXISTS /opt/vc/lib)
  message ("Building for Raspberry Pi")
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DBUILD_RPI -I/opt/vc/include/ -L/opt/vc/lib -lGLESv2 -lEGL -lbcm_host")
endif()

# Glob src files
file(GLOB SRC_FILES
  "src/*.cxx"
)

# add the executable
add_executable(${PROJECT_NAME} ${SRC_FILES})

# libs
INCLUDE(FindPkgConfig)

if (EXISTS /opt/vc/lib)
  # SDL
  PKG_SEARCH_MODULE(SDL REQUIRED sdl)
  INCLUDE_DIRECTORIES(${SDL_INCLUDE_DIRS})
  TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL_LIBRARIES})
else()
  # SDL2
  PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
  INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS})
  TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES})
  # GLEW
  PKG_SEARCH_MODULE(GLEW REQUIRED glew)
  INCLUDE_DIRECTORIES(${GLEW_INCLUDE_DIRS})
  TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${GLEW_LIBRARIES})
endif()

