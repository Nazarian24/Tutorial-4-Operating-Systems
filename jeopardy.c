/*
 * Tutorial 4 Jeopardy Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "questions.h"
#include "players.h"
#include "jeopardy.h"

// Put macros or constants here using #define
#define BUFFER_LEN 256
#define NUM_PLAYERS 4

// Put global environment variables here

// Processes the answer from the user containing what is or who is and tokenizes it to retrieve the answer.
void tokenize(char *input, char **tokens) {
    char *token = strtok(input, " ");  // Tokenize based on spaces
    int index = 0;

    while (token != NULL) {
        tokens[index++] = token;
        token = strtok(NULL, " ");
    }
    tokens[index] = NULL;  // Null-terminate the array
};

// Displays the game results for each player, their name and final score, ranked from first to last place
void show_results(player *players, int num_players) {
    // Simple bubble sort to rank players by score
    for (int i = 0; i < num_players - 1; i++) {
        for (int j = 0; j < num_players - i - 1; j++) {
            if (players[j].score < players[j + 1].score) {
                // Swap players
                player temp = players[j];
                players[j] = players[j + 1];
                players[j + 1] = temp;
            }
        }
    }

    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Final Results~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    for (int i = 0; i < num_players; i++) {
        printf("%d. %s - %d points\n", i + 1, players[i].name, players[i].score);
    }
}

int main(int argc, char *argv[])
{
    // Allocate memory dynamically for players using malloc
    player *players = (player *)malloc(NUM_PLAYERS * sizeof(player));
    if (!players) {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    // Input buffer and commands
    char buffer[BUFFER_LEN] = { 0 };

    // Display the game introduction and initialize the questions
    initialize_game();

    // Prompt for players' names
    for (int i = 0; i < NUM_PLAYERS; i++) {
        printf("Enter name for Player %d: ", i + 1);
        fgets(players[i].name, MAX_LEN, stdin);
        players[i].name[strcspn(players[i].name, "\n")] = '\0';  // Remove newline character
        players[i].score = 0;  // Initialize score
    }

    // Start the game loop
    while (1) {
        printf("Enter a command (or 'exit' to quit): ");
        if (fgets(buffer, BUFFER_LEN, stdin) == NULL) {
            break;
        }

        // Remove newline character from buffer
        buffer[strcspn(buffer, "\n")] = '\0';

        // If user enters 'exit', break the loop
        if (strcmp(buffer, "exit") == 0) {
            break;
        }

        // Process player answers
        char *tokens[10] = {NULL};  // Max 10 tokens for safety
        tokenize(buffer, tokens);

        // Further game logic should go here, such as checking answers

        printf("Processing input: %s\n", buffer);  // Placeholder action
    }

    // Display final game results
    show_results(players, NUM_PLAYERS);

    // Free allocated memory
    free(players);

    return EXIT_SUCCESS;
}