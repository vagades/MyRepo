#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define BUF_MAX 9

typedef struct node{
    struct node* next;
    struct node* prev;
    char* word;
} node;

node* create_node(char* word, node* prev, node* next){
    node* tmp = malloc(sizeof(node));
    tmp -> word = word;
    tmp -> next = next;
    tmp -> prev = prev;
    return tmp;
}

void insert(node** head, char* word){
    if (*head == NULL){
        *head = create_node(word, NULL, NULL);
        return;
    }
    node* tmp = *head;
    while(tmp->next != NULL){
        if (strcmp(tmp->word, word) < 0)        
            tmp = tmp -> next;
        else   {
            node* new  = create_node(word, tmp->prev, tmp);
            if (tmp -> prev != NULL){
                tmp -> prev -> next = new;
                tmp -> prev = new;
            }else{
                *head = new;
            }
            return;
        }
    }
    if (strcmp(tmp->word, word) > 0){ // word < tmp -> word
        node *new = create_node(word, tmp->prev ,tmp);
        if (tmp -> prev != NULL){
            printf(" between %s", tmp->word);
            tmp -> prev -> next = new;
            tmp -> prev = new;
        }else{
            *head = new;
        } 
        return;    
    }
    node* new = create_node(word, tmp, NULL);
    tmp -> next = new;
    return;
}

int dop_info(node* head, char* word){
    int cnt = 0;
    while( head != NULL){
        if (strcmp(head->word, word) == 0)
            cnt++;
        head = head -> next;
    }
    return cnt;
}

void print_list(node* head){
    node* tmp = head;
    while(tmp != NULL){
        printf("%s col-vo: %d \n", tmp->word, dop_info(head, tmp->word));
        tmp = tmp -> next;
    }
    return;
}

node** parse(){
    char ch;
    char* word = malloc(BUF_MAX * sizeof(char));
    int i = 0;
    node** heads = malloc(sizeof(node*) * 9); // будем нумеровать с 1 для удобства
    for (int i = 1; i<9; i++){
        heads[i] = NULL;
    }
    while((ch = getchar()) != '.'){
        if (ch == ','){
            word[i] = '\0';
            char* tmp = malloc(strlen(word) + 1); 
            strcpy(tmp, word);
            insert(&heads[strlen(word)], tmp);
            i = 0;
            continue;
        }
        word[i] = ch;
        i++;
    }
    word[i] = '\0';
    insert(&heads[strlen(word)], word);
    return heads;
}

int main(){
    node** heads = parse();
    for (int i = 1; i<9; i++){
        print_list(heads[i]);
    }
}
