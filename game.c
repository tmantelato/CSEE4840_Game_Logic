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
    sprite_info grandpa_sprite;
    grandpa_sprite.pos.y = 120;
    grandpa_sprite.pos.x = 310;
    grandpa_sprite.shape = GP_JUMP;
    grandpa_sprite.id = GP_ID;
    grandpa_sprite.count = 0;
    grandpa_sprite.layer = OBJECTS;
    grandpa_sprite.orientation = RIGHT;
    write_info(grandpa_sprite, back);

    sprite_info grandma_sprite;
    grandma_sprite.pos.y = 120;
    grandma_sprite.pos.x = 330;
    grandma_sprite.shape = GM_JUMP;
    grandma_sprite.id = GM_ID;
    grandma_sprite.count = 0;
    grandma_sprite.layer = OBJECTS;
    grandma_sprite.orientation = LEFT;
    write_info(grandma_sprite, back);

    // Creating characters structures
    character grandpa;
    grandpa.pos.x = grandpa_sprite.pos.x;
    grandpa.pos.y = grandpa_sprite.pos.y;
    grandpa.id = GP_ID;
    grandpa.vx = 0;
    grandpa.vy = 1;

    character grandma;
    grandma.pos.x = grandma_sprite.pos.x;
    grandma.pos.y = grandma_sprite.pos.y;
    grandma.id = GM_ID;
    grandma.vx = 0;
    grandma.vy = 1;

    int count_ground = 150;
    while (1)
    {   
        // Line of platforms have a 160 pixels gap between one another
        if (count_ground == 160)
        {
            generate_ground(-8, row);
            row = (row + 1) % 3; 
            count_ground = 0;
        }
        count_ground++;

        // Moves all platforms one pixel down
        int i, j;
        for (i = 0; i < 3; i++)
        {
            for (j = 0; j < line_length[i]; j++)
            {
                ground[i][j].pos.y += 1;
            }
        }

        // User motion capture
        grandpa.vx = rand() % 5;
        grandma.vx = rand() % 5;

        // Try to move grandpa
        x_translation (&grandpa, grandma);

        // Try to move grandma
        x_translation (&grandma, grandpa);




        while(pause)
        {
            // ### if y movement ###
            pause = 0;
        }


    }


    return 0;
}
