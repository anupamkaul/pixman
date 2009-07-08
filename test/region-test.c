#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "pixman.h"

int
main ()
{
    pixman_region32_t r1;
    pixman_region32_t r2;
    pixman_region32_t r3;
    pixman_box32_t boxes[] = {
	{ 10, 10, 20, 20 },
	{ 30, 30, 30, 40 },
    };
    int i;
    pixman_box32_t *b;

    /* This used to go into an infinite loop before pixman-region.c
     * was fixed to not use explict "short" variables
     */
    pixman_region32_init_rect (&r1, 0, 0, 20, 64000);
    pixman_region32_init_rect (&r2, 0, 0, 20, 64000);
    pixman_region32_init_rect (&r3, 0, 0, 20, 64000);

    pixman_region32_subtract (&r1, &r2, &r3);


    /* This would produce a region containing an empty
     * rectangle in it. Such regions are considered malformed,
     * but using an empty rectangle for initialization should
     * work.
     */
    pixman_region32_init_rects (&r1, boxes, 2);

    b = pixman_region32_rectangles (&r1, &i);

    assert (i == 1);
    
    while (i--)
    {
	assert (b[i].x1 < b[i].x2);
	assert (b[i].y1 < b[i].y2);
    }

    return 0;
}

