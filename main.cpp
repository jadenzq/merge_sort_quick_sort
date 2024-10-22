/*
    This is a program that implements Quicksort and Mergesort.
    Both algorithms are used to sort the randomly generated movie tickets
    and their prices in ascending order. 
    The number of movie tickets are decided by the user.
*/

#include<iostream>
#include<cstdlib>
#include<ctime>
#include<iomanip>
using namespace std;


void generateTicket (int tkID[], int msTkID[], int qsTkID[],
float tkPrice[], float msTkPrice[], float qsTkPrice[], int n){

    /*
        A function that randomly generates ticket IDs and prices
    */

    // initialize variables
    double decimal = 1; // to hold randomly generated price decimals
    time_t current_time = time(NULL); // set current time as seed for srand()

    for (int i=0; i<n; i++){
        // seeding srand() with current_time + i to reduce duplicate IDs
        srand((unsigned) current_time + i);
        
        // generating ticket id and store inside 3 arrays
        tkID[i] = rand() % 1000000; // limit the range to 0-999999
        msTkID[i] = tkID[i];
        qsTkID[i] = tkID[i];

        // generating ticket price and store inside 3 arrays
        // while loop makes sure randomly generated decimal is < 1
        while (decimal >= 1){ 
            decimal = (double)(rand()) / (double)(rand());
        }
        tkPrice[i] = 15 + rand() % 985 + decimal; // limit the range to 15.00-999.99
        msTkPrice[i] = tkPrice[i];
        qsTkPrice[i] = tkPrice[i];
        decimal = 1; // reset to enter next iteration's while loop
    }
}


int partition(int tkID[], float tkPrice[], int l, int r){

    /*
        A function that sort the array into two subarrays.
        One is smaller than pivot, another one is larger than pivot.
        Finally, return the new index position of pivit.
    */

    int p = (l+r)/2; // selecting middle element as pivot
    // put pivot to the first position in the array
    swap(tkID[p], tkID[l]);
    swap(tkPrice[p], tkPrice[l]);
    // update index of pivot to l after swapping
    p = l;
    
    // initiating i and j that scan from left and right of the array
    int i = l, j = r+1;

    while (i < j){
        // i scans the array from the left side, stops at element > pivot
        do{
            i++;
        }while(tkID[i] < tkID[p]);

        // j scans the array from the right side, stops at element < pivot
        do{
            j--;
        }while(tkID[j] > tkID[p]);

        // if i has not crossed j
        // swap elements in index i and j
        if (i < j){
            swap(tkID[i], tkID[j]);
            swap(tkPrice[i], tkPrice[j]);
        }
        // if i and j crossed each other, scanning is completed
        // swap pivot with last element in the first subarray
        // to put pivot in the correct position
        if (i >= j){
            swap(tkID[j], tkID[p]);
            swap(tkPrice[j], tkPrice[p]);
        }
    }

    // return the index position where pivot is
    return j;
}


void quickSort(int tkID[], float tkPrice[], int l, int r){

    /*
        Recursive funciton to execute Quicksort.
        Partition the array and use the returned new index position
        of pivot to divide the array into two subarrays.
    */
    
    int p = 0;

    // continue dividing the array until the array size becomes 1
    if (l<r){
        // p is the new index position where pivot is placed in after partition()
        p = partition(tkID, tkPrice, l, r);
        quickSort(tkID, tkPrice, l, p-1); // arr[l...s-1] is the smaller subarray
        quickSort(tkID, tkPrice, p+1, r); // arr[s+1...r] is the larger subarray
    }
}


void merge(int tkID[], float tkPrice[], int beg, int mid, int end){

    /*
        A function that merge two arrays into one sorted array.
    */

    // setting the iterators loop through left and right array
    // i and j are iterators for left and right array, k is iterator for original array
    int i = 0, j = 0, k = beg;
    // n is the left arr size, m is the right arr size
    int n = mid-beg+1, m = end-mid;

    // declaring pointers
    int *leftTkID, *rightTkID;
    float *leftTkPrice, *rightTkPrice;
    
    // dynamically allocate memory for left and right arrays
    leftTkID = new int[n];
    rightTkID = new int[m];
    leftTkPrice = new float[n];
    rightTkPrice = new float[m];

    // copy the left arr from the original array
    for (int i = 0; i < n; i++){
        leftTkID[i] = tkID[beg+i];
        leftTkPrice[i] = tkPrice[beg+i];
    }
    // copy the right arr from the original array
    for (int i = 0; i < m; i++){
        rightTkID[i] = tkID[mid+1+i];
        rightTkPrice[i] = tkPrice[mid+1+i];
    }
    
    // comparing left and right arrays using i&j
    // exit when one of the array is all arranged
    while (i < n && j < m){
        if (leftTkID[i] <= rightTkID[j]){ // left array <= right array
            tkID[k] = leftTkID[i]; // put left array element in original array
            tkPrice[k] = leftTkPrice[i]; 
            i++;
        } else if (leftTkID[i] > rightTkID[j]){ // left array > right array
            tkID[k] = rightTkID[j]; // put right array element in original array
            tkPrice[k] = rightTkPrice[j]; 
            j++;
        }
        k++;
    }

    // put left over elements to the arr
    while (i < n){ // put leftovers elements of left array in original array
        tkID[k] = leftTkID[i];
        tkPrice[k] = leftTkPrice[i]; 
        i++; k++;
    }
    while (j < m){ // put leftovers elements of right array in original array
        tkID[k] = rightTkID[j];
        tkPrice[k] = rightTkPrice[j]; 
        j++; k++;
    }

    // clear the allocated memory
    delete[] leftTkID;
    delete[] rightTkID;
    delete[] leftTkPrice;
    delete[] rightTkPrice;
}


void mergeSort(int tkID[], float tkPrice[], int beg, int end){

    /*
        Recursive function that execute Mergesort.
        Divides the array in the middle to create two halves of the array.
        Then merges the smaller arrays back into original size.
    */

    int mid = 0;

    // stop dividing when the array size is one
    if (beg < end){
        mid = (beg + end) / 2; // calculate the middle index of the array
        mergeSort(tkID, tkPrice, beg, mid); // divide the first half of the array
        mergeSort(tkID, tkPrice, mid+1, end); // divide the second half of the array
        merge(tkID, tkPrice, beg, mid, end); // merge the array's two halves
    }
}


void displayTk (int tkID[], float tkPrice[], int n){

    /*
        A function to display tiket IDs and prices in a formatted way.
    */

    cout.setf(ios::fixed);
    cout << "-----------------------------\n";
    cout << "|" << setfill(' ') << setw(10) << "Ticket ID" << setw(2) << "|" << setw(14) << "Ticket Price" << setw(3) << "|\n"; 
    cout << "-----------------------------\n";

    for (int i=0; i<n; i++){
        
        cout << "|" << setw(3) << "MT" << setfill('0') << setw(6) << tkID[i] << setfill(' ') << setw(3) << "|" << setw(14) << setprecision(2) << tkPrice[i] << setw(3) << "|\n"; 
    }
    cout << "-----------------------------\n";

}


int main (){

    // initializing variables, pointers to store ticket IDs and prices
    int n = 0, option = 0;
    int *tkID, *msTkID, *qsTkID;
    float *tkPrice, *msTkPrice, *qsTkPrice;
    // variables used to calculate cpu time used by each sorting algorithms
    clock_t time_req; 
    double msTime, qsTime;
    
    // ask for ticket quantity
    cout << "How many ticket would you like to generate?: ";
    cin >> n;

    // point the pointers to dynamically allocated memory spaces
    tkID = new int[n]; 
    msTkID = new int[n];
    qsTkID = new int[n];
    tkPrice = new float[n];
    msTkPrice = new float[n];
    qsTkPrice = new float[n];
    
    // generate ticket
    generateTicket(tkID, msTkID, qsTkID, tkPrice, msTkPrice, qsTkPrice, n);
    
    // calculating time used by each sorting methods, convert to milliseconds
    time_req = clock();
    mergeSort(msTkID, msTkPrice, 0, n-1);
    time_req = clock() - time_req;
    msTime = ((double)time_req/CLOCKS_PER_SEC) * 1000000;
    
    time_req = clock();
    quickSort(qsTkID, qsTkPrice, 0, n-1);
    time_req = clock() - time_req;
    qsTime = ((double)time_req/CLOCKS_PER_SEC) * 1000000;
    
    // display time used by each sorting algorithms
    cout << "\nTime used by MS: " << msTime << " microseconds";
    cout << "\nTime used by QS: " << qsTime << " microseconds";

    // A menu allowing user to choose to view unsorted/ sorted ticket IDs and prices
    while (true){
        cout << "\n\nPress 1 to see unsorted ticket ID and price";
        cout << "\nPress 2 to see sorted ticket ID and price";
        cout << "\nPress 0 to quit: ";
        cin >> option;
        
        if (option == 1){ //show unsorted ticket IDs and prices
            cout << "\n\nBefore Sorting:\n";
            displayTk(tkID, tkPrice, n);
        }
        else if (option == 2){ //show sorted ticket IDs and prices
            cout << "\n\nAfter Sorting:\n";
            displayTk(qsTkID, qsTkPrice, n);
        }
        else if (option == 0){ // quit the menu
            break;
        }
        else{ // prompt user to enter correct inputs
            cout << "\nEnter 1 or 2 or 0 only.";
        }
    }

    cout << "\n\n";
    return 0;
}