 #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//GROUP 14-387,380,364
//ADDING COMMENTS FOR USER UNDERSTANDING
// Define a structure for a song
struct Song {
    char title[100];
    char artist[100];
    struct Song *next;
};

// Define a structure for a playlist
struct Playlist {
    char name[100];
    struct Song *head;
    struct Song *queue; // Add a queue pointer for the queue of songs to play next
};
// Function to create a new playlist
struct Playlist *createPlaylist(const char *name) {
    struct Playlist *newPlaylist = (struct Playlist *)malloc(sizeof(struct Playlist));
    if (newPlaylist) {
        strcpy(newPlaylist->name, name);
        newPlaylist->head = NULL;
        newPlaylist->queue = NULL; // Initialize the queue member
    }
    return newPlaylist;
}

struct Song *createSong(const char *title, const char *artist) {
    struct Song *newSong = (struct Song *)malloc(sizeof(struct Song));
    if (newSong) {
        strcpy(newSong->title, title);
        strcpy(newSong->artist, artist);
        newSong->next = NULL;
    }
    return newSong;
}


// Function to insert a song into a playlist
void insertSong(struct Playlist *playlist, const char *title, const char *artist) {
    struct Song *newSong = createSong(title, artist);
    if (newSong) {
        if (playlist->head == NULL) {
            playlist->head = newSong;
        } else {
            struct Song *current = playlist->head;
            while (current->next) {
                current = current->next;
            }
            current->next = newSong;
        }
    }
}

// Function to add a song to the queue to play next
void addToQueue(struct Playlist *playlist, const char *title, const char *artist) {
    struct Song *newSong = createSong(title, artist);
    if (newSong) {
        if (playlist->queue == NULL) {
            playlist->queue = newSong;
        } 
        else {
            struct Song *current = playlist->queue;
            while (current->next) {
                current = current->next;
            }
            current->next = newSong;
        }
    }
}

// Function to view the queue
void viewQueue(struct Playlist *playlist) {
    if (playlist->queue == NULL) {
        printf("Queue is empty.\n");
        return;
    }

    struct Song *current = playlist->queue;
    printf("Queue:\n");
    while (current) {
        printf("%s - %s\n", current->title, current->artist);
        current = current->next;
    }
}


// Function to shuffle a playlist
void shufflePlaylist(struct Playlist *playlist) {
    struct Song *songs[100];
    int count = 0;

    struct Song *current = playlist->head;
    while (current) {
        songs[count++] = current;
        current = current->next;
    }

    srand(time(NULL));
    for (int i = count - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        struct Song *temp = songs[i];
        songs[i] = songs[j];
        songs[j] = temp;
    }

    playlist->head = songs[0];
    for (int i = 0; i < count - 1; i++) {
        songs[i]->next = songs[i + 1];
    }
    songs[count - 1]->next = NULL;
}

// Function to remove a song from a playlist
void removeSong(struct Playlist *playlist, const char *title) {
    struct Song *current = playlist->head;
    struct Song *prev = NULL;

    while (current) {
        if (strcmp(current->title, title) == 0) {
            if (prev == NULL) {
                playlist->head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            printf("%s removed from the playlist.\n", title);
            return;
        }
        prev = current;
        current = current->next;
    }

    printf("%s not found in the playlist.\n", title);
}

// Function to play songs in different orders
void playPlaylist(struct Playlist *playlist, int order) {
    if (playlist->head == NULL) {
        printf("Playlist is empty.\n");
        return;
    }

    if (order == 0) {
        // added first
        struct Song *current = playlist->head;
        while (current) {
            printf("Playing: %s - %s\n", current->title, current->artist);
            current = current->next;
        }
    } else if (order == 1) {
        // latest added
        struct Song *prev = NULL;
        struct Song *current = playlist->head;
        struct Song *next = NULL;

        // Reverse the order of songs in the playlist
        while (current) {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        
        // Now, 'prev' points to the first song, which was the last one added
        current = prev;
        while (current) {
            printf("Playing: %s - %s\n", current->title, current->artist);
            current = current->next;
        }
    } else if (order == 2) {
        // Shuffle
        shufflePlaylist(playlist);
        playPlaylist(playlist, 0); // Play shuffled playlist using order 0 (latest added)
    }
}


int main() {
    int choice;
    struct Playlist playlists[10];
    int playlistCount = 0;
    int currentPlaylist = -1;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Create a new playlist\n");
        printf("2. Insert a song into the current playlist\n");
        printf("3. Shuffle the current playlist\n");
        printf("4. Remove a song from the current playlist\n");
        printf("5. Play the current playlist (Added First)\n");
        printf("6. Play the current playlist (Latest Added)\n");
        printf("7. Play the current playlist (Shuffle)\n");
        printf("8. Add a song to the queue to play next\n"); // New option
        printf("9. View the queue\n"); // New option
        printf("10. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // Inside the main function
        // Inside the main function
if (choice == 1) {
    if (playlistCount < 10) {
        playlistCount++;
        currentPlaylist = playlistCount - 1;
        printf("Enter the name of the new playlist: ");
        scanf("%s", playlists[currentPlaylist].name);

        // Use a pointer to store the result of createPlaylist
        struct Playlist *newPlaylist = createPlaylist(playlists[currentPlaylist].name);

        // Assign the newPlaylist pointer to the current playlist
        playlists[currentPlaylist] = *newPlaylist;

        // Remember to free the newPlaylist pointer when it's no longer needed
        free(newPlaylist);
    } else {
        printf("You have reached the maximum limit of playlists.\n");
    }
}


         else if (choice == 2) {
            if (currentPlaylist != -1) {
                char title[100], artist[100];
                printf("Enter the song title: ");
                scanf("%s", title);
                printf("Enter the artist name: ");
                scanf("%s", artist);
                insertSong(&playlists[currentPlaylist], title, artist);
            } else {
                printf("Please create a playlist first.\n");
            }
        } else if (choice == 3) {
            if (currentPlaylist != -1) {
                shufflePlaylist(&playlists[currentPlaylist]);
                printf("Playlist shuffled.\n");
            } else {
                printf("Please create a playlist first.\n");
            }
        } else if (choice == 4) {
            if (currentPlaylist != -1) {
                char title[100];
                printf("Enter the song title to remove: ");
                scanf("%s", title);
                removeSong(&playlists[currentPlaylist], title);
            } else {
                printf("Please create a playlist first.\n");
            }
        } else if (choice == 5) {
            if (currentPlaylist != -1) {
                playPlaylist(&playlists[currentPlaylist], 0); // Play in added first order
            } else {
                printf("Please create a playlist first.\n");
            }
        } else if (choice == 6) {
            if (currentPlaylist != -1) {
                playPlaylist(&playlists[currentPlaylist], 1); // Play in latest added order
            } else {
                printf("Please create a playlist first.\n");
            }
        } else if (choice == 7) {
            if (currentPlaylist != -1) {
                playPlaylist(&playlists[currentPlaylist], 2); // Play shuffled playlist
            } else {
                printf("Please create a playlist first.\n");
            }
        } else if (choice == 8) {
            if (currentPlaylist != -1) {
                char title[100], artist[100];
                printf("Enter the song title: ");
                scanf("%99s", title);
                printf("Enter the artist name: ");
                scanf("%99s", artist);
                addToQueue(&playlists[currentPlaylist], title, artist);
                printf("Song added to the queue.\n");
            } else {
                printf("Please create a playlist first.\n");
            }
        } else if (choice == 9) {
            if (currentPlaylist != -1) {
                viewQueue(&playlists[currentPlaylist]);
            } else {
                printf("Please create a playlist first.\n");
            }
        } else if (choice == 10) {
            exit(0);
        } else {
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}       
