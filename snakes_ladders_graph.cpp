#include <iostream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

enum State{unvisited, visiting, visited};

struct GraphNode
{
    int value;
    int distance;
    State state;
};

struct SnakesLadders
{
    int start;
    int end;
    SnakesLadders(int _start, int _end) : start(_start), end(_end){};
};

template <class T> class Graph
{
public:
    int nVertices;
    vector<vector<T>> vertices;
    Graph(int _nVertices)
    {
        nVertices = _nVertices;
        vector<T> edge;
        for(int i = 0; i <= nVertices; i++)
        {
            vertices.push_back(edge);
        }
    }
    void addEdge(int start, T end)
    {
        if(start <= nVertices)
        {
            vertices[start].push_back(end);
        }
        else
        {
            //error
        }
    }
    GraphNode BFS(int start, int valueToFind);  //return the vertex
    
private:
    GraphNode BFS(queue<GraphNode> Q, int value);
};

template <> GraphNode Graph<GraphNode>::BFS(queue<GraphNode> Q, int value)
{
    GraphNode graphNode;
    graphNode.state = unvisited;
    graphNode.value = -1;
    //base case
    if(Q.empty())
    {
        //got to the end and didnt find it
        return graphNode;
    }
    else
    {
        graphNode = Q.front();
        Q.pop();
        if(graphNode.value == value)
        {
            graphNode.state = visited;
            return graphNode;
        }
        else
        {
            graphNode.state = visited;
        }
        //push new values onto queue
        for(int i = 0; i < vertices[value].size(); i++)
        {
            if(graphNode.state == unvisited)
            {
                Q.push(vertices[value][i]);
                graphNode.state = visiting;
            }
        }
        graphNode = BFS(Q, value);
        if(graphNode.value == value)
        {
            return graphNode;
        }
    }
    return graphNode;
}

//BFS
template <> GraphNode Graph<GraphNode>::BFS(int start, int valueToFind)
{
    GraphNode graphNode;
    queue<GraphNode> graphNodeQ;
    int nMoves = 0;
    //start at root node, move outwards
    //seed the queue
    if(vertices[start][0].value == valueToFind)
    {
        return vertices[start][0];
    }
    for(unsigned int i = 0; i < vertices[start].size(); i++)
    {
        if(vertices[start][i].state == unvisited)
        {
            vertices[start][i].state = visited;
            vertices[start][i].distance = 1;
            graphNodeQ.push(vertices[start][i]);
        }
    }
    while(!graphNodeQ.empty())
    {
        graphNode = graphNodeQ.front();
        graphNodeQ.pop();
        cout << "Visiting node " << graphNode.value << endl;
        if(graphNode.value == valueToFind)
        {
            cout << "n rolls = " << graphNode.distance << endl;
            return graphNode;
        }
        for(unsigned int i = 0; i < vertices[graphNode.value].size(); i++)
        {
            if(vertices[graphNode.value][i].state == unvisited)
            {
                vertices[graphNode.value][i].state = visited;
                vertices[graphNode.value][i].distance = graphNode.distance + 1;
                graphNodeQ.push(vertices[graphNode.value][i]);
            }
        }
    }
    
    cout << "Value " << valueToFind << " not found in graph" << endl;
    return graphNode;
}

map<int, int> createSnakesLaddersMap(vector<SnakesLadders> ladders, vector<SnakesLadders> snakes)
{
    vector<SnakesLadders>::iterator i;
    map<int,int> snakesLaddersMap;
    
    for(i = ladders.begin(); i != ladders.end(); i++)
    {
        snakesLaddersMap.insert(pair<int,int>(i->start,i->end));
    }
    for(i = snakes.begin(); i != snakes.end(); i++)
    {
        snakesLaddersMap.insert(pair<int,int>(i->start,i->end));
    }
    return snakesLaddersMap;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    int nVertices = 100;
    
    vector<SnakesLadders> ladders;
    vector<SnakesLadders> snakes;
    
    ladders.push_back(SnakesLadders(1,38));
    ladders.push_back(SnakesLadders(4,14));
    ladders.push_back(SnakesLadders(9,31));
    ladders.push_back(SnakesLadders(21,42));
    ladders.push_back(SnakesLadders(28,84));
    ladders.push_back(SnakesLadders(51,67));
    ladders.push_back(SnakesLadders(72,91));
    ladders.push_back(SnakesLadders(80,99));
    
    snakes.push_back(SnakesLadders(98,79));
    snakes.push_back(SnakesLadders(95,75));
    snakes.push_back(SnakesLadders(93,73));
    snakes.push_back(SnakesLadders(87,36));
    snakes.push_back(SnakesLadders(98,79));
    snakes.push_back(SnakesLadders(62,18));
    snakes.push_back(SnakesLadders(64,60));
    snakes.push_back(SnakesLadders(54,34));
    snakes.push_back(SnakesLadders(17,7));
    
    map<int,int> snakesLaddersMap = createSnakesLaddersMap(ladders, snakes);
    
    GraphNode boardNode;
    Graph<GraphNode> board(100);
    
    //create graph:
    for(int i = 0; i <= 100-6; i++)
    {
        for(int j = 1; j <= 6; j++)
        {
            boardNode.state = unvisited;
            if(snakesLaddersMap[i+j])
            {
                boardNode.value = snakesLaddersMap[i+j];
            }
            else
            {
                boardNode.value = (i+j);
            }
            board.addEdge(i, boardNode);
        }
    }
    
    //search for 100
    board.BFS(0,100);
    return 0;
}
