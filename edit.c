#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"file.h"
//Edit 
void edittag(const char *filename, const char *frameid,const char *new_value)
{
    //Open file in read binary mode
    FILE *fp=fopen(filename,"rb");
    //Check if file exists
    if(fp==NULL)
    {
        printf("File not found\n");
        return ;
    }
    //Create temp file 
    FILE *temp=fopen("temp.mp3","wb");
    //Check if temp file is created
    if(temp==NULL)
    {
        printf("Unable to create temp file\n");
        return ;
    }
    //String to store header
    char header[10];
    //Copy the intial header and write to temp file
    fread(header,1,10,fp);
    fwrite(header,1,10,temp);
    //Declare variables
    char tag[5];
    unsigned int size=0;
    char data[100];
    char flags[3];
    //Declare found variable
    int found=0;

    for(int i=0;i<6;i++)
    {
        //Read the data and store in the variables
        fread(tag, 4, 1,fp);
        tag[4]='\0';
        fread(&size, 4, 1,fp);
        //Store the size seperately
        unsigned int original =size;
        //Skip flag bytes
        fread(flags, 3, 1, fp);
        swap(&size);
        //Read data
        fread(data,(size-1),1,fp);
        //If frame tag matches replace with new data and size
        if(strcmp("COMM",frameid)==0)
        {
            unsigned int new_size =1+3+1+strlen(new_value); // enc + lang + '\0' + text
            unsigned int b_size = new_size;
            swap(&b_size);

            fwrite(tag,4,1,temp);
            fwrite(&b_size,4,1,temp);
            fwrite(flags,3,1,temp);          // flags[2] is the encoding byte
            fwrite("eng",3,1,temp);
            fputc('\0',temp);                //null
            fwrite(new_value,strlen(new_value),1,temp);
        }
        else if(strcmp(tag,frameid)==0)
        {
            //Store new data size
            unsigned int new_size=strlen(new_value)+1;
            unsigned int b_size=new_size;
            //Convert it to little endian form
            swap(&b_size);
            //Write the new data to the temp file
            fwrite(tag,4,1,temp);
            fwrite(&b_size,4,1,temp);
            fwrite(flags,3,1,temp);
            fwrite(new_value,strlen(new_value),1,temp);
            //Set flag
            found =1;

        }
        //Write remaining frames of the tag
        else
        {
            fwrite(tag,4,1,temp);
            fwrite(&original,4,1,temp);
            fwrite(flags,3,1,temp);
            fwrite(data,size-1,1,temp);
        }
    }
    //Copy rest of the file
    char buffer[4096];
    size_t bytes;
    while((bytes=fread(buffer,1,sizeof(buffer),fp))>0)
        fwrite(buffer,1,bytes,temp);
    //Close
    fclose(fp);
    fclose(temp);

    //If tag not found
    if(!found)
    {
        printf("Tag not found %s\n",frameid);
        remove("temp.mp3");
        return;
    }
    //remove old file
    remove(filename);
    //Rename updated file
    rename("temp.mp3",filename);
    printf("Tag updated sucessfully\n");
}