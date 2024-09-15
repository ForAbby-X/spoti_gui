
#ifndef GUI_ELEMENT_H
#define GUI_ELEMENT_H

#include <stdint.h>
#include "math_vec/types.h"
#include "vector.h"

/*
 *	This is where the pain begins, let's see how much time this is going to take.
 *
 *	Alan De Freitas - 23:23 Sep 15 2024
 */

typedef struct gui_element			gui_element;
typedef struct gui_element_text		gui_element_text;
/* typedef struct gui_element_check	gui_element_check; */
/* typedef struct gui_element_button	gui_element_button; */
/* typedef struct gui_element_list		gui_element_list; */
/* typedef struct gui_element_slider	gui_element_slider; */
/* typedef struct gui_element_image	gui_element_image; */
/* typedef struct gui_element_input	gui_element_input; */

int			gui_element_init(gui_element *element, uint16_t type);
void		gui_element_destroy(gui_element *element);

void		gui_element_display(gui_element *element);
void		gui_element_update(gui_element *element);

struct gui_element
{
	uint16_t			id;
	uint16_t			type;
	union
	{
		gui_element_text	element_text;
		float				place_holder;
		// insert implemented elements here...
	};
};



struct gui_element_text
{
	char	*text;
	size_t	text_length;
	uint8_t	alignment;
};

enum gui_element_type
{
	GUI_ELEMENT_NONE = 0,
	GUI_ELEMENT_TEXT,
};

#endif
