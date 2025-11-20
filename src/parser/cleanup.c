#include "../../include/amaze.h"

static void free_room(room_t *room)
{
    if (!room)
        return;
    
    free(room->name);
    
    if (room->links) {
        for (int i = 0; i < room->link_count; i++)
            free(room->links[i]);
        free(room->links);
    }
    
    free(room);
}

static void free_ant(ant_t *ant)
{
    if (!ant)
        return;
    
    free(ant->path);
    free(ant);
}

void free_colony(colony_t *colony)
{
    if (!colony)
        return;

    if (colony->rooms) {
        for (int i = 0; i < colony->room_count; i++)
            free_room(colony->rooms[i]);
        free(colony->rooms);
    }

    if (colony->ants) {
        for (int i = 0; i < colony->ant_count; i++)
            free_ant(colony->ants[i]);
        free(colony->ants);
    }

    free(colony->input_content);
    free(colony);
}
