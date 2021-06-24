#include <iostream>
#include <vector>
#include <ctime>
#include <iterator>
#include <string>
#include <list>

using namespace ::std;

enum class Player { GREEN, RED };

struct node {
	char value;
	list<int> adj;
};

class Board {
private:
	int size;
	int total;
	vector<node> board;
	string lines;
public:
	//constructors
	Board() {}
	Board(int size) :size(size),total(size*size) {
		board.resize(total);
		for (int n = 0; n < total; n++){
				board[n].value = '.';
				adj_list(n);
			}
		lines = "\\";
		for (int i = 1; i < size; i++) {
			lines += " / \\";
		}
	}
	//prints out the board for viewing
	void print_board() {
		cout << "  0";

		for (int i = 1; i < size; i++)
			if (i < 10) {
				cout << " r " << i;
			}
			else {
				cout << " r" << i;
			}
			cout << endl;

			//print first line
			cout << "0 " << board[0].value;
			for (int i = 1; i < size; i++)
				cout << " - " << board[i].value;
			cout << endl;

			//print rest of lines
			string indent = "";
			for (int i = 1; i < size; i++) {
				indent += ' ';
				cout << indent << "b " << lines << endl;
				if (i < 10) {
					indent += ' ';
					cout << indent << i << ' ' << board[i*size].value;
				}
				else {
					cout << indent << i << ' ' << board[i*size].value;
					indent += ' ';
				}
				for (int j = 1; j < size; j++)
					cout << " - " << board[i*size+j].value;
				cout << endl;
			}
			cout << endl;
	}
	//function to make a placement on the board
	bool place(int x, int y, Player p) {
		if (valid_place(x, y) && board[x*size+y].value == '.') {
			if (p == Player::RED)
				board[x*size+y].value = 'B';
			else
				board[x*size+y].value = 'R';
			return true;
		}
		return false;
	}
	//deletes a move
	void badMove(int n) {
		board[n].value = '.';
	}
	//checks for a win
	bool check_win(Player p) {
		char check_char = 'x';
		bool begin_edge = false;
		vector<int> begin_v;
		bool end_edge = false;
		vector<int> end_v;
		if (p == Player::RED) { //if player is RED
			check_char = 'B';
			//loop through left edge to check for RED's
			for (int i = 0; i < size; i++) {
				int j = 0;
				if (board[i*size+j].value == check_char) {
					begin_edge = true;
					begin_v.push_back(i*size+j);
				}
			}
			//loop through right edge to check for RED's
			for (int i = 0; i < size; i++) {
				int j = size - 1;
				if (board[i*size+j].value == check_char) {
					end_edge = true;
					end_v.push_back(i*size+j);
				}
			}
		}
		else { //if player is GREEN
			check_char = 'R';
			//loop through top edge to check for GREEN's
			for (int j = 0; j < size; j++) {
				int i = 0;
				if (board[i*size+j].value == check_char) {
					begin_edge = true;
					begin_v.push_back(i*size+j);
				}
			}
			//loop through bottom edge to check for GREEN's
			for (int j = 0; j < size; j++) {
				int i = size - 1;
				if (board[i*size+j].value == check_char) {
					end_edge = true;
					end_v.push_back(i*size+j);
				}
			}
		}
		//if there is not a placement on the beginning edge and ending edge return false
		if (!begin_edge || !end_edge)
			return(false);
		bool result = false;
		//check for paths from all beginning nodes to all ending nodes
		for (auto i_it = begin_v.begin(); i_it != begin_v.end(); i_it++) {
			for (auto j_it = end_v.begin(); j_it != end_v.end(); j_it++) {
				result = check_path(*i_it, *j_it, p);
				if (result == true)
					return true;
			}
		}
		return false;
	}
	//function to get all empty spots on the board
	vector<int> getEmpty() {
		vector<int> empty_spots;
		for (int n = 0; n < total; n++) {
			if (board[n].value == '.')
				empty_spots.push_back(n);
		}
		return empty_spots;
	}
private:
	//checks for a path from one vertex to another
	bool check_path(int a, int b, Player p) {
		char check_char = 'x';
		if (p == Player::RED)
			check_char = 'B';
		else
			check_char = 'R';
		vector<bool> visited(total,false);
		list<int> queue;
		visited[a] = true;
		queue.push_back(a);
		int x;
		while (!queue.empty()) {
			x = queue.front();
			queue.pop_front();
			list<int> X = board[x].adj;
			for (int v : X) {
				if (board[v].value == check_char) {
					if (v == b)
						return true;

					if (!visited[v]) {
						visited[v] = true;
						queue.push_back(v);
					}
				}
			}
		}
		return false;
	}
	//checks to see placement is valid
	bool valid_place(int x, int y) {
		if ((x < size) && (x >= 0) && (y < size) && (y >= 0))
			return true;
		else
			return false;
	}
	//function to create all adjacency lists
	void adj_list(int n) {
		int i = n / size;
		int j = n % size;
		if (i == 0 && j == 0) { //top left corner
			board[n].adj.push_front(i * size + j + 1);
			board[n].adj.push_front((i + 1) * size + j);
		}
		else if (i == 0 && j == size - 1) { //top right corner
			board[n].adj.push_front(i * size + j - 1);
			board[n].adj.push_front((i + 1) * size + j - 1);
			board[n].adj.push_front((i + 1) * size + j);
		}
		else if (i == size - 1 && j == 0) { //bottom left corner
			board[n].adj.push_front((i - 1) * size + j);
			board[n].adj.push_front((i - 1) * size + j + 1);
			board[n].adj.push_front(i * size + j + 1);
		}
		else if (i == size - 1 && j == size - 1) { //bottom right corner
			board[n].adj.push_front((i - 1) * size + j);
			board[n].adj.push_front(i * size + j - 1);
		}
		else if (i == 0) { //top edge
			board[n].adj.push_front(i * size + j - 1);
			board[n].adj.push_front((i + 1) * size + j - 1);
			board[n].adj.push_front((i + 1) * size + j);
			board[n].adj.push_front(i * size + j + 1);
		}
		else if (j == 0) { //left edge
			board[n].adj.push_front((i - 1) * size + j);
			board[n].adj.push_front((i - 1) * size + j + 1);
			board[n].adj.push_front(i * size + j + 1);
			board[n].adj.push_front((i + 1) * size + j);
		}
		else if (j == size - 1) { //right edge
			board[n].adj.push_front(i * size + j - 1);
			board[n].adj.push_front((i + 1) * size + j - 1);
			board[n].adj.push_front((i + 1) * size + j);
			board[n].adj.push_front((i - 1) * size + j);
		}
		else if (i == size - 1) { //bottom edge
			board[n].adj.push_front((i - 1) * size + j);
			board[n].adj.push_front((i - 1) * size + j + 1);
			board[n].adj.push_front(i * size + j + 1);
			board[n].adj.push_front(i * size + j - 1);
		}
		else { //middle nodes
			board[n].adj.push_front((i - 1) * size + j);
			board[n].adj.push_front((i - 1) * size + j + 1);
			board[n].adj.push_front(i * size + j + 1);
			board[n].adj.push_front(i * size + j - 1);
			board[n].adj.push_front((i + 1) * size + j);
			board[n].adj.push_front((i + 1) * size + j - 1);
		}
	}
};

class AI {
public:
	double WinProb(Board b, Player p, int size) {
		vector<int> empty = b.getEmpty();
		int winCount = 0;
		vector<int> copy;
		for (int k = 0; k < 1000; k++) {
			copy = empty;
			int turn = (p == Player::RED ? 0 : 1);
			while (!copy.empty()) {
				turn = !turn;
				int nextmove = rand() % copy.size();
				if (turn)
					b.place(copy[nextmove] / size, copy[nextmove] % size, Player::GREEN);
				else
					b.place(copy[nextmove] / size, copy[nextmove] % size, Player::RED);
				copy.erase(copy.begin() + nextmove);
			}
			if (b.check_win(p))
				winCount++;
			for (int i = 0; i < empty.size(); i++)
				b.badMove(empty[i]);
		}
		return static_cast<double> (winCount) / 1000;
	}
	int simulation(Board b, Player p, int size) {
		vector<int> empty = b.getEmpty();
		b.print_board();
		for (int i = 0; i < empty.size(); i++) {
			cout << empty[i] << endl;
		}
		double best = 0.0;
		int move_num = empty[0];

		for (int i = 0; i < empty.size(); i++) {
			b.place(empty[i] / size, empty[i] % size, p);
			double moveVal = WinProb(b, p, size);
			if (moveVal > best) {
				move_num = empty[i];
				best = moveVal;
			}
			b.badMove(empty[i]);
		}
		return move_num;
	}

};

class Game {
private:
	Board board;
	Player player1;
	Player computer;
	AI AI_comp;
	int boardsize = 0;
public:
	//constructors
	Game(Board board, AI AI_comp):board(board),AI_comp(AI_comp) {}
	void play() {
		bool winner = false;
		cout << "Let's play a game of Hex!" << endl;
		setup();
		choose_color();
		int turn = (player1 == Player::RED ? 0 : 1);
		while (!winner) {
			turn = !turn;
			if (turn)
				winner = player_turn();
			else
				winner = computer_turn();
		}

		if (turn == 1) {
				cout << "YOU WIN!!";
		}
		else {
				cout << "COMPUTER WINS!!";
		}
	}
private:
	//setup the board with any size input by player
	void setup() {
		cout << "What size of board do you want to play on?  ";
		cin >> boardsize;
		if (boardsize <= 0) {
			do {
				cout << "Sorry board size must be a positive number, try again.";
				cout << endl << "What size of board do you want to play on?  ";
				cin >> boardsize;
			} while (boardsize <= 0);
		}
		board = Board(boardsize);
		cout << "Here's your board:" << endl << endl;
		board.print_board();
	}
	//player chooses their color
	void choose_color() {
		char color = 'x';
		do {
			cout << "What color do you want to be?" << endl << "(enter b for RED and r for GREEN):" << endl;
			cin >> color;
			if (color == 'b' || color == 'B') {
				player1 = Player::RED;
				computer = Player::GREEN;
			}
			else if (color == 'r' || color == 'R') {
				player1 = Player::GREEN;
				computer = Player::RED;
			}
			else {
				cout << "That wasn't valid!" << endl;
				color = 'x';
			}
		} while (color == 'x');
	}
	//player chooses x and y coordinates for their turn
	bool player_turn() {
		int x, y;
		string color;
		while (true) {
			if (player1 == Player::RED)
				color = "RED";
			else
				color = "GREEN";
			cout << color << "'s Turn!\n";
			cout << "Select where you want to play. (x y): \n";
			cin >> x >> y;
			if (board.place(x, y, player1))
				break;
			cout << "Can't Play There Try Again! \n";
		}
		board.print_board();
		return(board.check_win(player1));
	}
	//computer calculates a turn
	bool computer_turn() {
		string color;
		if (computer == Player::RED)
			color = "RED";
		else
			color = "GREEN";
		cout << color << "'s Turn!\n";
		cout << "Waiting for Computer to take Turn.\n";
		int move = AI_comp.simulation(board, computer, boardsize);
		cout << move << endl;
		board.place(move / boardsize, move%boardsize, computer);
		board.print_board();
		return(board.check_win(computer));
	}
};



int main()
{
	srand(time(0)); //seed random generator
	Board newboard; 
	AI New_AI;
	//start game
	Game hex(newboard, New_AI);
	hex.play();
	return 0;
}