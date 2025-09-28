#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("ARGUMENT ERROR\n");
        return 1;
    }
    FILE *in = fopen(argv[1], "r");
    if (!in) { 
        printf("ERROR OPEN INPUT FILE"); 
        return 2; 
    }
    FILE *out = fopen(argv[2], "w");
    if (!out) { 
        printf("ERROR OPEN OUTPUT FILE");
        fclose(in); 
        return 3; 
    }
    int base;
    char *string;
    unsigned long long number;
    while ((string = ReadString(in)) != NULL) {
        base = MinBase(string);
        if (base == 0){
            printf("BASE ERROR %s", string);
            free(string);
            return 4;
        }
        number = ToDecimal(string,base);
        fprintf(out, "%s %d %llu\n", string, base, number);
        free(string);
    }

    fclose(in);
    fclose(out);
    return 0;
}
