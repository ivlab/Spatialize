#
# Copyright Regents of the University of Minnesota, 2014.  This software is released under the following license: http://opensource.org/licenses/lgpl-3.0.html.
# Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
#
# Code author(s):
# 		Dan Orban (dtorban)
#
 
cmake_minimum_required (VERSION 2.8.2) 
project (Spatialize)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "$ENV{MinVR_DIR}/cmake/modules")

if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set (CMAKE_INSTALL_PREFIX "${Spatialize_SOURCE_DIR}/build/install" CACHE PATH "default install path" FORCE )
endif()

set(Spatialize_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")
message(${Spatialize_INSTALL_PREFIX})

option(BUILD_DEPENDENCIES "If enabled, dependencies will be downloaded and built if an installed version is not found" ON)

#This way will auto detect all source files in the directory,
#while this will work, the preferred technique is to list out
#sourcefiles individually.  This will allow cmake to automatically
#rerun if a source file is added, which it will not do if you don't
#list the explicit source files.
#aux_source_directory(${CMAKE_SOURCE_DIR} SOURCEFILES})
#This is how you specific source file individually
set (SOURCEFILES 
		spatialize/source/main.cpp
		spatialize/source/SpatializeApp.cpp
		spatialize/source/example/ExampleCube.cpp
		spatialize/source/Box.cpp
		spatialize/source/VRModel.cpp)
set (HEADERFILES 
		spatialize/include/SpatializeApp.h
		spatialize/include/Scene.h
		spatialize/include/example/ExampleCube.h
		spatialize/include/Box.h
		spatialize/include/Shader.h
		spatialize/include/Mesh.h
		spatialize/include/VRModel.h)
source_group("Header Files" FILES ${HEADERFILES})

############################################################
#Start of library detection
#Any libraries outside of your source should have a corresponding
#find module in the $G/src/cmake/Modules directory and the 
#find_package method should be used here.
############################################################

set(MinVR_DIR $ENV{MinVR_DIR})
find_package(MinVR COMPONENTS MVRCore AppKit_GLFW REQUIRED)
include_directories(${MinVR_INCLUDE_DIRS})

############################################################
#End external library searching
############################################################

set (CMAKE_VERBOSE_MAKEFILE TRUE)

# Used for compiling in subdirectories of the project
include_directories (
  .
  ..
  ${Spatialize_SOURCE_DIR}/spatialize/include
)

# If you want to add any link directories you can add them here
link_directories (
  ${Spatialize_BINARY_DIR}
)

############################################################
#OS Specific flags should go here
############################################################

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++11")
  set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
    find_library(COCOA_LIB Cocoa)
    find_library(IOKIT_LIB IOKit)
    find_library(CORE_FOUNDATION_FRAMEWORK CoreFoundation)
    find_library(CORE_VIDEO_FRAMEWORK CoreVideo)
    set(LIBS_ALL ${LIBS_ALL} ${COCOA_LIB} ${IOKIT_LIB} ${CORE_FOUNDATION_FRAMEWORK} ${CORE_VIDEO_FRAMEWORK})
    message(STATUS "${CORE_VIDEO_FRAMEWORK}")

endif()

if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  # Linux specific code
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11") 
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")
	set(Lib_Config "none")
	set(MinVR_LIBS)
	FOREACH (LIB ${MinVR_LIBRARIES})
	  if("${LIB}" STREQUAL "debug" OR "${LIB}" STREQUAL "optimized")
	    set(Lib_Config ${LIB})
	  else()
	    list(APPEND MinVR_LIBS ${LIB})
	    if("${Lib_Config}" STREQUAL "debug" OR "${Lib_Config}" STREQUAL "optimized")
	      list(APPEND MinVR_LIBS ${Lib_Config})
	    endif()
	    set(Lib_Config none)
	  endif()
	ENDFOREACH(LIB)
	LIST(REVERSE MinVR_LIBS)

	set(MinVR_LIBRARIES)

	FOREACH (LIB ${MinVR_LIBS})
	  list(APPEND MinVR_LIBRARIES ${LIB})
	ENDFOREACH(LIB)	

	find_package(Threads)
	find_package(X11)
	set(LIBS_ALL ${LIBS_ALL} ${CMAKE_THREAD_LIBS_INIT} rt Xrandr Xxf86vm Xi m dl ${X11_LIBRARIES})
endif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  # Windows specific code

endif (${CMAKE_SYSTEM_NAME} MATCHES "Windows")

if (MSVC)
	# Windows specific code
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /MP")

endif (MSVC)

#------------------------------------------
# Download dependencies
#------------------------------------------
if (BUILD_DEPENDENCIES)
  set(assimp_checkout_Dir ${CMAKE_SOURCE_DIR}/dependencies/assimp)
  make_directory(${assimp_checkout_Dir})

  set(soil_dl_Dir ${CMAKE_SOURCE_DIR}/dependencies/SOIL)
  make_directory(${soil_dl_Dir})
  
  include(ExternalProject)
endif()
set(assimp_PREFIX "${assimp_checkout_Dir}")
set(assimp_INSTALL_DIR "${Spatialize_INSTALL_PREFIX}/assimp")

set(soil_PREFIX "${soil_dl_Dir}")
set(soil_INSTALL_DIR "${Spatialize_INSTALL_PREFIX}/SOIL")

if (BUILD_DEPENDENCIES)
  set(assimp_CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${assimp_INSTALL_DIR} -DBUILD_SHARED_LIBS=OFF -DASSIMP_BUILD_ASSIMP_TOOLS=OFF -DASSIMP_BUILD_SAMPLES=OFF -DASSIMP_ENABLE_BOOST_WORKAROUND=ON -DASSIMP_BUILD_TESTS=OFF )
  set(assimp_DIR "${assimp_INSTALL_DIR}")
  set(soil_DIR "${soil_INSTALL_DIR}")

  if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
		set(assimp_CMAKE_ARGS ${assimp_CMAKE_ARGS} -DCMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD=c++11 -DCMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY=libc++)
   endif()

   if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
		set(GIT_EXECUTABLE "C:/Program Files (x86)/Git/bin/git.exe")
   endif (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
   
   ExternalProject_add(assimp
		PREFIX ${assimp_PREFIX}
		GIT_REPOSITORY https://github.com/ivlab/assimp.git
		GIT_TAG master
		INSTALL_DIR ${assimp_INSTALL_DIR}
		CMAKE_ARGS ${assimp_CMAKE_ARGS}
		UPDATE_COMMAND ""
   )

   set_property(TARGET assimp PROPERTY FOLDER "Dependencies")

   ExternalProject_add(SOIL
		DEPENDS assimp		
		PREFIX ${soil_PREFIX}
		URL http://www.lonesock.net/files/soil.zip
		CONFIGURE_COMMAND "" #mkdir -p ${soil_PREFIX}/src/SOIL/projects/makefile/obj
		BINARY_DIR "${CMAKE_SOURCE_DIR}/dependencies/SOIL_makefile"		
		BUILD_COMMAND make
		INSTALL_DIR ${soil_INSTALL_DIR}
		INSTALL_COMMAND make install
		UPDATE_COMMAND ""
		PATCH_COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/dependencies/SOIL/obj
   )

   set_property(TARGET SOIL PROPERTY FOLDER "Dependencies")

endif()

#find_package(ZLIB)
#INCLUDE_DIRECTORIES(${ZLIB_INCLUDE_DIR})

set(ASSIMP_INCLUDE_DIR ${assimp_INSTALL_DIR}/include CACHE INTERNAL "Directory of assimp header files")
set(SOIL_INCLUDE_DIR ${soil_INSTALL_DIR}/include CACHE INTERNAL "Directory of SOIL header files")
if(MSVC)
	set(ASSIMP_LIBRARY ${assimp_INSTALL_DIR}/lib/assimp.lib CACHE INTERNAL "assimp lib file")
	set(SOIL_LIBRARY ${soil_INSTALL_DIR}/lib/SOIL.lib CACHE INTERNAL "SOIL lib file")
else()
	set(ASSIMP_LIBRARY ${assimp_INSTALL_DIR}/lib/libassimp.a CACHE INTERNAL "assimp lib file")
	set(SOIL_LIBRARY ${soil_INSTALL_DIR}/lib/libSOIL.a CACHE INTERNAL "SOIL lib file")
endif()	
find_package(ZLIB)
set(LIBASSIMP_LIBRARIES ${ASSIMP_LIBRARY} ${ZLIB_LIBRARIES})

include_directories(${ASSIMP_INCLUDE_DIR})
include_directories(${SOIL_INCLUDE_DIR})

############################################################
# Add POSTFIX info
############################################################

set(CMAKE_DEBUG_POSTFIX "d")
set(CMAKE_RELEASE_POSTFIX "")
set(CMAKE_RELWITHDEBINFO_POSTFIX "rd")
set(CMAKE_MINSIZEREL_POSTFIX "s")

#set the build postfix extension according to the current configuration
if (CMAKE_BUILD_TYPE MATCHES "Release")
  set(CMAKE_BUILD_POSTFIX "${CMAKE_RELEASE_POSTFIX}")
elseif (CMAKE_BUILD_TYPE MATCHES "MinSizeRel")
  set(CMAKE_BUILD_POSTFIX "${CMAKE_MINSIZEREL_POSTFIX}")
elseif (CMAKE_BUILD_TYPE MATCHES "RelWithDebInfo")
  set(CMAKE_BUILD_POSTFIX "${CMAKE_RELWITHDEBINFO_POSTFIX}")
elseif (CMAKE_BUILD_TYPE MATCHES "Debug")
  set(CMAKE_BUILD_POSTFIX "${CMAKE_DEBUG_POSTFIX}")
else()
  set(CMAKE_BUILD_POSTFIX "")
endif()

############################################################
#Finally add all the targets here
############################################################

#First an example of executable target
add_executable(spatialize ${HEADERFILES} ${SOURCEFILES})
#All of libs should be added here
#If its a debug-only lib specify it as "debug <libtoadd>"
#If its a opt-only lib specify it as "optimized <libtoadd>"
#<libtoadd> should either be a full path to the lib, or the OS
#indepdent way it would appear in the command line (i.e. -l<libtoadd>)
#If the second is way is used you need to sure the directory the lib is
#in will be found
target_link_libraries (spatialize ${MinVR_LIBRARIES} ${LIBASSIMP_LIBRARIES} ${SOIL_LIBRARY} ${LIBS_DEBUG} ${LIBS_OPT} ${LIBS_ALL})

#Second an example of a library target
#It should default to making a static library
add_library(spatializevr ${HEADERFILES} ${SOURCEFILES})

#You can also add subprojects that are in subdirectories
#These subdirectories must contain their own CMakeLists.txt
#add_subdirectory (mysubproject)

install(DIRECTORY spatialize/include/ DESTINATION include)

install( TARGETS spatializevr spatialize
         LIBRARY DESTINATION lib
         ARCHIVE DESTINATION lib
         RUNTIME DESTINATION bin)
