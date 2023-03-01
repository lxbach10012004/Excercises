#include<bits/stdc++.h>
using namespace std;

int m, n, k, x, y;

struct coordinate{
	bool opened = 0;
	int val = 0;
};

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

void printGraph(vector< vector <coordinate> > graph, bool gameOver){
	cout << "  ";
	for(int j = 0; j < n; j++)
		cout << j << " ";
	cout << endl;
	if(!gameOver){
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
		for(int i = 0; i < m; i++){
			cout << i << " ";
			for(int j = 0; j < n; j++){
				if(graph[i][j].val != -1)
					cout << graph[i][j].val << " ";
				else cout << "* ";
			}
			cout << endl;
		}
	}
}

void playMinesweeper(){
	input();
	vector< vector <coordinate> > graph = generateGraph();
	bool gameOver = 0;
	while(!gameOver){
		check();
		if(graph[x][y].val == -1){
			gameOver = 1;
		}
		else{
			int numMines = 0;
			for(int i = x - 1; i <= x + 1; i++){
				for(int j = y - 1; j <= y + 1; j++){
					if(i >= 0 && i < m && j >= 0 && j < n && graph[i][j].val == -1)
						numMines++;
				}
			}
			graph[x][y].val = numMines;
			graph[x][y].opened = 1;
		}
		printGraph(graph, gameOver);
	}
	
}

int main(){
	playMinesweeper();
	return 0;
}
