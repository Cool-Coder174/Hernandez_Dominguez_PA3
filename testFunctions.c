#include "testFunctions.h"

// Test for the insert feature using a record with boundary values.
void testInsert() {
    printf("Running testInsert...\n");
    Node* head = NULL;
    Record rec;
    strcpy(rec.artist, "Perry, Katy");
    strcpy(rec.album, "Witness");
    strcpy(rec.song, "Chained to the Rhythm");
    strcpy(rec.genre, "pop");
    rec.length.minutes = 4;
    rec.length.seconds = 36;
    rec.timesPlayed = -1;  // Boundary test: negative times played
    rec.rating = 6;        // Boundary test: rating above allowed maximum
    if (insertFront(&head, rec))
        printf("Test Insert: Record inserted.\n");
    else
        printf("Test Insert: Record insertion failed.\n");
    printList(head);
    freeList(&head);
    printf("testInsert completed.\n");
}

// Test for the delete feature by deleting a record from a single-item list.
void testDelete() {
    printf("Running testDelete...\n");
    Node* head = NULL;
    Record rec;
    strcpy(rec.artist, "Perry, Katy");
    strcpy(rec.album, "Witness");
    strcpy(rec.song, "Chained to the Rhythm");
    strcpy(rec.genre, "pop");
    rec.length.minutes = 4;
    rec.length.seconds = 36;
    rec.timesPlayed = 3;
    rec.rating = 5;
    insertFront(&head, rec);
    printf("Before deletion:\n");
    printList(head);
    // Delete the record matching the song title.
    char songToDelete[100];
    strcpy(songToDelete, "Chained to the Rhythm");
    Node* current = head;
    while (current) {
        if (strcasecmp(current->data.song, songToDelete) == 0) {
            if (current->prev)
                current->prev->next = current->next;
            else
                head = current->next;
            if (current->next)
                current->next->prev = current->prev;
            free(current);
            break;
        }
        current = current->next;
    }
    printf("After deletion (expected empty list):\n");
    printList(head);
    freeList(&head);
    printf("testDelete completed.\n");
}

// Test for the shuffle feature using three records.
// For consistency in testing, we fix the random seed.
void testShuffle() {
    printf("Running testShuffle...\n");
    Node* head = NULL;
    Record rec1, rec2, rec3;
    strcpy(rec1.artist, "Artist One");
    strcpy(rec1.album, "Album One");
    strcpy(rec1.song, "Song One");
    strcpy(rec1.genre, "Genre One");
    rec1.length.minutes = 3;
    rec1.length.seconds = 30;
    rec1.timesPlayed = 5;
    rec1.rating = 4;

    strcpy(rec2.artist, "Artist Two");
    strcpy(rec2.album, "Album Two");
    strcpy(rec2.song, "Song Two");
    strcpy(rec2.genre, "Genre Two");
    rec2.length.minutes = 4;
    rec2.length.seconds = 0;
    rec2.timesPlayed = 2;
    rec2.rating = 3;

    strcpy(rec3.artist, "Artist Three");
    strcpy(rec3.album, "Album Three");
    strcpy(rec3.song, "Song Three");
    strcpy(rec3.genre, "Genre Three");
    rec3.length.minutes = 5;
    rec3.length.seconds = 15;
    rec3.timesPlayed = 7;
    rec3.rating = 5;

    insertFront(&head, rec1);
    insertFront(&head, rec2);
    insertFront(&head, rec3);

    // For a deterministic test, set a fixed seed.
    srand(1);
    shufflePlaylist(head);

    freeList(&head);
    printf("testShuffle completed.\n");
}
//
// Created by Isaac Hernandez on 2/23/25.
//
