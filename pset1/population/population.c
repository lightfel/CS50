#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int start_size;
    int end_size;
    int size;
    int year;

    do {
        start_size = get_int("Please enter start size: ");
    }
    while (start_size < 9);
    do {
        end_size = get_int("Please enter end size: ");
    }
    while (end_size < start_size);
    size = start_size;
    for (year = 0; size < end_size; year++)
        size += size / 3 - size / 4;
    printf("Years: %d\n", year);
}
