#include "../../include/amaze.h"

int count_words(char *str, char delimiter)
{
    int count = 0;
    int in_word = 0;
    
    for (int i = 0; str[i]; i++) {
        if (str[i] == delimiter) {
            in_word = 0;
        } else if (!in_word) {
            in_word = 1;
            count++;
        }
    }
    return count;
}

char **split_string(char *str, char delimiter)
{
    if (!str)
        return NULL;
    
    int word_count = count_words(str, delimiter);
    char **result = malloc(sizeof(char*) * (word_count + 1));
    int word_idx = 0;
    int start = 0;
    int i = 0;
    
    while (str[i]) {
        if (str[i] == delimiter) {
            if (i > start) {
                int len = i - start;
                result[word_idx] = malloc(len + 1);
                strncpy(result[word_idx], str + start, len);
                result[word_idx][len] = '\0';
                word_idx++;
            }
            start = i + 1;
        }
        i++;
    }
    
    /* Handle last word */
    if (i > start) {
        int len = i - start;
        result[word_idx] = malloc(len + 1);
        strncpy(result[word_idx], str + start, len);
        result[word_idx][len] = '\0';
        word_idx++;
    }
    
    result[word_idx] = NULL;
    return result;
}

void free_split(char **split)
{
    if (!split)
        return;
    
    for (int i = 0; split[i]; i++)
        free(split[i]);
    free(split);
}

int str_is_number(char *str)
{
    if (!str || !str[0])
        return 0;
    
    int i = 0;
    if (str[0] == '-')
        i = 1;
    
    for (; str[i]; i++) {
        if (str[i] < '0' || str[i] > '9')
            return 0;
    }
    return 1;
}

int my_atoi(char *str)
{
    int result = 0;
    int sign = 1;
    int i = 0;
    
    if (str[0] == '-') {
        sign = -1;
        i = 1;
    }
    
    for (; str[i]; i++) {
        result = result * 10 + (str[i] - '0');
    }
    
    return result * sign;
}
