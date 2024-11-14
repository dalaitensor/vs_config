#include <stdio.h>
#include <string.h>


char *getline(){
    char buf[4];
    char *res;
    gets(buf);
    res = malloc(strlen(buf));
    strcpy(res, buf);
    return res;
}

int main(){
    getline();
    return 0;
}