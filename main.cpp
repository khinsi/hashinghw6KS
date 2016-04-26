//
//  main.cpp
//  hashing hw6
//
//  Created by Khin Yatana on 4/23/16.
//  Copyright © 2016 Khin Yatana. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstring>
#include <queue>
#include <stdlib.h>
using namespace std;


int extraction_method(int key);
int quadratic_prob (int *& Hashtable, int key, int Max);


int extraction_method(int key )
{
    
    string text = to_string (key);  //convert int key into string.
    string one ;
    one= text [2]; //extract the string index
    string two;
    two = text[4]; //extract the string index
    string three ;
    three = text[6];
    string four;
    four = text [7];
    
    string all = one + two + three + four;  //combine all of the strings
    int hashkey = stoi (all); //convert into an int.
    
    return hashkey; //return int
}

int quadratic_prob (int *& Hashtable, int key, int Max)
{
    int pos;
    int i;
    pos = extraction_method(key);  //position will be extraction method returned key.
    for (i = 0 ; i % Max != pos ; i++)
    {
        pos = (pos + i *i) % Max;
        if (Hashtable[pos]  == 0)//empty slot
        {
            Hashtable [pos] = key;
            return pos;
            
        }
    } //table overflow
    return -1;
}


int main()
{
    ifstream in;
    ofstream out;
    in.open ("socials.txt");
    string line; //will have words/ints from the file
    int number ;
    vector <int> i_vector;
    int i = 0;
    
    while (!in.eof () )
    {
        getline (in,line, ','); //read in & store in "line";
        number = stoi (line);  //string to int.
        i_vector.push_back(number); //store in vector.
        i++;
        
    }
    //for (int j = 0 ; j < i_vector.size() ; j++)  //put each word in vector
    //{
    //    cout<<i_vector [j] <<endl; //testing vector output.
    //}
    
    //----------------------------------------------------------------------------------//
    
    int index ;
    
    int M = 500;
    int *hash_table= new int [500];
    for(int i=0;i<M;i++)    //initialize the hash table to contain 0s
        hash_table[i]=0;
    
    for(int i=0;i<M;i++)    //hash the elements in array_of_numbers into the hash_table
    {
        index= extraction_method (i_vector[i]);
        
        if(hash_table[index]==0) //if the hashed number index is 0 do the following:
            hash_table[index]=i_vector [i]; //hashed number index within hashtable equals the number in the vector.
        
        else
        {
            //cout << "COLLISION! Fear not... I'll resolve it!\n"; //if the space is already taken , we will do quadratic probing to move it.
            
            quadratic_prob (hash_table , i_vector [i], M); //call the quadratic probing function.
        }
    }
    out.open("hashed_socials.txt"); //open up output file.
    for (int k = 0 ; k< 500; k++)  //writing out the hashtable onto console.
    {
        cout<<hash_table[k]<<",";
        out<<hash_table [k]<<","; //writing the hashtable into output textfile.
        
    }
    
    
    
    in.clear(); in.close ();
    out.clear (); out.close();
    delete[] hash_table;
}