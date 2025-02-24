#include "musicManager.h"

// Allocates a new node and initializes it with the given record.
Node* makeNode(Record data) {
    Node* newNode = malloc(sizeof(Node));
    if (!newNode) {
        printf("Error: Memory allocation failed. The music gods are disappointed.\n");
        return NULL;
    }
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Inserts a new node at the front of the list.
int insertFront(Node** head, Record data) {
    Node* newNode = makeNode(data);
    if (!newNode) return 0;
    newNode->next = *head;
    if (*head != NULL)
        (*head)->prev = newNode;
    *head = newNode;
    return 1;
}

// Prints all records in the list.
void printList(Node* head) {
    Node* current = head;
    if (!current) {
        printf("Playlist is empty. Time to add some jams!\n");
        return;
    }
    printf("=== Digital Music Manager Playlist ===\n");
    while (current) {
        printf("Artist: %s\n", current->data.artist);
        printf("Album: %s\n", current->data.album);
        printf("Song: %s\n", current->data.song);
        printf("Genre: %s\n", current->data.genre);
        printf("Length: %d:%02d\n", current->data.length.minutes, current->data.length.seconds);
        printf("Times Played: %d\n", current->data.timesPlayed);
        printf("Rating: %d\n", current->data.rating);
        printf("-------------------------------\n");
        current = current->next;
    }
}

// Frees all nodes in the list.
void freeList(Node** head) {
    Node* current = *head;
    while (current) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    *head = NULL;
}

// Loads the playlist from a CSV file.
// The CSV format is: artist,album,song,genre,duration,timesPlayed,rating
// Duration is provided as mm:ss.
void loadPlaylist(Node** head, const char* filename) {
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        printf("Error: Could not open file %s for reading. Check if it exists.\n", filename);
        return;
    }
    char line[512];
    // Clear any existing list
    freeList(head);
    while (fgets(line, sizeof(line), fp)) {
        // Remove newline character if present
        line[strcspn(line, "\n")] = 0;
        if (strlen(line) == 0) continue; // skip empty lines
        Record rec;
        char durationStr[10];
        // Parse CSV: artist,album,song,genre,duration,timesPlayed,rating
        char* token = strtok(line, ",");
        if(token) strcpy(rec.artist, token);
        token = strtok(NULL, ",");
        if(token) strcpy(rec.album, token);
        token = strtok(NULL, ",");
        if(token) strcpy(rec.song, token);
        token = strtok(NULL, ",");
        if(token) strcpy(rec.genre, token);
        token = strtok(NULL, ",");
        if(token) {
            strcpy(durationStr, token);
            sscanf(durationStr, "%d:%d", &rec.length.minutes, &rec.length.seconds);
        }
        token = strtok(NULL, ",");
        if(token) rec.timesPlayed = atoi(token);
        token = strtok(NULL, ",");
        if(token) rec.rating = atoi(token);
        // Insert each record at the front
        if (!insertFront(head, rec)) {
            printf("Error: Failed to insert record for song %s\n", rec.song);
        }
    }
    fclose(fp);
    printf("Playlist loaded successfully from %s!\n", filename);
}

// Stores the current playlist to a CSV file.
void storePlaylist(Node* head, const char* filename) {
    FILE* fp = fopen(filename, "w");
    if (!fp) {
        printf("Error: Could not open file %s for writing. The playlist is in trouble!\n", filename);
        return;
    }
    Node* current = head;
    while (current) {
        fprintf(fp, "%s,%s,%s,%s,%d:%02d,%d,%d\n",
                current->data.artist,
                current->data.album,
                current->data.song,
                current->data.genre,
                current->data.length.minutes,
                current->data.length.seconds,
                current->data.timesPlayed,
                current->data.rating);
        current = current->next;
    }
    fclose(fp);
    printf("Playlist stored successfully to %s!\n", filename);
}

// Displays records; allows either printing all records or filtering by artist.
void displayRecords(Node* head) {
    int choice;
    printf("Display Options:\n");
    printf("1. Display all records\n");
    printf("2. Display records by artist\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
    getchar(); // consume newline
    if (choice == 1) {
        printList(head);
    } else if (choice == 2) {
        char artist[100];
        printf("Enter artist name to filter: ");
        fgets(artist, sizeof(artist), stdin);
        artist[strcspn(artist, "\n")] = 0;
        Node* current = head;
        bool found = false;
        while (current) {
            if (strcasecmp(current->data.artist, artist) == 0) {
                printf("Artist: %s\n", current->data.artist);
                printf("Album: %s\n", current->data.album);
                printf("Song: %s\n", current->data.song);
                printf("Genre: %s\n", current->data.genre);
                printf("Length: %d:%02d\n", current->data.length.minutes, current->data.length.seconds);
                printf("Times Played: %d\n", current->data.timesPlayed);
                printf("Rating: %d\n", current->data.rating);
                printf("-------------------------------\n");
                found = true;
            }
            current = current->next;
        }
        if (!found) {
            printf("No records found for artist \"%s\". Time to broaden your musical horizons!\n", artist);
        }
    } else {
        printf("Invalid choice. Returning to main menu.\n");
    }
}

// Allows editing of a record found by artist.
// If multiple records match, the user chooses which one to edit.
void editRecord(Node* head) {
    char artist[100];
    printf("Enter artist name to edit record: ");
    fgets(artist, sizeof(artist), stdin);
    artist[strcspn(artist, "\n")] = 0;
    Node* current = head;
    int count = 0;
    Node* matches[100]; // assume no more than 100 matches
    while (current) {
        if (strcasecmp(current->data.artist, artist) == 0) {
            matches[count++] = current;
        }
        current = current->next;
    }
    if (count == 0) {
        printf("No record found for artist \"%s\".\n", artist);
        return;
    }
    int selection = 0;
    if (count > 1) {
        printf("Multiple records found for artist \"%s\":\n", artist);
        for (int i = 0; i < count; i++) {
            printf("%d. Song: %s, Album: %s\n", i+1, matches[i]->data.song, matches[i]->data.album);
        }
        printf("Select record to edit (1-%d): ", count);
        scanf("%d", &selection);
        getchar(); // consume newline
        if (selection < 1 || selection > count) {
            printf("Invalid selection. Returning to main menu.\n");
            return;
        }
    } else {
        selection = 1;
    }
    // Sorry for the long line, but it's just a prompt...
    Node* target = matches[selection - 1];
    printf("Editing record for song \"%s\" by \"%s\".\n", target->data.song, target->data.artist);
    // Prompt for new details (press enter to update)
    printf("Enter new artist (current: %s): ", target->data.artist);
    fgets(target->data.artist, sizeof(target->data.artist), stdin);
    target->data.artist[strcspn(target->data.artist, "\n")] = 0;
    printf("Enter new album (current: %s): ", target->data.album);
    fgets(target->data.album, sizeof(target->data.album), stdin);
    target->data.album[strcspn(target->data.album, "\n")] = 0;
    printf("Enter new song title (current: %s): ", target->data.song);
    fgets(target->data.song, sizeof(target->data.song), stdin);
    target->data.song[strcspn(target->data.song, "\n")] = 0;
    printf("Enter new genre (current: %s): ", target->data.genre);
    fgets(target->data.genre, sizeof(target->data.genre), stdin);
    target->data.genre[strcspn(target->data.genre, "\n")] = 0;
    printf("Enter new song length (mm:ss) (current: %d:%02d): ", target->data.length.minutes, target->data.length.seconds);
    char durationStr[10];
    fgets(durationStr, sizeof(durationStr), stdin);
    sscanf(durationStr, "%d:%d", &target->data.length.minutes, &target->data.length.seconds);
    printf("Enter new times played (current: %d): ", target->data.timesPlayed);
    char buffer[10];
    fgets(buffer, sizeof(buffer), stdin);
    target->data.timesPlayed = atoi(buffer);
    printf("Enter new rating (1-5) (current: %d): ", target->data.rating);
    fgets(buffer, sizeof(buffer), stdin);
    target->data.rating = atoi(buffer);
    printf("Record updated successfully!\n");
}

// Allows rating a record by searching for the song title.
void rateRecord(Node* head) {
    char song[100];
    printf("Enter song title to rate: ");
    fgets(song, sizeof(song), stdin);
    song[strcspn(song, "\n")] = 0;
    Node* current = head;
    while (current) {
        if (strcasecmp(current->data.song, song) == 0) {
            printf("Current rating for \"%s\" is %d.\n", current->data.song, current->data.rating);
            printf("Enter new rating (1-5): ");
            char buffer[10];
            fgets(buffer, sizeof(buffer), stdin);
            int newRating = atoi(buffer);
            if (newRating < 1 || newRating > 5) {
                printf("Invalid rating. Must be between 1 and 5. No changes made.\n");
            } else {
                current->data.rating = newRating;
                printf("Rating updated successfully!\n");
            }
            return;
        }
        current = current->next;
    }
    printf("Song \"%s\" not found.\n", song);
}

// Simulates playing the playlist.
// The user may specify a starting song; otherwise playback starts at the beginning.
void playPlaylist(Node* head) {
    if (!head) {
        printf("Playlist is empty. Add some tunes first!\n");
        return;
    }
    char song[100];
    printf("Enter song title to start playing from (or press enter to play from beginning): ");
    fgets(song, sizeof(song), stdin);
    song[strcspn(song, "\n")] = 0;
    Node* current = head;
    if (strlen(song) > 0) {
        // Find the starting song
        while (current && strcasecmp(current->data.song, song) != 0) {
            current = current->next;
        }
        if (!current) {
            printf("Song not found. Starting from the beginning.\n");
            current = head;
        }
    }
    // Simulate playing each song with a short delay
    while (current) {
        printf("Now playing: %s - %s [%s] (%d:%02d) | Played: %d times | Rating: %d\n",
               current->data.artist,
               current->data.song,
               current->data.album,
               current->data.length.minutes,
               current->data.length.seconds,
               current->data.timesPlayed,
               current->data.rating);
#ifdef _WIN32
        Sleep(2000);
        system("cls");
#else
        sleep(2);
        system("clear");
#endif
        current = current->next;
    }
    printf("Reached end of playlist.\n");
}

// Inserts a new record (prompts the user for details) and adds it at the front.
void insertRecord(Node** head) {
    printf("Insert a new record:\n");
    Record rec = createRecordFromInput();
    if (insertFront(head, rec))
        printf("Record inserted successfully!\n");
    else
        printf("Failed to insert record.\n");
}

// Deletes a record matching a song title.
void deleteRecord(Node** head) {
    if (!*head) {
        printf("Playlist is empty. Nothing to delete.\n");
        return;
    }
    char song[100];
    printf("Enter song title to delete: ");
    fgets(song, sizeof(song), stdin);
    song[strcspn(song, "\n")] = 0;
    Node* current = *head;
    while (current) {
        if (strcasecmp(current->data.song, song) == 0) {
            if (current->prev)
                current->prev->next = current->next;
            else
                *head = current->next; // deleting head
            if (current->next)
                current->next->prev = current->prev;
            free(current);
            printf("Record deleted successfully!\n");
            return;
        }
        current = current->next;
    }
    printf("Song \"%s\" not found. No record deleted.\n", song);
}

// Swaps two records – used in sorting.
void swapRecords(Record* a, Record* b) {
    Record temp = *a;
    *a = *b;
    *b = temp;
}

// Sorts the playlist based on a user-selected criterion using bubble sort.
void sortPlaylist(Node** head) {
    if (!*head) {
        printf("Playlist is empty. Nothing to sort.\n");
        return;
    }
    int choice;
    printf("Sort Options:\n");
    printf("1. Sort by artist (A-Z)\n");
    printf("2. Sort by album title (A-Z)\n");
    printf("3. Sort by rating (1-5)\n");
    printf("4. Sort by times played (largest to smallest)\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
    getchar(); // consume newline

    bool swapped;
    Node* ptr;
    Node* lptr = NULL;
    do {
        swapped = false;
        ptr = *head;
        while (ptr->next != lptr) {
            bool needSwap = false;
            switch(choice) {
                case 1:
                    if (strcasecmp(ptr->data.artist, ptr->next->data.artist) > 0)
                        needSwap = true;
                    break;
                case 2:
                    if (strcasecmp(ptr->data.album, ptr->next->data.album) > 0)
                        needSwap = true;
                    break;
                case 3:
                    if (ptr->data.rating > ptr->next->data.rating)
                        needSwap = true;
                    break;
                case 4:
                    if (ptr->data.timesPlayed < ptr->next->data.timesPlayed)
                        needSwap = true;
                    break;
                default:
                    printf("Invalid choice. Sorting aborted.\n");
                    return;
            }
            if (needSwap) {
                swapRecords(&ptr->data, &ptr->next->data);
                swapped = true;
            }
            ptr = ptr->next;
        }
        lptr = ptr;
    } while (swapped);
    printf("Playlist sorted successfully!\n");
}

// Shuffles the playlist (plays songs in random order without altering the list).
void shufflePlaylist(Node* head) {
    if (!head) {
        printf("Playlist is empty. Nothing to shuffle.\n");
        return;
    }
    // Count nodes
    int count = 0;
    Node* current = head;
    while (current) {
        count++;
        current = current->next;
    }
    // Create an array of node pointers
    Node** nodes = malloc(count * sizeof(Node*));
    current = head;
    for (int i = 0; i < count; i++) {
        nodes[i] = current;
        current = current->next;
    }
    // Fisher-Yates shuffle
    srand((unsigned)time(NULL));
    for (int i = count - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Node* temp = nodes[i];
        nodes[i] = nodes[j];
        nodes[j] = temp;
    }
    // Play songs in shuffled order
    printf("Shuffled playlist:\n");
    for (int i = 0; i < count; i++) {
        printf("Now playing: %s - %s [%s] (%d:%02d) | Played: %d times | Rating: %d\n",
               nodes[i]->data.artist,
               nodes[i]->data.song,
               nodes[i]->data.album,
               nodes[i]->data.length.minutes,
               nodes[i]->data.length.seconds,
               nodes[i]->data.timesPlayed,
               nodes[i]->data.rating);
#ifdef _WIN32
        Sleep(2000);
        system("cls");
#else
        sleep(2);
        system("clear");
#endif
    }
    free(nodes);
    printf("Finished shuffled playback.\n");
}

// Prompts the user to create a record and returns it.
Record createRecordFromInput() {
    Record rec;
    char buffer[100];
    printf("Enter artist: ");
    fgets(rec.artist, sizeof(rec.artist), stdin);
    rec.artist[strcspn(rec.artist, "\n")] = 0;
    printf("Enter album title: ");
    fgets(rec.album, sizeof(rec.album), stdin);
    rec.album[strcspn(rec.album, "\n")] = 0;
    printf("Enter song title: ");
    fgets(rec.song, sizeof(rec.song), stdin);
    rec.song[strcspn(rec.song, "\n")] = 0;
    printf("Enter genre: ");
    fgets(rec.genre, sizeof(rec.genre), stdin);
    rec.genre[strcspn(rec.genre, "\n")] = 0;
    printf("Enter song length (mm:ss): ");
    fgets(buffer, sizeof(buffer), stdin);
    sscanf(buffer, "%d:%d", &rec.length.minutes, &rec.length.seconds);
    printf("Enter number of times played: ");
    fgets(buffer, sizeof(buffer), stdin);
    rec.timesPlayed = atoi(buffer);
    printf("Enter rating (1-5): ");
    fgets(buffer, sizeof(buffer), stdin);
    rec.rating = atoi(buffer);
    return rec;
}
