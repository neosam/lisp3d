# Lisp3D Engine CMake file

# Project Name
project(lisp3d)

# Check and load dependencies
INCLUDE(${CMAKE_ROOT}/Modules/FindSDL.cmake)
#INCLUDE(${CMAKE_ROOT}/Modules/FindSDL_image.cmake)
INCLUDE(${CMAKE_ROOT}/Modules/FindOpenGL.cmake)
INCLUDE(${CMAKE_ROOT}/Modules/FindGLU.cmake)
#INCLUDE(${CMAKE_ROOT}/Modules/FindOpenAL.cmake)

# Bind include options for the c++ compiler
include_directories(${CMAKE_BINARY_DIR}
		    ${SDL_INCLUDE_DIR}
#		    ${SDLIMAGE_INCLUDE_DIR}
		    ${OPENGL_INCLUDE_DIR})

# Bind libraries for the linker
link_libraries(${SDL_LIBRARY}
	       ${SDLIMAGE_LIBRARY}
	       ${OPENGL_LIBRARIES}
	       ${OPENAL_LIBRARY}
	       #{GLU_LIBRARY}
	       -lalut)


#configure_file(src/config.h.cmake ${CMAKE_BINARY_DIR}/config.h)

# Create n3dViewer executable
add_executable(lisp3d
	src/camera.c
	src/elements.c
	src/globalindex.c
	src/lua.c
	src/object.c
	src/parser.c
	src/quad.c
	src/test.c
	src/lua/lapi.c
	src/lua/ldebug.c  
	src/lua/linit.c     
	src/lua/loadlib.c   
	src/lua/lstate.c   
	src/lua/ltm.c
	src/lua/lauxlib.c   
	src/lua/ldo.c     
	src/lua/liolib.c    
	src/lua/lobject.c   
	src/lua/lstring.c  
	src/lua/lundump.c
	src/lua/lbaselib.c  
	src/lua/ldump.c   
	src/lua/llex.c      
	src/lua/lopcodes.c  
	src/lua/lstrlib.c  
	src/lua/lvm.c
	src/lua/lcode.c     
	src/lua/lfunc.c   
	src/lua/lmathlib.c  
	src/lua/loslib.c    
	src/lua/ltable.c   
	src/lua/lzio.c
	src/lua/ldblib.c    
	src/lua/lgc.c     
	src/lua/lmem.c      
	src/lua/lparser.c   
	src/lua/ltablib.c  
	src/lua/print.c)

install(TARGETS lisp3d DESTINATION bin)