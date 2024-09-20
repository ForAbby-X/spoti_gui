
#include "gui/container.h"
#include "gui/element.h"
#include "random.h"
#include <stdio.h>
#include <time.h>

#include "engine.h"

static int _on_repeat(t_engine *eng, t_data *dat, double dt)
{
	gui_container *container = (gui_container *)dat;

	for (int key = XK_F1; key < XK_F10; ++key)
		if (ft_key(eng, key).pressed)
			container[1].options ^= 1 << (key - XK_F1);

	ft_clear(eng, (t_color){0xbbc8d2});
	gui_container_update(&container[0], eng); // update the gui container every frames
	gui_container_update(&container[1], eng); // update the gui container every frames
	return (1);
}

int main()
{
	gui_container container[2] = {0};
	t_engine *engine = ft_eng_create(1100, 750, "Spoti Gui");
	uint16_t elem_uuid[32] = {0};

	my_srand_u32(time(NULL));

	gui_container_init(&container[0]);
	gui_container_set_title(&container[0], "Gui Container Settings:");
	gui_container_add_options(&container[0], GUI_CONT_BASE_OPTIONS);
	gui_container_rem_options(&container[0], GUI_CONT_OPT_RESIZABLE | GUI_CONT_OPT_MOVABLE | GUI_CONT_OPT_INTERACTIVE);
	container[0].rect.dim[_x] = 180;
	// gui_container_add_element(&container[0], GUI_ELEM_TEXT, "Use these keys to change root container's settings:\n");
	gui_container_add_element(&container[0], GUI_ELEM_TEXT, "F1 - is movable");
	gui_container_add_element(&container[0], GUI_ELEM_TEXT, "F2 - is resizable");
	gui_container_add_element(&container[0], GUI_ELEM_TEXT, "F3 - has title bar");
	gui_container_add_element(&container[0], GUI_ELEM_TEXT, "F4 - has background");
	gui_container_add_element(&container[0], GUI_ELEM_TEXT, "F5 - is interactive");
	gui_container_add_element(&container[0], GUI_ELEM_TEXT, "F7 - row elements");

	gui_container_init(&container[1]);
	gui_container_set_title(&container[1], "Book Review");
	gui_container_add_options(&container[1], GUI_CONT_BASE_OPTIONS | GUI_CONT_OPT_CLOSED); // GUI_CONT_OPT_GROW_ROW
	gui_container_rem_options(&container[1], 0); // makes it not resizable
	container[1].rect.pos[_x] += 200;
	gui_container_add_element(&container[1], GUI_ELEM_TEXT, "Ravage");
	gui_container_add_element(&container[1], GUI_ELEM_TEXT, NULL);
	gui_container_add_element(&container[1], GUI_ELEM_TEXT, "Un roman de science fiction");
	gui_container_add_element(&container[1], GUI_ELEM_TEXT, "De Rene Barjavel");
	gui_container_add_element(&container[1], GUI_ELEM_TEXT, NULL);
	gui_container_add_element(&container[1], GUI_ELEM_TEXT, "Dans un paris moderne ou la technologie a envahie le monde.");
	gui_container_add_element(&container[1], GUI_ELEM_TEXT, "Un evenement spectaculaire vas changer la face de l'histoire !");
	gui_container_add_element(&container[1], GUI_ELEM_TEXT, NULL);
	gui_container_add_element(&container[1], GUI_ELEM_TEXT, "Liberation: stupefiant de realisme !!!");
	gui_container_add_element(&container[1], GUI_ELEM_TEXT, "Le monde: Je suis raciste.");

	/* stops here to loop in engine */
	ft_eng_play(engine, (t_data *)container, _on_repeat);

	gui_container_destroy(&container[0]);
	gui_container_destroy(&container[1]);
	ft_eng_destroy(engine);
	return (0);
}
