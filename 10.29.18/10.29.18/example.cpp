#include <iostream>
#include <string>
#include <cctype>
using namespace std;

bool isValidDate(int y, int m, int d) {

	const int NMONTHS = 12;

	const int daysInMonth[12] = { //this is how to declare an array
		31, 28, 31, 30, 31, 30,
		31, 31, 30, 31, 30, 31 };

	if (m < 1 || m > NMONTHS || d < 1) {
		return false;
	}
	if (m != 2)
		return d <= daysInMonth[m - 1]; //m - 1 because array elements begin at 0

	//at this point, m must be 2
	if (y % 4 != 0)
		return d == daysInMonth[m - 1];
	else
		return d == 29;
}

void printMonth() {

	const int NMONTHS = 12;

	const int daysInMonth[NMONTHS] = {
		31, 28, 31, 30, 31, 30,
		31, 31, 30, 31, 30, 31 };

	const string monthName[NMONTHS] = {
		"January", "February", "March", "April", "May", "June",
		"July", "August", "October", "November", "December"
	};
	cout << "These months have 31 days: " << endl;
	for (int i = 0; i < NMONTHS; i++) {
		if (daysInMonth[i] == 31)
			cout << monthName[i];
	}
}
/*
********************************************
size of array must be known at compile time
********************************************
const int NMONTHS = 12;
double a[NMONTHS]; //valid array declaration
double b[48]; //valid
double c[4 * NMONTHS]; //valid

int n;
cin >> n;
double d[n]; //error in Standard C++ because n is not known at compile time

int m = 10;
double e[m]; //error in Standard C++ because m is not const

array.size() //INVALID
array.length //INVALID
*/

void scores() {
	const int MAX_NUMBER_OF_SCORES = 10000;
	int scores[MAX_NUMBER_OF_SCORES];
	int nScores = 0;
	int total = 0; //don't make this a double just for average calculation because it never has fractional values
	cout << "Enter the scores (negative when done): ";
	for (;;) {
		int s;
		cin >> s;
		if (s < 0)
			break;
		if (nScores == MAX_NUMBER_OF_SCORES) {
			cout << "I can handle only " << MAX_NUMBER_OF_SCORES << " scores!" << endl;
			cout << "Continuing with just the first " << MAX_NUMBER_OF_SCORES << " values." << endl;
			break;
		}
		total += s;
		nScores++;
	}
	if (nScores == 0)
		cout << "There were no scores, so no average" << endl;
	else {
		double mean = static_cast<double>(total) / nScores; //can also create double temp = total;  to use only once in temp / nScores
		cout << "The average of all the scores is " << mean << endl;

		double sumOfSquares = 0;
		for (int k = 0; k < nScores; k++) {
			double diff = scores[k] - mean;
			sumOfSquares += diff * diff;
		}
		cout << "The std. deviation is " << sqrt(sumOfSquares / nScores) << endl;
	}
}
/*
finding average of scores does not require an array (can overwrite variable s after it's been added to total)
finding standard deviation of scores DOES require an array (bc SD requires mean and we won't know the mean until we've recorded all the values)
*/

double computeMean(const int a[], int n); //the prototype
void setFirst(int a[], int n, int value);

void scores2() {
	const int MAX_NUMBER_OF_SCORES = 10000;
	int scores[MAX_NUMBER_OF_SCORES];
	int nScores = 0;
	//... fill up the array (perhaps only partially)
	double m = computeMean(scores, nScores); //valid parameter bc function promises not to modify array
	//...
	int stuff[100];
	//... fill up all 100 elements of stuff 
	double m2 = computeMean(stuff, 100);

	const int daysInMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	double m3 = computeMean(daysInMonth, 12); //valid parameter bc daysInMonth and required type are both const 
	//...
	setFirst(stuff, 100, 42); //valid parameter bc stuff is not const
	//setFirst(daysInMonth, 12, 42); INVALID because daysInMonth is const, cannot be modified by setFirst --> won't compile
}

/*
-passing an array to a function does not create a copy of the array --> use const to ensure the original array will not be modified
-instead parameter has indication of where the array starts
-we do not know how many elements are in an array parameter
-impossible to find out how many elements are in an array parameter
*/
double computeMean(const int a[], int n) {
	if (n == 0)
		return 0;
	int total = 0;
	for (int k = 0; k < n; k++) //impossible to to check if k within array bounds --> won't be tested 
		total += a[k];
	// setFirst(a, n, 42); invalid bc computeMean promised not to modify a --> won't compile
	return static_cast<double>(total) / n;
}
void setFirst(int a[], int n, int value) { //when calling this function, we cannot pass a const array
	if (n >= 1)
		a[0] = value;
	computeMean(a, n); //valid because computeMean won't modify array, no matter if it is const
}

/*
C++ strings
===========

#include <string>
using namespace std;

string t = "Ghost";
string s; //empty string

for (int i = 0; i != t.size(); i++)
cout << t[i] << endl;

cout << t;
getline(cin, s);

s = t; //sets s to Ghost
s += "!!!"; //concatenates "!!!" to set s to Ghost!!!

if (t < s) //directional comparison: Ghost == Ghost, Ghost < Ghoul, Ghost < Ghostwriter 

*/


/*
C strings
=========

#define _CRT_SECURE_NO_WARNINGS //this line must come BEFORE #include; stops the warnings about strcpy and strcat 
#include <cstring>

cstrings are simply char arrays

char t[10] = {'G', 'h', 'o', 's', 't'}; //allowed to put fewer initializers than number of elements in the array
char t[10] = "Ghost"; //valid way to initialize C array
what t actually looks like: {'G', 'h', 'o', 's', 't', '\0'}

'\0': "zero byte" encodes NUL, which marks the end of the characters of interest in a string

char s[100] = "";
s is an empty string, which would be just {'\0'} bc we don't care about what comes after '\0'

t[2] = 'a'; "Ghost" becomes "Ghast"

strlen(char[]): gets number of characters in a C string array by counting the number of characters until the zero byte 
don't forget #include <cstring>
cannot be used with C++ strings 
ex. cout << strlen(t); prints 5

for (int i = 0; i != strlen(t); i++) //valid but DON'T DO THIS because it's inefficient!
for (int i = 0; t[i] != '\0'; i++) //preferred convention 

cin.getline(char[], int) //creates new array that can hold int elements
cin.getline(s, 100); //won't be tested on an input string longer than the length of array
'\0' must be the last character, so user can only type 99 characters to store in s

strcat(cstring original, cstring b concatenate);
strcat(s, "!!!"); //s is now "Ghost!!!"

s = t; //error! arrays CANNOT be assigned; need a loop that assigns character by character until it gets to '\0' OR strcpy()

strcpy(cstring destination, cstring source); //copies one cstring's array elements into another cstring
strcpy(s, t);  //destination array must be big enough to hold what's being copied
strcpy(t, "abcdefghij"); //INVALID bc t does not have enough space

strcmp(cstring a, cstring b); //returns an int 
								negative if a comes before b
								0 if a is equal to b
								positive if a comes after b

Does a come before b?
	if(t < s) //compiles, but doesn't do what you want --> use strcmp(cstring a, cstring b)
	if (strcmp(t, s) < 0) //VALID 

Does a equal b?
	if (strcmp(a, b)) //INVALID because strcmp() returns an int, not bool (always opposite result: 0 --> false, nonzero --> true)
	if (strcmp(a, b) == 0) //VALID

C++ strings: a OPERATOR b
C string:    strcmp(a, b) OPERATOR 0


void f(const char cs[]) {...}

int main() {
	string s = "Hello";
	f(s); //won't compile bc s is a C++ string, not a C string
	f(s.c_str()); //valid

	char t[10] = "Ghost";
	s = t; //s is now "Ghost"

	s = "Wow";
	t = s; //INVALID! won't compile
	t = s.c_str(); //INVALID! won't compile
	strcpy(t, s.c_str()); // valid, t is now "Wow"
}

*/

void attendance() {
	const int NWEEKS = 5;
	const int NDAYS = 7;

	int attendance[NWEEKS][NDAYS];

	cout << attendance[2][5];

	for (int w = 0; w < NWEEKS; w++) {
		int t = 0;
		for (int d = 0; d < NDAYS; d++) //row-by-row processing 
			t += attendance[w][d];
		cout << "The total for week " << w << " is " << t << endl;
	}

	const string dayNames[NDAYS] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" };
	int grandTotal = 0;
	for (int d = 4 /* Friday */; d < NDAYS; d++) {
		int t = 0;
		for (int w = 0; w < NWEEKS; w++)
			t += attendance[w][d];
		cout << "The total for " << dayNames[d] << " is " << t << endl;
		grandTotal += t;
	}
	cout << "Over the course of " << NWEEKS << " weeks, weekend attendance was " << grandTotal << endl;
}

double computeMean(const int a[], int n);
double meanForADay(const int a[][7], int nRows, int dayNumber);

double meanForADay(const int a[][7], int nRows, int dayNumber) { //must specify remaining dimensions
	if (nRows <= 0)
		return 0;
	int total = 0;
	for (int r = 0; r < nRows; r++)
		total += a[r][dayNumber];
	return static_cast<double>(total) / nRows;
}

/*
int multiplexChainAttendance[5][7][10][16]; //i have 10 multiplexes, each has 16 screen rooms

passing to a function:
void f(int b[][7][10]][16], ...)
*/

char pets[5][7] = { "cat", "mouse", "eel", "ferret", "horse" };

const int MAX_WORD_LENGTH = 6;
int countLength(const char a[][MAX_WORD_LENGTH + 1], int n, int targetLength);

void main1() {
	const int MAX_PETS = 5;
	char pets[MAX_PETS][MAX_WORD_LENGTH + 1] = { "cat", "mouse", "eel", "ferret", "horse" };
	cout << countLength(pets, MAX_PETS, 5); //how many 5-character strings?
}

int countLengthCSTRING(const char a[][MAX_WORD_LENGTH + 1], int n, int targetLength) {
	int total = 0;
	for (int k = 0; k < n; k++) {
		if (strlen(a[k]) == targetLength) //there is no way to select an entire column
			total++;
	}
	return total;
}

int countLength(const string a[], int n, int targetLength) {
	int total = 0;
	for (int k = 0; k < n; k++) {
		if (a[k].size() == targetLength) 
			total++;
	}
	return total;
}

/*
Pointers:
	-another way to implement passing-by-reference
	-traverse arrays
	-manipulate dynamic storage
	-represent relationships in data structures
*/

void polarToCartesian(double rho, double theta, double* xx, double* yy);

int main() {
	double r;
	cin >> r;
	double angle;
	cin >> angle;
	double x;
	cin >> x;
	double y;
	cin >> y;
	polarToCartesian(r, angle, &x, &y); //&x means generate a pointer to x 
}

void polarToCartesian(double rho, double theta, double* xx, double* yy) {
	*xx = rho * cos(theta); //*xx means follow the pointer xx
	*yy = rho * sin(theta);
}

/*	

double&		means		reference-to-double			or			another name for some double
double*		means		pointer-to-double			or			the-address-of-some-double
&x			means		generate a pointer to x		or			address of x
*p			means		follow the pointer p		or			the object that p points to


double a = 3.2;
double b = 5.1;
double* p = &a; //valid, p gets the pointer of a
double* q = 7.6; //INVALID 
double d = p; //INVALID
double d = *p //valid, *p refers to the double that p points to
double& dd = d; //valid, dd is a reference not a pointer

p = b; //INVALID 
p = &b; //valid, assigns one pointer to another (p gets the pointer of b)
*p = b; //valid, assigns one double to another (the object that p points to is now b)

*p += 4; //*p = *p + 4	
int k = 7;
p = &k; //INVALID because &k generates a pointer to an INT, and p is a pointer to a DOUBLE
		//a pointer to an int cannot be converted to a pointer to a double 

int* z = &k; //valid, z is an int pointer that now points to k

cout << (k * b); //valid, 2 doubles
cout << (k * p); //INVALID, can't multiply an int and a pointer 
cout << (k * *p); //valid, double multiplied by the double that p points to
cout << (*z**P); //valid, the double that z points to multiplied by the double that p points to

double* q;
q = 4.7; //INVALID, undefined behavior because q is uninitialized
q = p; //valid, because p is a pointer to the double b

double* r = &a; 
*r = b; //valid, the double that r points to is now b

if (p == r) //FALSE bc we are comparing the pointers' memory address (p points to b, r points to a), not the doubles they point to
if (p == q) //TRUE bc both point to the double b
if (*p == *r) //TRUE 




const int MAXSIZE = 5;
double da[MAXSIZE];
int k;
double* dp;

for (k = 0; k < MAXSIZE; k				for (dp = &da[0]; dp < &da[MAXSIZE]; dp++)					for (dp = da; dp < da + MAXSIZE; dp++)
	da[k] = 3.6;							*dp = 3.6; //*(&da[0]) == da[0] bc *& cancel out			*dp = 3.6; //*(&da[0]) == da[0] bc *& cancel out

we assigned to dp the address of da[0] (may look like an integer, but not actually type int)
&da[MAXSIZE] is NOT out of bounds! it's a valid pointer but trying to follow that pointer leads to undefined behavior
dp++ is valid because: 
	dp = dp + 1;
	dp = &da[0] + 1;
	dp = &da[0 + 1];
	dp = &da[1];

incrementing pointers: 
&a[i] + j ==> &a[i + j];
&a[i] - j ==> &a[i - j];
NOTE: machine language translation for dp++ means add 8 bytes to the address that dp contains (but we don't need to use dp +=8; compiler does it)

comparing pointers: 
&a[i] < &a[j] ==> i < j
NOTE: don't compare 2 pointers that point to different arrays (compiler picks addresses for each array)

a array pointer without an index points to the 0th element of an array:
a <==> &a[0]
&a[MAXSIZE] <==> a + MAXSIZE because: 
	&a[5] 
	&a[0 + 5]
	&a[0] + 5
	a + 5

********************pointer algebra summary**********************
*&x ==> x
&a[i] + j ==> &a[i + j]
&a[i] < &a[j] ==> i < j
a <==> &a[0]
p[i] ==> *(p + i)

*****************************************************************
		         v same thing as const string a[]
int lookup(const string* a, int n, string target) {
	... a[k] ...
}
int main() {
	string sa[5] = { "cat", "mouse", "eel", "ferret", "horse" };
	int i = lookup(sa, 5, "eel");
	int j = lookup(&sa[0], 5, "eel");
	int m = lookup(sa + 1, 3, "ferret");
				    ^ same things as &sa[1]
}


*/






