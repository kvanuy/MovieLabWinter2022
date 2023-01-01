#######################################################################
# Homework Assignment 5, for EECS 22, Winter 2022
#
# Initial author: Tim Schmidt
#
# Makefile: Makefile for HW 5
#
#######################################################################
all: MovieLab
# Variables
CC = gcc	
CFLAGS = -Wall -std=c11 $(DEBUG)
LFLAGS = -Wall -std=c11 $(DEBUG)
# Default target

######################### Generate object files #######################
# Target for MovieLab.o
MovieLab.o: FileIO.h DIPs.h Movie.h Constants.h Image.h MovieLab.c
	$(CC) $(CFLAGS) -c -g MovieLab.c  -o MovieLab.o -lm
# Target for FileIO.o
FileIO.o: FileIO.c FileIO.h Constants.h
	$(CC) $(CFLAGS) -c -g FileIO.c -o FileIO.o
# Target for DIPs.o
DIPs.o: DIPs.h DIPs.c Constants.h Image.h
	$(CC) $(CFLAGS) -c -g DIPs.c -o DIPs.o
# Target for Image.o
Image.o: Image.c Image.h Constants.h
	$(CC) $(CFLAGS) -c -g Image.c -o Image.o


# Target for ImageList.o
ImageList.o: ImageList.h ImageList.c Image.h
	$(CC) $(CFLAGS) -c -g ImageList.c -o ImageList.o
# Target for Movie.o
Movie.o: Movie.c Movie.h
	$(CC) $(CFLAGS)-c -g Movie.c -o Movie.o
######################### Generate the executable #####################
# Target for MovieLab
MovieLab: ImageList.o FileIO.o DIPs.o Image.o Movie.o MovieLab.o
	$(CC) $(CFLAGS)-g ImageList.o FileIO.o DIPs.o Image.o Movie.o MovieLab.o -o MovieLab -lm

###############################  others  ##############################
# Target for clean-up
clean:
	rm -f *.o
	rm -f MovieLab
