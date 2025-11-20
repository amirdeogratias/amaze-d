#include "../../include/amaze.h"

typedef struct queue_node_s {
    room_t *room;
    struct queue_node_s *parent;
    struct queue_node_s *next;
} queue_node_t;

typedef struct {
    queue_node_t *head;
    queue_node_t *tail;
} queue_t;

static void enqueue(queue_t *queue, room_t *room, queue_node_t *parent)
{
    queue_node_t *node = malloc(sizeof(queue_node_t));
    node->room = room;
    node->parent = parent;
    node->next = NULL;
    
    if (!queue->tail) {
        queue->head = queue->tail = node;
    } else {
        queue->tail->next = node;
        queue->tail = node;
    }
}

static queue_node_t *dequeue(queue_t *queue)
{
    if (!queue->head)
        return NULL;
    
    queue_node_t *node = queue->head;
    queue->head = node->next;
    
    if (!queue->head)
        queue->tail = NULL;
    
    return node;
}

static int is_visited(room_t **visited, int count, room_t *room)
{
    for (int i = 0; i < count; i++) {
        if (visited[i] == room)
            return 1;
    }
    return 0;
}

static room_t **reconstruct_path(queue_node_t *end_node)
{
    if (!end_node)
        return NULL;
    
    int length = 0;
    queue_node_t *node = end_node;
    
    while (node) {
        length++;
        node = node->parent;
    }
    
    length--;
    
    room_t **path = malloc(sizeof(room_t*) * (length + 1));
    if (!path)
        return NULL;
    
    path[length] = NULL;
    
    node = end_node;
    for (int i = length - 1; i >= 0 && node; i--) {
        path[i] = node->room;
        node = node->parent;
    }
    
    return path;
}

room_t **find_path(colony_t *colony, room_t *start, room_t *end)
{
    if (!colony || !start || !end)
        return NULL;
    
    queue_t queue = {NULL, NULL};
    room_t **visited = malloc(sizeof(room_t*) * colony->room_count);
    int visited_count = 0;
    room_t **result = NULL;
    queue_node_t **all_nodes = malloc(sizeof(queue_node_t*) * colony->room_count * 10);
    int node_count = 0;
    
    enqueue(&queue, start, NULL);
    visited[visited_count++] = start;
    
    while (queue.head) {
        queue_node_t *current = dequeue(&queue);
        all_nodes[node_count++] = current;
        
        if (current->room == end) {
            result = reconstruct_path(current);
            break;
        }
        
        for (int i = 0; i < current->room->link_count; i++) {
            room_t *neighbor = current->room->links[i]->room;
            
            if (!is_visited(visited, visited_count, neighbor)) {
                visited[visited_count++] = neighbor;
                enqueue(&queue, neighbor, current);
            }
        }
    }
    
    for (int i = 0; i < node_count; i++)
        free(all_nodes[i]);
    
    while (queue.head) {
        queue_node_t *tmp = dequeue(&queue);
        free(tmp);
    }
    
    free(all_nodes);
    free(visited);
    return result;
}

int calculate_path_length(room_t **path)
{
    int length = 0;
    while (path && path[length])
        length++;
    return length;
}
