cmake_minimum_required(VERSION 3.4 FATAL_ERROR)
project(xwm)

include(cmake/XEPHYR.cmake)

find_xephyr()
find_library(CHECK_LIBRARY NAMES check)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

set (DEBUG_FLAGS
    "-g")

set (OPT_FLAGS
    "-O0")

set (WARN_FLAGS
    "-Wall")

set(GCC_COMPILE_FLAGS
    "${DEBUG_FLAGS} ${OPT_FLAGS} ${WARN_FLAGS}")

set(CMAKE_C_FLAGS
    "${CMAKE_C_FLAGS} ${GCC_COMPILE_FLAGS}")

file(GLOB SOURCES "src/*.c")
file(GLOB LIB_SOURCES "lib/*.c")

set(PROJECT_SOURCES
    ${SOURCES}
    ${LIB_SOURCES}
)


set(PROJECT_INCLUDES
    ${PROJECT_SOURCE_DIR}/include/
    ${PROJECT_SOURCE_DIR}/lib/include
)

include_directories(${PROJECT_INCLUDES})

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
target_link_libraries(${PROJECT_NAME} "X11")

install(TARGETS ${PROJECT_NAME} DESTINATION /usr/local/bin/)

# clean target
set_property(DIRECTORY PROPERTY ADDITIONAL_CLEAN_FILES
    "${PROJECT_SOURCE_DIR}/build/CMakeFiles"
    "${PROJECT_SOURCE_DIR}/build/CMakeCache.txt"
    "${PROJECT_SOURCE_DIR}/build/Makefile"
    "${PROJECT_SOURCE_DIR}/build/cmake_install.cmake"
    "${PROJECT_SOURCE_DIR}/build/lib"
    "${PROJECT_SOURCE_DIR}/build/compile_commands.json"
)

# debug target
add_custom_target("debug"
    COMMENT "Debugging with GDB"
    DEPENDS ${PROJECT_NAME}
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    COMMAND gdb -tui bin/${PROJECT_NAME}
)

# uninstall target
add_custom_target("uninstall"
    COMMENT "Debugging with GDB"
    DEPENDS ${PROJECT_NAME}
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    COMMAND rm -f /usr/local/bin/${PROJECT_NAME}
)

if (CHECK_LIBRARY)
    message(STATUS "Check executable found")

    file(GLOB TEST_SOURCES "test/src/*.c")
    list(REMOVE_ITEM SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/main.c)

    set(TEST_PROJECT_SOURCES
        ${TEST_SOURCES}
        ${SOURCES}
        ${LIB_SOURCES}
    )

    set(TEST_PROJECT_INCLUDES
        ${PROJECT_SOURCE_DIR}/include/
        ${PROJECT_SOURCE_DIR}/test/include
        ${CHECK_INCLUDE_DIRS}
    )

    include_directories(${TEST_PROJECT_INCLUDES})
    link_directories(${CHECK_LIBRARY_DIRS})

    add_executable(test_${PROJECT_NAME} ${TEST_PROJECT_SOURCES})
    target_link_libraries(test_${PROJECT_NAME} "X11" ${CHECK_LIBRARY})

    add_custom_target(test
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/bin/TestRunner
        DEPENDS test_${PROJECT_NAME}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin
    )
else()
    message(FATAL_ERROR "Check library not found. Please install Check.")
endif()

if(${XEPHYR_FOUND})
    add_custom_target("run"
        COMMENT "Running Program"
        DEPENDS ${PROJECT_NAME}
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        COMMAND DISPLAY=:1
        COMMAND xinit  ./xinitrc -- Xephyr :100 -ac -screen 800x600 -host-cursor
    )
else()
    message(FATAL ERROR "Xephyr/Xephyr-Server not found. Please install Xephyr.")
endif()
