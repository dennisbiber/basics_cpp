// Dennis Biber
// June 23, 2021
// My C++ project intro to c++

#include <iostream>
using namespace :: std;
const double m_to_k = 1.609;

inline double convert(int mi){ return (mi * m_to_k);}

int main(void)
{
	int miles = 1;

	while (miles != 0) {
		cout << "Input distance in miles or 9 to terminate: ";
		cin >> miles;

		// the << acts like + in concatinating strings like python
		cout << "\nDistance is " << convert(miles) << " km." << endl;
	}
	// endl is same as adding a \n
	cout << endl;
}