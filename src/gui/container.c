
#include "gui/container.h"
#include "gui/element.h"
#include "random.h"
#include <memory.h>
#include "engine.h"

/* gui container init/destroy */

uint16_t gui_container_init(gui_container *gui_container)
{
	gui_container->uuid = my_rand_u32() & 0xFFFF; // ... just removed the overkill checksum *funny*

	gui_container->position = (v2ui){10, 10};
	gui_container->layer = 50;
	gui_container->size = (v2ui){600, 250};

	gui_container->scroll_value = 0.0f;

	gui_container->is_clicked = 0;
	gui_container->click_offset = (v2ui){0, 0};

	memcpy(gui_container->title, "Gui Container", 14);
	gui_container_add_options(gui_container, GUI_CONT_BASE_OPTIONS);
	
	gui_container->surface = 0; // todo: change it for real surface.

	gui_container->childs = vector_create(sizeof(gui_element));
	if (gui_container->childs.data == NULL)
		return (0);
	
	return (gui_container->uuid);
}

void gui_container_destroy(gui_container *gui_container)
{
	vector_for_each(&gui_container->childs, (void (*)(t_object object))gui_element_destroy); // cast to shut warning
	vector_destroy(&gui_container->childs);
}

/* gui container setter/getter */

void gui_container_set_title(gui_container *gui_container, char *title)
{
	if (title == NULL)
		memset(gui_container->title, 0, GUI_TITLE_MAX_LEN);
	else
		strncpy(gui_container->title, title, GUI_TITLE_MAX_LEN);
}

gui_container_options gui_container_add_options(gui_container *gui_container, gui_container_options options)
{
	/*
	 *	Some options will need to change some things in the container later.
	 *	For example allocate memory for a specifique thing or resize an image...
	 */
	gui_container->options |= options;

	return (gui_container->options);
}

gui_container_options gui_container_rem_options(gui_container *gui_container, gui_container_options options)
{
	/*
	 *	Some options will need to change some things in the container later.
	 *	For example allocate memory for a specifique thing or resize an image...
	 */
	gui_container->options &= ~options;

	return (gui_container->options);
}

uint16_t gui_container_add_element(gui_container *gui_container, gui_element_type type, void *arg)
{
	gui_element element = {0};

	int error = gui_element_init(&element, type, arg);
	if (error == 0)
		return (0);
	
	if (vector_addback(&gui_container->childs, &element) == NULL)
	{
		gui_element_destroy(&element);
		return (0);
	}

	return (element.uuid);
}

void gui_container_rem_element(gui_container *gui_container, uint16_t uuid)
{
	for (int i = 0; i < gui_container->childs.size; ++i)
	{
		gui_element *elem = vector_get(&gui_container->childs, i);
		if (elem->uuid == uuid)
		{
			gui_element_destroy(elem);
			vector_erase(&gui_container->childs, i);
			break ;
		}
	}
}

int gui_container_update(gui_container *container, void *arg)
{
	t_engine *eng = (t_engine *)arg;
	v2ui mouse_pos = {eng->mouse_x, eng->mouse_y};

	if (ft_mouse(eng, 1).released)
		container->is_clicked = 0;

	/* handle title bar and moving container */
	if (container->options & GUI_CONT_OPT_TITLE_BAR_VISIBLE)
	{
		if (container->options & GUI_CONT_OPT_MOVABLE)
		{
			if (ft_mouse(eng, 1).pressed
				&& mouse_pos[_x] >= 0 && mouse_pos[_x] < container->position[_x] + container->size[_x]
				&& mouse_pos[_y] >= 0 && mouse_pos[_y] < container->position[_y] + 20)
			{
				container->is_clicked = 1;
				container->click_offset = container->position - mouse_pos;
			}
			if (container->is_clicked == 1)
			{
				container->position = mouse_pos + container->click_offset;
				container->position[_x] = max(container->position[_x], 0);
				container->position[_y] = max(container->position[_y], 0);
				container->position[_x] = min(container->position[_x] + container->size[_x], eng->screen->size[_x]) - container->size[_x];
				container->position[_y] = min(container->position[_y] + 20, eng->screen->size[_y]) - 20;
			}
		}
	}
	
	v2ui title_h_off = {0};
	if (container->options & GUI_CONT_OPT_TITLE_BAR_VISIBLE)
	{
		title_h_off[_y] = 20;
		v2ui title_bar_dim = {container->size[0], 20};
		ft_rect(eng, container->position, title_bar_dim, (t_color){0x595b4d}); // title background color
		ft_put_text(eng, container->position + (v2ui){5, 5}, container->title, 1);
	}

	/* handle background */
	if (container->options & GUI_CONT_OPT_BACKGROUND_VISIBLE)
		ft_rect(eng, container->position + title_h_off, container->size - title_h_off, (t_color){0x7a8877}); // background color

	/* handle resizing */
	v2si resize_tick_dim = {10, 10};
	v2ui resize_tick_pos = container->position + container->size - resize_tick_dim;
	if (container->options & GUI_CONT_OPT_RESIZABLE)
	{
		if (mouse_pos[_x] >= resize_tick_pos[_x] && mouse_pos[_x] < resize_tick_pos[_x] + resize_tick_dim[_x]
			&& mouse_pos[_y] >= resize_tick_pos[_y] && mouse_pos[_y] < resize_tick_pos[_y] + resize_tick_dim[_y])
		{
			ft_rect(eng, resize_tick_pos, resize_tick_dim, (t_color){0x595b4d}); // resize mark
			if (ft_mouse(eng, 1).pressed)
			{
				container->is_clicked = 2;
				container->click_offset = mouse_pos - container->size;
			}
		}
		if (container->is_clicked == 2)
		{
			v2si other_size = mouse_pos - container->click_offset;
			container->size[_x] = max(other_size[_x], 300);
			container->size[_y] = max(other_size[_y], 130);
		}
	}

	if (container->is_clicked)
		ft_circle(eng, mouse_pos, 5, (t_color){0xc1864c});

	container->base_element_pos_y = 0; // @todo: move this to gui_container_render once it will be good
	container->min_element_pos = (v2ui){0, 0}; // @todo: move this to gui_container_render once it will be good
	for (int i = 0; i < container->childs.size; ++i)
	{
		gui_element *elem = vector_get(&container->childs, i);
		int error = gui_element_update(container, elem, arg);
		if (error)
			return (error);
	}

	return (0);
}

v2ui gui_container_element_offset(gui_container *container, gui_element *element)
{
	v2ui local_offset = {0, 0};

	if (container->options & GUI_CONT_OPT_TITLE_BAR_VISIBLE)
		local_offset[_y] += 20; // title's height

	local_offset += (v2ui){5, 5}; // container's padding

	if (container->options & GUI_CONT_OPT_GROW_ROW
		&& local_offset[_x] + container->min_element_pos[_x] + element->size[_x] < container->size[_x] - 5)
	{
		local_offset[_x] += container->min_element_pos[_x];
		local_offset[_y] += container->base_element_pos_y;
		container->min_element_pos[_x] += element->size[_x] + 2; // element size and padding
		container->min_element_pos[_y] = max(container->min_element_pos[_y], container->base_element_pos_y + element->size[_y] + 2);
	}
	else
	{
		container->base_element_pos_y = container->min_element_pos[_y];
		local_offset[_y] += container->min_element_pos[_y];
		container->min_element_pos[_x] = element->size[_x] + 2;
		container->min_element_pos[_y] += element->size[_y] + 2; // element size and padding
	}

	return (container->position + local_offset);
}
