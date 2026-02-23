/*
 * password.c - Password Generation Functions
 * MeowPassword - Cat Name Based Secure Password Generator
 *
 * Copyright (c) 2025 Jeffrey Kunzelman
 * MIT License
 */

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "meowpass.h"

/* Symbols for replacement */
static const char SYMBOLS[] = "!@#$%^&*()-_=+[]{;:.<>?";
static const char NUMBERS[] = "0123456789";

/**
 * Shuffle an array of indices (Fisher-Yates)
 */
static void shuffle_indices(size_t *arr, size_t n) {
    for (size_t i = n - 1; i > 0; i--) {
        size_t j = rand() % (i + 1);
        size_t tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }
}

/**
 * Select random cat names and join them
 */
static void select_and_join_names(int count, char *output, size_t output_size, int max_length) {
    (void)output_size; /* Reserved for future bounds checking */
    const char **names = get_cat_names();
    size_t names_count = get_cat_names_count();

    if (names_count == 0 || count <= 0) {
        output[0] = '\0';
        return;
    }

    /* Create indices for random selection */
    size_t *indices = malloc(names_count * sizeof(size_t));
    if (!indices) {
        output[0] = '\0';
        return;
    }

    for (size_t i = 0; i < names_count; i++) {
        indices[i] = i;
    }
    shuffle_indices(indices, names_count);

    /* Join selected names (lowercase, no spaces) */
    output[0] = '\0';
    size_t out_len = 0;
    int actual_count = (count > (int)names_count) ? (int)names_count : count;

    for (int i = 0; i < actual_count && out_len < (size_t)(max_length - 1); i++) {
        const char *name = names[indices[i]];
        for (const char *p = name; *p && out_len < (size_t)(max_length - 1); p++) {
            if (*p != ' ') {
                output[out_len++] = (char)tolower((unsigned char)*p);
            }
        }
    }
    output[out_len] = '\0';

    /* If too short, add more names */
    if (out_len < MIN_LENGTH) {
        shuffle_indices(indices, names_count);
        for (int i = 0; i < 5 && out_len < (size_t)max_length; i++) {
            const char *name = names[indices[i]];
            for (const char *p = name; *p && out_len < (size_t)(max_length - 1); p++) {
                if (*p != ' ') {
                    output[out_len++] = (char)tolower((unsigned char)*p);
                }
            }
        }
        output[out_len] = '\0';
    }

    free(indices);

    /* Truncate to max length */
    if (strlen(output) > (size_t)max_length) {
        output[max_length] = '\0';
    }
}

void randomly_capitalize(char *password, int count) {
    size_t len = strlen(password);
    if (len == 0 || count <= 0) return;

    /* Find letter indices */
    size_t *letter_indices = malloc(len * sizeof(size_t));
    if (!letter_indices) return;

    size_t letter_count = 0;
    for (size_t i = 0; i < len; i++) {
        if (isalpha((unsigned char)password[i])) {
            letter_indices[letter_count++] = i;
        }
    }

    if (letter_count == 0) {
        free(letter_indices);
        return;
    }

    /* Shuffle and capitalize */
    shuffle_indices(letter_indices, letter_count);
    int to_cap = (count > (int)letter_count) ? (int)letter_count : count;

    for (int i = 0; i < to_cap; i++) {
        size_t idx = letter_indices[i];
        password[idx] = (char)toupper((unsigned char)password[idx]);
    }

    free(letter_indices);
}

void insert_random_numbers(char *password, size_t password_size, int count) {
    size_t len = strlen(password);
    size_t num_chars = strlen(NUMBERS);

    for (int i = 0; i < count; i++) {
        if (len >= password_size - 1) break;

        /* Pick random number character */
        char num = NUMBERS[rand() % num_chars];

        /* Pick random insert position */
        size_t pos = rand() % (len + 1);

        /* Shift characters right */
        memmove(&password[pos + 1], &password[pos], len - pos + 1);
        password[pos] = num;
        len++;
    }
}

void replace_with_symbols(char *password, int count) {
    size_t len = strlen(password);
    if (len == 0 || count <= 0) return;

    size_t sym_chars = strlen(SYMBOLS);

    /* Find letter indices */
    size_t *letter_indices = malloc(len * sizeof(size_t));
    if (!letter_indices) return;

    size_t letter_count = 0;
    for (size_t i = 0; i < len; i++) {
        if (isalpha((unsigned char)password[i])) {
            letter_indices[letter_count++] = i;
        }
    }

    if (letter_count == 0) {
        free(letter_indices);
        return;
    }

    /* Shuffle and replace */
    shuffle_indices(letter_indices, letter_count);
    int to_replace = (count > (int)letter_count) ? (int)letter_count : count;

    for (int i = 0; i < to_replace; i++) {
        size_t idx = letter_indices[i];
        password[idx] = SYMBOLS[rand() % sym_chars];
    }

    free(letter_indices);
}

void generate_password(const PasswordConfig *config, char *output, size_t output_size) {
    /* Step 1: Select 2-6 random cat names */
    int name_count = (rand() % 5) + 2;  /* 2 to 6 names */

    /* Step 2: Create base phrase */
    select_and_join_names(name_count, output, output_size, config->max_length);

    /* Step 3: Apply security transformations */
    randomly_capitalize(output, 3);
    insert_random_numbers(output, output_size, config->num_numbers);

    /* Truncate before symbol replacement so symbols aren't placed past max_length */
    if (strlen(output) > (size_t)config->max_length) {
        output[config->max_length] = '\0';
    }
    replace_with_symbols(output, config->num_symbols);
}
