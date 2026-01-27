#include <stdio.h>

int main() {
    char str[100];
    int i = 0;

    printf("Enter string: ");
    fgets(str, sizeof(str), stdin);

    while (str[i] == 'a') {
        i++;
    }

    if (str[i] == 'b' && str[i + 1] == 'b') {
        i += 2;

        if (str[i] == '\n' || str[i] == '\0') {
            printf("Valid String\n");
        } else {
            printf("Invalid String\n");
        }
    } else {
        printf("Invalid String\n");
    }

    return 0;
}
