#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace :: std;
const int sides = 6;
inline int r_sides(){ return(rand() % sides + 1);}

int main(void)
{
	const int n_dice = 2;
	int d1, d2;
	srand(clocl());
	cout << "\nEnter number of trials: ";
	int trials;
	cin >> trials; // comparable to scanf
	int* outcomes = new int[n_dice * sides+1];
	// malloc replaced by "new"
	// free replaced by "delete"
	for (int j = 0; j < trials; ++j)
		outcomes[(d1 = r_sides()) + (d2 = r_sides())]++;
	cout << "probability\n";
	for (int j = 2; j < n_dice * sides +1; ++j)
		cout << "j = " << j << " p - " << static_cast<double>(outcomes[j])/trials << endl;	
}

