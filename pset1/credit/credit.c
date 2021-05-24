#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int digit;
    int total = 0;
    int head[2] = {};

    long number = get_long("Number: ");
    for (digit = 0; number != 0; digit++)
    {
        head[1] = head[0];
        head[0] = number % 10;
        if (digit % 2 == 0)
            total += number % 10;
        else
        {
            for (int tmp = number % 10 * 2; tmp != 0; tmp /= 10)
                total += tmp % 10;
        }
        number /= 10;
    }
    if (total % 10)
        printf("INVALID\n");
    else if (digit == 15 && head[0] == 3 && (head[1] == 4 || head[1] == 7))
        printf("AMEX\n");
    else if (digit == 16 && head[0] == 5 && (head[1] >= 1 && head[1] <= 5))
        printf("MASTERCARD\n");
    else if ((digit == 13 || digit == 16) && head[0] == 4)
        printf("VISA\n");
    else
        printf("INVALID\n");
    return (0);
}
