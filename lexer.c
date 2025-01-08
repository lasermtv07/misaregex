#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
typedef enum tokType {
    class,
    brack,
    bin,
    count,
    end
} tokType;
typedef struct charToken {
    bool any;
    bool neg;
    char* class;
    struct charToken* next;
} charToken;
typedef struct token {
    tokType type;
    int minChar;
    int maxChar;
    char c;
    charToken* class;
    struct token* next;
} token;

token* newToken(tokType type,int minChar,int maxChar,char c){
    token* a=malloc(sizeof(token));
    if(a!=NULL){
        a->type=type;
        a->minChar=minChar;
        a->maxChar=maxChar;
        a->c=c;
        a->class=NULL;
        a->next=NULL;
    }
    return a;
}
void addToken(token* a, tokType type,int minChar,int maxChar, char c){
    while(a->next!=NULL){
        a=a->next;
    }
    a->next=newToken(type,minChar,maxChar,c);
}
void addClass(token* a,bool any, bool neg,char* class){
    charToken* b=malloc(sizeof(charToken));
    b->any=any;
    b->neg=neg;
    b->class=class;
    if(a->class==NULL){
        a->class=b;
        return;
    }
    charToken* c=a->class;
    while(c->next!=NULL){
        c=c->next;
    }
    c->next=b;
}
