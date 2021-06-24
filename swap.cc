/* C swap
void swap(int* i, int* j){
	int temp = *i;
	*i = *j;
	*j = temp
}

void swap_double(double* i, double* j){
	double temp = *i;
	*i = *j;
	*j = temp;
}
*/

#include <iostream>
using namespace std;

inline void swap(int& i, int& j){
	int temp = i;
	i = j;
	i = temp;
}
inline void swap(double& i, double& j){
	double temp = i;
	i = j;
	j = temp;
}

int main()
{
	int m=5, n-10;
	double x = 5.3, y = 10.6;
	cout << "inputs: " << m << ", " << n << endl;
	swap(m, n);
	cout << "inputs: " << m << ", " << n << endl;
	cout << "double inputs: " << x << ", " << y << endl;
	swap(x, y);
	cout << "double inputs: " << x << ", " << y << endl;
}