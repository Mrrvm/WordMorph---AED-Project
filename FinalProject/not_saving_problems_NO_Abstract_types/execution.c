/***************************************************************
* Wordmorph @ AED-Project 2016-2017
* by
* Madalena Muller & Mariana Martins
*
* execution.c
* All functions that directly allow the wordmorphism to happen
***************************************************************/

#include "execution.h"

int binary_search(word_vector_element *got_word_vector, int l, int r, char *word) {
  
  char *temp_word;
  int m;

  while (l <= r) {  
    m = l + (r-l)/2;
    temp_word = get_word_vector_word(m, got_word_vector);
    if(strcmp(temp_word, word) == 0) 
        return m;  

    if (strcmp(temp_word, word) < 0) 
        l = m + 1; 
    else
    	r = m - 1; 
  }
  return -1; 
}


void merge(word_vector_element *got_word_vector, int left, int mid, int right) {
    char **temp_array  = NULL;
    char *wordl, *wordr;
    int pos=0,lpos = left,rpos = mid + 1;
    int iter = 0;

    /*Alloc a temporary array of strings*/
    temp_array = (char **)calloc((right-left+1),sizeof(char*));
    while(iter < right-left+1) {
    	temp_array[iter] = (char *)calloc(100, sizeof(char));
    	iter++;
    }

    /*Merge the 2 parts*/
    while(lpos <= mid && rpos <= right)
    {
    	wordl = get_word_vector_word(lpos, got_word_vector);
    	wordr = get_word_vector_word(rpos, got_word_vector);
        if(strcmp(wordl, wordr) < 0) {
            strcpy(temp_array[pos], wordl);
            pos++;
            lpos++;
        }
        else {
        	strcpy(temp_array[pos], wordr);
        	pos++;
        	rpos++;
        }
    }
    /*Merge the leftover part*/
    while(lpos <= mid) {
    	wordl = get_word_vector_word(lpos, got_word_vector);
    	strcpy(temp_array[pos], wordl);
         pos++;
         lpos++;
    }
    while(rpos <= right) {
    	wordr = get_word_vector_word(rpos, got_word_vector);
    	strcpy(temp_array[pos], wordr);
        pos++;
        rpos++;
    }
    
    /*Copy the temporary array to the real array*/
    for(iter = 0;iter < pos; iter++) {
    	copy_word_to_vector(temp_array[iter], got_word_vector, iter+left);
    }

    /*Free the temporary array*/
    iter = 0;
    while(iter < right-left+1) {
    	free(temp_array[iter]);
    	iter++;
    }
    free(temp_array);
    return;
}


void merge_sort(word_vector_element *got_word_vector, int left, int right) {
    int mid = (left+right)/2;
    /*When left=right it is already sorted*/
    if(left<right) {
            /*Sort the left part */
            merge_sort(got_word_vector, left, mid);
            /*Sort the right part */
            merge_sort(got_word_vector, mid+1, right);
            /*Merge the two sorted parts */
           	merge(got_word_vector, left, mid, right);
    }
}

/*Gets the correct vector to search the words position into and decides which
	function to execute depending on the number of problems of each number of 
	letters.*/
void run_position_search(pal_problem *new_problem, vector *indexing_vector) {

	int word_len = 0;
	element *got_element = NULL;
	word_vector_element *got_word_vector = NULL;
	int n_words = 0;

	word_len = strlen(get_problem_word1(new_problem));
	got_element = get_vector_item(word_len, indexing_vector);
	n_words = get_element_n_words(got_element);
	/*Just to be sure*/
	if(got_element != NULL) {
		got_word_vector = get_element_word_vector(got_element);
		/*If there words of this size in the dictionary, then...*/
		if(got_word_vector != NULL) {
			if(!get_element_sorted(got_element)) {
				merge_sort(got_word_vector, 0, n_words-1);
				set_element_sorted(got_element);
			}
			/*Set the position of the words in the problem structure after the search*/
			set_problem_position1(new_problem, binary_search(got_word_vector, 0, n_words, get_problem_word1(new_problem)));
			set_problem_position2(new_problem, binary_search(got_word_vector, 0, n_words, get_problem_word2(new_problem)));		
		}
		/*If the element has no words in the word vector, the result
			of the search will be -1*/
		else {
			set_problem_position1(new_problem, -1);
			set_problem_position2(new_problem, -1);
		}
	}
	return;
}

/*******************************************************************/

int check_number_of_comutations(char *word1, char *word2, int max_comut, int *n_comut) {
	int diff = 0, i=0, len = 0;

	len = strlen(word1);
	for(i=0; i < len; i++) {
    	if(word1[i] != word2[i])
    		diff ++;
    	if(diff > max_comut)
    		return 0;
    }
    *n_comut = diff;
	return 1;
}

void create_graph(element *got_element) {

	int size = 0, max_comut = 0, n_comut = 0;
	int i = 0, j = 0;
	word_vector_element *got_word_vector = NULL;
	char *curr_word, *temp_word;

	max_comut = get_element_max_comut(got_element);
	got_word_vector = get_element_word_vector(got_element);
	size = get_element_n_words(got_element);

	if(!get_element_sorted(got_element)) {
		merge_sort(got_word_vector, 0, size-1);
		set_element_sorted(got_element);
	}

	for(i=0; i<size; i++) {
		curr_word = get_word_vector_word(i, got_word_vector);
		for(j=i+1; j<size; j++) {
			temp_word = get_word_vector_word(j, got_word_vector);
			if(check_number_of_comutations(curr_word, temp_word, max_comut, &n_comut)) {
				push_adj_el_to_word_vector_el(i, got_word_vector, create_adj_element(j, n_comut));
				push_adj_el_to_word_vector_el(j, got_word_vector, create_adj_element(i, n_comut));
			}
		}
	}
	set_element_got_graph(got_element);

	return;
}

int check_similar_problems() {
	return 1;
}

void do_dijkstra() {
	return;
}

void run_problem_solver(pal_problem *new_problem, vector *indexing_vector) {

	int len = 0;
	element *got_element = NULL;

	len = strlen(get_problem_word1(new_problem));
	got_element = get_vector_item(len, indexing_vector);
	
	if(!get_element_got_graph(got_element))
		create_graph(got_element);
	do_dijkstra();
	save_problem_solution();
	
	sub_element_n_problems(got_element);
	if(get_element_n_problems(got_element) == 0)
		free_word_vector(get_element_word_vector(got_element), get_element_n_words(got_element));
	return;
}