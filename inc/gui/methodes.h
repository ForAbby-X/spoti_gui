
#ifndef GUI_METHODES_H
#define GUI_METHODES_H

#include "gui/element.h"

/* Text None Element */
int		_gui_elem_none_initialiser(gui_element *element, void *arg);
int		_gui_elem_none_updater(gui_container *container, gui_element *element, v2ui pos, void *arg);
void	_gui_elem_none_destroyer(gui_element *element);
/* Text Gui Element */
int		_gui_elem_text_initialiser(gui_element *element, void *arg);
int		_gui_elem_text_updater(gui_container *container, gui_element *element, v2ui pos, void *arg);
void	_gui_elem_text_destroyer(gui_element *element);

/* Gui element methodes relation map */
/* Should probably move it to the .c file, or let it here for ease to find */

struct _gui_element_methods
{
	int			(*initialiser)(gui_element *element, void *arg);
	int			(*updater)(gui_container *container, gui_element *element, v2ui pos, void *arg);
	void		(*destroyer)(gui_element *element);
};

static struct _gui_element_methods global_element_methods_table[]
= {
	[GUI_ELEM_NONE] =
	{
		.initialiser	= _gui_elem_none_initialiser,
		.updater		= _gui_elem_none_updater,
		.destroyer		= _gui_elem_none_destroyer,
	},
	[GUI_ELEM_TEXT] = 
	{
		.initialiser	= _gui_elem_text_initialiser,
		.updater		= _gui_elem_text_updater,
		.destroyer		= _gui_elem_text_destroyer,
	},
};

#endif
