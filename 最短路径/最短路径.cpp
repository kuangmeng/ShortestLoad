//
//  main.cpp
//  ���·��
//
//  Created by ������ on 16/4/7.
//  Copyright ? 2016�� HIT. All rights reserved.
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
	output << "����ͼ�Ķ������Ϊ:" << setw(5)<<G->n<< endl;
	output << "������Ϣ��";
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
	output<< "*****����ͼ�ڽӾ����ѽ��ɣ�*****" << endl;
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
		output<< "Sorry!��" << head << "��" << tail << "֮��û��ͨ·��" << endl;
		return;
	}
	stack<int> m;
	while (to != from){
		m.push(to);
		if (m.size() > G.n){
			output << "���ڸ������޷����·����"<<endl;
			return;
		}
		to = path[from][to];
	}
	m.push(from);
	output << "��" << head << "��" << tail << "���·����";
	while (!m.empty()){
		output << setw(5)<<G.vertex[m.top()];
		m.pop();
	}
	output <<"   "<< "���·�����ȣ�" << num << endl;
}
int main(int argc, const char * argv[]){
	MTGraph *G = new MTGraph;
	int path[MAX][MAX], dist[MAX][MAX];
			CreateMTGraph(G);
			Floyd(*G, dist, path);
			Elem head, tail;
			cout << "������������ֹ�㣺";
			cin >> head >> tail;
			output << "�û�ѡ���������ֹ�㣺" << head << "-->" << tail << endl;
			CoutPath(head, tail, *G, path, dist);
	return 0;
}

