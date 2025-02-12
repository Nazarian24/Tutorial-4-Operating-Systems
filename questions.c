/*
 * Tutorial 4 Jeopardy Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, Hasaan Rashidi 100876631, Arno Nazarian 100868853, Sanzir Anarbaev 100704172
 * All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "questions.h"

// Initializes the array of questions for the game
void initialize_game(void)
{
    strcpy(questions[0].category, "programming");
    strcpy(questions[0].question, "What language is this project written in?");
    strcpy(questions[0].answer, "C");
    questions[0].value = 100;
    questions[0].answered = false;

    strcpy(questions[1].category, "programming");
    strcpy(questions[1].question, "What does 'printf' do?");
    strcpy(questions[1].answer, "print");
    questions[1].value = 200;
    questions[1].answered = false;

    strcpy(questions[2].category, "programming");
    strcpy(questions[2].question, "What symbol is used to denote a pointer in C?");
    strcpy(questions[2].answer, "*");
    questions[2].value = 300;
    questions[2].answered = false;

    strcpy(questions[3].category, "programming");
    strcpy(questions[3].question, "What keyword is used to define a constant in C?");
    strcpy(questions[3].answer, "const");
    questions[3].value = 400;
    questions[3].answered = false;

    strcpy(questions[4].category, "algorithms");
    strcpy(questions[4].question, "What is the time complexity of binary search?");
    strcpy(questions[4].answer, "O(logn)");
    questions[4].value = 100;
    questions[4].answered = false;

    strcpy(questions[5].category, "algorithms");
    strcpy(questions[5].question, "What sorting algorithm has the worst-case time complexity of O(n^2)?");
    strcpy(questions[5].answer, "Bubble sort");
    questions[5].value = 200;
    questions[5].answered = false;

    strcpy(questions[6].category, "algorithms");
    strcpy(questions[6].question, "Which data structure uses LIFO ordering?");
    strcpy(questions[6].answer, "Stack");
    questions[6].value = 300;
    questions[6].answered = false;

    strcpy(questions[7].category, "algorithms");
    strcpy(questions[7].question, "What is the worst-case time complexity of quicksort?");
    strcpy(questions[7].answer, "O(n^2)");
    questions[7].value = 400;
    questions[7].answered = false;

    strcpy(questions[8].category, "databases");
    strcpy(questions[8].question, "What does SQL stand for?");
    strcpy(questions[8].answer, "Structured Query Language");
    questions[8].value = 100;
    questions[8].answered = false;

    strcpy(questions[9].category, "databases");
    strcpy(questions[9].question, "Which SQL command is used to retrieve data?");
    strcpy(questions[9].answer, "SELECT");
    questions[9].value = 200;
    questions[9].answered = false;

    strcpy(questions[10].category, "databases");
    strcpy(questions[10].question, "Which SQL clause is used to filter results?");
    strcpy(questions[10].answer, "WHERE");
    questions[10].value = 300;
    questions[10].answered = false;

    strcpy(questions[11].category, "databases");
    strcpy(questions[11].question, "Which type of join returns only matching rows from both tables?");
    strcpy(questions[11].answer, "INNER JOIN");
    questions[11].value = 400;
    questions[11].answered = false;
}

// Displays each of the remaining categories and question dollar values that have not been answered
void display_categories(void)
{
    printf("\nAvailable Categories and Questions:\n");
    for (int i = 0; i < NUM_QUESTIONS; i++) {
        if (!questions[i].answered) {
            printf("%s - $%d\n", questions[i].category, questions[i].value);
        }
    }
}

// Displays the question for the category and dollar value
void display_question(char *category, int value)
{
    for (int i = 0; i < NUM_QUESTIONS; i++) {
        if (!questions[i].answered && strcmp(questions[i].category, category) == 0 && questions[i].value == value) {
            printf("\nQuestion: %s\n", questions[i].question);
            return;
        }
    }
    printf("Question not found or already answered.\n");
}

// Returns true if the answer is correct for the question for that category and dollar value
bool valid_answer(char *category, int value, char *answer)
{
    for (int i = 0; i < NUM_QUESTIONS; i++) {
        if (!questions[i].answered && strcmp(questions[i].category, category) == 0 && questions[i].value == value) {
            return (strcmp(answer, questions[i].answer) == 0);
        }
    }
    return false;
}

// Returns true if the question has already been answered
bool already_answered(char *category, int value)
{
    for (int i = 0; i < NUM_QUESTIONS; i++) {
        if (strcmp(questions[i].category, category) == 0 && questions[i].value == value) {
            return questions[i].answered;
        }
    }
    return false;
}
