#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#define MAX_FILENAME 100
#define MAX_BUFFER_SIZE 1024

// Create a new file with the specified filename
void createFile(char* filename) {
    int fd = creat(filename, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
    if (fd == -1) {
        perror("Error creating file");
        return;
    }
    close(fd);
    printf("File '%s' created successfully.\n", filename);
}

// Delete the file with the specified filename
void deleteFile(char* filename) {
    int result = unlink(filename);
    if (result == -1) {
        perror("Error deleting file");
        return;
    }
    printf("File '%s' deleted successfully.\n", filename);
}

// Read and display the contents of the file with the specified filename
void readFile(char* filename) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return;
    }

    char buffer[MAX_BUFFER_SIZE];
    ssize_t bytesRead;
    while ((bytesRead = read(fd, buffer, MAX_BUFFER_SIZE)) > 0) {
        write(STDOUT_FILENO, buffer, bytesRead);
    }

    if (bytesRead == -1) {
        perror("Error reading file");
    }

    close(fd);
}

// Write the specified data to the file with the specified filename
void writeFile(char* filename, char* data) {
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
    if (fd == -1) {
        perror("Error opening file");
        return;
    }

    ssize_t bytesWritten = write(fd, data, strlen(data));
    if (bytesWritten == -1) {
        perror("Error writing to file");
    } else {
        printf("File '%s' written successfully.\n", filename);
    }

    close(fd);
}

// List the files in the specified directory
void listFiles(char* directory) {
    DIR* dir = opendir(directory);
    if (dir == NULL) {
        perror("Error opening directory");
        return;
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    closedir(dir);
}

int main() {
    char filename[MAX_FILENAME];

    // Create file
    printf("Enter filename to create: ");
    scanf("%s", filename);
    createFile(filename);

    // Write to file
    printf("Enter filename to write to: ");
    scanf("%s", filename);
    printf("Enter data to write: ");
    char data[MAX_BUFFER_SIZE];
    scanf("%s", data);
    writeFile(filename, data);

    // Read file
    printf("Enter filename to read: ");
    scanf("%s", filename);
    readFile(filename);

    // Delete file
    printf("Enter filename to delete: ");
    scanf("%s", filename);
    deleteFile(filename);

    return 0;
}
