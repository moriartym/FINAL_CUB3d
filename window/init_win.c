#include "../cub3d.h"

void change_to_win(t_var *data, t_bfs *bfs, int index)
{
    int i;
    int x;
    int y;

    i = 0;
    y = 0;
    while (y < data->map.height)
    {
        x = 0;
        while (x < data->map.width)
        {
            if (bfs->reachable[y][x] == true && !(y == bfs->ipy && x == bfs->ipx))
                i++;
            if (i == index)
            {
                // y = (int)data->player.py / TILE_SIZE - 5;
                // x = (int)data->player.px / TILE_SIZE - 1;
                data->winSprite.x = x * TILE_SIZE + 0.5 * TILE_SIZE;
                data->winSprite.y = y * TILE_SIZE + 0.5 * TILE_SIZE;
                data->map.arr[y][x] = '8';
                return ;
            }
            x++;
        }
        y++;
    }
}

void place_winning_tiles(t_var *data)
{
    t_bfs bfs;
    int y;
    int index;

    bfs = (t_bfs){0};
    do_bfs(data, &bfs);
    if (bfs.empty_spaces > 1)
    {
        index = rand() % bfs.empty_spaces;
        change_to_win(data, &bfs, index);
    } 
    else
        printf("Sorry, no winning tiles for this game.\n");
    y = 0; 
    while (y < data->map.height)
    {
        free(bfs.reachable[y]);
        y++;
    }
    free(bfs.reachable);
}
