#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    string key;
    string text;
    bool flag[26] = {};
    int num;

    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return (1);
    }
    for (num = 0; argv[1][num]; num++)
    {
        argv[1][num] = toupper(argv[1][num]);
        if (flag[argv[1][num] - 'A'])
        {
            printf("Key must not contain repeated characters.\n");
            return (1);
        }
        flag[argv[1][num] - 'A'] = true;
        if (!isalpha(argv[1][num]))
        {
            printf("Key must only contain alphabetic characters.\n");
            return (1);
        }
    }
    if (num != 26)
    {
        printf("Key must contain 26 characters.\n");
        return (1);
    }
    text = get_string("plaintext: ");
    key = argv[1];
    for (int i = 0; text[i]; i++)
    {
        if (isupper(text[i]))
            text[i] = key[text[i] - 'A'];
        else if (islower(text[i]))
            text[i] = key[text[i] - 'a'] - 'A' + 'a';
    }
    printf("ciphertext: %s\n", text);
    return (0);
}
