/*
    Name:Vinay Rohan S
    Date:25/09/2026
    Roll No:26015_275
    Class:26018c
    Project MP3 Tag Reader
    To view and edit MP3 Tag
    Input via command line arguments    
*/
#include <stdio.h>
#include <string.h>
#include"file.h"
//MP3 tag reader
int main(int argc, char *argv[])
{
    //Access file name
    char *filename2;
    //If no choice given
    if(argc==1)
    {
        printf("Enter choice!\n");
        return 1;
    }
    else if(strcmp(argv[1],"-v")==0)
    //For view mode
        filename2=argv[2];
    //Help function
    else if(strcmp(argv[1],"-h")==0)
    {
        printf("MP3 Commands\n");
        printf("To view MP3 Tag               : ./a.out -v filename.mp3\n");
        printf("To edit title of MP3 Tag      : ./a.out -e -t new_title filename.mp3\n");
        printf("To edit artists of MP3 Tag    : ./a.out -e -a new_artists filename.mp3\n");
        printf("To edit movie name of MP3 Tag : ./a.out -e -m new_moviename filename.mp3\n");
        printf("To edit year of MP3 Tag       : ./a.out -e -y new_year filename.mp3\n");
        printf("To edit language of MP3 Tag   : ./a.out -e -l new_language filename.mp3\n");
        printf("To edit comments of MP3 Tag   : ./a.out -e -c new_comments filename.mp3\n");
        return 0;

    }
    else if(strcmp(argv[1],"-e")==0)
    //For edit mode
        filename2=argv[4];
    else
    {
        printf("Enter valid choice!\n");
        printf("For commands: ./a.out -h\n");
        return 1;
    }
    //Open file in binary read mode
    FILE *mp3_file_pointer = fopen(filename2, "rb");
    //Check for file
    if(mp3_file_pointer==NULL)
    {
        printf("File not found\n");
        return 1;
    }
    //Create MP3 structure to store tag details
    MP3tag tag;
    //view the file
    view(mp3_file_pointer,&tag);
    //Close the file
    fclose(mp3_file_pointer);
    //Check if argument is for viewing file
    if(strcmp(argv[1],"-v")==0)
    {
        //Display
        printf("--------MP3 Song-------\n");
        printf("Title: %-9s\n",tag.Title);
        printf("Artists: %-9s\n",tag.Artists);
        printf("Movie: %-9s\n",tag.Movie);
        printf("Year: %-9s\n",tag.Year);
        printf("Language: %-9s\n",tag.Language);
        printf("Comments: %-9s\n",tag.Comments);    
    }
    //Check for edit option argument
    else if(strcmp(argv[1],"-e")==0)
    {
        //edit
        //Store the option and file name
        char *option=argv[2];
        char *filename=argv[4];
        char *frameid;
        //Store the frame to be searched
        if(strcmp(option,"-t")==0)frameid="TIT2";
        else if(strcmp(option,"-a")==0)frameid="TPE1";
        else if(strcmp(option,"-m")==0)frameid="TALB";
        else if(strcmp(option,"-y")==0)frameid="TYER";
        else if(strcmp(option,"-l")==0)frameid="TCON";
        else if(strcmp(option,"-c")==0)frameid="COMM";
        else
        {
            //if not valid choice
            printf("Enter valid choice\n");
            printf("For commands: ./a.out -h\n");
            return 1;
        }
        //Edit tag function
        edittag(filename,frameid,argv[3]);
    }
    else
    {
        //if not view or edit choice
        printf("Enter valid choice\n");
        printf("For commands: ./a.out -h\n");
        return 1;
    }
    return 0;
}
