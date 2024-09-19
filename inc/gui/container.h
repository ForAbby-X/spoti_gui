
#ifndef GUI_CONTAINER_H
#define GUI_CONTAINER_H

#include "gui/container_struct.h"
#include "gui/element.h"


/* On success return the uuid of the container, otherwise an integer value of 0. */
uint16_t				gui_container_init(gui_container *gui_container);
void					gui_container_destroy(gui_container *gui_container);

void					gui_container_set_title(gui_container *gui_container, char *title);

/* Return the modified container option flags.
 * @note Later i should make it return an error statuts...
 */
gui_container_options	gui_container_add_options(gui_container *gui_container, gui_container_options options);

/* Return the modified container option flags.
 * @note Later i should make it return an error statuts...
 */
gui_container_options	gui_container_rem_options(gui_container *gui_container, gui_container_options options);

/* Return the uuid of the new elemnt on success, otherwise return an integer value of 0. */
uint16_t				gui_container_add_element(gui_container *gui_container, gui_element_type type, void *arg);
void					gui_container_rem_element(gui_container *gui_container, uint16_t uuid);

int						gui_container_update(gui_container *gui_container, void *arg);

/*
 *	Return the screen space position of the element.
 *	@warning ! call only once per element update !
 */
v2ui					gui_container_element_offset(gui_container *gui_container, gui_element *element);

#endif
