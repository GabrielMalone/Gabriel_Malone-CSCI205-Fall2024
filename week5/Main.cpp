#include <iostream>
#include <string>
#include "LinkedList/List.hpp"

using namespace std;

int main(){

    // test constructor
    // List<int> myList{5};
    // // test capacity and size functions should be different values (size should be zero at this point since nothing yet added)
    // cout << "current list capacity: " << myList.getCapacity() << endl;
    // cout << "current list length: " << myList.length() << endl;
    // // testing insert 
    // // see results
    
    // myList.insert(12, 0);
    // myList.insert(45, 1);
    // myList.insert(31, 2);
    // myList.insert(45, 3);

    // // see results
    // myList.print();

    // // test capacity and size functions should be different values (size should be zero at this point since nothing yet added)
    // cout << "current list capacity: " << myList.getCapacity() << endl;
    // cout << "current list length: " << myList.length() << endl; 
    
    // // testing get 
    // cout << "getting element at 0 index: " << myList.get(0) << endl; // should return nothing
    // cout << "getting element at 1 index: " << myList.get(1) << endl; // should return 'goob'
    
    // //testing find
    // cout << "finding element '31' at index: " << myList.find(31) << endl; // should return 0
    // cout << "finding element '45' at index: " << myList.find(45) << endl; // should return -1

    // //testing remove at front, middle, end
    // cout << "removing element '12' " << endl;
    // myList.remove(12);
    // myList.print();

    // cout << "inserting element '10' at index 1" << endl;
    // myList.insert(10, 1);    
    // cout << myList.getCapacity() << endl;
    // myList.print();

    // cout << "testing resize" << endl;
    // cout << "old capacity: " << myList.getCapacity() << endl;
    // cout << "inserting 5th element '45' at index 3, this should cause resize since size == capacity" << endl;
    // myList.insert(45, 3);
    // myList.print();
    // cout << "reverse testing" << endl;
    //  myList.reverse();
    // myList.print();      
    // cout << "new capacity: " << myList.getCapacity() << endl;

    // List<int> myList2{5};
    // myList2.insert(45, 0);
    // myList2.insert(45, 1);
    // myList2.insert(45, 2);
    // myList2.insert(45, 3);
    // myList2.print();   
    // cout << "testing remove duplicates: " << endl;
    // myList2.removeDuplicates();
    // myList2.print();    

    // List<int> myList3{5};

    // myList3.insert(5, 0);
    // myList3.insert(5, 0);

    // myList3.print();

    // List<int> myList4;

    // myList4.insert(1, 0);
    // myList4.insert(2, 0);
    // myList4.insert(5, 0);
    // myList4.insert(6, 2);
    // myList4.insert(9, 0);
    // myList4.insert(8, 3);
    // myList4.insert(30, 6);
    // myList4.insert(5, 0);
    // myList4.insert(5, 0);
    // myList4.insert(5, 0);

    // myList4.print();

    // myList3.append(myList4);
    // myList3.print();

    // myList3.removeDuplicates();
    // myList3.print();

    int arr[5] = {1,20, 65, 199, 14};
    int arr2[5] = {12 ,66, 405, 9, 8766};

    List<int> myList5(arr, 5);
    List<int> myList6(arr2, 5);

    myList5.print();
    cout << myList5.length() << endl;
    cout << myList5.get_head_element() << endl;
    myList6.print();
    cout << myList6.length() << endl;
    cout << myList6.get_head_element() << endl;

    // cout << myList5.get(0) << endl;

    // cout << myList5.remove(2) << endl;
    // myList5.print();

    myList5.append(myList6);
    myList5.print();
    cout << myList5.length() << endl;
    return 0;
}