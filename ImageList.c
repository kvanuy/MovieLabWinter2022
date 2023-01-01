/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Winter 2022                   */
/*                                                                   */
/* Initial author: Tim Schmidt                                       */
/*                                                                   */
/* ImageList.c: source file for image list manipulations             */
/*                                                                   */
/*********************************************************************/

#include <stdlib.h>
#include <assert.h>
#include "ImageList.h"
#include "Image.h"
#include <stdio.h>
/* Create a new image list */
ILIST *CreateImageList(void)
{
	/* to be implemented */

	ILIST *iList;
	iList= malloc(sizeof(ILIST));
//	if (! iList){
//		perror("out of memory! Aborting...");
//		exit(10);
//		}
	iList->Length = 0;
	iList->First = NULL;
	iList->Last = NULL;
return iList;
}

/* Delete an image list (and all entries) */
void DeleteImageList(ILIST *list)
{
	/* to be implemented */

        IENTRY *ientry, *nentry;
	IMAGE *image;
	YUVIMAGE *yuv;
	assert(list);

	int counter = 1;
	ientry = list->First;
	while(ientry)
	{printf("counting %d ",counter);
	 counter = counter + 1;
		nentry = ientry->Next;
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


}

/* Insert a RGB image to the image list at the end */
void AppendRGBImage(ILIST *list, IMAGE *RGBimage)
{
	/* to be implemented */

	IENTRY *e = NULL;
	assert(list);
	assert(RGBimage);
	assert(RGBimage->R);
	assert(RGBimage->G);
	assert(RGBimage->B);
	e = malloc(sizeof(IENTRY));
//	if (! e)
//		{perror("Out of memory! Aborting...");
//		 exit(10);}
//	 e->RBGImage = malloc(sizeof(RBGIMAGE)*sizeof(char))
	 	e->RGBImage = RGBimage;
	 	e->YUVImage = NULL;		
		if (list->Last)
	 		{e->List = list;
	 		 e->Next = NULL;
	 	 	 e->Prev = list->Last;
	 	 	 list->Last->Next = e;
	 	 	 list->Last = e;
	 }
	else    // if the image is 
	{e->List= list;
	 e->Next= NULL;	 			
	 e->Prev= NULL;
	 list->First = e;
	 list->Last = e;

}
}
/* Insert a YUV image to the image list at the end */
void AppendYUVImage(ILIST *list, YUVIMAGE *YUVimage)
{
	/* to be implemented */

IENTRY *e = NULL;
	assert(list);
	assert(YUVimage);
	assert(YUVimage->Y);
	assert(YUVimage->U);
	assert(YUVimage->V);
//IMAGE *i = CreateImage(YUVimage->W,YUVimage->H);

	e = malloc(sizeof(IENTRY));
//	if (! e)
//		{perror("Out of memory! Aborting...");
//		 exit(10);}
//	e->YUVImage = malloc(sizeof(YUVIMAGE)*sizeof(char))
	e->YUVImage =YUVimage;
	e->RGBImage = NULL;	
	if (list->Last)
	{e->List = list;
	 e->Next = NULL;
	 e->Prev = list->Last;
	 list->Last->Next = e;
	 list->Last = e;
	 }
	else    // if the image is 
	{e->List= list;
	 e->Next= NULL;
	 e->Prev= NULL;
	 list->First = e;
	 list->Last = e;
	} 

}

/* Crop an image list */
void CropImageList(ILIST *list, unsigned int start, unsigned int end)
{IENTRY *ientry, *nentry;

        assert(list);
        int count = 1;
        int f = 0;
        ientry = list->First;
        assert(ientry->RGBImage->G);
        while (ientry)
        {nentry = ientry->Next;
                if ((count<start)|(count>end)){
        DeleteImage(ientry->RGBImage);
        free(ientry);}
        else{
                if (count==start){
                list->First = ientry;
		ientry->Prev = NULL;}
                if (count ==end){
                list->Last = ientry;
		ientry->Next = NULL;}
        f++;}
        count+=1;
        ientry = nentry;}
        list->Length = f;
}

/* Fast forward an image list */
void FastImageList(ILIST *list, unsigned int factor)
{
	/* to be implemented */
	IENTRY *ientry, *nentry, *placeholder;
//	IMAGE *image;
	assert(list);
	int count;
	ientry = list->First;
	count = 0;
	placeholder = NULL;
//	index = 0;
	while (ientry)
	{nentry = ientry->Next;
		if (count % factor == 0){
		ientry ->Next = NULL;
			if (placeholder){
				placeholder ->Next = ientry;
				ientry->Prev = placeholder;
				}
		 // going to reassign it when there's a placeholder
		placeholder = ientry;
	
		}
		else{ DeleteImage(ientry->RGBImage);
		free(ientry);}
//	free(ientry);}
	ientry=nentry;
	count+=1;}
//	printf("%d frames have been saved or something");
}

/* Reverse an image list */
void ReverseImageList(ILIST *list)
{
	/* to be implemented */
ILIST *newlist;
	IENTRY *ientry, *nentry;
	assert(list);
	newlist = CreateImageList();
	ientry = list->Last;
	while (ientry)
	{nentry = ientry->Prev;
	 AppendRGBImage(newlist, ientry->RGBImage);
	 free(ientry);
	 ientry = nentry;}
	list->First = newlist->First;
	list->Last = newlist->Last;	
	free(newlist);
}

/* EOF */
