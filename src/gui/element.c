
#include "gui/interaction_tools.h"
#include "gui/container.h"
#include "gui/methodes.h"
#include "gui/element.h"
#include "random.h"
#include "engine.h"

uint16_t gui_element_init(gui_element *element, gui_element_type type, void *arg)
{
	element->uuid = my_rand_u32() & 0x0FFF;

	element->type = type;
	element->dim = (v2ui){70, 30};
	element->options = 0;

	if (global_element_methods_table[type].initialiser(element, arg))
		return (0);
	return (element->uuid);
}

int gui_element_update(gui_container *container, gui_element *element, void *arg)
{
	t_engine *eng = (t_engine *)arg;
	v2ui elem_pos = gui_container_element_offset(container, element);
	r2si elem_rect = {elem_pos, element->dim};
	v2si mouse_pos = {eng->mouse_x, eng->mouse_y};

	if (container->options & GUI_CONT_OPT_INTERACTIVE)
	{
		/* @todo: fix this shit Alan */
		if (element->options & GUI_ELEM_OPT_SELECTABLE)
		{
			if (vec_in_rect(mouse_pos, elem_rect))
			{
				if (!(element->options & GUI_ELEM_OPT_IS_HOVERED))
					gui_element_add_options(element, GUI_ELEM_OPT_IS_HOVERED);
			}
			else
				gui_element_rem_options(element, GUI_ELEM_OPT_IS_HOVERED);
		}

		if (element->options & GUI_ELEM_OPT_BACKGROUND_VISIBLE)
			ft_rect(eng, elem_pos, element->dim, (t_color){0x566457});
		if (element->options & GUI_ELEM_OPT_IS_HOVERED)
		{
			if (ft_mouse(eng, 1).hold)
				ft_rect(eng, elem_pos, element->dim, (t_color){0x566457 << 1});
			else
				ft_rect(eng, elem_pos, element->dim, (t_color){0x978861});
		}
	}

	int error = global_element_methods_table[element->type].updater(container, element, elem_pos, arg);

	return (error);
}

void gui_element_destroy(gui_element *element)
{
	global_element_methods_table[element->type].destroyer(element);
}

gui_element_options gui_element_add_options(gui_element *gui_element, gui_element_options options)
{
	/*
	 *	Some options will need to change some things in the element later.
	 *	For example allocate memory for a specifique thing or resize an image...
	 */
	gui_element->options |= options;

	return (gui_element->options);
}

gui_element_options gui_element_rem_options(gui_element *gui_element, gui_element_options options)
{
	/*
	 *	Some options will need to change some things in the element later.
	 *	For example allocate memory for a specifique thing or resize an image...
	 */
	gui_element->options &= ~options;

	return (gui_element->options);
}
