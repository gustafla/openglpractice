cmake_minimum_required (VERSION 3.1)
project (openglpractice)

# C++11
set (CMAKE_CXX_STANDARD 11)

# Flags
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Dkiss_fft_scalar=float")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lGLESv2")

# Platform flags
if (EXISTS /opt/vc/lib)
  message ("Building for Raspberry Pi")
  set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DBUILD_RPI")
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DBUILD_RPI -I/opt/vc/include/ -L/opt/vc/lib -lEGL -lbcm_host")
else()
  message ("Building for PC")
endif()

# Release and debug flags
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -g -DBUILD_DEBUG")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2 -DSYNC_PLAYER -DBUILD_RELEASE")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O2 -DSYNC_PLAYER")
if (${BUILD_PLAYER})
  message("Rocket player")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DSYNC_PLAYER")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DSYNC_PLAYER")
endif()

# Glob src files
file(GLOB SRC_FILES
  "src/*.cxx"
  "src/scenes/*.cxx"
  "src/kissfft/*.c"
  "src/rocket/*.c"
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
  #PKG_SEARCH_MODULE(GLEW REQUIRED glew)
  #INCLUDE_DIRECTORIES(${GLEW_INCLUDE_DIRS})
  #TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${GLEW_LIBRARIES})
endif()

