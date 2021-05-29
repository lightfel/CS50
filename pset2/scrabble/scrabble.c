#include <cs50.h>
#include <ctype.h>
#include <stdio.h>

int compute_score(char *);

int main(void)
{

    char *word1 = get_string("Player 1: ");
    char *word2 = get_string("Player 2: ");
    int point1 = compute_score(word1);
    int point2 = compute_score(word2);

    if (point1 > point2)
        printf("Player 1 wins!\n");
    else if (point1 < point2)
        printf("Player 2 wins!\n");
    else
        printf("Tie!\n");
    return (0);
}

int compute_score(char *word)
{
    int score = 0;
    const int points[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

    for (; *word; word++)
    {
        if (isupper(*word))
            score += points[*word - 'A'];
        else if (islower(*word))
            score += points[*word - 'a'];
    }
    return (score);
}
