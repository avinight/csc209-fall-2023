#include <stdio.h>


int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./fscanf file\n");
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");

    int num_nums;
    fscanf(fp, "%d", &num_nums);
    printf("Number of numbers: %d\n", num_nums);

    for (int i = 0; i < num_nums; i++)
    {
        int num;
        fscanf(fp, "%d", &num);
        printf("%d\n", num);
    }
}
