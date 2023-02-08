// different between scanf and fgets
#include <stdio.h>
int main()
{
    char name[20];
    scanf("%s", name); // gets until a whitespace
    // fgets(name, 20, stdin);  // gets a line from stdin
    printf("%s\n", name);
    return 0;
}