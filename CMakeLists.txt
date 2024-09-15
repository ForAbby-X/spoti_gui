cmake_minimum_required(VERSION 3.15)
cmake_policy(VERSION 3.15)

project(spoti_gui)

set(BUILD_SHARED_LIBS FALSE)
set(CMAKE_C_STANDARD 99)

# Linux or Windows
# cmake_policy(SET CMP0135 NEW) # This cmake_policy avoids warning by cmake when we fetch contents based on URL

# add_link_options()
# add_compile_options(-Ofast)

# set(LIB_VECTOR lib_vector)
# add_library(${LIB_VECTOR})
# target_include_directories(${LIB_VECTOR} PUBLIC lib/inc/)
# target_sources(${MAIN_PROG} PUBLIC lib/libvector.a)

set(MAIN_PROG gui_test.out)
add_executable(${MAIN_PROG})
target_link_libraries(${MAIN_PROG} m)
target_include_directories(${MAIN_PROG} PUBLIC
	lib/inc/
	inc/
	)
target_sources(${MAIN_PROG} PUBLIC
	src/vec2f_test.c
	
	inc/gui/container.h
	inc/math_vec/types.h
	inc/math_vec/methodes.h

	lib/libvector.a
	)
