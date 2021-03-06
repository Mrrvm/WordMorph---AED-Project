/***************************************************************
* Wordmorph @ AED-Project 2016-2017
* by
* Madalena Muller & Mariana Martins
*
* main.c
* Main execution of the program
***************************************************************/

#include "execution.h"
#include "file.h"

int main(int argc, char **argv) {

	FILE *output_file, *pal_file;
	vector *indexing_vector = NULL;
	char *output_filename;
	pal_problem *new_problem = NULL;
	path_element *path_vector = NULL;

	/*Checks if the invocation is right*/
	if(argc != 3 || strcmp(get_filename_ext(argv[1]), "dic") || strcmp(get_filename_ext(argv[2]), "pal"))
		file_error("Missing arguments or wrong extension specified on file input");
	/*Alloc vector with each index as the number 
		of letters of a word. The maximum number of letters is 100*/
	indexing_vector = create_vector(101);
	/*Read pal file once, to get the maximum number of mutations for
		each different number of letters and to know which number of 
		letters	is a problem to solve*/
	manage_pal_file(argv[2], indexing_vector);
	/*Read dictionary file once to get the number of words 
		for each different number of letters*/
	manage_dic_file(argv[1], manage_dic_data1, indexing_vector);
	/*Read dictionary file again to put all the words in the dictionary*/
	manage_dic_file(argv[1], manage_dic_data2, indexing_vector);
	/*Open pal file again and leave it open till all the 
		problems are solved*/
	pal_file = fopen(argv[2], "r");
	if(pal_file == NULL)
		file_error("Unable to open specified file");
	/*Alloc space for a structure to hold the problems of pal file,
		temporarily*/
	new_problem = create_pal_problem();
	/*Create the output filename - pal filename with .path extension.
		Generate the output file*/
	output_filename = create_output_filename(argv[2]);
	output_file = fopen(output_filename, "w");
	if(output_file == NULL)
		file_error("Unable to create specified file");
	/*Start reading problem by problem until EOF*/
	while(read_pal_file(pal_file, new_problem)) {
		/*Solve the problem by receiving a vector with the paths from
			the source word to all the other words that fulfill the 
			requirements of the problem (aka number of maximum mutations)*/
		path_vector = run_problem_solver(new_problem, indexing_vector);
		/*Get the path required from path_vector and write it to an
			output file*/
		write_to_file(indexing_vector, new_problem, output_file, path_vector);
 		if(path_vector == NULL)
 			free(path_vector);
 	}
 	
 	/*Bring freedom upon this data structures!*/
 	free(output_filename);
 	free(new_problem);
 	free_vector(indexing_vector, free_element);
 	/*Bring death upon this files!*/
 	fclose(output_file);
	fclose(pal_file);
	exit(0);
}