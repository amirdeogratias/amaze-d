/*
** amaze.h
** Amaze-D - Ant colony pathfinding simulator
*/

#ifndef AMAZE_H
#define AMAZE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>

#define EXIT_SUCCESS 0
#define EXIT_ERROR 84

/* Room structure */
typedef struct room_s {
    char *name;
    int x;
    int y;
    int is_start;
    int is_end;
    struct link_s **links;
    int link_count;
    int link_capacity;
} room_t;

/* Link between rooms */
typedef struct link_s {
    room_t *room;
} link_t;

/* Ant entity */
typedef struct ant_s {
    int id;
    room_t *current_room;
    room_t **path;
    int path_length;
    int path_index;
    int finished;
} ant_t;

/* Main colony structure */
typedef struct colony_s {
    int ant_count;
    room_t **rooms;
    int room_count;
    int room_capacity;
    ant_t **ants;
    room_t *start;
    room_t *end;
    char *input_content;
} colony_t;

/* Parser functions */
colony_t *parse_input(char *content);
int validate_colony(colony_t *colony);
void free_colony(colony_t *colony);

/* Core engine */
int run_simulation(colony_t *colony);
room_t **find_path(colony_t *colony, room_t *start, room_t *end);
int calculate_path_length(room_t **path);

/* Room management */
room_t *create_room(char *name, int x, int y);
int add_link(room_t *room1, room_t *room2);
room_t *find_room(colony_t *colony, char *name);

/* Utility functions */
char *read_stdin(void);
char **split_string(char *str, char delimiter);
int count_words(char *str, char delimiter);
void free_split(char **split);
int str_is_number(char *str);
int my_atoi(char *str);

/* Output functions */
void print_moves(colony_t *colony);
void print_error(char *message);

#endif /* AMAZE_H */
