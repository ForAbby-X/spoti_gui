
#include "gui/interaction_tools.h"
#include "gui/container.h"
#include "gui/element.h"
#include "random.h"
#include <memory.h>
#include "engine.h"

/* gui container init/destroy */

uint16_t gui_container_init(gui_container *gui_container)
{
	gui_container->uuid = my_rand_u32() & 0xFFFF; // ... just removed the overkill checksum *funny*

	gui_container->rect.pos = (v2si){10, 10};
	gui_container->rect.dim= (v2si){600, 250};
	gui_container->layer = 50;

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
	 *	For example allocate memory for a specifique thing or dim an image...
	 */
	gui_container->options |= options;

	return (gui_container->options);
}

gui_container_options gui_container_rem_options(gui_container *gui_container, gui_container_options options)
{
	/*
	 *	Some options will need to change some things in the container later.
	 *	For example allocate memory for a specifique thing or dim an image...
	 */
	gui_container->options &= ~options;

	return (gui_container->options);
}

uint16_t gui_container_add_element(gui_container *gui_container, gui_element_type type, void *arg)
{
	gui_element element = {0};

	if (type >= GUI_ELEM_MAX) // no such type
		return (1);

	/*
	 *	gui_element_init returns the uuid of the new elem,
	 *	 if it is 0 that means something wrong happened.
	 */
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
	v2ui mouse_pos = {
			min(max(eng->mouse_x, 0), eng->screen->size[_x] - 1),
			min(max(eng->mouse_y, 0), eng->screen->size[_y] - 1)};

	if (ft_mouse(eng, 1).released)
		container->is_clicked = 0;

	/* handle title bar graphics and logic */
	v2ui title_h_off = {0};
	if (container->options & GUI_CONT_OPT_TITLE_BAR_VISIBLE)
	{
		title_h_off[_y] = 20;
		r2si title_rect = {container->rect.pos, {container->rect.dim[0], 20}};
		if (container->options & GUI_CONT_OPT_MOVABLE)
		{
			if (ft_mouse(eng, 1).pressed && vec_in_rect(mouse_pos, title_rect))
			{
				container->is_clicked = 1;
				container->click_offset = container->rect.pos - mouse_pos;
			}
			if (container->is_clicked == 1)
			{
				container->rect.pos = mouse_pos + container->click_offset;
				container->rect.pos[_x] = max(container->rect.pos[_x], 0);
				container->rect.pos[_y] = max(container->rect.pos[_y], 0);
				container->rect.pos[_x] = min(container->rect.pos[_x] + container->rect.dim[_x], eng->screen->size[_x]) - container->rect.dim[_x];
				container->rect.pos[_y] = min(container->rect.pos[_y] + 20, eng->screen->size[_y]) - 20;
			}
		}
		/* container pos used instead of rect to remove tearing while moving container */
		if (container->options & GUI_CONT_OPT_MOVABLE)
			ft_rect(eng, container->rect.pos, title_rect.dim, (t_color){0x595b4d}); // movable title bar background color
		else
			ft_rect(eng, container->rect.pos, title_rect.dim, (t_color){0x6d6f61}); // immovable title bar background color
		ft_put_text(eng, container->rect.pos + (v2ui){5, 5}, container->title, 1); // title offset for move icon

		r2si reduce_rect = {
				{container->rect.pos[_x] + title_rect.dim[_x] - 16 - 2, container->rect.pos[_y] + 2},
				{16, 16}};
		if (ft_mouse(eng, 1).pressed && vec_in_rect(mouse_pos, reduce_rect))
			container->options ^= GUI_CONT_OPT_CLOSED; // ¹⁺³⁼⁽⁴⁾ just found this shi..	
		ft_rect(eng, reduce_rect.pos, reduce_rect.dim, (t_color){0x6b6e5b});
		ft_put_text(eng, reduce_rect.pos + (v2si){1, -1}, (container->options & GUI_CONT_OPT_CLOSED) ? "+": "-", 2);

	}


	if (container->options & GUI_CONT_OPT_CLOSED)
		return (0);

	/* handle background graphics */
	if (container->options & GUI_CONT_OPT_BACKGROUND_VISIBLE)
	{
		ft_rect(eng, container->rect.pos + title_h_off + 1, container->rect.dim - title_h_off - 2, (t_color){0x7a8877}); // background color
		
		v2ui s_back = container->rect.pos + title_h_off;
		v2ui e_back = container->rect.pos + container->rect.dim - 1;

		ft_rect(eng, s_back, (v2ui){container->rect.dim[_x], 1}, (t_color){0x595b4d});
		ft_rect(eng, s_back, (v2ui){1, container->rect.dim[_y] - title_h_off[_y]}, (t_color){0x595b4d});
		ft_rect(eng, (v2ui){s_back[_x], e_back[_y]}, (v2ui){container->rect.dim[_x], 1}, (t_color){0x595b4d});
		ft_rect(eng, (v2ui){e_back[_x], s_back[_y]}, (v2ui){1, container->rect.dim[_y] - title_h_off[_y]}, (t_color){0x595b4d});
	}

	/* handle resizing logic and graphics*/
	r2si tick_rect = {container->rect.pos + container->rect.dim - (v2si){10, 10}, {10, 10}};
	if (container->options & GUI_CONT_OPT_RESIZABLE)
	{
		
		ft_rect(eng, tick_rect.pos, tick_rect.dim, (t_color){0x595b4d}); // dim mark
		if (vec_in_rect(mouse_pos, tick_rect))
		{
			if (ft_mouse(eng, 1).pressed)
			{
				container->is_clicked = 2;
				container->click_offset = mouse_pos - container->rect.dim;
			}
		}
		if (container->is_clicked == 2)
		{
			v2si other_rect_dim = mouse_pos - container->click_offset;
			container->rect.dim[_x] = max(other_rect_dim[_x], 300);
			container->rect.dim[_y] = max(other_rect_dim[_y], 130);
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
		&& local_offset[_x] + container->min_element_pos[_x] + element->dim[_x] < container->rect.dim[_x] - 5)
	{
		local_offset[_x] += container->min_element_pos[_x];
		local_offset[_y] += container->base_element_pos_y;
		container->min_element_pos[_x] += element->dim[_x] + 2; // element dimension and padding
		container->min_element_pos[_y] = max(container->min_element_pos[_y], container->base_element_pos_y + element->dim[_y] + 2);
	}
	else
	{
		container->base_element_pos_y = container->min_element_pos[_y];
		local_offset[_y] += container->min_element_pos[_y];
		container->min_element_pos[_x] = element->dim[_x] + 2;
		container->min_element_pos[_y] += element->dim[_y] + 2; // element rect.dim and padding
	}

	return (container->rect.pos + local_offset);
}
