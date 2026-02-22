/*
 * complexity.c - Kolmogorov Complexity and Shannon Entropy Analysis
 * MeowPassword - Cat Name Based Secure Password Generator
 *
 * Copyright (c) 2025 Jeffrey Kunzelman
 * MIT License
 */

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "meowpass.h"

/* Hash table size for character counting */
#define HASH_SIZE 256

double calculate_shannon_entropy(const char *str) {
    if (!str || *str == '\0') return 0.0;

    size_t len = strlen(str);
    int char_counts[HASH_SIZE] = {0};

    /* Count character occurrences */
    for (size_t i = 0; i < len; i++) {
        unsigned char c = (unsigned char)str[i];
        char_counts[c]++;
    }

    /* Calculate entropy */
    double entropy = 0.0;
    double dlen = (double)len;

    for (int i = 0; i < HASH_SIZE; i++) {
        if (char_counts[i] > 0) {
            double probability = (double)char_counts[i] / dlen;
            entropy -= probability * log2(probability);
        }
    }

    return entropy;
}

double calculate_compression_ratio(const char *str) {
    if (!str || *str == '\0') return 0.0;

    size_t len = strlen(str);

    /* Simple run-length encoding approximation */
    int compressed = 0;
    char previous = '\0';
    int run_length = 1;

    for (size_t i = 0; i < len; i++) {
        char current = str[i];
        if (current == previous) {
            run_length++;
        } else {
            compressed += (run_length > 1) ? 2 : 1;
            run_length = 1;
            previous = current;
        }
    }
    compressed += (run_length > 1) ? 2 : 1;

    return 1.0 - ((double)compressed / (double)len);
}

/**
 * Get substrings of specified max length and count unique ones
 */
double calculate_pattern_complexity(const char *str) {
    if (!str || *str == '\0') return 0.0;

    size_t len = strlen(str);
    if (len < 2) return 0.0;

    int max_substr_len = 4;
    int total_substrings = 0;
    int unique_substrings = 0;

    /* Simple uniqueness check using array comparison */
    /* For each substring length 2 to max_substr_len */
    char **substrings = NULL;
    size_t substr_capacity = 0;
    size_t substr_count = 0;

    for (int slen = 2; slen <= max_substr_len && slen <= (int)len; slen++) {
        for (size_t start = 0; start <= len - slen; start++) {
            total_substrings++;

            /* Check if this substring is unique */
            int is_unique = 1;
            for (size_t j = 0; j < substr_count; j++) {
                if (strncmp(&str[start], substrings[j], slen) == 0 &&
                    strlen(substrings[j]) == (size_t)slen) {
                    is_unique = 0;
                    break;
                }
            }

            if (is_unique) {
                /* Add to list */
                if (substr_count >= substr_capacity) {
                    substr_capacity = (substr_capacity == 0) ? 64 : substr_capacity * 2;
                    char **new_arr = realloc(substrings, substr_capacity * sizeof(char *));
                    if (!new_arr) break;
                    substrings = new_arr;
                }
                substrings[substr_count] = malloc(slen + 1);
                if (substrings[substr_count]) {
                    strncpy(substrings[substr_count], &str[start], slen);
                    substrings[substr_count][slen] = '\0';
                    substr_count++;
                    unique_substrings++;
                }
            }
        }
    }

    /* Free allocated memory */
    for (size_t i = 0; i < substr_count; i++) {
        free(substrings[i]);
    }
    free(substrings);

    if (total_substrings == 0) return 0.0;
    return (double)unique_substrings / (double)total_substrings;
}

double calculate_character_diversity(const char *str) {
    if (!str || *str == '\0') return 0.0;

    int has_lower = 0;
    int has_upper = 0;
    int has_digit = 0;
    int has_symbol = 0;

    for (const char *p = str; *p; p++) {
        unsigned char c = (unsigned char)*p;
        if (islower(c)) has_lower = 1;
        else if (isupper(c)) has_upper = 1;
        else if (isdigit(c)) has_digit = 1;
        else if (!isspace(c)) has_symbol = 1;
    }

    int categories = has_lower + has_upper + has_digit + has_symbol;
    return (double)categories / 4.0;
}

void analyze_complexity(const char *password, ComplexityResult *result) {
    if (!password || !result) return;

    result->length = (int)strlen(password);
    result->entropy = calculate_shannon_entropy(password);
    result->compression_ratio = calculate_compression_ratio(password);
    result->pattern_complexity = calculate_pattern_complexity(password);
    result->character_diversity = calculate_character_diversity(password);

    /* Weighted complexity score (same formula as Swift version) */
    double score = (result->entropy * 0.3) +
                   (result->compression_ratio * 0.25) +
                   (result->pattern_complexity * 0.2) +
                   (result->character_diversity * 0.15) +
                   (fmin((double)result->length / 25.0, 1.0) * 0.1);

    result->score = fmin(score, 10.0);
}
