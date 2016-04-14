#ifndef _UTIL_H_
#define _UTIL_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include "vga_led.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

// Shapes
#define GROUND 3
#define GP_STAND 10
#define GP_JUMP 0
#define GM_STAND 11
#define GM_JUMP 1

// ID for OBJECTS' layer
#define GP_ID 0
#define GM_ID 1

// Layers
#define SCENARIO 0
#define OBJECTS  1

// Orientation
#define RIGHT 0
#define LEFT  1

// Offset from center
#define OFFSET 16

/* Struct to facilitate control of sprites on software */
typedef struct 
{
    coordinate *pos;
    int id;
    int vy;
    int vx;
    int jumping;
}character;

/* Sends information to the driver through the ioctl call */
void write_info(sprite_info, screen);

/* Generates platforms in the given line, allocating the memory according to 
   the given row */
void generate_ground (int, int);

/* Try to move the character received by parameter in the x axis handling the 
   collision if necessary */
void x_translation (character *, character);

/* Try to move the character received by parameter in the y axis handling the 
   collision if necessary */
void y_translation (character *, character);



#endif





