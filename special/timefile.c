#include <time.h>

// GET CURRENT TIME
#include <stdio.h>
#include <time.h>
int main()
{
    time_t t = time(0);      // Get current time in seconds
    printf("%s", ctime(&t)); // Convert to readable format and print
    return 0;
}

// WRITE FILES
FILE *fptr;
// Open a file in writing mode
fptr = fopen("filename.txt", "w");
// Write some text to the file
fprintf(fptr, "Some text");
// Close the file
fclose(fptr);

// READ FILES
FILE *fptr;
// Open a file in read mode
fptr = fopen("filename.txt", "r");
// Store the content of the file
char myString[100];
// Read the content and store it inside myString
fgets(myString, 100, fptr);
// Print the file content
printf("%s", myString);
// Close the file
fclose(fptr);