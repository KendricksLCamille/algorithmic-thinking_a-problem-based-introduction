#ifndef CH1_HASH_TABLES_H
#define CH1_HASH_TABLES_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

constexpr int number_of_branches = 6;

int (*snow_flakes_dynamic_ptr)[number_of_branches] = NULL;
int *snowflake_sums = NULL; // Store precomputed sums
int current_num_snowflakes_global = 0;

void generate_random_snowflake(int snowflake[number_of_branches]) {
    for (int i = 0; i < number_of_branches; ++i) {
        snowflake[i] = (rand() % 2)+1;
    }
}

int sum(const int snowflake[number_of_branches]) {
    int total = 0;
    for (int i = 0; i < number_of_branches; ++i) {
        total += snowflake[i];
    }
    return total;
}

bool find_identical(const int snowflake1[number_of_branches], const int snowflake2[number_of_branches]) {
    for (int offset = 0; offset < number_of_branches; offset++) {
        bool match_left = true;
        bool match_right = true;
        for (int i = 0; i < number_of_branches; i++) {
            int s2_left = (offset + i) % number_of_branches;
            int s2_right = (offset - i + number_of_branches) % number_of_branches;
            if (snowflake1[i] != snowflake2[s2_left]) match_left = false;
            if (snowflake1[i] != snowflake2[s2_right]) match_right = false;
            if (!match_left && !match_right) break;
        }
        if (match_left || match_right)
            return true;
    }
    return false;
}

int compare(const void* snowflake1, const void* snowflake2)
{
    const int s1Sum = sum(snowflake1);
    const int s2Sum = sum(snowflake2);
    return s1Sum - s2Sum;
}

void test_identicals() {
    int num_snowflakes_to_generate = 10000;
    srand((unsigned int)time(NULL));

    // Allocate memory
    snow_flakes_dynamic_ptr = (int (*)[number_of_branches])malloc(num_snowflakes_to_generate * sizeof(int[number_of_branches]));
    if (!snow_flakes_dynamic_ptr) {
        fprintf(stderr, "Memory allocation failed!\n");
        return;
    }
    snowflake_sums = (int*)malloc(num_snowflakes_to_generate * sizeof(int));
    if (!snowflake_sums) {
        free(snow_flakes_dynamic_ptr);
        fprintf(stderr, "Memory allocation failed!\n");
        return;
    }

    current_num_snowflakes_global = num_snowflakes_to_generate;

    // Generate snowflakes and precompute sums
    for (int i = 0; i < current_num_snowflakes_global; ++i) {
        generate_random_snowflake(snow_flakes_dynamic_ptr[i]);
        snowflake_sums[i] = sum(snow_flakes_dynamic_ptr[i]);
    }

    printf("Generated %d snowflakes.\n", current_num_snowflakes_global);

    printf("Starting testing\n");
    clock_t start_time = clock();

    qsort(snow_flakes_dynamic_ptr, num_snowflakes_to_generate,sizeof(snow_flakes_dynamic_ptr[0]), compare);

    // Main comparison loop, can be parallelized
    for (int i1 = 0; i1 < current_num_snowflakes_global; ++i1) {
        const int *sf1 = snow_flakes_dynamic_ptr[i1];
        const int sf1Sum = snowflake_sums[i1];

        for (int i2 = i1 + 1; i2 < current_num_snowflakes_global; ++i2) {
            if (snowflake_sums[i2] != sf1Sum) break; // Skip if sums differ
            const int *sf2 = snow_flakes_dynamic_ptr[i2];

            if (find_identical(sf1, sf2)) {
                // Optional: do something with the pair
                // printf("Snowflakes %d and %d are identical.\n", i1, i2);
            }
        }
    }

    clock_t end_time = clock();

    double elapsed_time_seconds = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("Finished testing. Time taken: %.4f seconds.\n", elapsed_time_seconds);

    free(snow_flakes_dynamic_ptr);
    free(snowflake_sums);
    snow_flakes_dynamic_ptr = NULL;
    snowflake_sums = NULL;
    current_num_snowflakes_global = 0;
}
#endif //CH1_HASH_TABLES_H