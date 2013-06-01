#
# This file is part of the CMaNGOS Project. See AUTHORS file for Copyright information
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#

cmake_minimum_required(VERSION 2.8)

project(MaNGOS)
set(MANGOS_VERSION 0.17)

set(CMAKE_MODULE_PATH
  ${CMAKE_MODULE_PATH}
  ${CMAKE_SOURCE_DIR}/cmake
)

# define all options here
option(DEBUG                "Debug mode"                            OFF)
option(TBB_USE_EXTERNAL     "Use external TBB"                      OFF)
option(USE_STD_MALLOC       "Use standard malloc instead of TBB"    OFF)
option(ACE_USE_EXTERNAL     "Use external ACE"                      OFF)
if(PCHSupport_FOUND AND WIN32) # TODO: why only enable it on windows by default?
  option(PCH                "Use precompiled headers"               ON)
else()
  option(PCH                "Use precompiled headers"               OFF)
endif()
# TODO: options that should be checked/created:
#option(CLI                  "With CLI"                              ON)
#option(RA                   "With Remote Access"                    OFF)
#option(SQL                  "Copy SQL files"                        OFF)
#option(TOOLS                "Build tools"                           OFF)

# Output description of this script
message("")
message(
  "This script builds the MaNGOS server.
  Options that can be used in order to configure the process:
    CMAKE_INSTALL_PREFIX    Path where the server should be installed to
    PCH                     Use precompiled headers
    DEBUG                   Debug mode
    TBB_USE_EXTERNAL        Use external TBB
    USE_STD_MALLOC          Use standard malloc instead of TBB
    ACE_USE_EXTERNAL        Use external ACE
  To set an option simply type -D<OPTION>=<VALUE> after 'cmake <srcs>'.
  Also, you can specify the generator with -G. see 'cmake --help' for more details
  For example: cmake .. -DDEBUG=1 -DCMAKE_INSTALL_PREFIX=/opt/mangos"
)
message("")

# Force out-of-source build
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message(FATAL_ERROR
    "This project requires an out of source build. Remove the file 'CMakeCache.txt' found in this directory before continuing, create a separate build directory and run 'cmake [options] <srcs>' from there."
  )
endif()

# TODO: allow other compilers under windows in the future
if(WIN32 AND NOT MSVC)
  message(FATAL_ERROR
    "Under Windows other compiler than Microsoft Visual Studio are not supported."
  )
endif()

# TODO: remove this in the future! it has only been added to make the switch easier for end users
if(PREFIX)
  message(FATAL_ERROR "The parameter PREFIX has been removed. Please re-run CMake and use CMAKE_INSTALL_PREFIX instead to define your installation location!")
endif()





# Find needed packages and if necessery abort if something important is missing
unset(ACE_INCLUDE_DIR CACHE)
unset(ACE_LIBRARIES CACHE)
unset(ACE_LIBRARIES_DIR CACHE)
unset(ACE_INCLUDE_DIR)
unset(ACE_LIBRARIES)
unset(ACE_LIBRARIES_DIR)
if(ACE_USE_EXTERNAL)
  find_package(ACE)
  if(NOT ACE_FOUND)
    message(FATAL_ERROR
      "This project requires ACE installed when ACE_USE_EXTERNAL is set. Please download the ACE Micro Release Kit from http://download.dre.vanderbilt.edu/ and install it. If this script didn't find ACE and it was correctly installed please set ACE_ROOT to the correct path."
    )
  endif()
  if(EXISTS ${ACE_INCLUDE_DIR}/ace/Stack_Trace.h)
    set(HAVE_ACE_STACK_TRACE_H ON) # config.h.cmake
  endif()
else()
  include(cmake/ImportACE.cmake)
endif()


add_subdirectory(src)
# if(SQL)
#   add_subdirectory(sql)
# endif()
