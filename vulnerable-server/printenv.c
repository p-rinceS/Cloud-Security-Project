#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>


int main() {
   // Open a file to write the addresses
   FILE *file = fopen("addresses.txt", "w");
   if (!file) {
       perror("Failed to open file");
       return 1;
   }


   // Get and write the address of the MYSHELL environment variable
   char *shell = getenv("MYSHELL");
   if (shell) {
       fprintf(file, "%x\n", (unsigned int)shell);
   } else {
       fprintf(file, "MYSHELL environment variable is not set.\n");
   }


   // Get and write the address of the MYSHELL environment variable
   char *flag = getenv("MYFLAG");
   if (flag) {
       fprintf(file, "%x\n", (unsigned int)flag);
   } else {
       fprintf(file, "MYFLAG environment variable is not set.\n");
   }


   // Get and write the address of the system() function
   void (*sys_ptr)() = system; // Function pointer to system()
   fprintf(file, "%x\n", (unsigned int)sys_ptr);


   // Get and write the address of the system() function
   void (*exit_ptr)() = exit; // Function pointer to system()
   fprintf(file, "%x\n", (unsigned int)exit_ptr);


   // Get and write the address of the system() function
   void (*execv_ptr)() = execv; // Function pointer to system()
   fprintf(file, "%x\n", (unsigned int)execv_ptr);


   // Close the file
   fclose(file);


   printf("MYSHELL: %x\n", (unsigned int)shell);
   printf("MYSHELL: %s\n", shell);
   printf("MYFLAG %x\n", (unsigned int)flag);
   printf("MYFLAG: %s\n", flag);
   printf("system() %x\n", (unsigned int)sys_ptr);
   printf("exit() %x\n", (unsigned int)exit_ptr);
   printf("execv() %x\n", (unsigned int)execv_ptr);
   return 0;
}
