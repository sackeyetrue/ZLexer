#include <stdio.h>

struct Vec2
{
    int x;
    int y;
};

int add(int num1, int num2) { return num1 + num2; };

int main(int argc, char const *argv[])
{
    // char *name = "Zeke!";
    // int *age_weight;

    // age_weight[0] = 0;
    // age_weight[1] = 1;
    // age_weight[2] = 2;
    // age_weight[3] = 3;
    // age_weight[4] = 4;

    // int size = sizeof(age_weight);
    // int sizen = sizeof(name);

    // printf("Welcome To Ghana Card!!! \n");

    // scanf("Enter Name: ", name);
    // scanf("Enter Age: ", age_weight[0]);
    // scanf("Enter Weight: ", age_weight[1]);

    // printf("Hello %s! \n", name);
    // printf("You Are : %d Years Old. \n", age_weight[1]);
    // printf("You Weight: %d pounds. \n", age_weight[1]);

    // printf("Size of AGEWEIGHT: %d! \n", size);
    // printf("Size of NAME: %d! \n", sizen);

    /*File Handling*/
    // FILE *even;
    // even = fopen("even.txt", "w");
    // fprintf(even, "Hello C File");
    // fclose(even);

    struct Vec2 position;
    position.x = 23;
    position.y = 25;

    // printf("X: %d, Y: %d \n", position, position.y);

    int (*sum)(int, int) = &add;
    int (*mul)(int, int) = add;

    printf("\n");
    printf("Sum: %d \n", (*sum)(23, 34));
    printf("Sum: %d \n", mul(23, 34));

    return 0;
}
