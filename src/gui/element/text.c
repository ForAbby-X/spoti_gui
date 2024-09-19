
#include "gui/container.h"
#include "gui/methodes.h"
#include <string.h>
#include "random.h"

#include "engine.h"

int _gui_elem_text_initialiser(gui_element *element, void *arg)
{
	gui_element_text *element_text =  &element->element_text;


	if (arg == NULL)
		return (0);

	element_text->text = strdup(arg); // should be text
	if (element_text->text == NULL)
		return (1);
	element_text->text_length = strlen(arg);

	element->size = (v2ui){element_text->text_length * 7 + 5, 7 + 5};
	
	element->options = 0;
	gui_element_add_options(element, GUI_ELEM_OPT_VISIBLE | GUI_ELEM_OPT_SELECTABLE);
	
	return (0);
}

int _gui_elem_text_updater(gui_container *container, gui_element *element, v2ui pos, void *arg)
{
	t_engine *eng = (t_engine *)arg;

	if (element->element_text.text)
		ft_put_text(eng, pos + (t_v2i){2, 2}, element->element_text.text, 1);

	return (0);
}

void _gui_elem_text_destroyer(gui_element *element)
{
	free(element->element_text.text);
}
