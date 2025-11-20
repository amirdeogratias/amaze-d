#include "../../include/amaze.h"

static int parse_ant_count(colony_t *colony, char *line)
{
    if (!str_is_number(line) || my_atoi(line) <= 0) {
        print_error("Invalid ant count\n");
        return 0;
    }
    colony->ant_count = my_atoi(line);
    return 1;
}

static int parse_room(colony_t *colony, char *line, int *is_start, int *is_end)
{
    char **parts = split_string(line, ' ');
    room_t *room;

    if (!parts) {
        return 0;
    }

    int count = 0;
    while (parts[count])
        count++;

    if (count != 3) {
        free_split(parts);
        return 0;
    }

    if (!str_is_number(parts[1]) || !str_is_number(parts[2])) {
        free_split(parts);
        return 0;
    }

    room = create_room(parts[0], my_atoi(parts[1]), my_atoi(parts[2]));
    if (!room) {
        free_split(parts);
        return 0;
    }

    room->is_start = *is_start;
    room->is_end = *is_end;

    if (*is_start) {
        colony->start = room;
        *is_start = 0;
    }
    if (*is_end) {
        colony->end = room;
        *is_end = 0;
    }

    if (colony->room_count >= colony->room_capacity) {
        colony->room_capacity *= 2;
        colony->rooms = realloc(colony->rooms, 
            sizeof(room_t*) * colony->room_capacity);
    }
    colony->rooms[colony->room_count++] = room;

    free_split(parts);
    return 1;
}

static int parse_tunnel(colony_t *colony, char *line)
{
    char **parts = split_string(line, '-');
    room_t *room1, *room2;

    if (!parts) {
        return 0;
    }

    int count = 0;
    while (parts[count])
        count++;

    if (count != 2) {
        free_split(parts);
        return 0;
    }

    room1 = find_room(colony, parts[0]);
    room2 = find_room(colony, parts[1]);

    free_split(parts);

    if (!room1 || !room2)
        return 0;

    return add_link(room1, room2) && add_link(room2, room1);
}

colony_t *parse_input(char *content)
{
    colony_t *colony = calloc(1, sizeof(colony_t));
    char **lines = split_string(content, '\n');
    int i = 0, is_start = 0, is_end = 0, ant_parsed = 0;

    if (!colony || !lines)
        return NULL;

    colony->room_capacity = 16;
    colony->rooms = malloc(sizeof(room_t*) * colony->room_capacity);
    colony->input_content = strdup(content);

    while (lines[i]) {
        if (lines[i][0] == '\0') {
            i++;
            continue;
        }
        if (lines[i][0] == '#') {
            if (strcmp(lines[i], "##start") == 0)
                is_start = 1;
            else if (strcmp(lines[i], "##end") == 0)
                is_end = 1;
        } else if (!ant_parsed && str_is_number(lines[i])) {
            if (!parse_ant_count(colony, lines[i])) {
                free_split(lines);
                free_colony(colony);
                return NULL;
            }
            ant_parsed = 1;
        } else if (strchr(lines[i], ' ')) {
            if (!parse_room(colony, lines[i], &is_start, &is_end)) {
                free_split(lines);
                free_colony(colony);
                return NULL;
            }
        } else if (strchr(lines[i], '-')) {
            if (!parse_tunnel(colony, lines[i])) {
                free_split(lines);
                free_colony(colony);
                return NULL;
            }
        }
        i++;
    }

    free_split(lines);
    return colony;
}

int validate_colony(colony_t *colony)
{
    if (!colony || colony->ant_count <= 0) {
        print_error("Invalid colony\n");
        return 0;
    }
    if (!colony->start || !colony->end) {
        print_error("Missing start or end room\n");
        return 0;
    }
    if (colony->start == colony->end) {
        print_error("Start and end are the same\n");
        return 0;
    }
    return 1;
}
