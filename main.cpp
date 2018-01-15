#include<iostream>
using namespace std;
typedef struct element {
                         int info;
                         struct element *next;
                       } termen;

typedef struct {
                int length;
                termen *start,*current,*finalist;
                } lista;

lista *L;

lista *initlist() {
    lista *result=new lista;
    result->length=0;
    result->start=result->current=result->finalist=NULL;
    return result;
}

int isempty(lista *L) {
    return  (L->length==0);
}

int searchvalue(lista **L,int value) {
    termen *carrier;
    carrier=(*L)->start;
    while ((carrier!=(*L)->finalist)&&(carrier->info!=value)) {
        carrier=carrier->next;
    }
    if ((carrier==(*L)->finalist)&&(carrier->info!=value)) {
        return 0;
    }
    (*L)->current=carrier;
    return 1;
}

lista * addleft(lista *L, int value) {
    if(isempty(L)) {
        termen *newone=new element;
        newone->info=value;
        L->current=L->finalist=L->start=newone;
        L->length++;
        return L;
    }
    if(L->current == L->start) {
        termen *newone=new element;
        newone->info=value;
        newone->next = L->start;
        L->current = L->start = newone;
        L->length++;
        return L;
    }
    termen *newone=new element;
    newone->info=value;
    newone->next = L->current;
    termen *carrier;
    carrier = L->start;
    while(carrier->next->info != L->current->info) carrier = carrier->next;
    carrier->next = newone;
    L->current = newone;
    L->length++;
    return L;
}

lista *delleft(lista *L) {
    if(isempty(L) || L->current == L->start) return L;
    if(L->start->next == L->current) {
        delete L->start;
        L->start = L->current;
        L->length--;
        return L;
    }
    termen *aux;
    aux = L->start;
    while(aux->next->next->info != L->current->info) aux = aux->next;
    delete aux->next;
    aux->next = L->current;
    L->length--;
    return L;
}

int show(lista *L) {
    cout<<endl;
    termen *carrier;
    carrier=L->start;
    int counter=L->length;
    while (counter>0) {
        cout<<carrier->info<<" ";
        carrier=carrier->next;
        counter--;
    }
}

int main() {
    L=initlist();
    for(int i=1;i<=3;i++) L=addleft(L,i);
    show(L); // 3 2 1
    searchvalue(&L,2);
    L=addleft(L,0);
    show(L); // 3 0 2 1
    searchvalue(&L,1);
    L=delleft(L);
    show(L); // 3 0 1
    searchvalue(&L,456);
    L=addleft(L,-1);
    show(L); // 3 0 -1 1
    return 0;
}
