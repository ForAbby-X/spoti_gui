
#include "gui/container.h"
#include "gui/element.h"
#include "random.h"

/* gui container init/destroy */

int		gui_container_init(gui_container *gui_container)
{
	gui_container->id = my_rand_u32() & 0xFFFF; // ... just removed the overkill checksum *funny*

	gui_container->position = (v2ui){10, 10};
	gui_container->layer = 50;
	gui_container->size = (v2ui){60, 25};

	memcpy(gui_container->title, "Gui Container", 14);
	gui_container->options = GUI_BASE_OPTIONS;
	
	gui_container->surface = 0; // todo: change it for real surface.

	gui_container->childs = vector_create(sizeof(gui_element));
}

void	gui_container_destroy(gui_container *gui_container)
{

}

/* gui container setter/getter */

void	gui_container_set_title(gui_container *gui_container, char *title)
{

}

int		gui_container_set_options(gui_container *gui_container, uint32_t options)
{

}

int		gui_container_get_options(gui_container *gui_container, uint32_t options)
{

}

