#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int digit;
    int total = 0;
    int head = 0;
    char *message = "INVALID";

    long number = get_long("Number: ");
    for (digit = 0; number != 0; digit++)
    {
        if (number >= 10)
            head = number % 100;
        if (digit % 2 == 0)
            total += number % 10;
        else if (number % 10 < 5)
            total += number % 10 * 2;
        else
            total += 1 + (number % 10 * 2) % 10;
        number /= 10;
    }
    if (total % 10)
        message = "INVALID";
    else if (digit == 15 && (head == 34 || head == 37))
        message = "AMEX";
    else if (digit == 16 && (head >= 51 && head <= 55))
        message = "MASTERCARD";
    else if ((digit == 13 || digit == 16) && head / 10 == 4)
        message = "VISA";
    printf ("%s\n", message);
    return (0);
}
