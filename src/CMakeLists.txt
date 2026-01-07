cmake_minimum_required(VERSION 3.10)
project(ds_finder C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_COMPILER gcc)
set(CMAKE_C_FLAGS "-Wall -Wextra -Werror")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

include_directories(includes libs/libft)

file(GLOB LIBFT_SRCS "libs/libft/*.c")

set(SRCS
    core/main.c
    core/utils/parser.c
    core/utils/time.c
    core/utils/logger.c
    core/struct/graph.c
    core/struct/covers.c
    core/solvers/solver.c
    core/solvers/greedy.c
    core/solvers/periphery_greedy.c
    core/solvers/optimizer.c
    core/solvers/prune.c
    core/solvers/swap.c
    core/solvers/sorter.c
    ${LIBFT_SRCS}
)

add_executable(ds_finder ${SRCS})

if(CMAKE_BUILD_TYPE STREQUAL "Release")
	add_definitions(-DDEBUG=0)
	target_compile_options(ds_finder PRIVATE -O3 -flto)
	target_link_options(ds_finder PRIVATE -flto)
elseif(CMAKE_BUILD_TYPE STREQUAL "Static")
	add_definitions(-DDEBUG=0)
    target_compile_options(ds_finder PRIVATE -O3 -flto)
    target_link_options(ds_finder PRIVATE -static -flto)
else()
    target_compile_options(ds_finder PRIVATE -g3)
endif()

if(NOT FILENO)
	set(FILENO "001")
endif()
if(NOT REDIN)
	set(REDIN "tmp/instances/heuristic_${FILENO}.gr")
endif()
if(NOT REDOUT)
	set(REDOUT "/dev/stdout")
endif()

string(STRIP "${REDIN}" INPUT)
string(STRIP "${REDOUT}" OUTPUT)

add_custom_target(test
    COMMAND sh -c "./ds_finder < ${INPUT} > ${OUTPUT}"
    DEPENDS ds_finder
	COMMENT "Running test with input: ${INPUT} and output: ${OUTPUT}"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    VERBATIM
)

add_custom_target(leaks
    COMMAND sh -c "valgrind --leak-check=full --show-leak-kinds=all ./ds_finder < ${INPUT} > ${OUTPUT}"
    DEPENDS ds_finder
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    VERBATIM
)

add_custom_target(binary_solution
	COMMAND rm -f ds_finder
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target unify
	COMMAND gcc -static -O3 -flto ds_finder.c -o ds_finder
	COMMAND rm -f ds_finder.c
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

add_custom_target(source_solution
    COMMAND tar -czf ds_finder.tgz CMakeLists.txt includes libs core
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

add_custom_target(unify
    COMMAND sh -c "echo '/* Unified Source - DS_FINDER */' > ds_finder.c"
    COMMAND sh -c "sed '/# *include \"/d' includes/types.h >> ds_finder.c; echo >> ds_finder.c"
    COMMAND sh -c "find includes libs/libft -name '*.h' -not -name 'types.h' | LC_ALL=C sort | xargs -I {} sh -c 'sed \"/# *include \\\"/d\" {}; echo' >> ds_finder.c"
    COMMAND sh -c "find libs/libft core/struct core/utils core/solvers -name '*.c' -not -name 'main.c' | LC_ALL=C sort | xargs -I {} sh -c 'sed \"/# *include \\\"/d\" {}; echo' >> ds_finder.c"
    COMMAND sh -c "sed '/# *include \"/d' core/main.c >> ds_finder.c"
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Unifying all sources into ds_finder.c"
    VERBATIM
)

add_custom_target(fclean
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target clean
    COMMAND rm -f ds_finder.tgz
    COMMAND rm -f ds_finder.c
	COMMAND find ${CMAKE_SOURCE_DIR} -iwholename '*cmake*' -not -name CMakeLists.txt -delete
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

add_custom_target(re
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target clean
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target ds_finder
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Rebuilding ds_finder..."
)
