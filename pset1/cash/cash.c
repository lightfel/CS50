#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float change_dollars;
    int change_cent;
    int coin;

    do {
        change_dollars = get_float("Please enter change: ");
    }
    while (change_dollars < 0);
    change_cent = round(change_dollars * 100);
    //printf("dollars = %f\n", change_dollars);
    //printf("cent = %d\n", change_cent);
    coin = 0;
    coin = change_cent / 25;
    change_cent %= 25;
    coin += change_cent / 10;
    change_cent %= 10;
    coin += change_cent / 5;
    change_cent %= 5;
    coin += change_cent / 1;
    printf("%d\n", coin);
}
