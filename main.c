#include <stdio.h>
#include "lab14.h"

int main(void)
{
    //Finding File that we need to read into the computer
    FILE * fp = fopen("students.csv","r");
    Student ** test = readRecord(fp);
    //Commented out, but will print an unsorted list
 /*   for(int i = 0; i<10000; i++)
    {
        printf("Student[%d]   \t   Age - %d\t   ID - %d\n",i,test[i]->age,test[i]->ID);
    }*/
    //Creating Database to store sorted list
    StudentDB othertest;
    //Initialize othertest by reading test (which contains 10000 items) into it which will sort it
    othertest = createDatabase(test, 10000);
    //Printing the sort
    printf("After sort\n");
    //Printing all sorted items
    for(int i = 0; i<10000; i++)
    {
        printf("Student[%d]   \t   Age - %d\t   ID - %d\n",i,othertest.array[i]->age,othertest.array[i]->ID);
    }
    //BS stands for BinarySearch, and will search for any student ID (in this case 22094) and see if its in the list
    Student * bs = findStudentByID(othertest, 22094);
    //If bs comes back NULL, we cannot read the value
    if(!bs)
    {
        printf("BS is invalid\n");
    }
    //Otherwise we print BS
    else
    printf("%d\n",bs->ID);
    //printing the total size of othertest
    printf("%d\n",othertest.sizeOfDB);
    //Printing the sorted list again
    for(int i = 0; i<10000; i++)
    {
        printf("Student[%d]   \t   Age - %d\t   ID - %d\n",i,othertest.array[i]->age,othertest.array[i]->ID);
    }
    //Freeing all data
    freeDatabase(othertest);
}
