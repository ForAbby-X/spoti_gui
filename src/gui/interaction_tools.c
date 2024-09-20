
#include "gui/interaction_tools.h"

int vec_in_rect(v2si pos, r2si box)
{
	return (
		pos[_x] >= box.pos[_x] &&
		pos[_x] < box.pos[_x] + box.dim[_x] &&
		pos[_y] >= box.pos[_y] &&
		pos[_y] < box.pos[_y] + box.dim[_y]);
}

int rect_in_rect(r2si box_a, r2si box_b)
{
	return (!(
		box_a.pos[_x] + box_a.dim[_x] < box_b.pos[_x] ||
		box_a.pos[_x] > box_b.pos[_x] + box_b.dim[_x] ||
		box_a.pos[_y] + box_a.dim[_y] < box_b.pos[_y] ||
		box_a.pos[_y] > box_b.pos[_y] + box_b.dim[_y]));
}

/*
+-----------+
|  +------+ |
|--|-ELEM-|-|-----
|  +------+ |
|           |
|           |
+-----------+
*/
