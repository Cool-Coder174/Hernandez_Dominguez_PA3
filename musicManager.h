#ifndef MUSIC_MANAGER_H
#define MUSIC_MANAGER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

// Structure for song duration
typedef struct Duration {
    int minutes;
    int seconds;
} Duration;

// Structure for a music record
typedef struct Record {
    char artist[100];
    char album[100];
    char song[100];
    char genre[50];
    Duration length;
    int timesPlayed;
    int rating;
} Record;

// Node for the doubly linked list
typedef struct Node {
    Record data;
    struct Node* prev;
    struct Node* next;
} Node;

// Function prototypes for list management
Node* makeNode(Record data);
int insertFront(Node** head, Record data);
void printList(Node* head);
void freeList(Node** head);

// Menu operations (PA2 and PA3 features)
void loadPlaylist(Node** head, const char* filename);
void storePlaylist(Node* head, const char* filename);
void displayRecords(Node* head);
void editRecord(Node* head);
void rateRecord(Node* head);
void playPlaylist(Node* head);
void insertRecord(Node** head);
void deleteRecord(Node** head);
void sortPlaylist(Node** head);
void shufflePlaylist(Node* head);

// Utility function
Record createRecordFromInput();
void swapRecords(Record* a, Record* b);

#endif
