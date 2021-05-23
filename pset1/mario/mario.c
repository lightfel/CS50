#include <cs50.h>
#include <unistd.h>

int main(void)
{
    int height;
    do {
        height = get_int("Height: ");
    } while (height < 1 || height > 8);
    for (int i = 0; i < height; i++)
    {
        for (int j = height - i - 1; j > 0; j--)
            write(1, " ", 1);
        for (int k = 0; k <= i; k++)
            write(1, "#", 1);
        write(1, "  ", 2);
        for (int l = 0; l <= i; l++)
            write(1, "#", 1);
        write(1, "\n", 1);
    }
}
