# include "csapp.c"
int main ()
{
int fd;
char c[10];
fd = Open ("foobar.txt", O_RDONLY , 0) ;
if ( Fork () == 0) {
Read (fd , &c, 3) ;
printf ("c = %3s\n", c) ;
exit (0) ;
}
Wait ( NULL ) ;
Read (fd , &c, 3) ;
printf ("c = %3s\n", c) ;
exit (0) ;
}