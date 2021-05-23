#include <stdio.h>
#include <cs50.h>

int main(void)
{
    long number;
    int digit;
    int total = 0;
    int head = 0;
    int next = 0;
    int tmp = 0;

    number = get_long("Number: ");
    for (digit = 0; number != 0; digit++)
    {
        next = head;
        head = number % 10;
        if (digit % 2 == 0)
            total += number % 10;
        else
        {
            tmp = number % 10 * 2;
            while (tmp)
            {
                total += tmp % 10;
                tmp /= 10;
            }
        }
        number /= 10;
    }
    if (total % 10)
        printf("INVALID\n");
    else if (digit == 15 && head == 3 && (next == 4 || next == 7))
        printf("AMEX\n");
    else if (digit == 16 && head == 5 && (next == 1 || next == 2 || next == 3 || next == 4 || next == 5))
        printf("MASTERCARD\n");
    else if ((digit == 13 || digit == 16) && head == 4)
        printf("VISA\n");
    else
        printf("INVALID\n");
    return (0);
}
