
#ifndef GUI_ELEMENT_H
#define GUI_ELEMENT_H

#include <stdint.h>
#include "gui/container_struct.h"
#include "math_vec/types.h"
#include "vector.h"
#include "engine.h"

#define min(A, B) ((A) < (B) ? (A) : (B))
#define max(A, B) ((A) > (B) ? (A) : (B))

/*
 *	This is where the pain begins, let's see how much time this is going to take.
 *
 *	Alan De Freitas - 23:23 Sep 15 2024
 */

/*
 *	Good progress, i did the element methodes structure and the container 'api',
 *	 now i am implementing the graphics.
 *
 *	That means a lot of fidling around to make the structure container->element
 *	 work while being still digest (hope so atleast...).
 *
 *	Alan De Freitas - 23:49 Sep 18 2024
 */

/* forward declare to break circular include */
// typedef struct gui_container gui_container;

typedef struct gui_element			gui_element;
typedef uint16_t					gui_element_options; // not the directly enum to reduce memory usage

typedef uint16_t					gui_element_type; // not the directly enum to reduce memory usage
typedef struct gui_element_text		gui_element_text;
typedef struct gui_element_color	gui_element_color;
/* typedef struct gui_element_check	gui_element_check; */
/* typedef struct gui_element_button	gui_element_button; */
/* typedef struct gui_element_list		gui_element_list; */
/* typedef struct gui_element_slider	gui_element_slider; */
/* typedef struct gui_element_image	gui_element_image; */
/* typedef struct gui_element_input	gui_element_input; */

/* Generic Gui Element */

/* Return the element's uuid on success, otherwise an integer value of 0. */
/* A va_list here wouldn't hurt, it will make everything more polyvalent and smoother to use, but the manual will be necessary. */
uint16_t	gui_element_init(gui_element *element, gui_element_type type, void *arg);
int			gui_element_update(gui_container *container, gui_element *element, void *arg);
void		gui_element_destroy(gui_element *element);

/* Return the modified element option flags.
 * @note Later i should make it return an error statuts...
 */
gui_element_options	gui_element_add_options(gui_element *gui_element, gui_element_options options);

/* Return the modified element option flags.
 * @note Later i should make it return an error statuts...
 */
gui_element_options	gui_element_rem_options(gui_element *gui_element, gui_element_options options);


enum gui_element_type
{
	GUI_ELEM_NONE = 0,
	GUI_ELEM_TEXT,
	GUI_ELEM_CHECK,
	GUI_ELEM_BUTTON,
	GUI_ELEM_LIST,
	GUI_ELEM_SLIDER,
	GUI_ELEM_IMAGE,
	GUI_ELEM_INPUT,

	GUI_ELEM_MAX
};

enum gui_element_options
{
	GUI_ELEM_OPT_SELECTABLE				= 1 << 0, // is the gui movable ?
	GUI_ELEM_OPT_HOVERABLE				= 1 << 1, // resizing from the lower right corner (or every edges ?)
	GUI_ELEM_OPT_IS_HOVERED				= 1 << 2, // is the element selected
	GUI_ELEM_OPT_BACKGROUND_VISIBLE		= 1 << 3, // is the container background visible ? if yes only see the title bar (prob. tool bar)
	GUI_ELEM_OPT_VISIBLE				= 1 << 4, // for empty void container (probably used for docking simplicity)

	GUI_ELEM_OPT_LAST // here to compile error if too many options
};

struct gui_element_text
{
	char		*text;
	size_t		text_length;
};

struct gui_element_color
{
	t_color		color;
};

// with sui 32 bytes, with ui 40
struct gui_element
{
	// uint16_t			group: 4; // Just thinking for a bit... or four... (funny !)
	uint16_t			uuid;//: 12;

	gui_element_type	type;
	v2ui				size;
	gui_element_options	options;

	union
	{
		gui_element_text	element_text;
		gui_element_color	element_color;
		// insert implemented elements here...
	};
};



#endif
