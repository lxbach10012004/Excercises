#include<bits/stdc++.h>
using namespace std;

int m, n, k, x, y;

struct coordinate{
	bool opened = 0;
	int val = 0;
};

vector< vector <coordinate> > graph;

void input(){
	cout << "Enter number of rows: ";
	cin >> m;
	cout << "Enter number of columns: ";
	cin >> n;
	cout << "Enter number of mines: ";
	cin >> k;
}

void check(){
	cout << "Enter x, y coordinates: ";
	cin >> x >> y;
}

vector< vector <coordinate> > generateGraph(){
	vector< vector <coordinate> > graph(m, vector< coordinate >(n));
	srand(time(NULL));
	int count = 0;
	while(count < k){
		int i = rand() % m;
		int j = rand() % n;
		if(graph[i][j].val != -1){
			graph[i][j].val = -1;
			count++;
		}
	}
	return graph;
}

void printGraph(int gameOver){
	
	if(gameOver == 0){
		cout << "  ";
		for(int j = 0; j < n; j++)
			cout << j << " ";
		cout << endl;
		for(int i = 0; i < m; i++){
			cout << i << " ";
			for(int j = 0; j < n; j++){
				if(graph[i][j].opened == 1)
					cout << graph[i][j].val << " ";
				else cout << "- ";
			}
			cout << endl;
		}
	}
	else{
		if(gameOver == 1)cout << "YOU'RE DEAD!\n";
		else cout << "YOU WIN!\n";
		cout << "  ";
		for(int j = 0; j < n; j++)
			cout << j << " ";
		cout << endl;
		for(int i = 0; i < m; i++){
			cout << i << " ";
			for(int j = 0; j < n; j++){
				if(graph[i][j].val != -1){
					if(!graph[i][j].opened) cout << '-' << " ";
					else cout << graph[i][j].val << " ";
				}
				else cout << "* ";
			}
			cout << endl;
		}
	}
	cout << endl;
}

int countMines(int x, int y){
	int numMines = 0;
	for(int i = x - 1; i <= x + 1; i++){
		for(int j = y - 1; j <= y + 1; j++){
			if(i >= 0 && i < m && j >= 0 && j < n && graph[i][j].val == -1)
				numMines++;
		}
	}
	graph[x][y].val = numMines;
	graph[x][y].opened = 1;
	return numMines;
}

void clearOut(int x, int y){
	if(x < 0 || x >= m || y < 0 || y >=m || graph[x][y].opened)
		return;
	int mines = countMines(x, y);
	if(mines != 0) return;
	for(int i = x - 1; i <= x + 1; i++){
		for(int j = y - 1; j <= y + 1; j++){
			clearOut(i, j);
		}
	}
	return;
}

bool win(){
	int count = 0;
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			if(graph[i][j].opened){
				count++;
			}
		}
	}
	if(count == m * n - k) return 1;
	else return 0;
}

void playMinesweeper(){
	input();
	graph = generateGraph();
	int gameOver = 0;
	while(gameOver == 0){
		check();
		if(graph[x][y].val == -1){
			gameOver = 1;
		}
		else{
			clearOut(x, y);
			if( win() ) gameOver = 2;
		}
		printGraph(gameOver);
	}
	
}

int main(){
	playMinesweeper();
	return 0;
}
