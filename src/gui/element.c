
#include "gui/element.h"

int			gui_element_init(gui_element *element, uint16_t type)
{
	element->id = my_rand_u32() & 0xFFFF;
	element->type = 
}

void		gui_element_destroy(gui_element *element)
{

}


void		gui_element_display(gui_element *element)
{

}

void		gui_element_update(gui_element *element)
{

}
