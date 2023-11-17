
cmake_minimum_required(VERSION 3.19)
project(federate__c LANGUAGES C)

if(CMAKE_BUILD_TYPE STREQUAL "Test")
  set(CMAKE_BUILD_TYPE "Debug")
  if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
    find_program(LCOV_BIN lcov)
    if(LCOV_BIN MATCHES "lcov$")
      set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage -fprofile-arcs -ftest-coverage")
    else()
      message("Not producing code coverage information since lcov was not found")
    endif()
  else()
    message("Not producing code coverage information since the selected compiler is no gcc")
  endif()
endif()
# Require C11
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Require C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

cmake_policy(SET CMP0023 OLD)  # This causes deprecation warnings

set(DEFAULT_BUILD_TYPE Debug)
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE ${DEFAULT_BUILD_TYPE} CACHE STRING "Choose the type of build." FORCE)
endif()

# do not print install messages
set(CMAKE_INSTALL_MESSAGE NEVER)


# Set default values for build parameters
if (NOT DEFINED LF_REACTION_GRAPH_BREADTH)
    set(LF_REACTION_GRAPH_BREADTH 2)
endif()
if (NOT DEFINED EXECUTABLE_PREAMBLE)
    set(EXECUTABLE_PREAMBLE TRUE)
endif()
if (NOT DEFINED NUMBER_OF_FEDERATES)
    set(NUMBER_OF_FEDERATES 3)
endif()
if (NOT DEFINED FEDERATED)
    set(FEDERATED TRUE)
endif()
if (NOT DEFINED FEDERATED_CENTRALIZED)
    set(FEDERATED_CENTRALIZED TRUE)
endif()
if (NOT DEFINED LOG_LEVEL)
    set(LOG_LEVEL 2)
endif()
add_subdirectory(core)

set(LF_MAIN_TARGET federate__c)

# Declare a new executable target and list all its sources
add_executable(
    ${LF_MAIN_TARGET}
    lib/schedule.c
    _federate__c_main.c
    _count.c
    _networksender_0null.c
    federate__c.c
)

find_library(MATH_LIBRARY m)
if(MATH_LIBRARY)
  target_link_libraries(${LF_MAIN_TARGET} PUBLIC ${MATH_LIBRARY})
endif()
target_link_libraries(${LF_MAIN_TARGET} PRIVATE core)
target_include_directories(${LF_MAIN_TARGET} PUBLIC .)
target_include_directories(${LF_MAIN_TARGET} PUBLIC include/)
target_include_directories(${LF_MAIN_TARGET} PUBLIC include/api)
target_include_directories(${LF_MAIN_TARGET} PUBLIC include/core)
target_include_directories(${LF_MAIN_TARGET} PUBLIC include/core/platform)
target_include_directories(${LF_MAIN_TARGET} PUBLIC include/core/modal_models)
target_include_directories(${LF_MAIN_TARGET} PUBLIC include/core/utils)
# Find threads and link to it
find_package(Threads REQUIRED)
target_link_libraries(${LF_MAIN_TARGET} PRIVATE Threads::Threads)

# Set the number of workers to enable threading/tracing
target_compile_definitions(${LF_MAIN_TARGET} PUBLIC NUMBER_OF_WORKERS=0)



    install(
        TARGETS ${LF_MAIN_TARGET}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )

include("federate__c_extension.cmake")



