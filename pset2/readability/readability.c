#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>

double calc_coleman_liau_index(char *);

int main(void)
{
    char *text = get_string("Text: ");
    int grade = round(calc_coleman_liau_index(text));
    if (grade < 1)
        printf("Before Grade 1\n");
    else if (grade >= 16)
        printf("Grade 16+\n");
    else
        printf("Grade %d\n", grade);
    return (0);
}

double  calc_coleman_liau_index(char *text)
{
    int letter = 0;
    int word = 0;
    int sentence = 0;
    double index = 0;
    double l;
    double s;

    if (*text && isprint(*text))
        word = 1;
    for (char *c = text; *c; c++)
    {
        if (*c == '.' || *c == '!' || *c == '?')
            sentence++;
        else if (*c == ' ' && isprint(*(c + 1)) && *(c + 1) != ' ')
            word++;
        else if (isalpha(*c))
            letter++;
    }
    //printf("%d letter(s)\n", letter);
    //printf("%d word(s)\n", word);
    //printf("%d sentence(s)\n", sentence);
    l = (double)letter / (double)word * 100;
    s = (double)sentence / (double)word * 100;
    index = 0.0588 * l - 0.296 * s - 15.8;
    //printf("index = %lf\n", index);
    return (index);
}
