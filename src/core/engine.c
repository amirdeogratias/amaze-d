#include "../../include/amaze.h"
#include "../../include/visual.h"

static void init_ants(colony_t *colony)
{
    colony->ants = malloc(sizeof(ant_t*) * colony->ant_count);
    
    for (int i = 0; i < colony->ant_count; i++) {
        colony->ants[i] = calloc(1, sizeof(ant_t));
        colony->ants[i]->id = i + 1;
        colony->ants[i]->current_room = colony->start;
        colony->ants[i]->finished = 0;
    }
}

static int all_ants_finished(colony_t *colony)
{
    for (int i = 0; i < colony->ant_count; i++) {
        if (!colony->ants[i]->finished)
            return 0;
    }
    return 1;
}

static int room_will_be_occupied(colony_t *colony, room_t *room, room_t **next_rooms, int current_ant)
{
    if (room == colony->start || room == colony->end)
        return 0;
    
    for (int i = 0; i < colony->ant_count; i++) {
        if (i == current_ant)
            continue;
        
        ant_t *ant = colony->ants[i];
        
        if (ant->current_room == room && !ant->finished)
            return 1;
        
        if (next_rooms[i] == room)
            return 1;
    }
    return 0;
}

static void move_ants(colony_t *colony)
{
    room_t **next_rooms = calloc(colony->ant_count, sizeof(room_t*));
    int *just_finished = calloc(colony->ant_count, sizeof(int));
    
    for (int i = colony->ant_count - 1; i >= 0; i--) {
        ant_t *ant = colony->ants[i];
        
        if (ant->finished || !ant->path) {
            continue;
        }
        
        if (ant->path_index >= ant->path_length) {
            ant->finished = 1;
            continue;
        }
        
        room_t *next = ant->path[ant->path_index];
        
        if (!room_will_be_occupied(colony, next, next_rooms, i)) {
            next_rooms[i] = next;
        }
    }
    
    for (int i = 0; i < colony->ant_count; i++) {
        if (next_rooms[i]) {
            colony->ants[i]->current_room = next_rooms[i];
            colony->ants[i]->path_index++;
            
            if (colony->ants[i]->current_room == colony->end) {
                just_finished[i] = 1;
            }
        }
    }
    
    for (int i = 0; i < colony->ant_count; i++) {
        if (just_finished[i])
            colony->ants[i]->finished = 1;
    }
    
    free(just_finished);
    free(next_rooms);
}

int run_simulation(colony_t *colony)
{
    stats_t *stats = NULL;
    
    init_ants(colony);
    
    for (int i = 0; i < colony->ant_count; i++) {
        colony->ants[i]->path = find_path(colony, colony->start, colony->end);
        if (!colony->ants[i]->path) {
            print_error("No path found\n");
            return EXIT_ERROR;
        }
        colony->ants[i]->path_length = calculate_path_length(colony->ants[i]->path);
        colony->ants[i]->path_index = 0;
    }
    
    if (g_visual_config.verbose) {
        print_pathfinding_info(colony);
    }
    
    if (g_visual_config.show_stats || g_visual_config.verbose) {
        stats = init_stats();
    }
    
    write(1, "#moves\n", 7);
    
    int turn = 0;
    int max_turns = colony->ant_count * colony->room_count * 2;
    
    while (!all_ants_finished(colony) && turn < max_turns) {
        turn++;
        move_ants(colony);
        
        if (g_visual_config.verbose) {
            print_moves_visual(colony, turn);
            if (g_visual_config.animate) {
                usleep(100000);
            }
        } else {
            print_moves(colony);
        }
        
        if (stats) {
            update_stats(stats, colony, turn);
        }
        
        if (g_visual_config.verbose && !g_visual_config.animate) {
            print_simulation_progress(colony, turn, max_turns);
        }
    }
    
    if (g_visual_config.verbose) {
        printf("\n");
    }
    
    if (turn >= max_turns) {
        print_error("Simulation timeout\n");
        if (stats)
            free(stats);
        return EXIT_ERROR;
    }
    
    if (stats) {
        finalize_stats(stats, colony);
        if (g_visual_config.show_stats || g_visual_config.verbose) {
            print_statistics(stats, colony);
        }
        free(stats);
    }
    
    return EXIT_SUCCESS;
}
