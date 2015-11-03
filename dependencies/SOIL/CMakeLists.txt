#
# Copyright Regents of the University of Minnesota, 2014.  This software is released under the following license: http://opensource.org/licenses/GPL-2.0.
# Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
#
# Code author(s):
# 		Dan Orban (dtorban)
#

cmake_minimum_required (VERSION 2.8)
project (SOIL)

#aux_source_directory(${CMAKE_SOURCE_DIR}/src SOURCEFILES)

set(SOURCEFILES src/image_DXT.c src/image_helper.c src/SOIL.c src/stb_image_aug.c)

set (CMAKE_VERBOSE_MAKEFILE TRUE)

# Used for compiling in subdirectories of the project
include_directories (
  .
  src
)


############################################################
#OS Specific flags should go here
############################################################

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++11")
  set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
  #set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++11 -stdlib=libc++")
endif()

if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  # Linux specific code
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -std=c++11") 
  add_definitions("-DOSC_HOST_LITTLE_ENDIAN")
endif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  # Windows specific code
endif (${CMAKE_SYSTEM_NAME} MATCHES "Windows")

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

add_library(SOIL ${SOURCEFILES})

#------------------------------------------
# Install Target
#------------------------------------------

install( TARGETS ${PROJECT_NAME}
         LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
         ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
         RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/src/ DESTINATION "${CMAKE_INSTALL_PREFIX}/include")
