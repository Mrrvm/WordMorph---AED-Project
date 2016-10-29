/***************************************************************
* Wordmorph @ AED-Project 2016-2017
* by
* Madalena Muller & Mariana Martins
*
* structures.c
* All functions that create/append/add/free/get/set structures.
***************************************************************/

#include "structures.h"


struct _node {
    item this;
    node *next;
};

struct _list {
    size_t size;
    node *head;
};

struct _element {
    item this;
};

struct _vector {
    size_t size;
    element data;
};

/*****************************NODE*****************************/

node *create_node(item new_item, node *next_node) {
    node *new_node = NULL;

    /* Memory allocation */
    new_node = (node *)malloc(sizeof(node));

    if (new_node == NULL)
        memory_error("Unable to reserve node memory");

    /* Add item to node*/
    new_node->this = new_item;
    new_node->next = next_node;

    return new_node;
}

item get_node_item(node *got_node) {
    return got_node->this;
}

node *get_next_node(node *got_node) {
    return got_node->next;
}

void free_node(node *got_node, void (*free_item)(item)) {
    /* Free node item */
    free_item(got_node->this);

    /* Free the node to save on the load */
    free(got_node);

    return;
}

void free_connected_nodes(node *got_node, void (*free_item)(item)) {
    node *aux_node = NULL;

    /* Free every node connected*/
    while(got_node != NULL) {
        aux_node = get_next_node(got_node);
        free_node(got_node, free_item);
        got_node = aux_node;
    }
    return;
}

/*****************************LIST*****************************/

list *create_list() {
    list *new_list = NULL;

    /* Create List */
    new_list = (list *)malloc(sizeof(list));
    if(new_list == NULL)
        memory_error("Unable to reserve list memory");

    /* Set head to null */
    new_list->head = NULL;

    /* Set size to 0 :( */
    new_list->size = 0;

    return new_list;
}

node *get_head(list *got_list) {
    return got_list->head;
}

void set_head(list *got_list, node *got_head) {
    got_list->head = got_head;
    return;
}

void push_node_to_list(list *got_list, node *got_node) {
    got_node->next = got_list->head;
    got_list->head = got_node;

    /* Increase List size :D */
    got_list->size ++;

    return;
}

void push_item_to_list(list *got_list, item new_item) {
    /* Node Creation */
    node *new_node = NULL;
    new_node = create_node(new_item, NULL);

    /* Prepend node to list*/
    push_node_to_list(got_list, new_node);
    return;
}


size_t get_list_size(list *got_list) {
    return got_list->size;
}

void print_list(list *got_list, void (*print_item)(item)) {
    node *aux_node;
    spam(("Print list:\n"));
    spam(("Size of list: %lu\n", get_list_size(got_list)));

    for(aux_node = get_head(got_list);
            aux_node != NULL;
            aux_node = get_next_node(aux_node)) {
        spam(("[ "));
        print_item(get_node_item(aux_node));
        spam(("] -> \n"));
    }

    spam(("-> [ " KBLU "NULL" RESET " ]"));

}

void free_list(list *got_list, void (*free_item)(item)) {
    node *got_node = get_head(got_list);

    /* Free every node of list*/
    free_connected_nodes(got_node, free_item);

    /* Bring freedom to stack */
    free(got_list);

    return;
}


/***************************** VECTOR *****************************/


vector *create_vector(int n_elements) {

    vector *new_vector = NULL;
    
    new_vector = (vector *)malloc(sizeof(vector));
    if(new_vector == NULL)
        memory_error("Unable to reserve vector memory");

    new_vector->data = (element *)malloc(sizeof(element)*n_elements);
    if(new_vector->data == NULL)
         memory_error("Unable to reserve vector memory");

     vector->size = n_elements;

     return new_vector;
}

size_t get_vector_size(vector *got_vector) {
    return got_vector->size;
}

element *get_vector_element(int index, vector *got_vector) {
    if(index >= got_vector->size || index < 0) {
        memory_error("Unable to reach element memory");
        exit(0);
    }
    return got_vector->data[index];
}

void set_element_to_vector(int index, vector *got_vector, item new_item) {

    if(index >= got_vector->size || index < 0) {
        memory_error("Unable to reach element memory");
        exit(0);
    }
    
    element *new_element =  NULL;
    new_element->this = new_item;
   
    vector->data[index] = new_element;
    return;
}

void realloc_vector(vector *got_vector, int n_elements) {

    got_vector->data = realloc(got_vector->data, sizeof(element)*n_elements);
    if(got_vector->data == NULL)
        memory_error("Unable to reserve vector memory");

    got_vector->size = n_elements;
}

void free_vector(vector *got_vector, void (*free_item)(item)) {

    int size = got_vector->size;
    int i = 0;

    while(i < size) {
        free_item(got_element->this);
        i++;
    }

    free(got_vector->data)
    free(got_vector);
    return;
}

void print_vector(vector *got_vector, void (*print_item)(item)) {
    
    int size = got_vector->size;
    int i = 0;

    while(i < size) {
        spam((KGRN "\n[Element = %d]:\n" RESET, i));
        print_item(got_vector->data[i]->this);
        spam(("\n"));
        i++;
    }
    return;
}

