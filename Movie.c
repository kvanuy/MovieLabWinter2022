/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Winter 2022                   */
/*                                                                   */
/* Initial author: Tim Schmidt                                       */
/*                                                                   */
/* Movie.c: source file for basic movie manipulations                */
/*                                                                   */
/*********************************************************************/

#include <stdlib.h>
#include <assert.h>
#include "Movie.h"

/* Allocate the memory space for the movie and the memory space */
/* for the frame list. Return the pointer to the movie. */
MOVIE *CreateMovie(void)
{
	/* to be implemented */

	MOVIE *movie = (MOVIE *)malloc(sizeof(MOVIE));
	movie->Frames = malloc(sizeof(ILIST));
	

return movie;

}

/* Release the memory space for the frame list. */
/* Release the memory space for the movie. */
void DeleteMovie(MOVIE *movie)
{
	/* to be implemented */
	assert(movie);

/*        IENTRY *ientry, *nentry;
        IMAGE *image;
        YUVIMAGE *yuv;
        ILIST *list = movie->Frames;

        ientry = list->First;
        while(ientry)
        {nentry = ientry->Next;
                image = ientry->RGBImage;
                yuv = ientry->YUVImage;
        if (image){
                DeleteImage(image);}
        if (yuv){
                DeleteYUVImage(yuv);}
        free(ientry);
        ientry = nentry;
}
        free(list);
*/



//	assert(movie->Frames);
//	free(movie->Frames);
	free(movie);
	/* to be implemented */

}

/* Convert a YUV movie to a RGB movie */
void YUV2RGBMovie(MOVIE *movie)
{
	/* to be implemented */
	assert(movie);
int clip, C, D, E;

        /* to be implemented */
	IENTRY *ientry, *nentry;
	ientry = movie->Frames->First;
	
while (ientry)	{
	nentry = ientry->Next;

	IMAGE *i = CreateImage(ientry->YUVImage->W,ientry->YUVImage->H);
	ientry->RGBImage = i;
	ientry->RGBImage->W =ientry->YUVImage->W;
	ientry->RGBImage->H = ientry->YUVImage->H; 
 for (int x = 0; x < ientry->YUVImage->W; x++) {
                        for (int y = 0; y < ientry->YUVImage->H; y++) {

C = GetPixelY(ientry->YUVImage,x,y) - 16;
D = GetPixelU(ientry->YUVImage,x,y) - 128;
E = GetPixelV(ientry->YUVImage,x,y) - 128;

clip = (( 298 * C + 409 * E + 128) >> 8);
if (clip>255){
	clip=255;}
if (clip<0){
	clip=0;}

SetPixelR(ientry->RGBImage, x, y,clip);

clip = (( 298 * C - 100 * D - 208 * E + 128) >> 8);
if (clip>255){
	clip=255;}
if (clip<0){
	clip=0;}

SetPixelG(ientry->RGBImage, x, y,clip);

clip = (( 298 * C + 516 * D + 128) >> 8) ;
if (clip>255){
	clip=255;}
if (clip<0){
	clip=0;}

SetPixelB(ientry->RGBImage, x, y,clip);
}}
DeleteYUVImage(ientry->YUVImage);
ientry->YUVImage = NULL;

	ientry=nentry;

}}

/* Convert a RGB movie to a YUV movie */
void RGB2YUVMovie(MOVIE *movie)
{
	assert(movie);
int clip;

        /* to be implemented */
	int x,y;
	IENTRY *ientry, *nentry;
	ientry = movie->Frames->First;
	
while (ientry)	{
	nentry = ientry->Next;
	YUVIMAGE *i = CreateYUVImage(ientry->RGBImage->W,ientry->RGBImage->H);
       ientry->YUVImage = i;
        ientry->YUVImage->W =ientry->RGBImage->W;
        ientry->YUVImage->H = ientry->RGBImage->H;


for (x = 0; x < ientry->RGBImage->W; x++) {
                        for (y = 0; y < ientry->RGBImage->H; y++) {

clip = (((66 * GetPixelR(ientry->RGBImage,x,y) + 129*GetPixelG(ientry->RGBImage,x,y) + 25*GetPixelB(ientry->RGBImage,x,y) + 128)>>8)+16);
if (clip>255){
	clip=255;}
if (clip<0){
	clip=0;}
SetPixelY(ientry->YUVImage, x, y,clip);

clip = (((-38 * GetPixelR(ientry->RGBImage,x,y) - 74*GetPixelG(ientry->RGBImage,x,y) + 112*GetPixelB(ientry->RGBImage,x,y) + 128)>>8)+128);
if (clip>255){
	clip=255;}
if (clip<0){
	clip=0;}
SetPixelU(ientry->YUVImage, x, y,clip);

clip = (((112* GetPixelR(ientry->RGBImage,x,y) - 94*GetPixelG(ientry->RGBImage,x,y) -18*GetPixelB(ientry->RGBImage,x,y) + 128)>>8)+128);
if (clip>255){
	clip=255;}
if (clip<0){
	clip=0;}
SetPixelV(ientry->YUVImage, x, y,clip);
}}

DeleteImage(ientry->RGBImage);
ientry->RGBImage = NULL;

ientry = nentry;

}
}

/* EOF */
