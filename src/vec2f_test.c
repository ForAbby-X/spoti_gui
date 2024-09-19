
#include "gui/container.h"
#include "gui/element.h"
#include "random.h"
#include <stdio.h>
#include <time.h>

#include "engine.h"

static int _on_repeat(t_engine *eng, t_data *dat, double dt)
{
	gui_container *container = (gui_container *)dat;


	ft_clear(eng, (t_color){0xbbc8d2});
	gui_container_update(container, eng); // update the gui container every frames
	return (1);
}

int main()
{
	gui_container container = {0};
	t_engine *engine = ft_eng_create(1100, 750, "Spoti Gui");
	uint16_t elem_uuid[32] = {0};

	my_srand_u32(time(NULL));

	gui_container_init(&container);
	gui_container_add_options(&container, GUI_CONT_BASE_OPTIONS); // GUI_CONT_OPT_GROW_ROW
	gui_container_rem_options(&container, 0); // makes it not resizable
	
	elem_uuid[0] = gui_container_add_element(&container, GUI_ELEM_TEXT, "Ravage");
	elem_uuid[1] = gui_container_add_element(&container, GUI_ELEM_TEXT, NULL);
	elem_uuid[2] = gui_container_add_element(&container, GUI_ELEM_TEXT, "Un roman de science fiction");
	elem_uuid[3] = gui_container_add_element(&container, GUI_ELEM_TEXT, "De Rene Barjavel");
	elem_uuid[4] = gui_container_add_element(&container, GUI_ELEM_TEXT, NULL);
	elem_uuid[5] = gui_container_add_element(&container, GUI_ELEM_TEXT, "Dans un paris moderne ou la technologie a envahie le monde.");
	elem_uuid[6] = gui_container_add_element(&container, GUI_ELEM_TEXT, "Un evenement spectaculaire vas changer la face de l'histoire !");
	elem_uuid[7] = gui_container_add_element(&container, GUI_ELEM_TEXT, NULL);
	elem_uuid[8] = gui_container_add_element(&container, GUI_ELEM_TEXT, "Liberation: stupefiant de realisme !!!");
	elem_uuid[9] = gui_container_add_element(&container, GUI_ELEM_TEXT, "Le monde: Je suis raciste.");

	/* stops here to loop in engine */
	ft_eng_play(engine, (t_data *)&container, _on_repeat);

	gui_container_destroy(&container);
	ft_eng_destroy(engine);
	return (0);
}
