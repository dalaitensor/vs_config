#include "csapp.c"


int main(){
    int fd1, fd2;
    char c[10];

    fd1 = 0 ;
    fd2 = Open ("foobar.txt", O_RDONLY , 0) ;

    Read (fd2 , &c, 5) ;
    Dup2 (fd2 , fd1 ) ;
    Read (fd1 , &c, 2) ;
    printf ("c = %3s\n", c) ;
    exit (0) ;

    return 0;
}