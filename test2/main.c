#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct DirectoryNode {
    char name[256];
    struct DirectoryNode* next;
};

struct DirectoryList {
    struct DirectoryNode* head;
};

void initializeDirectoryList(struct DirectoryList* list) {
    list->head = NULL;
}

void addDirectory(struct DirectoryList* list, const char* name) {
    struct DirectoryNode* newNode = (struct DirectoryNode*)malloc(sizeof(struct DirectoryNode));
    strncpy(newNode->name, name, sizeof(newNode->name));
    newNode->next = NULL;

    if (list->head == NULL) {
        list->head = newNode;
    } else {
        struct DirectoryNode* current = list->head;
        struct DirectoryNode* prev = NULL;
        while (current != NULL) {
            if (strcmp(newNode->name, current->name) < 0) {
                break;
            }
            prev = current;
            current = current->next;
        }
        if (prev == NULL) {
            newNode->next = list->head;
            list->head = newNode;
        } else {
            prev->next = newNode;
            newNode->next = current;
        }
    }
}

void removeDirectory(struct DirectoryList* list, const char* name) {
    struct DirectoryNode* current = list->head;
    struct DirectoryNode* prev = NULL;

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            if (prev == NULL) {
                list->head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

char** convertDirectoryListToArray(struct DirectoryList* list, size_t* length) {
    size_t count = 0;
    struct DirectoryNode* current = list->head;
    while (current != NULL) {
        count++;
        current = current->next;
    }

    char** result = (char **)malloc(count * sizeof(char *));
    current = list->head;
    for (size_t i = 0; i < count; i++) {
        result[i] = (char *)malloc(256);
        strcpy(result[i], current->name);
        current = current->next;
    }
    result[count] = NULL;
    *length = count;
    return result;
}

void copyDirectory(struct DirectoryList* list, const char* source, const char* dest) {
    struct DirectoryNode* current = list->head;

    while (current != NULL) {
        if (strcmp(current->name, source) == 0) {
            break;
        }
        current = current->next;
    }

    if (current == NULL) {
        return;
    }

    char destName[256];
    snprintf(destName, sizeof(destName), "%s", dest);

    current = list->head;
    size_t sourceLen = strlen(source);
    while (current != NULL) {
        size_t nameLen = strlen(current->name);
        if (strncmp(current->name, source, sourceLen) == 0 && (nameLen == sourceLen || current->name[sourceLen] == '/')) {
            char subDir[256];
            snprintf(subDir, sizeof(subDir), "%s", current->name + sourceLen);

            if (strlen(subDir) > 0) {
                char subDirDest[512];
                snprintf(subDirDest, sizeof(subDirDest), "%s%s", destName, subDir);
                addDirectory(list, subDirDest);
            }
        }
        current = current->next;
    }
}

void executeCommands(struct DirectoryList* list, const char* command[], size_t command_len) {
    for (size_t i = 0; i < command_len; i++) {
        const char* cmd = command[i];
        if (strncmp(cmd, "mkdir", 5) == 0) {
            addDirectory(list, cmd + 6);
        } else if  (strncmp(cmd, "rm", 2) == 0) {
            removeDirectory(list, cmd + 3);
        } else if (strncmp(cmd, "cp", 2) == 0) {
            char source[256];
            char dest[256];
            if (sscanf(cmd + 3, "%255s %255s", source, dest) == 2) {
                copyDirectory(list, source, dest);
            }
        }
    }
}

char** solution(const char* directory[], size_t directory_len, const char* command[], size_t command_len) {
    struct DirectoryList dirList;
    initializeDirectoryList(&dirList);

    for (size_t i = 0; i < directory_len; i++) {
        addDirectory(&dirList, directory[i]);
    }

    executeCommands(&dirList, command, command_len);

    size_t length;
    char** result = convertDirectoryListToArray(&dirList, &length);

    return result;
}

int main(void) {
    const char *initial_directory[] = {"/"};
    size_t initial_directory_len = 1;

    const char *commands[] = {
        "mkdir /a",
        "mkdir /a/b",
        "mkdir /a/b/c",
        "cp /a/b /",
        "rm /a/b/c"
    };
    size_t command_len = 5;

    char **result = solution(initial_directory, initial_directory_len, commands, command_len);

    for (size_t i = 0; i < initial_directory_len + command_len; i++) {
        printf("%s\n", result[i]);
    }
 
    for (size_t i = 0; i < initial_directory_len + command_len; i++) {
        free(result[i]);
    }
    free(result);

    return 0;
}
