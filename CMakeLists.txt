cmake_minimum_required(VERSION 3.4 FATAL_ERROR)
project(xwm)

include(cmake/XEPHYR.cmake)

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

include_directories(include)

set(PROJECT_INCLUDES
    ${PROJECT_SOURCE_DIR}/include/
    ${PROJECT_SOURCE_DIR}/lib/include
)

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

Find_Xephyr()
if(${XEPHYR_FOUND})
    add_custom_target("run"
        COMMENT "Running Program"
        DEPENDS ${PROJECT_NAME}
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        COMMAND DISPLAY=:1
        COMMAND xinit  ./xinitrc -- Xephyr :100 -ac -screen 800x600 -host-cursor
    )
else()
    message(FATAL ERROR "Xephyr/Xephyr-Server is not installed and is needed to test the wm!")
endif()
