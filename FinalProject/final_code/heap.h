/***************************************************************
* Wordmorph @ AED-Project 2016-2017
* by
* Madalena Muller & Mariana Martins
*
* heap.h
* All functions auxiliary for running dijkstra
****************************************************************/

#ifndef heapHeader
#define heapHeader

#include "storing.h"

typedef struct _heap_element heap_element;
typedef struct _path_element path_element;

/************************* HASH TABLE ***************************/
int *create_hash_table(int n_elements);
int get_hash_table_value(int i, int *hash_table);
void set_hash_table_value(int _value, int i, int *hash_table);
void print_hash_table(int *hash_table, int size);

/*********************** PATH VECTOR ***************************/
path_element *create_path_vector(int n_elements);
path_element get_path_vector_element(int i, path_element *path_vector);

/********************* PATH VECTOR ELEMENT **********************/
int get_path_element_total_weight(int i, path_element *path_vector);
int get_path_element_parent(int i, path_element *path_vector);
void set_path_element_total_weight(int _total_weight, int i, path_element *path_vector);
void set_path_element_parent(int _parent, int i, path_element *path_vector);
void print_path_vector(path_element *path_vector, int size);

/************************ HEAP VECTOR ***************************/
heap_element *create_heap_vector(int n_elements);
heap_element get_heap_vector_element(int i, heap_element *heap_vector);

/******************** HEAP VECTOR ELEMENT ***********************/
int get_heap_element_dic_index(int i, heap_element *heap_vector);
int get_heap_element_weight(int i, heap_element *heap_vector);
void set_heap_element_dic_index(int _dic_index, int i, heap_element *heap_vector);
void set_heap_element_weight(int _weight, int i, heap_element *heap_vector);

/*********************** HEAP FUNCTIONS ************************/
void print_heap_vector(heap_element *heap_vector, int size);
void initialize_heap(int size, int *hash_table, path_element *path_vector, heap_element *heap_vector);
void heapify(int i, int size, int *hash_table, heap_element *heap_vector);
int get_first_heap_dic_index(int *hash_table, int size, heap_element *heap_vector);

/********************* DIJKSTRA ALGORITHM **********************/
void find_better_path(path_element *path_vector, int curr_heap_dic_index, adj_element *node, int *hash_table, heap_element *heap_vector);

#endif