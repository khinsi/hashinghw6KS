//
//  main.cpp
//  hw5
//
//  Created by Khin Yatana on 4/18/16.
//  Copyright © 2016 Khin Yatana. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>



using namespace std;

void bubblesort (int A[], int n);
void insertionsort(int A[], int n);
void selectionsort (int A[] , int n );
void shellsort(int A[], int n);
void merge (int *a, int low, int high , int mid );
void mergesort (int *a , int  low, int high );

int compare = 0;
int exchanges = 0 ;


void bubblesort (int A[], int n)
{
    int i, j, temp;
    for(i = 1; i < n; i++)
    {
        for(j = 0; j < n - 1; j++)
        {
            compare++;
            if(A[j] > A[j + 1])
            {
                temp = A[j];
                A[j] = A[j + 1];
                A[j + 1] = temp;
                exchanges++;
            }
        }
    }
    
}
void insertionsort(int A[], int n)
{
    int i, j, element;
    for(i = 1; i < n; i++)
    {
        element = A[i];
        j = i;
        compare++;
        while ((j > 0) && (A[j - 1] > element))
        {
            A[j] = A[j - 1];
            j = j - 1;
            exchanges++;
        }
        A[j] = element;
    }
    
}
void selectionsort (int A[] , int n )
{
    int i ;
    int j;
    int minpos=0;
    int temp;
    for (i = 0 ; i< n -1; i++)
    {
        compare++;
        if ( A[j] < A [minpos] )  //compare
        {
            minpos = j ;
            
        }
        if (minpos != i )
        {
            temp = A[i];
            A[i] = A[minpos]; //swap the ith element and minpos element.
            A[minpos] = temp;
            exchanges++;
        }
    }
}

void shellsort(int A[], int n)
{
    int temp, gap, i;
    int swapped;
    gap = n/2;
    do
    {
        do
        {
            swapped = 0;
            for(i = 0; i < n - gap; i++)
            {
                compare++;
                if(A[i] > A[i + gap])
                {
                    exchanges++;
                    temp = A[i];
                    A[i] = A[i + gap];
                    A[i + gap] = temp;
                    swapped = 1;
                }
            }
        }
        while(swapped == 1);
    }
    while((gap = gap/2) >= 1);
    
}

void merge(int *a, int low, int high, int mid)
{
    int i, j, k, c[10000];
    i = low;
    k = low;
    j = mid + 1;
    while (i <= mid && j <= high)
    {
        compare++;
        if (a[i] < a[j])
        {
            c[k] = a[i];
            k++;
            i++;
            compare++;
            exchanges++;
        }
        else
        {
            c[k] = a[j];
            k++;
            j++;
            exchanges++;
        }
    }
    while (i <= mid)
    {
        c[k] = a[i];
        k++;
        i++;
    }
    while (j <= high)
    {
        c[k] = a[j];
        k++;
        j++;
    }
    for (i = low; i < k; i++)
    {
        a[i] = c[i];
    }
}

void mergesort(int *a, int low, int high)
{
    int mid;
    if (low < high)
    {
        mid=(low+high)/2;
        mergesort(a,low,mid);
        mergesort(a,mid+1,high);
        merge(a,low,high,mid);
    }
    return;
}



bool filearray(string file_name, int *& numbers)
{
    ifstream in;
    in.open (file_name.c_str());
    
    if(in.fail () )
    {
        cerr<< " Error opening file" <<endl;
    }
    string temp;
    string file_content="";
    while(in.peek()!=EOF)
    {
        in>>temp;
        file_content += temp + " ";
    }
    in.clear();
    in.close();
    
    vector<string> lines;
    temp= "";
    for( int i = 0; i < file_content.length();i++)
    {
        if (file_content[i] == ' ')
        {
            lines.push_back(temp);
            temp= "";
        }
        else
        {
            temp +=file_content[i];
        }
    }
    if(numbers!=NULL) delete numbers;
    numbers = new int[lines.size()];
    for(int i=0; i<lines.size(); i++)
    {
        numbers[i]= atoi(lines[i].c_str());
    }
    return true;
}




int main(int argc, const char * argv[])
{
    int * allNums;
    string fileNames[4];
    fileNames[0] = "FewUnique.txt";
    fileNames[1] = "NearlySorted.txt";
    fileNames[2] = "Random.txt";
    fileNames[3] = "Reversed.txt";
    //int * test=file_to_array("Random.txt");
    
    for(int i= 0;i<4; i++)
    {
        filearray(fileNames[i],allNums);
         bubblesort (allNums,10000);
        
         cout << compare << endl;
         cout << exchanges << endl;
        cout<<"---------------"<<endl;
        
        filearray (fileNames[i],allNums);
        insertionsort(allNums,10000);
        cout << compare << endl;
        cout << exchanges << endl;
        
      
        
        filearray(fileNames[i], allNums);
        selectionsort (allNums,10000);
         cout << compare << endl;
         cout << exchanges << endl;
        
        filearray(fileNames[i],allNums);
         shellsort(allNums,10000);
         cout << compare << endl;
         cout << exchanges << endl;
        
        filearray(fileNames[i],allNums);
         mergesort(allNums,0,10000);
         cout << compare << endl;
         cout << exchanges << endl;
        
    }
    
}
