#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "functions.h"

int MinBase(char *string) {
    int max_val = 0;
    int i = 0;
    while (string[i] != '\0') {
        char c = string[i];
        int val;
        if ('0' <= c && c <= '9') {
            val = c - '0';
        } else if ('A' <= c && c <= 'Z') {
            val = c - 'A' + 10;
        } else if ('a' <= c && c <= 'z') {
            val = c - 'a' + 10;
        } else { 
            return 0;
        } 
        if (val > max_val){
            max_val = val;
        }
        i++;
    }
    if (max_val<=35 && max_val>=1){
        return max_val + 1;
    } else {
        return 0 ;
    }
}

unsigned long long ToDecimal(char *string, int base) {
    unsigned long long result = 0;
    int i = 0;
    while (string[i] != '\0') {
        char c = string[i];
        int val;
        if ('0' <= c && c <= '9') {
            val = c - '0';
        } else if ('A' <= c && c <= 'Z') {
            val = c - 'A' + 10;
        } else if ('a' <= c && c <= 'z') {
            val = c - 'a' + 10;
        }
        result = result * base + val;
        i++;
    }
    return result;
}

char *ReadString(FILE *f) {
    int c;
    int cap = 1;
    int len = 0;
    char *buf = malloc(cap);
    if (!buf){ 
        return NULL;
    }
    while ((c = fgetc(f)) != EOF && isspace(c))
        ;
    if (c == EOF) { 
        free(buf); 
        return NULL; 
    }
    buf[len++] = c;
    while ((c = fgetc(f)) != EOF && !isspace(c)){
        if (len + 1 >= cap) {
            cap += 1;
            char *tmp = realloc(buf, cap);
            if (!tmp) { 
                free(buf); 
                return NULL; }
            buf = tmp;
        }
        buf[len++] = c;
    }
    buf[len] = '\0';
    return buf;
}
