
#ifndef GUI_CONTAINER_H
#define GUI_CONTAINER_H

#include <stdint.h>
#include "math_vec/types.h"
#include "vector.h"

#define GUI_TITLE_MAX_LEN 32

#define GUI_BASE_OPTIONS  GUI_IS_MOVABLE \
						| GUI_IS_RESIZABLE \
						| GUI_IS_TITLE_BAR_VISIBLE \
						| GUI_IS_BACKGROUND_VISIBLE \
						| GUI_IS_INTERACTIVE

typedef int						gui_surface; // temporary place holder for compiling
typedef struct gui_container	gui_container;
typedef uint32_t				gui_options;

int		gui_container_init(gui_container *gui_container);
void	gui_container_destroy(gui_container *gui_container);

void	gui_container_set_title(gui_container *gui_container, char *title);
int		gui_container_set_options(gui_container *gui_container, gui_options options);
int		gui_container_get_options(gui_container *gui_container, gui_options options);

struct gui_container
{
	uint16_t	id;
	
	v2ui		position;
	uint16_t	layer;
	v2ui		size;
	
	char 		title[GUI_TITLE_MAX_LEN];
	gui_options	options;
	
	gui_surface	surface; // to store the texture of the container
	t_vector	childs;	// vector(gui_container *child) or vector(uint16_t ids)
};

/* max options nb 32 - 1 (last option) */
enum gui_options
{
	GUI_IS_MOVABLE				= 1 << 0,
	GUI_IS_RESIZABLE			= 1 << 1,
	GUI_IS_TITLE_BAR_VISIBLE	= 1 << 2,
	GUI_IS_BACKGROUND_VISIBLE	= 1 << 3,
	GUI_IS_INTERACTIVE			= 1 << 4,

	GUI_LAST_OPTIONS
};

#endif
