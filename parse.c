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
    struct node* right;
} node;
node* newNode(class class,token* t,node* left,node* right){
    node* a=malloc(sizeof(node));
    if(a!=NULL){
        a->class=class;
        a->t=t;
        a->left=left;
        a->right=right;
    }
    return a;
}
token** pt=NULL;
token* scanToken(){
    if(pt!=NULL && *pt!=NULL && (*pt)->next!=NULL){
        *pt=(*pt)->next;
    }
    return *pt;
}

node* pTerm();
node* pExpr(){
    node* a=newNode(expr,NULL,pTerm(),NULL);
    if((*pt)->next!=NULL && ((*pt)->next)->type==meta && ((*pt)->next)->class[0]=='|'){
        scanToken();
        a->right=pTerm();
    }
    return a;
}
node* pFactor();
node* pTerm(){
    node* a=newNode(term,NULL,pFactor(),NULL);
    if((*pt)->next!=NULL && ((*pt)->next)->type==meta && ((*pt)->next)->class[0]!=')'){
        a->right=pTerm();
    }
    return a;
}
node* pAtom();
node* pFactor(){
    node* a=(factor,NULL,pAtom(),NULL);
    if((*pt)->next!=NULL && ((*pt)->next)->type==meta && (((*pt)->next)->class[0]=='*' || ((*pt)->next)->class[0]=='.' )){
        node* b=newNode(nMeta,scanToken(),NULL,NULL);
        a->right=b;
    }
    return a;
}
//TODO: finished parser
node* pChar();
node* pAtom(){
    if((*pt)->next->type==meta && (*pt)->next->class[0]=='('){
        scanToken();
    }
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