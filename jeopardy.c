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
    // Trim leading spaces
    while (*input == ' ') {
        input++;
    }

    // Check if input starts with "What is" or "Who is" and remove it
    if (strncmp(input, "What is ", 8) == 0) {
        input += 8;
    } else if (strncmp(input, "Who is ", 7) == 0) {
        input += 7;
    }

    // Tokenize the remaining string
    int index = 0;
    char *token = strtok(input, " ");
    while (token != NULL) {
        tokens[index++] = token;
        token = strtok(NULL, " ");
    }
    tokens[index] = NULL;  // Null-terminate the array
}

void display_questions() {
    printf("\nAvailable Questions:\n");
    for (int i = 0; i < NUM_QUESTIONS; i++) {
        if (!questions[i].answered) {
            printf("[%s] $%d: %s\n", questions[i].category, questions[i].value, questions[i].question);
        }
    }
}

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

// Check if all questions have been answered
bool all_questions_answered() {
    for (int i = 0; i < NUM_QUESTIONS; i++) {
        if (!questions[i].answered) {
            return false;
        }
    }
    return true;
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

    // Display available questions before starting the game loop
    display_questions();

    // Start the game loop
    int current_player = 0;  // Track the current player
    while (1) {
        // Check if all questions have been answered
        if (all_questions_answered()) {
            printf("\nAll questions have been answered!\n");
            break;
        }

        printf("\nCurrent Player: %s\n", players[current_player].name);
        printf("Enter the category and value (e.g., 'Science 200') or 'exit' to quit: ");
        if (fgets(buffer, BUFFER_LEN, stdin) == NULL) {
            break;
        }

        // Remove newline character from buffer
        buffer[strcspn(buffer, "\n")] = '\0';

        // If user enters 'exit', break the loop
        if (strcmp(buffer, "exit") == 0) {
            break;
        }

        // Process player input
        char *tokens[10] = {NULL};  // Max 10 tokens for safety
        tokenize(buffer, tokens);

        // Assuming the player selects a category and value (like "Science 200")
        if (tokens[0] && tokens[1]) {
            char *category = tokens[0];
            int value = atoi(tokens[1]);

            // Find the corresponding question for this category and value
            bool question_found = false;
            for (int i = 0; i < NUM_QUESTIONS; i++) {
                if (strcmp(questions[i].category, category) == 0 && questions[i].value == value) {
                    question_found = true;

                    // Check if the question has already been answered
                    if (questions[i].answered) {
                        printf("This question has already been answered. Please choose another.\n");
                        break;
                    }

                    // Display the question and prompt the player for the answer
                    printf("\nQuestion: %s\n", questions[i].question);
                    printf("Enter your answer: ");
                    fgets(buffer, BUFFER_LEN, stdin);
                    buffer[strcspn(buffer, "\n")] = '\0';  // Remove newline character

                    // Check the player's answer
                    char *tokens[10] = {NULL};
                    tokenize(buffer, tokens);  // Extract tokens

                    if (tokens[0] && strcmp(tokens[0], questions[i].answer) == 0) {
                        printf("Correct! You earned $%d.\n", value);
                        players[current_player].score += value;  // Adjust score for the current player
                        questions[i].answered = true;  // Mark the question as answered
                    } else {
                        printf("Incorrect. Try again next turn!\n");
                        // Do not mark the question as answered, allowing other players to attempt it
                    }

                    // Display updated scores
                    printf("\nUpdated Scores:\n");
                    for (int j = 0; j < NUM_PLAYERS; j++) {
                        printf("%s: $%d\n", players[j].name, players[j].score);
                    }

                    // Move to the next player
                    current_player = (current_player + 1) % NUM_PLAYERS;
                    break;
                }
            }

            if (!question_found) {
                printf("Invalid category or value. Please try again.\n");
            }
        } else {
            printf("Invalid input. Please enter a category and value (e.g., 'Science 200').\n");
        }
    }

    // Display final game results
    show_results(players, NUM_PLAYERS);

    // Free allocated memory
    free(players);

    return EXIT_SUCCESS;
}