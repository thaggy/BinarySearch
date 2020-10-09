#include "lab14.h"

Student** readRecord(FILE* fp)
{
    //Special Case 0 : There is no file passed to us
    if(!fp)
    {
        //We will warn the user that no memory will be passed back
        printf("There is no file! Return NULL\n");
        return NULL;
    }
    //Creating an int that will store the number of Elements in the array, by default it will be 0
    int numElems = 0;
    //Reading the first line of the file and saving it to the number which we just created
    fscanf(fp,"%d",&numElems);
    //Creating a temporary student pointer
    Student ** temp;
    temp = (Student **)malloc(numElems*sizeof(Student*));
    // Special Case 0 : Malloc fails
    if(!temp)
    {
        printf("Oopsie! Memory failed to allocate!Return NULL\n");
        return NULL;
    }
    //Now we go through every element and read in each value found
    for(int i=0;i<numElems;i++)
    {
        temp[i]=(Student *)malloc(sizeof(Student));
        fscanf(fp,"%d,%d\n",&temp[i]->age,&temp[i]->ID);
    }
    //Return the temp value
    return temp;
}
StudentDB createDatabase(Student** Array, int size)
{
    //Special Case 0 : No array is given to us
    if(!Array)
    {
        printf("There is no array being passed. Exiting with code 0\n");
        exit(0);
    }
    //We create the temp StudentDB that will be passed to main
    StudentDB temp;
    // Tempo is for temporary but since we already have a temp and I want another temp, this is Tempo for either another way to say temporary or TempOther
    int tempo, j;
    //Insertion Sort
    for (int i = 1; i < size; i++)
    {
        //Tempo will be set equal the the second value of the array
        tempo = Array[i]->ID;
        //J is set to the first value of the array
        j = i - 1;
        //Now we do a loop till two conditions are met, J must not be bigger than, or equal to 0, and J must be smaller than the tempo (which is currently the second value in the array)
        //So basically when tempo is smaller than tempo-1, we swap them and we do this for the entire array
        while(j >= 0 && Array[j]->ID > tempo)
        {
            //We then do some swapping here and outside of the loop when these conditions are true
            Array[j + 1]->ID = Array[j]->ID;
            j = j - 1;
        }
        //Other part of the swap
        Array[j + 1]->ID = tempo;
    }
    //After everything is sorted, we store it into our struct and set the size to be correct
    temp.array = Array;
    temp.sizeOfDB = size;
    //Returning temp
    return temp;
}
Student* findStudentByID(StudentDB db, int search)
{
    //Special Case 0 : we don't have an array
    if(!db.array)
    {
        printf("There is no array, returning NULL\n");
        return NULL;
    }
    //Creating Mid point
    int mid = db.sizeOfDB / 2;
    //If the mid point is our desired search, we return that Student
    if(db.array[mid]->ID == search)
    {
        printf("Search Found!\n");
        return db.array[mid];
    }
    //Special Case 1 : Mid point becomes 0
    if(mid == 0)
    {
        //This means that the desired data was NOT found so we return NULL
        printf("Nothing was found. Returning NULL\n");
        return NULL;
    }
    //Special Case 1 : The Mid point is bigger than the desired search
    if (db.array[mid]->ID > search)
    {
        //This means that we need to check the first half of the array so we decrease the total size and search again recursively
        db.sizeOfDB=mid;
        return findStudentByID(db, search);
    }
    //Special Case 2 : The Mid point is smaller than the desired search
    else if (db.array[mid]->ID < search)
    {
        //This means that we still need change the total size as we will decrease the total problem size
        db.sizeOfDB = (db.sizeOfDB+1)/2;
        //We also need to move the array forward. We can do this by setting it equal the address of the midpoint and searching again
        db.array = &db.array[mid];
        return findStudentByID(db,search);
    }
    else
        //If none of the above conditions are met, that means that the search is still found and we return the midpoint. Since special case 1 deals with our search NOT being found, that means that our search was found so we can safely return the midpoint
        printf("Search found!\n");
        return db.array[mid];
}
void freeDatabase(StudentDB db)
{
    //Special Case 0 : We were pranked and the array was already freed
    if(!db.array)
    {
        printf("Array was already freed\n");
    }
    //Otherwise we go through the whole array and free each data point
    else
    {
        for(int i=0;i < db.sizeOfDB; i++)
        {
            //Freeing each datapoint of the array
            free(db.array[i]);
           // printf("freed memory at %p\n",db.array[i]);
        }
        //Finally freeing the "head" of the array
        free(db.array);
        //printf("freed memory at %p\n",db.array);
        printf("All memory was freed\n");
    }
}
