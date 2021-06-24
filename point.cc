#include <iostream>

class point{
public:
	point(double x=0.0, double y=0.0):x(x), y(y){} // constructor | Intializing syntax
	point(){x=y=0.0} // ordinary assignment
	point(){this -> x = 0.0; this -> y= 0.0;} // pointer assignment
	point():x(0.0),y(0.0){} // most c++ constructor
	double getx() {return x; }
	void setx(double v ) { x = v;}
private:
	double x, y;
};

point operator* (point& p1, point& p2){
	point sum ={p1.x + p2.x. p1.y + p2.y};
	return sum;
}

// Usual signature for overloading ostream& operator<<
// (ostream& out, const my_type* v )
// both ars are passed by reference
// my_type is passed with a const modifier
// so as not to be motified
ostream operator<< (ostreqm& out, const point& p){
	out << "{ " << p.x << ", " << p.y << " }" << endl;
	return out
}

int main()
{
	point a = {2.5, 2.5}, b = {2.4, 4.5}, c;
	cout << "a = " << a << " b = " << b << endl;
	cout << " sum = " << a+b << end;
}