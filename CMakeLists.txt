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
target_link_directories(${MAIN_PROG}
	PUBLIC lib
	PUBLIC engine
	PUBLIC engine/minilibx-linux
	)
target_link_libraries(${MAIN_PROG} m vector Xext X11 Xfixes engine)
target_include_directories(${MAIN_PROG}
	PUBLIC inc/
	PUBLIC lib/inc/
	PUBLIC engine/inc
	)
target_sources(${MAIN_PROG}
	PUBLIC src/vec2f_test.c

	PUBLIC inc/random.h
	PUBLIC src/random.c

	PUBLIC inc/gui/container.h
	PUBLIC src/gui/container.c

	PUBLIC inc/gui/element.h
	PUBLIC src/gui/element.c
	PUBLIC inc/gui/methodes.h
	PUBLIC src/gui/element/none.c
	PUBLIC src/gui/element/text.c

	PUBLIC inc/math_vec/types.h
	PUBLIC inc/math_vec/methodes.h
	)
