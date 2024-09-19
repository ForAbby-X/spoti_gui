
#include "gui/element.h"
#include "gui/methodes.h"

int _gui_elem_none_initialiser(gui_element *element, void *arg)
{
	(void)element;
	(void)arg;
	return (0);
}

int _gui_elem_none_updater(gui_container *container, gui_element *element, v2ui pos, void *arg)
{
	(void)container;
	(void)element;
	(void)arg;
	return (0);
}

void _gui_elem_none_destroyer(gui_element *element)
{
	(void)element;
}
