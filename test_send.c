#include<stdio.h>
#include<unistd.h>

int main() {
    char input[200];
    fgets(input, 200, stdin);
    sleep(5);
    printf("%s", input);
    return 0;
}
