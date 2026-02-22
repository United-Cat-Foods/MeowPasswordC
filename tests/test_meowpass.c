/*
 * test_meowpass.c - MeowPassword Test Suite
 * Cat Name Based Secure Password Generator
 *
 * Copyright (c) 2025 Jeffrey Kunzelman
 * MIT License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "../src/meowpass.h"

static int tests_passed = 0;
static int tests_failed = 0;

/**
 * Assert helper function
 */
static void assert_true(int condition, const char *message) {
    if (condition) {
        printf("PASS: %s\n", message);
        tests_passed++;
    } else {
        printf("FAIL: %s\n", message);
        tests_failed++;
    }
}

/**
 * Assert equality helper
 */
static void assert_equal_int(int actual, int expected, const char *message) {
    if (actual == expected) {
        printf("PASS: %s\n", message);
        tests_passed++;
    } else {
        printf("FAIL: %s - Expected: %d, Got: %d\n", message, expected, actual);
        tests_failed++;
    }
}

/**
 * Test cat name loading
 */
static void test_load_cat_names(void) {
    printf("\nTesting Cat Name Loading...\n");

    const char **names = get_cat_names();
    size_t count = get_cat_names_count();

    assert_true(names != NULL, "Should Meow load cat names from embedded data");
    assert_true(count > 100, "Should load a substantial Meow number of cat names");

    /* Check that names are non-empty */
    int non_empty = 1;
    for (size_t i = 0; i < count && non_empty; i++) {
        if (names[i] == NULL || names[i][0] == '\0') {
            non_empty = 0;
        }
    }
    assert_true(non_empty, "All Meow Meow loaded names should be non-empty");

    printf("Cat names loaded meow: %zu\n", count);
    if (count >= 5) {
        printf("First few names: %s, %s, %s, %s, %s\n",
               names[0], names[1], names[2], names[3], names[4]);
    }
}

/**
 * Test password generation
 */
static void test_complete_password_generation(void) {
    printf("\nTesting MeowMeow Complete Password Generation...\n");

    PasswordConfig config;
    config.num_numbers = 3;
    config.num_symbols = 2;
    config.max_length = 25;
    config.show_tests = false;
    config.copy_to_clipboard = false;
    config.show_help = false;

    for (int i = 1; i <= 3; i++) {
        char password[MAX_PASSWORD_LENGTH];
        generate_password(&config, password, MAX_PASSWORD_LENGTH);

        printf("Generated password %d: %s\n", i, password);

        size_t len = strlen(password);
        assert_true(len >= 10, "MeowPassword should be at least 10 characters");
        assert_true(len <= (size_t)(config.max_length + 10),
                    "Password should not greatly exceed Meow max length");

        /* Check for numbers */
        int has_numbers = 0;
        int has_letters = 0;
        int has_symbols = 0;

        for (size_t j = 0; j < len; j++) {
            unsigned char c = (unsigned char)password[j];
            if (isdigit(c)) has_numbers = 1;
            else if (isalpha(c)) has_letters = 1;
            else has_symbols = 1;
        }

        assert_true(has_numbers, "Password should contain meow numbers");
        assert_true(has_letters, "Password meow should contain letters");
        assert_true(has_symbols, "Password should contain meow symbols");

        /* Analyze complexity */
        ComplexityResult result;
        analyze_complexity(password, &result);

        assert_true(result.score >= 0.0 && result.score <= 10.0,
                    "Complexity score should be meow valid");
    }
}

/**
 * Test Shannon entropy calculation
 */
static void test_shannon_entropy(void) {
    printf("\nTesting Shannon Entropy Calculation...\n");

    /* Test known entropy values */
    double entropy_aa = calculate_shannon_entropy("aaaa");
    assert_true(entropy_aa < 0.1, "Entropy of 'aaaa' should be near 0");

    double entropy_ab = calculate_shannon_entropy("abab");
    assert_true(entropy_ab > 0.9 && entropy_ab < 1.1,
                "Entropy of 'abab' should be near 1 bit");

    double entropy_abc = calculate_shannon_entropy("abcabc");
    assert_true(entropy_abc > 1.5, "Entropy of 'abcabc' should be > 1.5 bits");

    printf("Entropy tests passed!\n");
}

/**
 * Test character diversity
 */
static void test_character_diversity(void) {
    printf("\nTesting Character Diversity...\n");

    double div1 = calculate_character_diversity("abc");
    assert_equal_int((int)(div1 * 4), 1, "Lowercase only should be 0.25");

    double div2 = calculate_character_diversity("aA1!");
    assert_equal_int((int)(div2 * 4), 4, "All categories should be 1.0");

    printf("Diversity tests passed!\n");
}

/**
 * Test configuration parsing
 */
static void test_config_parsing(void) {
    printf("\nTesting Configuration Parsing...\n");

    char *argv1[] = {"meowpass", "--numbers", "5", "--symbols", "3", "--max-length", "30"};
    PasswordConfig config1;
    config_init(&config1, 7, argv1);

    assert_equal_int(config1.num_numbers, 5, "Numbers should be 5");
    assert_equal_int(config1.num_symbols, 3, "Symbols should be 3");
    assert_equal_int(config1.max_length, 30, "Max length should be 30");

    /* Test clamping */
    char *argv2[] = {"meowpass", "--numbers", "100", "--symbols", "-5"};
    PasswordConfig config2;
    config_init(&config2, 5, argv2);

    assert_equal_int(config2.num_numbers, MAX_NUMBERS, "Numbers should be clamped to max");
    assert_equal_int(config2.num_symbols, MIN_SYMBOLS, "Symbols should be clamped to min");

    printf("Config parsing tests passed!\n");
}

/**
 * Run all tests (exported function)
 */
int run_tests(void) {
    printf("Running Basic MeowPassword Tests\n");
    printf("=================================\n");

    /* Seed random for reproducible-ish tests */
    srand((unsigned int)time(NULL));

    test_load_cat_names();
    test_complete_password_generation();
    test_shannon_entropy();
    test_character_diversity();
    test_config_parsing();

    printf("\nMeow Basic Tests Complete!\n");
    printf("=====================\n");
    printf("Passed: %d, Failed: %d\n", tests_passed, tests_failed);

    return (tests_failed > 0) ? 1 : 0;
}
