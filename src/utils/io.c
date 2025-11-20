#include "../../include/amaze.h"

char *read_stdin(void)
{
    char buffer[4096];
    char *content = NULL;
    int total_size = 0;
    ssize_t bytes_read;
    
    while ((bytes_read = read(0, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytes_read] = '\0';
        
        char *new_content = realloc(content, total_size + bytes_read + 1);
        if (!new_content) {
            free(content);
            return NULL;
        }
        
        content = new_content;
        
        if (total_size == 0)
            content[0] = '\0';
        
        strcat(content, buffer);
        total_size += bytes_read;
    }
    
    return content;
}

void print_moves(colony_t *colony)
{
    int has_move = 0;
    char buffer[256];
    
    for (int i = 0; i < colony->ant_count; i++) {
        ant_t *ant = colony->ants[i];
        
        /* Skip ants that haven't started */
        if (ant->current_room == colony->start)
            continue;
        
        /* Show ants that just moved (including those that just finished) */
        if (has_move)
            write(1, " ", 1);
        
        int len = snprintf(buffer, sizeof(buffer), "P%d-%s", 
            ant->id, ant->current_room->name);
        write(1, buffer, len);
        has_move = 1;
    }
    
    if (has_move)
        write(1, "\n", 1);
}

void print_error(char *message)
{
    write(2, "Error: ", 7);
    write(2, message, strlen(message));
}
