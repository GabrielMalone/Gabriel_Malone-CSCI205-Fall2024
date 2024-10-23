//------------------------------------------------------------------------------------
// GABRIEL MALONE / CSCI205 / WEEK 9 / ITERATIVE SORTING
//------------------------------------------------------------------------------------
#include "menu/menu.hpp"
#include "menu/graphCharts.hpp"
#include "menu/graphicalDisplay.hpp"

//-----------------------------------------------------------------------------------

using namespace std;

//-----------------------------------------------------------------------------------
// MAIN
//-----------------------------------------------------------------------------------
int main(){
                                                                  // vars for program
    //-------------------------------------------------------------------------------
    char type = 'r';                                             // set type of array 
    int algo_selection;                                   // set type of sorting algo
    int array_type_selection;                    // type of sorting in array to start
    int experiment_selection;      // graph performance or see visual display of algo
    //-------------------------------------------------------------------------------
                                                                      // show options 
    printMenu(algo_selection, array_type_selection, experiment_selection);

    //-------------------------------------------------------------------------------
    // execute selections
    //-------------------------------------------------------------------------------
    switch (array_type_selection)
    {
    case 1: type = 'a';                                            // ascending order
        break;
    case 2: type = 'd';                                           // descending order
        break;
    case 3: type = 'p';                                           // partially sorted
        break;
    case 4: type = 'r';                                            // randomly sorted
        break;
    default: type = 'r';                                        
        break;
    }
    //-------------------------------------------------------------------------------
    vector<int>algo_selections;      // to hold multiple algo selections for graphing
    //-------------------------------------------------------------------------------
    switch (experiment_selection)   
    {
    case 1: cout << "  SELECT ALOGORITHM: "; cin >> algo_selection;
            //-----------------------------------------------------------------------
            graphical_sorting_data(type, algo_selection);// visual display of sorting
            //-----------------------------------------------------------------------
            break;
    case 2: cout << "  SELECT ALOGORITHM(S) FOR COMAPRISON" << endl;
            cout << "  (Enter after each, 0 when done): "; 
            cin >> experiment_selection;
                while (experiment_selection != 0){
                algo_selections.emplace_back(experiment_selection);
                cin >> experiment_selection;
            }
            //-----------------------------------------------------------------------
            graph_data(type, algo_selections);              // graph the sorting data
            //-----------------------------------------------------------------------
            break;
    }

    //---------------------------------------------------------------------------------
       
    return 0;
}









