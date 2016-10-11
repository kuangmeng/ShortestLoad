//
//  main.cpp
//  最短路径
//
//  Created by 匡盟盟 on 16/4/7.
//  Copyright ? 2016年 HIT. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <stack>
#include <fstream>
#include <iomanip>
#define MAX 60
#define INF 65535
typedef char Elem;
using namespace std;
typedef struct {
	int n;
	int edge[MAX][MAX];
	Elem vertex[MAX];
} MTGraph;
ifstream input("input.txt");
ofstream output("output.txt",ios::app);
int Locate(Elem vertex, MTGraph *G) {
	for (int i = 0; i<G->n; i++) {
		if (G->vertex[i] == vertex) return i;
	}
	return -1;
}
void CreateMTGraph(MTGraph *G) {
	 G->n = 60;
	output << "无向图的顶点个数为:" << setw(5)<<G->n<< endl;
	output << "顶点信息：";
	for (int i = 0; i<6; i++) {
		for (int j = 0; j < 10; j++) {
			input >> G->vertex[i*10+j];
			output << setw(6) << G->vertex[i*10+j];
		}
		output << endl;
	}
	output << endl;
	for (int i = 0; i<G->n; i++){
		for (int j = 0; j<G->n; j++){
			G->edge[i][j] = INF;
		}
	}
	for (int i = 0; i < G->n; i++) {
		for (int j = 0; j < i; j++) {
			input >> G->edge[i][j];
		}
	}
	output<< "*****无向图邻接矩阵已建成！*****" << endl;
}
void Floyd(MTGraph &G, int dist[][MAX], int path[][MAX]) {
	for (int i = 0; i<G.n; i++){
		for (int j = 0; j<G.n; j++){
			if (G.edge[i][j]!=INF) dist[i][j] = G.edge[i][j];
			else dist[i][j] = INF;
			path[i][j] = i;
		}
	}
	for (int k = 0; k<G.n; k++){
		for (int i = 0; i<G.n; i++){
			for (int j = 0; j<G.n; j++){
				if (!(dist[i][k] == INF || dist[k][j] == INF)&& dist[i][j]>dist[k][j] + dist[i][k]) {
					dist[i][j] = dist[i][k] + dist[k][j];
					path[i][j] = path[k][j];
				}
			}
		}
	}
}
void CoutPath(Elem head, Elem tail, MTGraph &G, int path[][MAX], int dist[][MAX]) {
	int from = Locate(head, &G);
	int to = Locate(tail, &G);
	int num = dist[from][to];
	if (num >= INF){
		output<< "Sorry!从" << head << "到" << tail << "之间没有通路！" << endl;
		return;
	}
	stack<int> m;
	while (to != from){
		m.push(to);
		if (m.size() > G.n){
			output << "存在负环！无法输出路径！"<<endl;
			return;
		}
		to = path[from][to];
	}
	m.push(from);
	output << "从" << head << "到" << tail << "最短路径：";
	while (!m.empty()){
		output << setw(5)<<G.vertex[m.top()];
		m.pop();
	}
	output <<"   "<< "最短路径长度：" << num << endl;
}
int main(int argc, const char * argv[]){
	MTGraph *G = new MTGraph;
	int path[MAX][MAX], dist[MAX][MAX];
			CreateMTGraph(G);
			Floyd(*G, dist, path);
			Elem head, tail;
			cout << "请输入搜索起、止点：";
			cin >> head >> tail;
			output << "用户选择的搜索起、止点：" << head << "-->" << tail << endl;
			CoutPath(head, tail, *G, path, dist);
	return 0;
}

