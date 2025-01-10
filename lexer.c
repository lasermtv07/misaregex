#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
typedef enum tokType {
    normal,
    meta,
    init,
    rep
} tokType;
typedef struct token {
    tokType type;
    char* class;
    int minRep;
    int maxRep;
    struct token* next;
} token;
token* newToken(tokType type,char* class,int minRep,int maxRep){
    token* a=malloc(sizeof(token));
    if(a!=NULL){
        a->type=type;
        a->class=class;
        a->next=NULL;
        a->minRep=minRep;
        a->maxRep=maxRep;
    }
    return a;
}
void addToken(token* a,tokType type,char* class,int minRep,int maxRep){
    if(a==NULL)
        return;
    while(a->next!=NULL){
        a=a->next;
    }
    a->next=newToken(type,class,minRep,maxRep);
}
bool isMeta(char* regex, int i){
    if(i>0 && regex[i-1]=='\\'){
        if((i>1 && regex[i-2]!='\\') || i<=1)
            return false;
    }
    else if(regex[i]=='\\')
        return true;
    else if(regex[i]=='(' || regex[i]==')')
        return true;
    else if(regex[i]=='[' || regex[i]==']')
        return true;
    if(regex[i]=='{' || regex[i]=='}')
        return true;
    if(regex[i]=='.' || regex[i]=='$' || regex[i]=='*')
        return true;
    else
        return false;
}
char* char2str(char c){
    char* o=malloc(2);
    o[0]=c;
    o[1]=0;
    return o;
}
int scanCharClass(char* regex, int i,token* a){
    i++;
    char* tmpStr=malloc(strlen(regex)+1);
    strncpy(tmpStr,"",strlen(regex)+1);
    int extI=0;
    while(regex[i]!=']' && regex[i]!='\0'){
        tmpStr[extI]=regex[i];
        i++;
        extI++;
    }
    addToken(a,normal,tmpStr,1,1);
    return i;
}
int scanCount(char* regex,int i, token* a){
    i++;
    char* min=malloc(strlen(regex)+1);
    char* max=malloc(strlen(regex)+1);
    strncpy(min,"",strlen(regex)+1);
    strncpy(max,"",strlen(regex)+1);
    int extI=0;
    bool sw=false;
    while(regex[i]!='}' && regex[i]!='\0'){
        if(regex[i]==','){
            extI=0;
            sw=true;
            i++;
        }
        if(!sw)
            min[extI]=regex[i];
        else
            max[extI]=regex[i];
        i++;
        extI++;
    }
    addToken(a,rep,NULL,atoi(min),atoi(max));
    free(min);
    free(max);
    return i;
}
token* tokenize(char* regex){
    int i=0;
    token* a=newToken(init,NULL,0,0);
    while(regex[i]!=0){
        if(!isMeta(regex,i))
            addToken(a,normal,char2str(regex[i]),1,1);
        else if(regex[i]!='[' && regex[i]!=']' && regex[i]!='{' && regex[i]!='}')
            addToken(a,meta,char2str(regex[i]),1,1);
        else if(regex[i]=='[')
            i=scanCharClass(regex,i,a);
        else if(regex[i]=='{')
            i=scanCount(regex,i,a);

        i++;
    }
    return a;
}
