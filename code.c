#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include<time.h>

#define MAX_LENGTH 256
#define MAX_NAP_TIME 10

// Converts a string to lowercase
void toLowercase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

// Draws a simple ASCII cat
void drawCat() {
    printf(" /\\_/\\\n( o.o )\n > ^ <\n");
}

// Simulates purring
void purrSound() {
    printf("*purring noises*\n");
}

// Creates a file
void createFile(const char *filename) {
    if (strlen(filename) == 0) {
        printf("hisss You must specify a filename!\n");
        return;
    }
    FILE *file = fopen(filename, "w");
    if (file) {
        printf("File '%s' created successfully!\n", filename);
        fclose(file);
    } else {
        printf("hisss Could not create file '%s'\n", filename);
    }
}

// Appends text to a file
void writeFile(const char *filename, const char *content) {
    if (strlen(filename) == 0 || strlen(content) == 0) {
        printf("hisss Invalid syntax. Use: bury [filename] [text]\n");
        return;
    }
    FILE *file = fopen(filename, "a");
    if (file) {
        fprintf(file, "%s\n", content);
        fclose(file);
        printf("Text written to '%s'.\n", filename);
    } else {
        printf("hisss Could not write to file '%s'\n", filename);
    }
}

// Reads and prints the content of a file
void readFile(const char *filename) {
    if (strlen(filename) == 0) {
        printf("hisss You must specify a filename!\n");
        return;
    }

    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("hisss Could not open file '%s'\n", filename);
        return;
    }

    printf("Contents of '%s':\n", filename);
    char line[MAX_LENGTH];
    int foundContent = 0;
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
        foundContent = 1;
    }
    fclose(file);

    if (!foundContent) {
        printf("(empty file)\n");
    }
}

// Pauses execution for a given number of seconds
void takeNap(int seconds) {
    if (seconds <= 0) {
        printf("hisss Nap time must be a positive number!\n");
        return;
    }
    if (seconds > MAX_NAP_TIME) {
        printf("hisss I won't nap that long! (Max %d seconds)\n", MAX_NAP_TIME);
        return;
    }
    printf("Zzz... (%d seconds)\n", seconds);
    sleep(seconds);
}

// Prints the help message
void showHelp() {
    printf("\n Meow Language - Command List \n");
    printf("  meow [text]       - Prints text\n");
    printf("  draw cat          - Displays an ASCII cat\n");
    printf("  purr              - Simulates purring\n");
    printf("  litterbox [file]  - Creates an empty file\n");
    printf("  bury [file] [txt] - Appends text to a file\n");
    printf("  peek [file]       - Reads and displays file contents\n");
    printf("  scratch [n]       - Prints 'Scratch!' n times\n");
    printf("  nap [n]           - Pauses execution for n seconds (Max %d)\n", MAX_NAP_TIME);
    printf("  help              - Shows this help menu\n");
    printf("  exit              - Exits the program\n\n");
}

// Executes a single command
void executeCommand(char *command) {
    char lowerCommand[MAX_LENGTH];
    strncpy(lowerCommand, command, MAX_LENGTH);
    toLowercase(lowerCommand);

    // Handle "meow" command
    if (strncmp(lowerCommand, "meow ", 5) == 0) {
        printf("%s\n", command + 5);
    }
    // Handle "draw cat"
    else if (strcmp(lowerCommand, "draw cat") == 0) {
        drawCat();
    }
    // Handle "purr"
    else if (strcmp(lowerCommand, "purr") == 0) {
        purrSound();
    }
    // Handle "litterbox" (file creation)
    else if (strncmp(lowerCommand, "litterbox ", 10) == 0) {
        createFile(command + 10);
    }
    // Handle "bury" (write to file)
    else if (strncmp(lowerCommand, "bury ", 5) == 0) {
        char *filename = strtok(command + 5, " ");
        char *content = strtok(NULL, "");
        if (filename && content) {
            writeFile(filename, content);
        } else {
            printf("hisss Invalid syntax for bury.\n");
        }
    }
    // Handle "peek" (read file)
    else if (strncmp(lowerCommand, "peek ", 5) == 0) {
        readFile(command + 5);
    }
    // Handle "scratch" (repeat scratch)
    else if (strncmp(lowerCommand, "scratch ", 8) == 0) {
        int times;
        if (sscanf(command + 8, "%d", &times) == 1 && times > 0) {
            for (int i = 0; i < times; i++) {
                printf("Scratch!\n");
            }
        } else {
            printf("hisss Invalid number for scratch.\n");
        }
    }
    // Handle "nap" (sleep)
    else if (strncmp(lowerCommand, "nap ", 4) == 0) {
        int seconds;
        if (sscanf(command + 4, "%d", &seconds) == 1) {
            takeNap(seconds);
        } else {
            printf("hisss Invalid nap time.\n");
        }
    }
    // Handle "help"
    else if (strcmp(lowerCommand, "help") == 0) {
        showHelp();
    }
    // Unknown command
    else {
        printf("hisss Unknown command! Type 'help' for a list.\n");
    }
}

// Main loop
int main() {
    char command[MAX_LENGTH];

    printf(" Welcome to Meow Language! Type 'help' for commands.\n");
    while (1) {
        printf("> ");
        if (!fgets(command, MAX_LENGTH, stdin)) {
            break;
        }

        // Remove newline character
        command[strcspn(command, "\n")] = '\0';

        if (strcmp(command, "exit") == 0) {
            printf("Goodbye!\n");
            break;
        }

        executeCommand(command);
    }

    return 0;
}
