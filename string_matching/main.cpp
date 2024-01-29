#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Directory {
    char path[21];
    struct Directory *next;
} Directory;

Directory* create_directory(const char *path) {
    Directory *new_dir = (Directory *)malloc(sizeof(Directory));
    strcpy(new_dir->path, path);
    new_dir->next = NULL;
    return new_dir;
}

bool starts_with(const char *pre, const char *str) {
    size_t lenpre = strlen(pre), lenstr = strlen(str);
    return lenstr < lenpre ? false : strncmp(pre, str, lenpre) == 0;
}

void add_directory(Directory **head, const char *path) {
    Directory *new_dir = create_directory(path), *current;

    if (*head == NULL || strcmp(path, (*head)->path) < 0) {
        new_dir->next = *head;
        *head = new_dir;
    } else {
        current = *head;
        while (current->next != NULL && strcmp(path, current->next->path) > 0) {
            current = current->next;
        }
        new_dir->next = current->next;
        current->next = new_dir;
    }
}

void remove_directory(Directory **head, const char *path) {
    Directory *temp = *head, *prev = NULL;

    while (temp != NULL) {
        if (starts_with(path, temp->path)) {
            if (prev == NULL) {
                *head = temp->next;
            } else {
                prev->next = temp->next;
            }
            Directory *toDelete = temp;
            temp = temp->next;
            free(toDelete);
            continue;
        }
        prev = temp;
        temp = temp->next;
    }
}


void copy_directory(Directory **head, const char *source, const char *dest) {
    int source_len = strlen(source);
    Directory *current = *head;

    while (current != NULL) {
        if (starts_with(source, current->path) && strlen(current->path) > source_len) {
            char new_path[21];
            if (source[source_len - 1] != '/') {
                // 원본 경로가 슬래시로 끝나지 않는 경우, 슬래시를 추가
                snprintf(new_path, 21, "%s/%s", dest, current->path + source_len + 1);
            } else {
                // 원본 경로가 슬래시로 끝나는 경우
                snprintf(new_path, 21, "%s%s", dest, current->path + source_len);
            }
            add_directory(head, new_path);
        }
        current = current->next;
    }
}



void execute_command(Directory **head, const char *command) {
    char cmd[6], path1[21], path2[21];
    if (sscanf(command, "%s %s %s", cmd, path1, path2) == 2) {
        if (strcmp(cmd, "mkdir") == 0) {
            add_directory(head, path1);
        } else if (strcmp(cmd, "rm") == 0) {
            remove_directory(head, path1);
        }
    } else if (sscanf(command, "%s %s %s", cmd, path1, path2) == 3) {
        if (strcmp(cmd, "cp") == 0) {
            copy_directory(head, path1, path2);
        }
    }
}

void print_directories(Directory *head) {
    Directory *current = head;
    while (current != NULL) {
        printf("%s\n", current->path);
        current = current->next;
    }
}

int main() {
    Directory *head = NULL;

    execute_command(&head, "mkdir /a");
    execute_command(&head, "mkdir /a/b");
    execute_command(&head, "mkdir /a/b/c");
    execute_command(&head, "cp /a/b /");
    execute_command(&head, "rm /a/b/c");

    print_directories(head);

    while (head != NULL) {
        Directory *temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}
