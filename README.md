# filters
A program that can apply grayscale, sepia, mirror and blur filters on a .bmp image. Also uses Sobel operators to detect edges in .bmp images and highlight them.
To run, collect all the files (except recover.c) into one folder along with the images you want to edit and compile using "make filter". Input the command line argument "./filter -f image.bmp out.bmp" where -f is the filter you want to apply, image.bmp is the .bmp file you want to apply the filter to and out.bmp is the name of your output file. Use -g for grayscale, -s for sepia, -r for mirror, -b for blur and -e for edge detection.   

#recover.c 
can recover 'lost' JPEGs from a corrupted file and output them. Run the command-line argument "./recover.c input" after running "Make recover", where input is the file you want to extract JPEGs from. recover.c will output any extracted JPEGs. 
