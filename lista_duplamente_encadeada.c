#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node *prev;
    struct Node *next;
} Node;

typedef struct LinkedList {
    Node *head;
    Node *tail;
    int size;
} List;

void init(List *list) {
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

Node *create_node(int value) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = value;
    new_node->prev = NULL;
    new_node->next = NULL;
    return new_node;
}

void append(List *list, int value) {
    Node *new_node = create_node(value);

    if (list->head == NULL) {
        list->head = new_node;
    }
    else {
        list->tail->next = new_node;
        new_node->prev = list->tail;
    }

    list->tail = new_node;
    list->size++;
}

void append_ordered(List *list, int data) {
    Node *new_node = create_node(data), *current;
    bool appended = false;

    if (list->head == NULL) {
        list->head = new_node;
        list->tail = new_node;
    }
    else {
        current = list->head;

        while (current != NULL) {
            if (current->data >= new_node->data) {
                appended = true;

                if (current->prev == NULL) {
                    list->head = new_node;
                    new_node->next = current;
                    current->prev = new_node;
                    break;
                }
                    
                current->prev->next = new_node;
                new_node->prev = current->prev;

                current->prev = new_node;
                new_node->next = current;
                break;
            }

            current = current->next;
        }


        if (!appended) {
            new_node->prev = list->tail;
            list->tail->next = new_node;
            
            list->tail = new_node;
        }
    }

    list->size++;
}

void remove_(List *list, int value) {
    Node *current = list->head;

    while (current != NULL) {
        if (current->data == value) {
            if (list->head == current) {
                list->head = current->next;
                list->head->prev = NULL;
            }
            else {
                current->prev->next = current->next;
                current->next->prev = current->prev;
            }

            if (current->next == NULL) {
                list->tail = current->prev;
            }

            free(current);
            list->size--;
            return;
        }

        current = current->next;
    }
}

void print_list(List list) {
    Node *current = list.head;

    printf("[");
    while (current != NULL) {
        printf("%d", current->data);
        if (current->next != NULL) {
            printf(", ");
        }
        current = current->next;
    }
    printf("]\n");
}

void print_list_reverse(List list) {
    Node *current = list.tail;

    printf("[");
    while (current != NULL) {
        printf("%d", current->data);
        if (current->prev != NULL) {
            printf(", ");
        }
        current = current->prev;
    }
    printf("]\n");
}

int main() {
    List list;
    init(&list);
    append_ordered(&list, 7);
    append_ordered(&list, 9);
    append_ordered(&list, 8);
    append_ordered(&list, 6);
    append_ordered(&list, 7);
    print_list(list);
    print_list_reverse(list);

    remove_(&list, 7);
    print_list(list);
    print_list_reverse(list);
    
    return 0;
}
