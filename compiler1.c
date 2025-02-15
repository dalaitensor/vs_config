#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef char* String;
int max(int a, int b)
{
    return (a > b)? a : b;
}

typedef struct binding* Binding;
struct binding {
    enum {INT, STRING, DOUBLE} kind;
    union {
        int i;
        String s;
        double d;
    } val;
};

typedef struct tree * T_tree;
struct tree { 
    T_tree left; 
    String key; 
    T_tree right;
    Binding binding;    
    int height;
};


void print(T_tree t){
    if(t == NULL) return;
    if(t -> binding -> kind == INT){
        printf("%s %d\n", t -> key, t -> binding -> val.i);
    } else if(t -> binding -> kind == DOUBLE){
        printf("%s %.2f\n", t -> key, t -> binding -> val.d);
    } else if(t -> binding -> kind == STRING){
        printf("%s %s\n", t -> key, t -> binding -> val.s);
    }

    print(t -> left);
    print(t -> right);
}

T_tree insert(String key, Binding binding, T_tree t);
// Binding *lookup(String key, T_tree t);


T_tree Tree ( T_tree l , String k, Binding b, T_tree r ) {
    T_tree t = malloc(sizeof(*t));
    t -> left = l ; t -> key = k ; t -> right = r; t -> binding = b;
    return t;
}


T_tree insert ( String key, Binding binding , T_tree t ) {
    if ( t == NULL )
        return Tree ( NULL , key, binding , NULL );
    else if ( strcmp ( key , t -> key ) < 0)
        return Tree ( insert ( key , binding, t -> left ) ,t -> key, t -> binding ,t -> right ) ;
    else if ( strcmp ( key ,t -> key )> 0)
        return Tree (t -> left ,t -> key , t -> binding,  insert ( key , binding, t -> right ) ) ;
    else
        return Tree (t -> left , key , binding, t -> right );
}

int lookup(String key, T_tree t){
    if(t == NULL)
        return 0;
    else if(strcmp(key, t -> key) < 0)
        return lookup(key, t -> left);
    else if(strcmp(key, t -> key) > 0)
        return lookup(key, t -> right);
    else 
        return 1;
}


int main(){
    
    String s1[30] = {"t", "s", "p", "i", "a", "f", "b", "s", "e", NULL};
    String s2[30] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", NULL};

    T_tree t = NULL;

    int sd[30] = {12, 31,2, 63,89, 23,47,78,34,45};
    for(int i = 0; i < 30 && s1[i] != NULL; i++){
        Binding item = (Binding)malloc(sizeof(item));
        item -> kind = INT;
        item -> val.i = *(sd + i);
        t = insert(s1[i], item, t);
    }

    print(t);



    T_tree t2 = NULL;
    for(int i = 0; i < 30 && s2[i] != NULL; i++){
        Binding item = (Binding)malloc(sizeof(item));
        item -> kind = INT;
        item -> val.i = *(sd + i);
        t2 = insert(s1[i], item, t2);
    }

    printf("%d\n", lookup("z", t));
    print(t2);








    return 0;
}
