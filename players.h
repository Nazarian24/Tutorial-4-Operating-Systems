/*
 * Tutorial 4 Jeopardy Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, 
 * All rights reserved.
 *
 */
#ifndef PLAYERS_H_
#define PLAYERS_H_

#include <stdbool.h>

#define MAX_LEN 256  // Maximum length for player names

// Player struct to store player's name and score
typedef struct {
    char name[MAX_LEN];  // Player's name
    int score;  // Player's score
} player;

// Function to check if a player exists in the array of players
extern bool player_exists(player *players, int num_players, char *name);

// Function to update a player's score given their name
extern void update_score(player *players, int num_players, char *name, int score);

#endif /* PLAYERS_H_ */