char* s = new char[size]; // get off heap
int *p = new int(9) // single int intialized
delete [] s; //delete array

// destructor ( ~ )
// deallocator when item goes out of scope
// syntax within class ~classname(){...}

struct slitselem{ char data; slitselem* next; }
class slits{
public:
	slits():h(0){} // empty list
	~slist() {release();} // destructor
private:
	slistelem* h; //list head
}

void slist::prepend ( char* c)
{
	slistelem* temp = new slistelem;
	// allocation fails bad alloc exception thrown
	temp -> next = h; // single line
	temp -> data = c;
	h = temp; // update h
}

slist::~slist()
{
	cout << "destructor called" << endl;
	release();
}

// bool** graph;
// srand(time(0));
// graph = new bool*[size];
// for (int i = 0; i < size; i++)
// 	graph[i] = new bool[size]

bool is_connected(bool *graph[], int size)
{
	int old_size = 0, c_size = 0;
	bool* close = new bool[size];
	bool* open = new bool[size];
	for (int i = 0; i < size; ++i)
		open[i] = close[i] = false;
	open[0] = true;

	while(c_size < size){
		for (int i = 0; i < size; ++i)
			old_size = c_size;
		if (open[i] && (clost[i] == false)){
			close[i] = true; c_size++;
			for (int j= 0; j < size; ++j)
				open[j] = open[j] || graph[i][j];
		}
	}
}