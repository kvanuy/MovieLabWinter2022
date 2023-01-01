/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Winter 2022                   */
/*                                                                   */
/* Initial author: Tim Schmidt                                       */
/*                                                                   */
/* MovieLab.c: source file for the main function                     */
/*                                                                   */
/* Please use this template for your HW5.                            */
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <math.h>

#include "FileIO.h"
#include "DIPs.h"
#include "Movie.h"
#include "Constants.h"
#include "Image.h"

/* Load one movie frame from the input file */
YUVIMAGE* LoadOneFrame(const char* fname, int n,
                       unsigned int width, unsigned height);

/* Load the movie frames from the input file */
MOVIE *LoadMovie(const char *fname, int frameNum,
                 unsigned int width, unsigned height);

/* Saves one movie frame to the output file */
void SaveOneFrame(YUVIMAGE *image, const char *fname, FILE *file);

/* Save the movie frames to the output file */
int SaveMovie(const char *fname, MOVIE *movie);

/* Print the command-line arguments usage of the program */
void PrintUsage();

int main(int argc, char *argv[])
{
	int x = 0;
	char *fin = NULL;
	char *fout = NULL;

	unsigned int width = 0; // = 512;
	unsigned int height = 0; // = 288;
	int frames = 0;

	/* the while loop to check options in the command line */
	while (x < argc) {
		/* the input file name */
		if (strcmp(argv[x], "-i") == 0) {
			if (x < argc - 1) {
				fin = argv[x + 1];
			} /*fi*/
			else {
				printf("Missing argument for the input file name!\n");
				return 5;
			} /*esle*/
			x += 2;
			continue;
		} /*fi*/

		/* the output file name */
		if (strcmp(argv[x], "-o") == 0) {
			if (x < argc - 1) {
				fout = argv[x + 1];
			} /*fi*/
			else {
				printf("Missing argument for the output file name!\n");
				return 5;
			} /*esle*/
			x += 2;
			continue;
		} /*fi*/

		/* the help option */
		if (strcmp(argv[x], "-h") == 0) {
			PrintUsage();
			return 0;
		} /*fi*/

		/* to be implemented */
		if (strcmp(argv[x], "-i") ==0){
			if (x<argc - 1){
			fin = argv[x+1];
		} else{
			printf("Missing argument for the input file name!\n");
			return 5;
		}
		x += 2;
		continue;
		}

		if (strcmp(argv[x],"-f")==0){
			if (x<argc -1){
				sscanf( argv[x+1], "%d", &frames);}
			else{ printf("Missing argument for frames\n");
			return 5;
		}
		x+=2;
	continue;}

		if (strcmp(argv[x], "-s")==0){
			if (sscanf(argv[x+1], "%ux%u", &width, &height) == 2) {
width = width;
height = height;			


		}else{	
			printf("Missing dimensions argument\n");
		return 5;
		}
		x+=2;
		continue;
		}
//to be edited
		x++;
	} /*elihw*/
	if (fin == NULL) {
		printf("Missing argument for the input file name!\n");
		PrintUsage();
		return 5;
	}

	if (fout == NULL) {
		printf("Missing argument for the output file name!\n");
		PrintUsage();
		return 5;
	}
	if ((width == 0)&(height ==0) ){
		printf("Missing argument for dimensions!\n");
		PrintUsage();
		return 5;}
	if ((frames ==0)){
		printf("Missinig agrument for frames!\n");
		return 5;}
//need an exiting error if not all requirements are met

	/* to be implemented */

MOVIE* movie=NULL;
movie = LoadMovie(fin, frames,width, height);
//*convert to rgb;
YUV2RGBMovie(movie);	
	x=0;
	while (x<argc){
 		if (strcmp(argv[x],"-aging")==0){
			IENTRY *i;
			IENTRY *e = movie->Frames->First;
			while (e){
				i= e->Next;
				e->RGBImage= Aging(e->RGBImage);
				e = i;}
			printf("Operation Aging is done!\n");}
//			printf("hi");}
		if (strcmp(argv[x],"-hflip")==0){
	                IENTRY *i;
                        IENTRY *e = movie->Frames->First;
                        while (e){
                                i= e->Next;
                                e->RGBImage= HFlip(e->RGBImage);
                                e = i;}
			printf("Operation HFlip is done!\n");}
//			printf("horixontal flip");}
		if (strcmp(argv[x],"-edge")==0){
                        IENTRY *i;
                        IENTRY *e = movie->Frames->First;
                        while (e){
                                i= e->Next;
                                e->RGBImage= Edge(e->RGBImage);
                                e = i;}
				printf("Operation Edge is done!\n");}

		if (strcmp(argv[x],"-crop")==0){
			int start,end;
			if (sscanf(argv[x+1], "%d-%d", &start, &end)==2){

				ILIST *ilist = movie->Frames;
				CropImageList(ilist,start, end); 
				assert(ilist->Last->RGBImage->R);
				assert(ilist->Last->RGBImage->B);
				assert(ilist->Last->RGBImage->G);
printf("Operation Crop is done!\n New number of frames is %d\n",ilist->Length);
				x+=2;
				continue;}
				else{
			printf("missing start and end for crop\n");
			PrintUsage();
			return 5;
				}}

		if (strcmp(argv[x],"-fast")==0){
			int factor;
			if (sscanf(argv[x+1],"%d",&factor)==1){
				ILIST *ilist = movie->Frames;
				FastImageList(ilist, factor);
			x+=2;
                                printf("Operation Fast Forward is done! New number of frames is %d\n",ilist->Length);

			continue;
			}else{printf("Missing factor\n");}}

		if (strcmp(argv[x],"-reverse")==0){
			ILIST *ilist = movie->Frames;
			ReverseImageList(ilist);
			printf("Operation Reverse is done!\n");
			}
			
		if (strcmp(argv[x],"-watermark")==0){
			ILIST *ilist = movie->Frames;
			if (x<argc-1){
				char *wfile;
				wfile = argv[x+1];

			srand(time(NULL));
			int topleftx;
			int toplefty;
			int tx, ty;
			IMAGE *wimage = LoadImage(wfile);
			IENTRY *i;
			int wei = (ilist->First->RGBImage->W)/1.45;
			int hei = (ilist->First->RGBImage->H)/1.45;
      IENTRY *e = movie->Frames->First;
			int count =0;
                        while (e){
			if ((count % WATERMARK_PER_FRAMES) ==0){
                        topleftx = rand() % wei;
                         toplefty = rand() % hei;
}
 			 tx = topleftx;
                         ty = toplefty;
				
                                i= e->Next;
                                e->RGBImage= Watermark(e->RGBImage,wimage,tx,ty);
                                
                                e = i;
count++;
}
DeleteImage(wimage);
printf("Operation Watermark is done!\n");}
			else{
			printf("Missing watermark file\n");
			PrintUsage();
			return 5;
			}
			x+=2;
			continue;}




		if (strcmp(argv[x],"-spotlight")==0){
		
			IENTRY *ientry, *nentry;
			ientry = movie->Frames->First;
			IMAGE *newimage;
	
			
	 	int cenx = ( movie->Frames->First->RGBImage->W)/2;
			int ceny = ( movie->Frames->First->RGBImage->H)/2;
			int squ = ((ceny)*(ceny)) + ((cenx)*(cenx));
			unsigned int radius = sqrt((squ));
			double piece = radius/19;
			int f = 0;
			ILIST *new = CreateImageList();


			for (int a=0; a<20;a=a+1){
	
				int rad = piece * a;
  
				IMAGE *dupimg = CreateImage(ientry->RGBImage->W, ientry->RGBImage->H);
          for (int hpixel = 0; hpixel< dupimg->H; hpixel= hpixel+1){
            for (int wpixel = 0; wpixel< dupimg->W; wpixel=wpixel+1){
                SetPixelR(dupimg,wpixel, hpixel, GetPixelR(ientry->RGBImage,wpixel,hpixel));
                SetPixelG(dupimg,wpixel, hpixel, GetPixelG(ientry->RGBImage,wpixel,hpixel));
                SetPixelB(dupimg,wpixel, hpixel, GetPixelB(ientry->RGBImage,wpixel,hpixel));
            }
        }
newimage = Spotlight(dupimg,cenx, ceny,rad); 
        AppendRGBImage(new,newimage);
  
        f=f+1;}
        

			while(ientry){
				nentry = ientry->Next;
     
				AppendRGBImage(new,ientry->RGBImage);
				free(ientry);
				ientry = nentry;
				f=f+1;}
        

			ientry = new->Last;

			for (int a = 0; a<20; a=a+1){

				int rad = piece *(19-a);
  
        IMAGE *dupimg = CreateImage(ientry->RGBImage->W, ientry->RGBImage->H);
        
        for (int hpixel = 0; hpixel< dupimg->H; hpixel= hpixel+1){
            for (int wpixel = 0; wpixel< dupimg->W; wpixel=wpixel+1){
                SetPixelR(dupimg,wpixel, hpixel, GetPixelR(ientry->RGBImage,wpixel,hpixel));
                SetPixelG(dupimg,wpixel, hpixel, GetPixelG(ientry->RGBImage,wpixel,hpixel));
                SetPixelB(dupimg,wpixel, hpixel, GetPixelB(ientry->RGBImage,wpixel,hpixel));
            }
        }
        
        
				newimage = Spotlight(dupimg,cenx, ceny,rad); 
        AppendRGBImage(new,newimage);
   
        f=f+1;}
        

			movie->Frames->First = new->First;
			movie->Frames->Last = new->Last;
			free(new);
			movie->Frames->Length = f;
			printf("Operation Spotlight is done!\n");
}

		
		if (strcmp(argv[x],"-zoom")==0){
	
			IENTRY *ientry, *nentry;
			ientry = movie->Frames->First;
			IMAGE *newimage;

			

			int f = 0;
			ILIST *new = CreateImageList();


			for (int a=0; a<20;a=a+1){

				int addpercent = ZOOM_SPEED * a + 20;

				IMAGE *dupimg = CreateImage(ientry->RGBImage->W, ientry->RGBImage->H);
          for (int hpixel = 0; hpixel< dupimg->H; hpixel= hpixel+1){
            for (int wpixel = 0; wpixel< dupimg->W; wpixel=wpixel+1){
                SetPixelR(dupimg,wpixel, hpixel, GetPixelR(ientry->RGBImage,wpixel,hpixel));
                SetPixelG(dupimg,wpixel, hpixel, GetPixelG(ientry->RGBImage,wpixel,hpixel));
                SetPixelB(dupimg,wpixel, hpixel, GetPixelB(ientry->RGBImage,wpixel,hpixel));
            }
        }
newimage = Zoom(dupimg,addpercent); 
        AppendRGBImage(new,newimage);
   
        f=f+1;}
        

			while(ientry){
				nentry = ientry->Next;
 
				AppendRGBImage(new,ientry->RGBImage);
				free(ientry);
				ientry = nentry;
				f=f+1;}
        

			ientry = new->Last;
			for (int a = 0; a<20; a=a+1){
		int addpercent = 100 - ZOOM_SPEED * a ;
        IMAGE *dupimg = CreateImage(ientry->RGBImage->W, ientry->RGBImage->H);
        
        for (int hpixel = 0; hpixel< dupimg->H; hpixel= hpixel+1){
            for (int wpixel = 0; wpixel< dupimg->W; wpixel=wpixel+1){
                SetPixelR(dupimg,wpixel, hpixel, GetPixelR(ientry->RGBImage,wpixel,hpixel));
                SetPixelG(dupimg,wpixel, hpixel, GetPixelG(ientry->RGBImage,wpixel,hpixel));
                SetPixelB(dupimg,wpixel, hpixel, GetPixelB(ientry->RGBImage,wpixel,hpixel));
            }
        }
        
        
				newimage = Zoom(dupimg,addpercent); 
        AppendRGBImage(new,newimage);
   
        f=f+1;}
        

			movie->Frames->First = new->First;
			movie->Frames->Last = new->Last;
			free(new);
			movie->Frames->Length = f;
 		  printf("Operation Zoom is done!\n");
		}
x++;}

RGB2YUVMovie(movie);



x = SaveMovie(fout, movie);

DeleteImageList(movie->Frames);

DeleteMovie(movie);


	fin = NULL;
	fout = NULL;

	return 0;
}

void PrintUsage()
{
	printf("\nUsage: MovieLab -i <file> -o <file> -f <framenum> -s <WIDTHxHEIGHT> [options]\n"
	       "Options:\n"
	       "-aging                Activate the aging filter on every movie frame\n"
	       "-hflip                Activate horizontal flip on every movie frame\n"
	       "-edge                 Activate the edge filter on every movie frame\n"
	       "-crop <start-end>     Crop the movie frames from <start> to <end>\n"
	       "-fast <factor>        Fast forward the movie by <factor>\n"
	       "-reverse              Reverse the frame order of the input movie\n"
	       "-watermark <file>     Add a watermark from <file> to every movie frame\n"
	       "-spotlight            Spotlight the fade in and fade out\n"
	       "-zoom                 Zoom in and out the input movie\n"
	       "-h                    Display this usage information\n"
	      );
}

/* Load one movie frame from the input file */
YUVIMAGE* LoadOneFrame(const char* fname, int n,
                       unsigned int width, unsigned height)
{
	FILE *file;
	unsigned int x, y;
	unsigned char c;
	YUVIMAGE* YUVimage;

	/* Check errors */
	assert(fname);
	assert(n >= 0);

	YUVimage = CreateYUVImage(width, height);
	if (YUVimage == NULL) {
		return NULL;
	}

	/* Open the input file */
	file = fopen(fname, "r");
	if (file == NULL) {
		DeleteYUVImage(YUVimage);
		return NULL;
	}

	/* Find the desired frame */
	fseek(file, 1.5 * n * width * height, SEEK_SET);

	for (y = 0; y < height; y++) {
		for (x = 0; x < width; x++) {
			c = fgetc(file);
			SetPixelY(YUVimage, x, y, c);
		} /*rof*/
	}

	for (y = 0; y < height; y += 2) {
		for (x = 0; x < width; x += 2) {
			c = fgetc(file);
			SetPixelU(YUVimage, x, y, c);
			SetPixelU(YUVimage, x + 1, y, c);
			SetPixelU(YUVimage, x, y + 1, c);
			SetPixelU(YUVimage, x + 1, y + 1, c);
		}
	}

	for (y = 0; y < height; y += 2) {
		for (x = 0; x < width; x += 2) {
			c = fgetc(file);
			SetPixelV(YUVimage, x, y, c);
			SetPixelV(YUVimage, x + 1, y, c);
			SetPixelV(YUVimage, x, y + 1, c);
			SetPixelV(YUVimage, x + 1, y + 1, c);
		}
	}

	/* Check errors */
	assert(ferror(file) == 0);

	/* Close the input file and return */
	fclose(file);
	file = NULL;
	return YUVimage;
}

/* Load the movie frames from the input file */
MOVIE *LoadMovie(const char *fname, int frameNum,
                 unsigned int width, unsigned height)
{
	/* to be implemented */
//        FILE *file;
     //   IENTRY *curr;
	YUVIMAGE *yuv;
	MOVIE *movie;

     //   file = fopen(fname, "r"); // open fname
	movie = CreateMovie();
//	curr = movie->Frames->First;
for (int num=0; num < frameNum; num++){

	yuv = LoadOneFrame(fname, num, width,height);
	AppendYUVImage(movie->Frames, yuv);
	movie->Frames->Length = frameNum;	

}
        printf("The movie file %s has been loaded  successfully!\n",fname);
return movie;

}

/* Save the movie frames to the output file */
int SaveMovie(const char *fname, MOVIE *movie)
{
	/* to be implemented */
	int count;
	FILE *file;
	IENTRY *curr;
	file = fopen(fname, "w"); // open fname

	count = 0;
	curr = movie->Frames->First;
	while (curr != NULL){
		SaveOneFrame(curr->YUVImage, fname, file);
		curr = curr->Next;
		count++;
}
	printf("The movie file %s has been written successfully!\n",fname);
	printf("%d frames are written to the file %s in total.\n",count,fname );
	fclose(file);	

return(0);
}

/* Saves one movie frame to the output file */
void SaveOneFrame(YUVIMAGE *image, const char *fname, FILE *file)
{
	int x, y;
	for (y = 0; y < image->H; y++) {
		for (x = 0; x < image->W; x++) {
			fputc(GetPixelY(image, x, y), file);
		}
	}

	for (y = 0; y < image->H; y += 2) {
		for (x = 0; x < image->W; x += 2) {
			fputc(GetPixelU(image, x, y), file);
		}
	}

	for (y = 0; y < image->H; y += 2) {
		for (x = 0; x < image->W; x += 2) {
			fputc(GetPixelV(image, x, y), file);
		}
	}
}

/* EOF */
