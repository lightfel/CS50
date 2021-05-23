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
        write(1, "       ", height - i - 1);
        write(1, "########", i + 1);
        write(1, "  ", 2);
        write(1, "########", i + 1);
        write(1, "\n", 1);
    }
}
