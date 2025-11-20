#include "../../include/amaze.h"

room_t *create_room(char *name, int x, int y)
{
    room_t *room = calloc(1, sizeof(room_t));
    
    if (!room)
        return NULL;
    
    room->name = strdup(name);
    room->x = x;
    room->y = y;
    room->link_capacity = 8;
    room->links = malloc(sizeof(link_t*) * room->link_capacity);
    
    return room;
}

int add_link(room_t *room1, room_t *room2)
{
    if (!room1 || !room2)
        return 0;
    
    for (int i = 0; i < room1->link_count; i++) {
        if (room1->links[i]->room == room2)
            return 1;
    }
    
    if (room1->link_count >= room1->link_capacity) {
        room1->link_capacity *= 2;
        room1->links = realloc(room1->links, 
            sizeof(link_t*) * room1->link_capacity);
    }
    
    link_t *link = malloc(sizeof(link_t));
    link->room = room2;
    room1->links[room1->link_count++] = link;
    
    return 1;
}

room_t *find_room(colony_t *colony, char *name)
{
    for (int i = 0; i < colony->room_count; i++) {
        if (strcmp(colony->rooms[i]->name, name) == 0)
            return colony->rooms[i];
    }
    return NULL;
}
