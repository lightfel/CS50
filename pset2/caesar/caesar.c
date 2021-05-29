#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    string text;
    int key;

    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return (1);
    }
    for (int i = 0; argv[1][i]; i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return (1);
        }
    }
    key = atoi(argv[1]) % 26;
    text = get_string("plaintext: ");
    for (int i = 0; text[i]; i++)
    {
        if (isupper(text[i]))
            text[i] = (text[i] - 'A' + key) % 26 + 'A';
        else if (islower(text[i]))
            text[i] = (text[i] - 'a' + key) % 26 + 'a';
    }
    printf("ciphertext: %s\n", text);
    return (0);
}
