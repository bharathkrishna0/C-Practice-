#include <stdio.h>
#include <ctype.h>

int main() {
    FILE *input, *output;
    char ch;
    int characters = 0, words = 0, lines = 0;
    int in_word = 0;

    input = fopen("input.txt", "r");
    if (input == NULL) {
        printf("Error opening input file!\n");
        return 1;
    }

    while ((ch = fgetc(input)) != EOF) {
        characters++;

        if (ch == '\n')
            lines++;

        if (isspace(ch))
            in_word = 0;
        else if (in_word == 0) {
            in_word = 1;
            words++;
        }
    }
    fclose(input);

    printf("Characters: %d\n", characters);
    printf("Words: %d\n", words);
    printf("Lines: %d\n", lines);

    output = fopen("output.txt", "w");
    if (output == NULL) {
        printf("Error opening output file!\n");
        return 1;
    }
    fprintf(output, "Characters: %d\n", characters);
    fprintf(output, "Words: %d\n", words);
    fprintf(output, "Lines: %d\n", lines);
    fclose(output);

    return 0;
}
