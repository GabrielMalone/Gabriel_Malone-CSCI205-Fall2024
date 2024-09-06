// Gabriel Malone // CSCI205 // Lab 2 // 9/1/2024

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <unordered_map>

// TODO -> change some of the functions to use long long for outputs (like the factorials and quadratics)

using namespace std;

unordered_map<int, int>matrixMultiplcationMap;						// stores trial number and data results for that trial
unordered_map<int, int>primeNumbersMap; 							// stores trial number and data results for that trial
unordered_map<int, int>primeNumbersMapEnhancedMap; 					// stores trial number and data results for that trial
unordered_map<int, int>factorialsMap; 								// stores trial number and data results for that trial
unordered_map<int, int>matrixMaxElementMap; 						// stores trial number and data results for that trial
unordered_map<int, int>exponentialFunctionMap;						// stores trial number and data results for that trial
unordered_map<int, int>arrayRangeMap;								// stores trial number and data results for that trial
unordered_map<int, int>middleIndexingMap;							// stores trial number and data results for that trial

unordered_map<string, unordered_map<int, int> >allExperimentResults;// stores name of function and map associated with it ^

int matrixMultiplication(size_t arraySize);
int primeNumbersFunction(int primeNumberCandidate);
int primeNumbersFunctionEnhanced(int primeNumberCandidate);
int factorialFunction(int factorial);
int matrixMaxElement(int arraySize);
int exponentialFunction(int power);
int arrayRange(int arraySize);
int middleIndexing(int arraySize);
void outputFile(string &filename, int loops);

int main()
{
	string selection; 		// variable to hold user input
	string numTimes; 		// variable to hold num of times to run the functions
	vector<int> selections; // vector to hold user's graph selections

	// MENU START 

	int minWidth = 42; 		// menu formatting 

	cout << "\n";
	cout << "  Select Functions to Graph - Then Press Enter \n";
	cout << "+----------------------------------------------+ \n";
	// vector of the file names / function names
	vector<string> fileNames =
		{
			"constant_time_middle_index",
			"linear_time_array_range",
			"quadratic_time_matrix_max_element",
			"linear_time_exponential_function",
			"linear_time_factorials_function",
			"linear_time_prime_numbers",
			"linear_time_prime_numbers_enhanced",
			"quadratic_time_matrix_multiplication"};

	// create menu seleciton box
	int i = 1;
	for (string fileName : fileNames)
	{
		cout << "| " << i << ") " << setw(minWidth) << left << fileName << "|" << "\n";
		i ++;
	}
	cout << "+----------------------------------------------+ " << endl;

	cout << "  Enter number(s): "; getline(cin, selection);

	cout << "  Enter number of times to run experiements: "; cin >> numTimes;

	// MENU END

	// iterate through user's input and run selected functions
	// (int)c - 48  to convert char to int, then minus 1 to index vector properly. 

	for (char c : selection) {
		if (c > '0' && c <= '8')
		{
			outputFile(fileNames[((int)c - 48) - 1], stoi(numTimes)); 
		}
	}

	// run the python script to show graphs

	int status = system("python3 plot.py"); 
	if (status == -1)
	{
		cerr << "\npython script failed :[\n" << endl;
	} else {
		cout << "\n  graphs created successfully!\n" << endl;
		cout << "  all .txt data cleared\n" << endl;
	}

	return 0;
}

/**
 * run each test/function and output results of testing to an appropriately named text file
 * outputs the number of comparisons / time complexity / and actual data output
 * @param filename
 */
void outputFile(string &filename, int loops)
{
	ofstream outFile(filename + ".txt");
	if (outFile.is_open())
	{
		for (int i = 0; i < loops; i++) 
		{
			if (filename == "constant_time_middle_index"){ 
				outFile << (i) << " " 											// comparisons
						<< middleIndexing(i) << " "								// time complexity
				 		<< allExperimentResults["middle"][middleIndexing(i)] 	// actual data from function 
						<< endl;
			}

			if (filename == "linear_time_array_range"){
				outFile << (i) << " " 
						<< arrayRange(i) << " " 
						<< allExperimentResults["range"][arrayRange(i)] 
						<< endl;
			}

			if (filename == "quadratic_time_matrix_max_element"){
				outFile << (i) << " " 
						<< matrixMaxElement(i) << " " 
						<< allExperimentResults["matrixMaxElement"][matrixMaxElement(i)] 
						<< endl;
			}

			if (filename == "linear_time_exponential_function"){
				outFile << (i) << " " 
						<< exponentialFunction(i) << " " 
						<< allExperimentResults["exponential"][exponentialFunction(i)] 
						<< endl;
			}

			if (filename == "linear_time_factorials_function"){
				outFile << (i) << " " 
						<< factorialFunction(i) << " "
						<< allExperimentResults["factorials"][factorialFunction(i)] 
						<< endl;
			}

			if (filename == "linear_time_prime_numbers"){
				outFile << (i) << " " 
						<< primeNumbersFunction(i) << " " 
						<< allExperimentResults["prime"][primeNumbersFunction(i)] 
						<< endl;
			}

			if (filename == "linear_time_prime_numbers_enhanced"){
				outFile << (i) << " " 
						<< primeNumbersFunctionEnhanced(i) << " "
						<< allExperimentResults["primeEnhanced"][primeNumbersFunctionEnhanced(i)] 
						<< endl;
			}

			if (filename == "quadratic_time_matrix_multiplication"){
				outFile << (i) << " " 
						<< matrixMultiplication(i) << " "
						<< allExperimentResults["matrixmult"][matrixMultiplication(i)]  
						<< endl;
			}
		}
		outFile.close();
	}
	else
	{
		cerr << "Unable to open file";
	}
}

/**
 * QUADRATIC TIME - MATRIX MULTIPLICATION
 * Implements “dot product” matrix multiplication for square matrices 
 * There are 3 for-loops, and so O(n^3).
 * @param int arraySize
 * @return time complexity of this function (n)
 */
int matrixMultiplication(size_t arraySize)
{
	int result = 0; 	// sum of the products
	int n = 0;			// time complexity variable
	int elementA = 0; 	// number to be multiplied from first matrix
	int elementB = 0; 	// number to be multiplied from second matrix

	// create 1st dynamic matrices
	size_t** matrixA = new size_t*[arraySize];

	for (size_t i = 0 ; i < arraySize ; i ++ )
	{
		matrixA[i] = new size_t[arraySize];
	}
	// create 2nd dynamic matrices
	size_t** matrixB = new size_t*[arraySize];

	for (size_t i = 0 ; i < arraySize ; i ++ )
	{
		matrixB[i] = new size_t[arraySize];
	}
	// create 3rd dynamic matrices
	size_t** matrixC = new size_t*[arraySize];

	for (size_t i = 0 ; i < arraySize ; i ++ )
	{
		matrixC[i] = new size_t[arraySize];
	}

	// fill matrices
	for (int i = 0; i < arraySize; i++)
	{
		for (int j = 0; j < arraySize; j++)
		{
			matrixA[i][j] = j+i;
			matrixB[i][j] = j+i;
		}
	}

	// first two loops set the numbers to be multiplied
	// third loop places the proudct into 3rd matrix
	for (size_t i = 0; i < arraySize; i++)
	{
		for (size_t j = 0; j < arraySize; j++)
		{
			elementA = matrixA[i][j];
			elementB = matrixB[i][j];
			for (size_t k = 0; k < arraySize; k++)
			{
				matrixC[i][j] = elementA * elementB;
				// just flattening out the matrix
				//to one value for the result output
				n++;
			}
		}
	}

	// output visualization of all three matrices in terminal
	cout << endl;
	cout << "matrix A" << endl;
	for (int i = 0; i < arraySize; i++)
	{
		for (int j = 0; j < arraySize; j++)
		{
			cout <<  setw(5) << left << matrixA[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	cout << "matrix B" << endl;
	for (int i = 0; i < arraySize; i++)
	{
		for (int j = 0; j < arraySize; j++)
		{
			cout <<  setw(5) << left << matrixB[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	cout << "matrix C" << endl;
	for (int i = 0; i < arraySize; i++)
	{
		for (int j = 0; j < arraySize; j++)
		{
			cout <<  setw(5) << left << matrixC[i][j] << " ";
			result += matrixC[i][j];
		}
		cout << endl;
	}
	cout << endl;
	cout << "sum of products from Matrix C: " << result << endl;

	// save actual experiement data
	matrixMultiplcationMap[n] = result;
	allExperimentResults["matrixmult"] = matrixMultiplcationMap;

	// delete
	for (size_t i = 0 ; i < arraySize ; i ++ )
	{
		delete matrixA[i];
	}
	// delete
	for (size_t i = 0 ; i < arraySize ; i ++ )
	{
		delete matrixB[i];
	}
	// delete
	for (size_t i = 0 ; i < arraySize ; i ++ )
	{
		delete matrixC[i];
	}
	// delete
	delete [] matrixA;
	delete [] matrixB;
	delete [] matrixC;

	return n;
}

/**
 * LINEAR TIME - PRIME NUMBERS 
 * @param primeNumberCandidate
 * @return time complexity of function
 */
int primeNumbersFunction(int primeNumberCandidate)
{
	bool prime = true;
	int n = 0; // time complexity variable
	// only makes sense to check numbers > 2
	// loop needs to start at 2 (1 and 0 have their own issues)
	// one for-loop = linear time, though could end very quickly if divisible by a small number.
	if (primeNumberCandidate > 2)
	{ 
		for (int i = 2; i < primeNumberCandidate; i++)
		{		 
			n++; 
			if (primeNumberCandidate % i == 0)
			{
				prime = false;
			}
		}
		// save actual experiement data
		primeNumbersMap[n] = prime;
		allExperimentResults["prime"] = primeNumbersMap;
	}

	return n;
}

/**
 * LINEAR TIME - PRIME NUMBERS ENHANCED 
 * @param primeNumberCandidate
 * @return time complexity of function
 */
int primeNumbersFunctionEnhanced(int primeNumberCandidate)
{
	bool prime = true;
	int n = 0; // time complexity variable
	if (primeNumberCandidate > 2)
	{
		// only makes sense to check numbers > 2
		// loop needs to start at 2 (1 and 0 have their own issues)
		// one for-loop = linear time
		for (int i = 2; i < primeNumberCandidate; i++)
		{		 
			n++; 
			if (primeNumberCandidate % i == 0)
			{	
				// end loop when any divisible number found
				prime = false;
				break; 
			}
			
			if (i * i == primeNumberCandidate)
			{ 
				// square root strategy
				prime = false;
				break;
			}
		}
		// save actual experiement data
		primeNumbersMapEnhancedMap[n] = prime;
		allExperimentResults["primeEnhanced"] = primeNumbersMapEnhancedMap;
	}

	return n;
}

/**
 * LINEAR TIME - FACTORIALS 
 * calculates the factorials of a number, not including 1 and itself.
 * O(n) because one for-loop to calc factorial. Dependent on factorial size.
 * @param factorial
 * @return time complexity (n) of this function
 */
int factorialFunction(int factorial)
{
	int n = 0;							// time complexity variable
	int result = 1;						// variable to save the products
	int base = factorial;				// the current factorial
	int next = base - 1;				// the next number to multiply to the base factorial

	if (factorial > 1){
		for (int i = 0; i < factorial; i++) // loop through each
		{
			n++;
			result *= base * next;
			base -= 2;	  // move to the next pair of numbers to multiply
			next -= 2;	  // move to the next pair of numbers to multiply
			if (next < 1) // prevent multiplying by zero
			{
				break;
			}
		}

		// save actual experiement data
		factorialsMap[n] = result;
		allExperimentResults["factorials"] = factorialsMap;
	}
	return n;
}

/**
 * QUADRATIC TIME - MATRIX MAX ELEMENT 
 * Matrix Max Element: a function to find the maximum
 * two for-loops, so complexity = O(n^2) (n*n)
 * @param matrixSize
 * @return time complexity of the operation O(n^2)
 */
int matrixMaxElement(int arraySize)
{
	int n = 0;						  // time complexity variable
	int max = 0;					  // variable to store min element found
	int currentInt;					  // variable to track current element in the matrix
	int count = 0;


	// create dynamic matrix 
    size_t** matrix = new size_t*[arraySize];

	for (int i = 0 ; i < arraySize ; i ++ )
    {
        matrix[i] = new size_t[arraySize];
    }

	// fill matrix
	for (int i = 0; i < arraySize; i++)
	{
		for (int j = 0; j < arraySize; j++)
		{	
			count ++;
			matrix[i][j] = count;
		}
	}

	// find max element / calc time complexity (filling matrix not really necessary)
	for (int i = 0; i < arraySize; i++)
	{
		for (int j = 0; j < arraySize; j++)
		{
			currentInt = matrix[i][j];
			if (currentInt > max)
			{
				max = currentInt;
			}
			n++; // count inner iterations
		}
	}

	// clean up memory
	for (int i = 0 ; i < arraySize ; i ++ )
    {
        delete matrix[i];
    }
	delete [] matrix;

	// save actual experiement data
	matrixMaxElementMap[n] = max;
	allExperimentResults["matrixMaxElement"] = matrixMaxElementMap;

	return n;

}

/**
 * LINEAR TIME - EXPONENTIAL FUNCTION 
 * Implements an iterative function
 * one for-loop, thus time complexity O(n)
 * @param matrixSize
 * @return time complexity of the operation O(n^2)
 */
int exponentialFunction(int power)
{
	int n = 0; // time complexity variable
	int base = power; // base that will be raised
	int total = 1; // should you want to see that the function works correctly
	if (power == 0) // any num raised to 0 = 1
	{
		total = 1;
	}
	else
	{
		// one for-loop, so time complexity = O(n)
		for (int i = 0; i < power; i++)
		{
			n++; // linear time complexity
			total *= base;
		}
	}
	// save actual experiement data
	exponentialFunctionMap[n] =  total;
	allExperimentResults["exponential"] = exponentialFunctionMap;
	// return time complexity
	return n;
}

/**
 * LINEAR TIME - ARRAY RANGE 
 * @param arraySize
 * @return time complexity of the operation (n Linear)
 */
int arrayRange(int arraySize)
{
	int n = 0;			  				// time complexity variable
	int* array = new int[arraySize]; 	// initialize array
	int min = 0;			  			// min number in array to calc range
	int max = 0;			 	 		// max number in array to calc range
	int currentInt;		 		 		// for use in loop / determining min & max
	int range; 			  				// final result but not actually needed for this project

	for (int i = 0; i < arraySize; i++)
	{
		array[i] = i;
	}
	// find min and max
	for (int i = 0; i < arraySize; i++)
	{
		currentInt = array[i];
		if (currentInt <= min)
		{
			min = currentInt;
		}
		if (currentInt > max)
		{
			max = currentInt;
		}
		n++; 							// each iteration increases time complexity
	}
	 range = max - min; 

	// clean up memory
	delete[] array;

	// save actual experiement data
	arrayRangeMap[n] = range;
	allExperimentResults["range"] =  arrayRangeMap;

	return n;
}

/**
 * CONSTANT TIME - MIDDLE ARRAY ELEMENT
 * @return time complexity of middle indexing.
 */
int middleIndexing(int arraySize)
{
	int c = 0;							// track how many const operations are performed
	int* array = new int[arraySize];	// make array

	for (int i = 0; i < arraySize; i++) // fill array
	{
		array[i] = i;
	}
	int midElement = array[arraySize/2]; // get the middle element (constant time operation)
	c++; // increment constant operation variable

	// clean up memory
	delete [] array;

	// save actual experiement data
	middleIndexingMap[c] = midElement;
	allExperimentResults["middle"] =  middleIndexingMap;

	return c;
}
