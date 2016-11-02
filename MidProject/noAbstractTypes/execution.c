/***************************************************************
* Wordmorph @ AED-Project 2016-2017
* by
* Madalena Muller & Mariana Martins
*
* execution.c
* All functions that directly allow the wordmorphism to happen
***************************************************************/

#include "execution.h"

/*Searches the position of the 2 words of the problem in the word 
	vector of its number of letters. 
	The search is made by comparing the problem strings with each vector
	string. If the vector string is less than the problem string, the 
	problem string position adds up. 
	Example:
		VECTOR: roxa boca rola bola roda 
		A PROBLEM STRING: rola 
		COMPARISSONS:
			rola > roxa - discarded
			rola < boca - adds up (+1)
			rola = rola - discarded
			rola < bola - adds up (+1)
			rola < roda - adds up (+1)
		POSITION: rola 3 
*/
void simple_search_for_words(pal_problem *new_problem, char **got_word_vector, int size) {

	char *word1, *word2, *curr_word;
	int i = 0;
	int found_word1 = 0, found_word2 = 0;
	
	word1 = get_problem_word1(new_problem);
	word2 = get_problem_word2(new_problem);

	while(i < size) {
		curr_word = got_word_vector[i];
		if(strcmp(word1, curr_word) > 0) {
			addto_problem_position1(new_problem);
		}
		if(strcmp(word2, curr_word) > 0) {
			addto_problem_position2(new_problem);
		}
		if(strcmp(word1, curr_word) == 0) {
			found_word1 = 1;
		}
		if(strcmp(word2, curr_word) == 0) {
			found_word2 = 1;
		}
		i++;
	}

	if(found_word1 != 1) {
		set_problem_position1(new_problem, -1);
	}
	if(found_word2 != 1) {
		set_problem_position2(new_problem, -1);
	}
	return;
}


/*Gets the correct vector to search the words position into.*/
void run_position_search(pal_problem *new_problem, vector *indexing_vector) {

	int word_len = 0;
	element *got_element = NULL;
	char **got_word_vector = NULL;

	word_len = strlen(get_problem_word1(new_problem));
	got_element = get_vector_item(word_len, indexing_vector);
	/*Just to be sure*/
	if(got_element != NULL) {
		got_word_vector = get_element_word_vector(got_element);
		if(got_word_vector != NULL) {
			simple_search_for_words(new_problem, got_word_vector, get_element_n_words(got_element));
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