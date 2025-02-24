#include "musicManager.h"
#include "testFunctions.h"

int main() {
    Node* head = NULL;
    int choice;
    char filename[] = "musicPlayList.csv";

    do {
        printf("=== Digital Music Manager ===\n");
        printf("1. Load playlist\n");
        printf("2. Store playlist\n");
        printf("3. Display records\n");
        printf("4. Insert record\n");
        printf("5. Delete record\n");
        printf("6. Edit record\n");
        printf("7. Sort playlist\n");
        printf("8. Rate record\n");
        printf("9. Play playlist\n");
        printf("10. Shuffle playlist\n");
        printf("11. Run test functions\n");
        printf("12. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // consume newline

        switch(choice) {
            case 1:
                loadPlaylist(&head, filename);
                break;
            case 2:
                storePlaylist(head, filename);
                break;
            case 3:
                displayRecords(head);
                break;
            case 4:
                insertRecord(&head);
                break;
            case 5:
                deleteRecord(&head);
                break;
            case 6:
                editRecord(head);
                break;
            case 7:
                sortPlaylist(&head);
                break;
            case 8:
                rateRecord(head);
                break;
            case 9:
                playPlaylist(head);
                break;
            case 10:
                shufflePlaylist(head);
                break;
            case 11:
                // Run test functions
                testInsert();
                testDelete();
                testShuffle();
                break;
            case 12:
                // Before exiting, store the playlist to file.
                storePlaylist(head, filename);
                freeList(&head);
                printf("Exiting the Digital Music Manager. Rock on!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 12);

    return 0;
}
// Compare this snippet from testFunctions.c:
//     printf("Running testInsert...\n");
//     Node* head = NULL;
//     Record rec1, rec2, rec3;
//     strcpy(rec1.artist, "Artist One");
//     strcpy(rec1.album, "Album One");
//     strcpy(rec1.song, "Song One");
//     strcpy(rec1.genre, "Genre One");
//     rec1.length.minutes = 3;
//     rec1.length.seconds = 30;
//     rec1.timesPlayed = 5;
//     rec1.rating = 4;