#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "lexer.c"
typedef enum class {
    chr,
    nMeta,
    atom,
    factor,
    term,
    expr
} class;
typedef struct node {
    class class;
    token* t;
    struct node* left;
    struct node* middle;
    struct node* right;
} node;
token** pt=NULL;
token* scanToken(){
    if(pt!=NULL && *pt!=NULL && (*pt)->next!=NULL){
        *pt=(*pt)->next;
    }
    return *pt;
}
int main(){
    token* t=tokenize("ab|c(abba){,5}");
    pt=&t;
    scanToken();
    printf("%s\n",(*pt)->class);

    while(t!=NULL){
        if(t->type==rep)
            printf("%d,%d\n",t->minRep,t->maxRep);
        else
            printf("%s\n",t->class);
        t=t->next;
    }
}