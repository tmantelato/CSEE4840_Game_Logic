#ifndef _UTIL_H_
#define _UTIL_H_

#include <stdio.h>
#include <stdlib.h>
#include "vga_led.h"

// Shapes
#define GROUND 0
#define GP_STAND 10
#define GM_STAND 12

// ID: range from 8 - 15 (% 8 when assigning to sprite_info)
#define GP_ID 8
#define GM_ID 9

// Layers
#define SCENARIO 0
#define OBJECTS  1

// Orientation
#define RIGHT 0
#define LEFT  1

// Offset from center
#define OFFSET 16

/* Generates platforms in the given line, allocating the memory according to 
   the given row */
void generate_ground (int, int);

/* Try to move the character received by parameter handling the necessary
   collisions */
void move (character *);



#endif





