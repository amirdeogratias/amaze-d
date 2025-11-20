#include "../../include/amaze.h"
#include "../../include/visual.h"
#include <sys/time.h>

visual_config_t g_visual_config = {
    .use_colors = 1,
    .use_emojis = 1,
    .show_stats = 1,
    .show_graph = 0,
    .animate = 0,
    .verbose = 0
};

void print_header(void)
{
    printf("\n");
    printf("%s%s", COLOR_CYAN, COLOR_BOLD);
    printf("╔═══════════════════════════════════════════════════════════╗\n");
    printf("║                                                           ║\n");
    printf("║                   %s → %s → %s → %s                       ║\n", 
          EMOJI_ANT, EMOJI_HOME, EMOJI_HOME, EMOJI_TARGET);
    printf("║                                                           ║\n");
    printf("║          AMAZE-D: Where Ants Meet Algorithms              ║\n");
    printf("║                                                           ║\n");
    printf("╚═══════════════════════════════════════════════════════════╝\n");
    printf("%s\n", COLOR_RESET);
}

void print_separator(int width)
{
    printf("%s%s", COLOR_CYAN, COLOR_DIM);
    for (int i = 0; i < width; i++)
        printf("═");
    printf("%s\n", COLOR_RESET);
}

void print_config_info(colony_t *colony)
{
    printf("%s%s%s Configuration:%s\n", COLOR_YELLOW, COLOR_BOLD, EMOJI_ROCKET, COLOR_RESET);
    printf("   %s Ants:    %s%d%s\n", EMOJI_ANT, COLOR_GREEN, colony->ant_count, COLOR_RESET);
    printf("   %s Rooms:   %s%d%s\n", EMOJI_HOME, COLOR_GREEN, colony->room_count, COLOR_RESET);
    
    int tunnel_count = 0;
    for (int i = 0; i < colony->room_count; i++)
        tunnel_count += colony->rooms[i]->link_count;
    tunnel_count /= 2;
    
    printf("   %s Tunnels: %s%d%s\n", EMOJI_ARROW, COLOR_GREEN, tunnel_count, COLOR_RESET);
    printf("\n");
}

void print_pathfinding_info(colony_t *colony)
{
    printf("%s%s%s Pathfinding:%s\n", COLOR_BLUE, COLOR_BOLD, EMOJI_FIRE, COLOR_RESET);
    
    if (colony->ants && colony->ants[0]->path) {
        printf("   %s BFS completed\n", EMOJI_CHECK);
        printf("   %s Path length: %s%d%s rooms\n", 
            EMOJI_ARROW, COLOR_GREEN, colony->ants[0]->path_length, COLOR_RESET);
        
        printf("   %s Route: %s", EMOJI_HOME, COLOR_CYAN);
        printf("%s", colony->start->name);
        for (int i = 0; i < colony->ants[0]->path_length; i++) {
            printf(" %s %s", EMOJI_ARROW, colony->ants[0]->path[i]->name);
        }
        printf("%s\n", COLOR_RESET);
    }
    printf("\n");
}

void print_simulation_progress(colony_t *colony, int current_turn, int total_turns)
{
    (void)total_turns;
    
    int total_progress = 0;
    int max_progress = colony->ant_count * 100;
    
    for (int i = 0; i < colony->ant_count; i++) {
        ant_t *ant = colony->ants[i];
        
        if (ant->finished) {
            total_progress += 100;
        } else if (ant->path_length > 0) {
            int ant_progress = (ant->path_index * 100) / ant->path_length;
            total_progress += ant_progress;
        }
    }
    
    int percent = (total_progress * 100) / max_progress;
    int bar_width = 40;
    int filled = (percent * bar_width) / 100;
    
    printf("\r%s%s%s Simulation:%s Turn %d [", 
        COLOR_MAGENTA, COLOR_BOLD, EMOJI_ANT, COLOR_RESET, current_turn);
    
    printf("%s", COLOR_GREEN);
    for (int i = 0; i < filled; i++)
        printf("█");
    printf("%s", COLOR_DIM);
    for (int i = filled; i < bar_width; i++)
        printf("░");
    printf("%s] %d%%", COLOR_RESET, percent);
    
    fflush(stdout);
}

void print_statistics(stats_t *stats, colony_t *colony)
{
    (void)colony;
    
    printf("\n\n");
    printf("%s%s%s Statistics:%s\n", COLOR_YELLOW, COLOR_BOLD, EMOJI_STAR, COLOR_RESET);
    printf("   %s Total turns:        %s%d%s\n", 
        EMOJI_FIRE, COLOR_GREEN, stats->total_turns, COLOR_RESET);
    printf("   %s Total moves:        %s%d%s\n", 
        EMOJI_ARROW, COLOR_GREEN, stats->total_moves, COLOR_RESET);
    printf("   %s Avg moves per ant:  %s%.2f%s\n", 
        EMOJI_ANT, COLOR_GREEN, stats->avg_moves_per_ant, COLOR_RESET);
    printf("   %s Throughput:         %s%.2f%s ants/turn\n", 
        EMOJI_ROCKET, COLOR_GREEN, stats->throughput, COLOR_RESET);
    
    long elapsed_us = stats->end_time_us - stats->start_time_us;
    double elapsed_ms = elapsed_us / 1000.0;
    printf("   %s Execution time:     %s%.3f ms%s\n", 
        EMOJI_FIRE, COLOR_GREEN, elapsed_ms, COLOR_RESET);
    
    printf("\n%s%s%s All ants reached destination successfully!%s\n", 
        COLOR_GREEN, COLOR_BOLD, EMOJI_CHECK, COLOR_RESET);
}

void print_moves_visual(colony_t *colony, int turn)
{
    int has_move = 0;
    int moves_count = 0;
    
    for (int i = 0; i < colony->ant_count; i++) {
        if (colony->ants[i]->current_room != colony->start)
            moves_count++;
    }
    
    if (moves_count == 0)
        return;
    
    printf("%s┌─ Turn %d ", COLOR_CYAN, turn);
    for (int i = 0; i < 50; i++)
        printf("─");
    printf("┐%s\n", COLOR_RESET);
    
    printf("%s│%s ", COLOR_CYAN, COLOR_RESET);
    
    for (int i = 0; i < colony->ant_count; i++) {
        ant_t *ant = colony->ants[i];
        
        if (ant->current_room == colony->start)
            continue;
        
        if (has_move) {
            printf("%s│%s ", COLOR_DIM, COLOR_RESET);
        }
        
        if (ant->current_room == colony->end) {
            printf("%s%sP%d%s %s✓ %s%s", 
                COLOR_GREEN, COLOR_BOLD, ant->id, COLOR_RESET,
                EMOJI_TARGET, ant->current_room->name, COLOR_RESET);
        } else {
            printf("%sP%d%s %s→ %s%s", 
                COLOR_YELLOW, ant->id, COLOR_RESET,
                EMOJI_HOME, ant->current_room->name, COLOR_RESET);
        }
        has_move = 1;
    }
    
    printf("\n%s└", COLOR_CYAN);
    for (int i = 0; i < 60; i++)
        printf("─");
    printf("┘%s\n", COLOR_RESET);
}

void clear_screen(void)
{
    printf("\033[2J\033[H");
}

void move_cursor(int row, int col)
{
    printf("\033[%d;%dH", row, col);
}

void save_cursor(void)
{
    printf("\033[s");
}

void restore_cursor(void)
{
    printf("\033[u");
}
