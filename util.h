#ifndef _UTIL_H_
#define _UTIL_H_

#include <stdio.h>
#include <stdlib.h>
#include "vga_led.h"

// Shapes
#define GROUND 0
#define GP_STAND 10
#define GM_STAND 12

// ID
#define GP_ID 0
#define GM_ID 1

// Layers
#define SCENARIO 0
#define OBJECTS  1

// Orientation
#define RIGHT 0
#define LEFT  1

/* Generates platforms in the given line, allocating the memory according to 
   the given row */
void generate_ground (int, int);

/* Receives the x translation and returns the valid resulting sprite location.
   (Called only for the characters) */
void translation (int *);

/* Receives the next (x,y) location for the sprite and generates a transition
   to that point. */
void transition (sprite_info *, int);



#endif





