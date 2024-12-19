# include "csapp.c"
int main ()
{
int fd1 , fd2;
char c[10];
fd1 = Open ("foobar.txt", O_RDONLY , 1) ;
fd2 = Open ("foobar.txt", O_RDONLY , 1) ;
Read (fd1 , &c, 3) ;
Read (fd2 , &c, 4
) ;
printf ("c = %6s\n", c) ;
exit (0) ;
}