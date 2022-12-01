

#include <stdio.h>
#include <stdlib.h>
#include "ppm_info.h"

int main(int argc, char* argv[]) {
	// check for the correct arguements entered on the command line
	if(argc != 3) {
	printf("USAGE: <executable> <image1> <image2>\n\n");
	return -1;
	}		

	// variable declarations
	int count;
	filePtr_t* userPtr = (filePtr_t*)malloc(sizeof(filePtr_t));

	// opening command line files
	FILE* file1 = fopen(argv[1], "r");
	FILE* file2 = fopen(argv[2], "r");

	// filePtr for output file
	filePtr_t* out_file = NULL;

	// reading ppm of first command line file
	image_t* image1;
	image1 = read_ppm(file1);
	
	// initializing filePtr for first command line file
	filePtr_t* filePtr1 = (filePtr_t*)malloc(sizeof(filePtr_t));
	filePtr1->theFile = file1;
	filePtr1->imageFileName = argv[1];
	filePtr1->theImage = image1;
	filePtr1->next = NULL;

	// set out_file to the first filePtr
	out_file = filePtr1;
	
	// read ppm of second command line file
	image_t* image2;
	image2 = read_ppm(file2);

	// initializing filePtr for second command line file
	filePtr_t* filePtr2 = (filePtr_t*)malloc(sizeof(filePtr_t));
	filePtr2->theFile = file2;
	filePtr2->imageFileName = argv[2];
	filePtr2->theImage = image2;
	filePtr2->next = NULL;

	out_file->next = filePtr2;

	// printing manipulation menu
	int usersChoice = 0;
	usersChoice = printMenu1();
	
	// calling manipulation function based on users manipulation choice
	while (usersChoice != 0) {
		if(usersChoice == 1) {	
			userPtr = printList(out_file);
			gray_scale(userPtr, &out_file, count);
		}
		else if(usersChoice == 2) {
			userPtr = printList(out_file);
			mirror(userPtr, &out_file,  count);
		}
		else if(usersChoice == 3) {
			userPtr = printList(out_file);
			green_screen(filePtr1, userPtr, &out_file, count);
		}
		count++;
		usersChoice = printMenu1();
	}

return 0;
}
