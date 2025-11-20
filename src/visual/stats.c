#include "../../include/amaze.h"
#include "../../include/visual.h"
#include <sys/time.h>

static long get_time_us(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000000 + tv.tv_usec;
}

stats_t *init_stats(void)
{
    stats_t *stats = calloc(1, sizeof(stats_t));
    if (!stats)
        return NULL;
    
    stats->start_time_us = get_time_us();
    return stats;
}

void update_stats(stats_t *stats, colony_t *colony, int turn)
{
    stats->total_turns = turn;
    
    /* Count moves this turn */
    int moves_this_turn = 0;
    for (int i = 0; i < colony->ant_count; i++) {
        if (colony->ants[i]->current_room != colony->start)
            moves_this_turn++;
    }
    
    stats->total_moves += moves_this_turn;
}

void finalize_stats(stats_t *stats, colony_t *colony)
{
    stats->end_time_us = get_time_us();
    
    if (colony->ant_count > 0) {
        stats->avg_moves_per_ant = (double)stats->total_moves / colony->ant_count;
    }
    
    if (stats->total_turns > 0) {
        stats->throughput = (double)colony->ant_count / stats->total_turns;
    }
    
    /* Calculate efficiency (theoretical minimum vs actual) */
    if (colony->ants[0]->path_length > 0) {
        int theoretical_min = colony->ants[0]->path_length + colony->ant_count - 1;
        stats->efficiency = (double)theoretical_min / stats->total_turns * 100.0;
    }
}
