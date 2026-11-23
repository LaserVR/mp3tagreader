#include<stdio.h>
#include"file.h"
#include<string.h>
//Convert size from big endian to little endian 
void swap(unsigned int *size)
{
    char *ptr = (char *)size;
    char temp = *(ptr);
    *(ptr) = *(ptr + 3);
    *(ptr + 3) = temp;

    temp = *(ptr + 1);
    *(ptr + 1) = *(ptr + 2);
    *(ptr + 2) = temp;
}
void view(FILE *mp3_fp,MP3tag *mp3)
{
    //Skip first 10 bytes
    fseek(mp3_fp, 10, SEEK_CUR);
    
    //Tag variables
    char Tag[5];
    char Tags[6][4] = {"TIT2", "TALB", "TYER", "TCOM", "TPE1", "TCON"};
    //Size and data varaibles
    unsigned int size = 0;
    char data_cont[100];
    //Read and store all 6 frames in the structure
    for (int i=0;i<6;i++)
    {
        //Read the initial 4 bytes of tag 
        fread(Tag, 4, 1, mp3_fp);
        //Add null to store as string
        Tag[4] = '\0';
        //Read the size of frame data
        fread(&size, 4, 1, mp3_fp);
        //Skip 3 bytes flag
        fseek(mp3_fp, 3, SEEK_CUR);
        //Convert size to little endian
        swap(&size);
        //Read the frame data
        fread(data_cont,(size-1),1,mp3_fp);
        //Add Null to make it a string
        data_cont[size-1]='\0';
        //printf(" %s\n", data_cont);
        //Copy the data to the structure based on the tag
        if(strcmp(Tag,"TIT2")==0)
            strcpy(mp3->Title,data_cont);
        else if(strcmp(Tag,"TPE1")==0)
            strcpy(mp3->Artists,data_cont);
        else if(strcmp(Tag,"TALB")==0)
            strcpy(mp3->Movie,data_cont);
        else if(strcmp(Tag,"TYER")==0)
            strcpy(mp3->Year,data_cont);
        else if(strcmp(Tag,"TCON")==0)
            strcpy(mp3->Language,data_cont);
        else if(strcmp(Tag,"COMM")==0)
        {
            int len=size-1;      
            char *p=data_cont+3;     // skip the 3-byte language code
            int remaining =len-3;

            // skip the '\0'
            while(remaining>0 && *p!='\0')
            {
                p++;
                remaining--;
            }
            if(remaining>0)            // skip the '\0'
            {
                p++;
                remaining--;
            }

            memcpy(mp3->Comments,p,remaining);
            mp3->Comments[remaining]='\0';
        }
        //else if(strcmp(Tag,"COMM")==0)
          //  strcpy(mp3->Comments,data_cont);
        //printf("Tag %d -> %s : ", i, Tag);
       
    }
}