/*
** visual.h
** Visual interface with colors and animations
*/

#ifndef VISUAL_H
#define VISUAL_H

#include "amaze.h"

/* ANSI Color codes */
#define COLOR_RESET   "\033[0m"
#define COLOR_BOLD    "\033[1m"
#define COLOR_DIM     "\033[2m"

#define COLOR_RED     "\033[31m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_YELLOW  "\033[33m"
#define COLOR_BLUE    "\033[34m"
#define COLOR_MAGENTA "\033[35m"
#define COLOR_CYAN    "\033[36m"
#define COLOR_WHITE   "\033[37m"

#define BG_RED        "\033[41m"
#define BG_GREEN      "\033[42m"
#define BG_YELLOW     "\033[43m"
#define BG_BLUE       "\033[44m"
#define BG_MAGENTA    "\033[45m"
#define BG_CYAN       "\033[46m"

/* Box drawing characters */
#define BOX_H         "═"
#define BOX_V         "║"
#define BOX_TL        "╔"
#define BOX_TR        "╗"
#define BOX_BL        "╚"
#define BOX_BR        "╝"
#define BOX_VR        "╠"
#define BOX_VL        "╣"
#define BOX_HU        "╩"
#define BOX_HD        "╦"

/* Emojis and symbols */
#define EMOJI_ANT     "🐜"
#define EMOJI_HOME    "🏠"
#define EMOJI_TARGET  "🎯"
#define EMOJI_ARROW   "→"
#define EMOJI_CHECK   "✓"
#define EMOJI_CROSS   "✗"
#define EMOJI_STAR    "⭐"
#define EMOJI_FIRE    "🔥"
#define EMOJI_ROCKET  "🚀"

/* Visual mode flags */
typedef struct visual_config_s {
    int use_colors;
    int use_emojis;
    int show_stats;
    int show_graph;
    int animate;
    int verbose;
} visual_config_t;

/* Statistics */
typedef struct stats_s {
    int total_turns;
    int total_moves;
    double efficiency;
    double avg_moves_per_ant;
    double throughput;
    long start_time_us;
    long end_time_us;
} stats_t;

/* Visual functions */
void print_header(void);
void print_separator(int width);
void print_box_line(const char *content, int width);
void print_config_info(colony_t *colony);
void print_pathfinding_info(colony_t *colony);
void print_simulation_progress(colony_t *colony, int current_turn, int total_turns);
void print_statistics(stats_t *stats, colony_t *colony);
void print_graph_visual(colony_t *colony);
void print_moves_visual(colony_t *colony, int turn);
void clear_screen(void);
void move_cursor(int row, int col);
void save_cursor(void);
void restore_cursor(void);

/* Stats functions */
stats_t *init_stats(void);
void update_stats(stats_t *stats, colony_t *colony, int turn);
void finalize_stats(stats_t *stats, colony_t *colony);

/* Config */
extern visual_config_t g_visual_config;

#endif /* VISUAL_H */
