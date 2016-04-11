/*
 * Userspace program that communicates with the vga_led device driver
 * primarily through ioctls
 *
 * Stephen A. Edwards
 * Columbia University
 *
 * Name: Bernardo de Almeida Abreu
 * UNI:  bd2440
 *
 * Name: Henrique Pizzol Grando
 * UNI:  hp2409
 * 
 * Name: Lucas Ikenaga Barros
 * UNI:  li2176
 *
 * Name: Tomas Mantelato
 * UNI:  tm2779
 *
 */

#include "vga_led.h"
#include "util.h"
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int vga_led_fd;

sprite_info *ground[3];
int line_length[3] = { -1, -1, -1 };

void write_info(sprite_info sprite, screen background)
{
    vga_screen_arg_t screen_game;
    screen_game.sprite = sprite;
    screen_game.background = background;
    if (ioctl(vga_led_fd, VGA_LED_WRITE_DIGIT, &screen_game))
    {
        perror("ioctl(VGA_LED_WRITE_DIGIT) failed");
        return;
    }
}

int main()
{
    static const char filename[] = "/dev/vgaled";

    printf("GAME TEST Userspace program started\n");

    if ( (vga_led_fd = open(filename, O_RDWR)) == -1)
    {
        fprintf(stderr, "could not open %s\n", filename);
        return -1;
    }

    int row = 0;        // The next row of ground to be generated

    screen back;
    back.life_1 = 2;
    back.life_2 = 2;
    back.background_color = 0x152050;
  

    printf("GAME TEST Userspace program terminating\n");

    int pause = 1;

    // Generating start ground
    generate_ground(0, row++);
    generate_ground(160, row++);
    generate_ground(320, row++);
    row = 0;

    // Writing to driver
    int i, j;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < line_length[i]; j++)
        {
            write_info(ground[i][j], back);
        }
    }

    // Setting grandpa and grandma starting positions
    sprite_info grandpa;
    grandpa.sprite_y = 120;
    grandpa.sprite_x = 310;
    grandpa.shape = GP_STAND;
    grandpa.id = GP_ID;
    grandpa.count = 0;
    grandpa.layer = OBJECTS;
    grandpa.orientation = RIGHT;

    sprite_info grandma;
    grandma.sprite_y = 120;
    grandma.sprite_x = 330;
    grandma.shape = GM_STAND;
    grandma.id = GM_ID;
    grandma.count = 0;
    grandma.layer = OBJECTS;
    grandma.orientation = LEFT;

    while (1)
    {
        while(pause)
        {
            // ### if y movement ###
            pause = 0;
        }


    }


    return 0;
}
