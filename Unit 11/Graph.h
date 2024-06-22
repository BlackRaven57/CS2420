#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

template <typename Type>
class Graph;

template <typename Type>
ostream& operator << (ostream & out, const Graph<Type> &g);

template <typename Type>
class Graph {
private:
	vector<Type> verticies;
	vector<vector<Type>> edges;

public:
	Graph();
	void addVertex(Type vertex);
	void addEdge(Type, Type);
	int getVertexPos(Type item);
	int getNumVertices() const;
	bool isEdge(Type, Type);
	friend ostream& operator << <>(ostream& out, const Graph<Type>& g);
	vector<Type>getPath(Type, Type);
};

template<typename Type>
Graph<Type>::Graph() {

}

template <typename Type>
void Graph<Type>::addVertex(Type vertex) {
	verticies.push_back(vertex);
	vector<Type> lst;
	edges.push_back(lst);
}

template<typename Type>
int Graph<Type>::getNumVertices() const {
	return verticies.size();
}

template <typename Type>
int Graph<Type>::getVertexPos(Type item) {
	for (unsigned int i = 0; i < verticies.size(); i++) {
		if (item == verticies[i]) {
			return i;
		}
	}
	return -1;
}

template <typename Type>
void Graph<Type>::addEdge(Type source, Type target) {
	int scrPos = getVertexPos(source);
	if (scrPos < 0) {
		throw runtime_error("Vertex not found");
	}
	edges[scrPos].push_back(target);
}

template <typename Type>
bool Graph<Type>::isEdge(Type source, Type dest) {
	int scrPos = getVertexPos(source);
	if (scrPos < 0) {
		throw runtime_error("Vertex not found");
	}
	for (unsigned int i = 0; i < edges[scrPos].size(); i++) {
		if (edges[scrPos][i] == dest) {
			return true;
		}
	}
	return false;
}

template <typename Type>
ostream& operator << (ostream& out, const Graph<Type>& g) {
	for (unsigned int i = 0; i < g.verticies.size(); i++) {
		out << g.verticies[i] << ": ";
		for (unsigned int e = 0; e < g.edges[i].size(); e++) {
			out << g.edges[i][e] << " ";
		}
		out << endl;
	}
	return out;
}

template <typename Type>
vector<Type> Graph<Type>::getPath(Type source, Type dest) {
	vector<Type> solution;
	queue<Type> open;
	open.push(source);
	vector<Type> visited;
	int parents[verticies.size()];
	for (int i = 0; i < verticies.size(); i++) {
		parents[i] = -1;
	}
	int pPos = getVertexPos(source);
	int pos;
	int dPos = getVertexPos(dest);
	bool vis;

	// Going through the graph to find parents
	while (!open.empty()) {
		// Setting curr to front and marking it as visited
		Type curr = open.front();
		open.pop();
		visited.push_back(curr);
		// Setting position value
		pos = getVertexPos(curr);

		// Finding and setting children of curr
		vector<Type> children;
		for (int i = 0; i < verticies.size(); i++) {
			if (i != pos) {
				if (isEdge(curr, verticies[i])) {
					children.push_back(verticies[i]);
				}
			}
		}

		// Looping through children of curr
		for (int i = 0; i < children.size(); i++) {
			int cPos = getVertexPos(children[i]);
			vis = false;
			// Checking if it's in visited
			for (int j = 0; j < visited.size(); j++) {
				if (visited[j] == children[i]) {
					vis = true;
					break;
				}
			}
			if (!vis) {
				open.push(children[i]);
			}
			if (parents[cPos] == -1) {
				parents[cPos] = pos;
			}
		}
		pPos = getVertexPos(curr);
	}

	// Find the solution
	pos = dPos;
	while (pos != getVertexPos(source)) {
		solution.push_back(verticies[pos]);
		pos = parents[pos];
		if (pos == 0) {
			break;
		}
	}

	// Reverse the solution
	vector<Type> fSolution;
	fSolution.push_back(source);
	for (int i = solution.size() - 1; i > -1; i--) {
		fSolution.push_back(solution[i]);
	}
	return fSolution;
}

