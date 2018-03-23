#include "tween.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    float t, s, e, d;
    
    if (argc != 5)
    {
	fprintf(stderr,
		"Usage: %s <time> <start> <end> <duration>\n", argv[0]);
	return 1;
    }

    t = atof(argv[1]);
    s = atof(argv[2]);
    e = atof(argv[3]);
    d = atof(argv[4]);

    printf("tween_linear       (%f, %f, %f, %f) -> %f\n\n",
	   t, s, e, d, tween_linear(t, s, e, d));
    printf("tween_quad_in      (%f, %f, %f, %f) -> %f\n",
	   t, s, e, d, tween_quad_in(t, s, e, d));
    printf("tween_quad_out     (%f, %f, %f, %f) -> %f\n",
	   t, s, e, d, tween_quad_out(t, s, e, d));
    printf("tween_quad_inout   (%f, %f, %f, %f) -> %f\n\n",
	   t, s, e, d, tween_quad_inout(t, s, e, d));
    printf("tween_cubic_in     (%f, %f, %f, %f) -> %f\n",
	   t, s, e, d, tween_cubic_in(t, s, e, d));
    printf("tween_cubic_out    (%f, %f, %f, %f) -> %f\n",
	   t, s, e, d, tween_cubic_out(t, s, e, d));
    printf("tween_cubic_inout  (%f, %f, %f, %f) -> %f\n\n",
	   t, s, e, d, tween_cubic_inout(t, s, e, d));
    printf("tween_quart_in     (%f, %f, %f, %f) -> %f\n",
	   t, s, e, d, tween_quart_in(t, s, e, d));
    printf("tween_quart_out    (%f, %f, %f, %f) -> %f\n",
	   t, s, e, d, tween_quart_out(t, s, e, d));
    printf("tween_quart_inout  (%f, %f, %f, %f) -> %f\n\n",
	   t, s, e, d, tween_quart_inout(t, s, e, d));
    printf("tween_quint_in     (%f, %f, %f, %f) -> %f\n",
	   t, s, e, d, tween_quint_in(t, s, e, d));
    printf("tween_quint_out    (%f, %f, %f, %f) -> %f\n",
	   t, s, e, d, tween_quint_out(t, s, e, d));
    printf("tween_quint_inout  (%f, %f, %f, %f) -> %f\n\n",
	   t, s, e, d, tween_quint_inout(t, s, e, d));
    printf("tween_sine_in      (%f, %f, %f, %f) -> %f\n",
	   t, s, e, d, tween_sine_in(t, s, e, d));
    printf("tween_sine_out     (%f, %f, %f, %f) -> %f\n",
	   t, s, e, d, tween_sine_out(t, s, e, d));
    printf("tween_sine_inout   (%f, %f, %f, %f) -> %f\n\n",
	   t, s, e, d, tween_sine_inout(t, s, e, d));
    printf("tween_expo_in      (%f, %f, %f, %f) -> %f\n",
	   t, s, e, d, tween_expo_in(t, s, e, d));
    printf("tween_expo_out     (%f, %f, %f, %f) -> %f\n",
	   t, s, e, d, tween_expo_out(t, s, e, d));
    printf("tween_expo_inout   (%f, %f, %f, %f) -> %f\n\n",
	   t, s, e, d, tween_expo_inout(t, s, e, d));
    printf("tween_circle_in    (%f, %f, %f, %f) -> %f\n",
	   t, s, e, d, tween_circle_in(t, s, e, d));
    printf("tween_circle_out   (%f, %f, %f, %f) -> %f\n",
	   t, s, e, d, tween_circle_out(t, s, e, d));
    printf("tween_circle_inout (%f, %f, %f, %f) -> %f\n\n",
	   t, s, e, d, tween_circle_inout(t, s, e, d));
    printf("tween_elastic_in   (%f, %f, %f, %f) -> %f\n",
	   t, s, e, d, tween_elastic_in(t, s, e, d));
    printf("tween_elastic_out  (%f, %f, %f, %f) -> %f\n",
	   t, s, e, d, tween_elastic_out(t, s, e, d));
    printf("tween_elastic_inout(%f, %f, %f, %f) -> %f\n\n",
	   t, s, e, d, tween_elastic_inout(t, s, e, d));
    printf("tween_bounce_in    (%f, %f, %f, %f) -> %f\n",
	   t, s, e, d, tween_bounce_in(t, s, e, d));
    printf("tween_bounce_out   (%f, %f, %f, %f) -> %f\n",
	   t, s, e, d, tween_bounce_out(t, s, e, d));
    printf("tween_bounce_inout (%f, %f, %f, %f) -> %f\n\n",
	   t, s, e, d, tween_bounce_inout(t, s, e, d));
    return 0;
}
