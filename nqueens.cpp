#include <iostream>
#include <vector>

using namespace std;

void calculateAllowedPositions(int prevPos[2], vector<vector<bool>> &LUT, int N, int column) {
    if(column > N-1)
    {
        return;
    }
    int counter = 1;
    for(int i = column; i < N; i++)
    {
        LUT[prevPos[0]][i] = false; //set all in that row false
        if(prevPos[0]+counter < N)
        {
            LUT[prevPos[0]+counter][i] = false; //lower diag
        }
        if(prevPos[0]-counter >= 0)
        {
            LUT[prevPos[0]-counter][i] = false; //upper diag
        }
        counter++;
    }
    return;
}

vector<vector<int>> findNQueens(int column, vector<vector<bool>> LUT,
                                vector<vector<int>> prevPositions, int prevPos[2], int N,
                                int nQueens){
    
    if(nQueens > 0){    //not on first call
        vector<int> newColumn;
        newColumn.push_back(prevPos[0]);
        newColumn.push_back(prevPos[1]);
        prevPositions.push_back(newColumn);
    }
    
    if(nQueens == N){
        return prevPositions;
    }
    if(column > N-1){
        return prevPositions;
    }
    
    if(nQueens > 0)
    {
        calculateAllowedPositions(prevPos, LUT, N, column);
    }
    
    for(int i = 0; i < N ; i++){
        if(LUT[i][column] == true){
            prevPos[0] = i; //row
            prevPos[1] = column;
            vector<vector<int>> positions = findNQueens(column+1, LUT, prevPositions, prevPos, N, nQueens+1);
            if(positions.size() == N)
            {
                return positions;
            }
        }
    }
    
    //no allowed positions in column
    return prevPositions;
}

vector<vector<int>> findNQueens(int N){
    vector<vector<int>> prevPositions;
    vector<int> newColumn;
    vector<vector<bool>> LUT(N,vector<bool>(N,true)); //init NxN vector of falses
    vector<vector<int>> positions = findNQueens(0, LUT, prevPositions, new int[2], N, 0);
    return positions;
}

int main(int argc, const char * argv[]) {
    int nQueens = 10;
    vector<vector<int>> positions = findNQueens(nQueens);
    for(int i = 0; i < nQueens; i++)
    {
        vector<int> pos = positions[i];
        cout << "( " << pos[0] << ", " << pos[1] <<") "<< endl;
    }
    
}
