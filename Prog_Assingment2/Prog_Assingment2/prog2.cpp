// Dynamic Programming implementation of edit distance
#include<iostream>
#include<stdlib.h>
#include<string.h>
using namespace std;
 
// Change these strings to test the program
#define STRING_X "AGGCTATCACCTGACCTCCAGGCCGATGCCC"
#define STRING_Y "TAGCTATCACGACCGCGGTCGATTTGCCCGAC"
 
#define gap_penalty 1
#define mismatch_penalty 2
 
inline
int min(int a, int b) {
   return a < b ? a : b;
}
 
// Returns Minimum among a, b, c
int Minimum(int a, int b, int c)
{
    return min(min(a, b), c);
}
 
// Strings of size m and n are passed.
// Construct the Table for X[0...m, m+1], Y[0...n, n+1]
int EditDistanceDP(char X[], char Y[])
{
    // Cost of alignment
    int cost = 0;
    int leftCell, topCell, cornerCell;
 
    const int m = strlen(X)+1;
    const int n = strlen(Y)+1;
    
 
    // T[m][n]
    int T[m][n];   
 
    // Initialize table
    for(int i = 0; i < m; i++)
        for(int j = 0; j < n; j++)
            T[i][j] = -1;
    
	// Set up base cases
    // T[i][0] = i
    for(int i = 0; i <m; i++)
        T[i][0] = i*gap_penalty;
   
	// T[0][j] = j
    for(int j = 0; j <n; j++)
        T[0][j] = j*gap_penalty;
 
    // Build the T in top-down fashion
    for(int i = 1; i < m; i++)
    {
        for(int j = 1; j < n; j++)
        {
            // T[i][j-1]
            leftCell = T[i][j-1];
            leftCell += gap_penalty;
 
            // T[i-1][j]
            topCell = T[i-1][j];
            topCell += gap_penalty;
 
            // Top-left (corner) cell
            // T[i-1][j-1]
            cornerCell = T[i-1][j-1];
            if(X[i-1] != Y[j-1]) 
             cornerCell += mismatch_penalty; 
            
            // Minimum cost of current cell
            // Fill in the next cell T[i][j]
            T[i][j] = Minimum(leftCell, topCell, cornerCell);
        }
    }
    cout<<endl;
     for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
        	cout<<T[i][j]<<" ";
        }
        cout<<"\n";
    }
    // Cost is in the cell T[m][n]
    cost = T[m-1][n-1];
    return cost;
}
 
int main()
{
    char X[] = STRING_X; // vertical
    char Y[] = STRING_Y; // horizontal
 
    cout<<"\nPenalty cost of the alignment is "<<EditDistanceDP(X, Y);
    return 0;
}
