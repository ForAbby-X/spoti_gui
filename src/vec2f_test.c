
#include <stdio.h>
#include "math_vec/methodes.h"

#include "gui/container.h"
#include "gui/element.h"

/* v2f_swap(vec) */
/* v2f_sum(vec) */
/* v2f_sub(vec) */
/* v2f_mul(vec) */
/* v2f_div(vec) */
/* v2f_mag(vec) */
/* v2f_norm(vec) */
/* v2f_dot(vec_a, vec_b) */
/* v2f_cross(vec_a, vec_b) */

int main()
{
	{
		/* v2f_swap(vec) */
		printf("Test v2f_swap()\n");
		v2f a = {5.0f, 9.0f};
		printf("vec <%f, %f>\n", a[0], a[1]);
		a = v2f_swap(a);
		printf("v2f_swap() !\n");
		printf("swap <%f, %f>\n\n", a[0], a[1]);
	}
	{
		/* v2f_sum(vec) */
		printf("Test v2f_sum()\n");
		v2f a = {5.0f, 9.0f};
		printf("vec <%f, %f>\n", a[0], a[1]);
		float s_a = v2f_sum(a);
		printf("v2f_sum() !\n");
		printf("sum %f\n\n", s_a);
	}
	{
		/* v2f_sub(vec) */
		printf("Test v2f_sub()\n");
		v2f a = {5.0f, 9.0f};
		printf("vec <%f, %f>\n", a[0], a[1]);
		float s_a = v2f_sub(a);
		printf("v2f_sub() !\n");
		printf("sub %f\n\n", s_a);
	}
	{
		/* v2f_mul(vec) */
		printf("Test v2f_mul()\n");
		v2f a = {5.0f, 9.0f};
		printf("vec <%f, %f>\n", a[0], a[1]);
		float s_a = v2f_mul(a);
		printf("v2f_mul() !\n");
		printf("mul %f\n\n", s_a);
	}
	{
		/* v2f_div(vec) */
		printf("Test v2f_div()\n");
		v2f a = {5.0f, 9.0f};
		printf("vec <%f, %f>\n", a[0], a[1]);
		float s_a = v2f_div(a);
		printf("v2f_div() !\n");
		printf("div %f\n\n", s_a);
	}
	{
		/* v2f_mag(vec) */
		printf("Test v2f_mag()\n");
		v2f a = {5.0f, 9.0f};
		printf("vec <%f, %f>\n", a[0], a[1]);
		float d_a = v2f_mag(a);
		printf("v2f_mag() !\n");
		printf("mag %f\n\n", d_a);
	}
	{
		/* v2f_norm(vec) */
		printf("Test v2f_norm()\n");
		v2f a = {5.0f, 9.0f};
		printf("vec <%f, %f>\n", a[0], a[1]);
		v2f n_a = v2f_norm(a);
		printf("v2f_norm() !\n");
		printf("norm <%f, %f>\n\n", n_a[0], n_a[1]);
	}
	{
		/* v2f_dot(vec) */
		printf("Test v2f_dot()\n");
		v2f a = {5.0f, 9.0f};
		v2f b = {5.0f, 9.0f};
		printf("vec a <%f, %f>\n", a[0], a[1]);
		printf("vec b <%f, %f>\n", b[0], b[1]);
		float d_a = v2f_dot(a, b);
		printf("v2f_dot() !\n");
		printf("dot %f\n\n", d_a);
	}
	{
		gui_container container = {0};

		gui_container_init(&container);
		gui_container_set_options(&container, GUI_BASE_OPTIONS & (~GUI_IS_RESIZABLE)); // makes it not resizable

		gui_container_destroy(&container);
	}


	return 0;
}