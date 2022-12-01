
/*manipulations file for PPM-SHOP */

#include "ppm_info.h"

// make each color pixel the average of the r, g, b components
// which will gray-scale the image
void gray_scale(filePtr_t* image, filePtr_t** theList, int count) {
   int row = 0;
   int col = 0;
   int avg = 0;
   
   // allocating memory for new image
   header_t header = image->theImage->header;
   image_t* out_image = allocate_memory(header);

   char fileName[30] = "g";
   strcat(fileName, image->imageFileName);
   
   // creating name for file
   if(fileName[1] != 'g') {
	   char buf[5];
	   fileName[strlen(fileName)-4] = '\0';
	   int length = snprintf(buf, 5, "%d", count);
	   char* imageName = (char*)malloc(length);
	   sprintf(imageName, "%s%02d.ppm", fileName, count);

	   FILE* grayedImage = fopen(imageName, "w");
	   if(!grayedImage) {
		   fprintf(stderr, "grayed image file could not open\n\n");
		   exit(1);
	   }

   for(row = 0; row < header.height; row++) {
      for(col = 0; col < header.width; col++) {
                        // calculate the average of the r, g, b values for the pixel
                        avg = ( image->theImage->pixels[row][col].r +
                                image->theImage->pixels[row][col].g +
                                image->theImage->pixels[row][col].g ) / 3;

                        // assign avg to each r, g, b value of the pixel

                        out_image->pixels[row][col].r = avg;
                        out_image->pixels[row][col].g = avg;
                        out_image->pixels[row][col].b = avg;


     		 }
  	}
	
	write_p6(grayedImage, out_image);
	fclose(grayedImage);
	
	// adding new image to list of images
	filePtr_t* temp = *theList;
	addToList(temp, grayedImage, out_image, imageName);
   }
}

void mirror(filePtr_t* image, filePtr_t** theList, int count) {
	int row = 0;
	int col = 0;
	
	// allocating memory for new image
	header_t header = image->theImage->header;
	image_t* out_image = allocate_memory(header);
	
	char fileName[30] = "m";
	strcat(fileName, image->imageFileName);
	
	// creating new image name
	if(fileName[1] != 'm') {
           char buf[5];
           fileName[strlen(fileName)-4] = '\0';
           int length = snprintf(buf, 5, "%d", count);
           char* imageName = (char*)malloc(length);
           sprintf(imageName, "%s%02d.ppm", fileName, count);

           FILE* mirroredImage = fopen(imageName, "w");
           if(!mirroredImage) {
                   fprintf(stderr, "grayed image file could not open\n\n");
                   exit(1);
           }

	   for(row = 0; row < header.height; row++) {
		   for(col = 0; col < header.width; col++) {
			   out_image->pixels[row][col] = image->theImage->pixels[row][header.width-1-col];
			   out_image->pixels[row][header.width-1-col] = image->theImage->pixels[row][col];
		   }
	   }

	   write_p6(mirroredImage, out_image);
	   fclose(mirroredImage);

	   // adding new image to list of images
	   filePtr_t* temp = *theList;
	   addToList(temp, mirroredImage, out_image, imageName);

	   }
}


void green_screen(filePtr_t* image1, filePtr_t* image2, filePtr_t** theList, int count) {
	int row = 0;
	int col = 0;

	// allocating memory for new image
	header_t header = image1->theImage->header;
	image_t* out_image = allocate_memory(header);
	
	char fileName[30] = "gs";
	strcat(fileName, image2->imageFileName);
	if(fileName[2] != 's') {
           char buf[5];
           fileName[strlen(fileName)-4] = '\0';
           int length = snprintf(buf, 5, "%d", count);
           char* imageName = (char*)malloc(length);
           sprintf(imageName, "%s%02d.ppm", fileName, count);

           FILE* greenScreenImage = fopen(imageName, "w");
           if(!greenScreenImage) {
                   fprintf(stderr, "grayed image file could not open\n\n");
                   exit(1);
           }

	   for(row = 0; row < header.height; row++) {
		   for(col = 0; col < header.width; col++) {

			   // check for green pixels in image 1
			   if(image1->theImage->pixels[row][col].r == 0 && image1->theImage->pixels[row][col].g == 255 && image1->theImage->pixels[row][col].b == 0) {

	out_image->pixels[row][col].r = image2->theImage->pixels[row][col].r;
	out_image->pixels[row][col].g = image2->theImage->pixels[row][col].g;
	out_image->pixels[row][col].b = image2->theImage->pixels[row][col].b;
			  }
		   }
	   }

	   write_p6(greenScreenImage, out_image);
	   fclose(greenScreenImage);

	   // add new image to list of images
	   filePtr_t* temp = *theList;
	   addToList(temp, greenScreenImage, out_image, imageName);
	
	}
}


void addToList(filePtr_t* frontOfList, FILE* newImage, image_t* theNewImage, char* nameOfImage) {
	// allocating memory for a new node in the linked list
	filePtr_t* newNode = (filePtr_t*)malloc(sizeof(filePtr_t));

	// copying new image data to new node
	newNode->theFile = newImage;
        newNode->imageFileName = nameOfImage;
	newNode->theImage = theNewImage;
	newNode->next = NULL;

	filePtr_t* current = frontOfList;
	if(current == NULL) {
		frontOfList  = newNode;
	}
	else {
		while(current->next != NULL) {
			current = current->next;
		}
		current->next = newNode;
	}
}
