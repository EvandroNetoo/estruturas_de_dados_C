#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
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
    }

    list->tail = new_node;
    list->size++;
}

void append_ordered(List *list, int data) {
    Node *new_node = create_node(data), *previous, *current;
    bool appended = false;

    if (list->head == NULL) {
        list->head = new_node;
        list->tail = new_node;
    }
    else {
        current = list->head;
        previous = NULL;

        while (current != NULL) {
            if (current->data >= new_node->data) {
                appended = true;
                if (previous == NULL) {
                    list->head = new_node;
                    new_node->next = current;
                    break;
                }
                previous->next = new_node;
                new_node->next = current;
                break;
            }

            previous = current;
            current = current->next;
        }

        if (!appended) {
            list->tail->next = new_node;
            list->tail = new_node;
        }
    }

    list->size++;
}

void remove_(List *list, int value) {
    Node *current = list->head, *previous = NULL;

    while (current != NULL) {
        if (current->data == value) {
            if (previous == NULL) {
                list->head = current->next;
            }
            else {
                previous->next = current->next;
            }

            if (current->next == NULL) {
                list->tail = previous;
            }

            free(current);
            list->size--;
            return;
        }

        previous = current;
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
    printf("]");

    printf("\n");
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

    remove_(&list, 7);
    print_list(list);
    
    return 0;
}
