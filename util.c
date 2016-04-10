#include "util.h"

extern int line_length[3];
extern sprite_info *ground[3];

void generate_ground (int line, int row)
{            
    // 3 blocks = 50% chance
    // 2 blocks = 40% chance 
    // 1 block  = 10% chance

    if (line_length[row] != -1)
    {
        free(ground[row]);
    }

    int blocks_chance = rand() % 20;

    if (blocks_chance < 10)
    {     
        ground[row] = (sprite_info *) malloc (3 * sizeof(sprite_info));
        line_length[row] = 3;
    }
    else if (blocks_chance < 18)
    {
        ground[row] = (sprite_info *) malloc (2 * sizeof(sprite_info));
        line_length[row] = 2;
    }
    else
    {
        ground[row] = (sprite_info *) malloc (1 * sizeof(sprite_info));
        line_length[row] = 1;
    }

    // Defining the ground size and starting point
    // The starting point is defined depending on how many blocks we
    // have per line (line_length[row]) and an offset of 8 pixels on 
    // each side of the screen is added.  (8 ~ 632)

    int j;
    int dx = (632 - 8) / line_length[row];        // size of each column 
    for (j = 0; j < line_length[row]; j++)
    {
        ground[row][j].shape = 0;

        int begin = dx * j + 8;                 // begin of curr. column
        
        // 6 blocks long = 50% chance
        // 5 blocks long = 40% chance
        // 4 blocks long = 10% chance
        
        int length_chance = rand() % 20;

        if (length_chance < 10)
        {     
            ground[row][j].count = 5;

            ground[row][j].sprite_x = 
                (rand() % (dx - ground[row][j].count)) + begin;

        }
        else if (length_chance < 18)
        {
            ground[row][j].count = 4;

            ground[row][j].sprite_x = 
                (rand() % (dx - ground[row][j].count)) + begin;
        }
        else
        {
            ground[row][j].count = 3;

            ground[row][j].sprite_x = 
                (rand() % (dx - ground[row][j].count)) + begin;
        }

        ground[row][j].sprite_y = line;
    }
}