#include<stdio.h>
#include<strings.h>
//User defined structure for MP3 tag header
typedef struct
{
    char Title[100];
    char Artists[100];
    char Movie[30];
    char Year[10];
    char Language[10];
    char Comments[50];
}MP3tag;
//Function declarations
void view(FILE *mp3_fp,MP3tag *mp3);
void swap(unsigned int *size);
void edittag(const char *filename, const char *frame_id,const char* new_value);

