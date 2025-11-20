#include "../include/amaze.h"
#include "../include/visual.h"
#include <string.h>

static int parse_args(int ac, char **av)
{
    for (int i = 1; i < ac; i++) {
        if (strcmp(av[i], "-v") == 0 || strcmp(av[i], "--verbose") == 0)
            g_visual_config.verbose = 1;
        else if (strcmp(av[i], "-s") == 0 || strcmp(av[i], "--stats") == 0)
            g_visual_config.show_stats = 1;
        else if (strcmp(av[i], "-g") == 0 || strcmp(av[i], "--graph") == 0)
            g_visual_config.show_graph = 1;
        else if (strcmp(av[i], "-a") == 0 || strcmp(av[i], "--animate") == 0)
            g_visual_config.animate = 1;
        else if (strcmp(av[i], "--no-color") == 0)
            g_visual_config.use_colors = 0;
        else if (strcmp(av[i], "--no-emoji") == 0)
            g_visual_config.use_emojis = 0;
        else if (strcmp(av[i], "-h") == 0 || strcmp(av[i], "--help") == 0) {
            printf("Usage: %s [OPTIONS] < input_file\n", av[0]);
            printf("\nOptions:\n");
            printf("  -v, --verbose    Show detailed information\n");
            printf("  -s, --stats      Show statistics\n");
            printf("  -g, --graph      Show graph visualization\n");
            printf("  -a, --animate    Animate simulation\n");
            printf("  --no-color       Disable colors\n");
            printf("  --no-emoji       Disable emojis\n");
            printf("  -h, --help       Show this help\n");
            return 0;
        }
    }
    return 1;
}

int main(int ac, char **av)
{
    char *input = read_stdin();
    colony_t *colony;
    int result;

    if (!parse_args(ac, av))
        return EXIT_SUCCESS;

    if (!input) {
        print_error("Failed to read input\n");
        return EXIT_ERROR;
    }

    colony = parse_input(input);
    if (!colony) {
        free(input);
        return EXIT_ERROR;
    }

    if (!validate_colony(colony)) {
        free_colony(colony);
        return EXIT_ERROR;
    }

    if (g_visual_config.verbose) {
        print_header();
        print_config_info(colony);
    }

    result = run_simulation(colony);
    free_colony(colony);

    return result;
}
