
#ifndef GUI_CONTAINER_STRUCT_H
#define GUI_CONTAINER_STRUCT_H

#include <stdint.h>
#include "math_vec/types.h"
#include "vector.h"

#define GUI_TITLE_MAX_LEN 32

#define GUI_CONT_BASE_OPTIONS \
						  GUI_CONT_OPT_MOVABLE \
						| GUI_CONT_OPT_RESIZABLE \
						| GUI_CONT_OPT_TITLE_BAR_VISIBLE \
						| GUI_CONT_OPT_BACKGROUND_VISIBLE \
						| GUI_CONT_OPT_INTERACTIVE \
						| GUI_CONT_OPT_VISIBLE

typedef int							gui_surface; // temporary place holder for compiling
typedef struct gui_container		gui_container;
typedef uint16_t					gui_container_options; // not the directly enum to reduce memory usage

/* max options nb 32 - 1 (last option) */
enum gui_container_options
{
	GUI_CONT_OPT_MOVABLE				= 1 << 0, // is the gui movable ?
	GUI_CONT_OPT_RESIZABLE				= 1 << 1, // resizing from the lower right corner (or every edges ?)
	GUI_CONT_OPT_TITLE_BAR_VISIBLE		= 1 << 2, // no title bar visible / interactive
	GUI_CONT_OPT_BACKGROUND_VISIBLE		= 1 << 3, // is the container background visible ? if yes only see the title bar (prob. tool bar)
	GUI_CONT_OPT_INTERACTIVE			= 1 << 4, // is the container clickable ? 
	GUI_CONT_OPT_VISIBLE				= 1 << 5, // for empty void container (probably used for docking simplicity)
	GUI_CONT_OPT_GROW_ROW				= 1 << 6, // define if the container content can grow in row

	GUI_CONT_OPT_LAST // here to compile error if too many options
};

struct gui_container
{
	uint16_t				uuid;

	v2si					position;
	uint16_t				layer;
	v2ui					size;

	float					scroll_value; // dont know if float type is good
	
	uint8_t					is_clicked;
	v2si					click_offset;
	
	uint16_t				base_element_pos_y; // work in progress...
	v2ui					min_element_pos; // work in progress...

	char 					title[GUI_TITLE_MAX_LEN];
	gui_container_options	options;
	
	gui_surface				surface; // to store the texture of the container
	t_vector				childs;	// vector(gui_container *child) or vector(uint16_t ids)
};

#endif
