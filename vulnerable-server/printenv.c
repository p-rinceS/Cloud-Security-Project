#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main() {
    // Open a file to write the addresses
    FILE file = fopen("addresses.txt", "w");
    if (!file) {
        perror("Failed to open file");
        return 1;
    }

    // Get and write the address of the MYSHELL environment variable
    charshell = getenv("MYSHELL");
    if (shell) {
        fprintf(file, "%x\n", (unsigned int)shell);
    } else {
        fprintf(file, "MYSHELL environment variable is not set.\n");
    }

    // Get and write the address of the system() function
    void (*sys_ptr)() = system; // Function pointer to system()
    fprintf(file, "%x\n", (unsigned int)sys_ptr);

    // Close the file
    fclose(file);

    printf("Addresses written to addresses.txt\n");
    return 0;
}