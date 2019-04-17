#include <stdio.h>

int main () {
    FILE *input;
    FILE *output;
    int spaces = 0;
    char cypher(char x);
    
    input = fopen("input.txt", "r");
    output = fopen("output.txt", "w");
    
    while(!feof(input)) {
        char charFromFile;
        //Read Character
        fscanf(input, "%c", &charFromFile);
        
        //Put a function for encryption here
        charFromFile = cypher(charFromFile);
        
        //Print to the screen
        fprintf(output,"%c", charFromFile);
        

    }
    printf("%d\n", spaces);
}

char cypher(char x) {
    return x;
}
