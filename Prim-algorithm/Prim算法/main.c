#include "myhead.h"

int main(int args, char* argv[]) {
	MGraph* g;
	edge tree[M - 1];
	g = (MGraph*)malloc(sizeof(MGraph));
	if (g) {
		char filename[100] = "Text.txt";
		int c = 0;// c == 0为无向图
		creat(g, filename, c);
		prim(*g, tree);
	}
	return 0;
}

void creat(MGraph* g, char* filename, int c) {
	int i, j, k, w;
	FILE* fp;
	fopen_s(&fp, filename, "r");
	if (fp) {
		fscanf_s(fp, "%d%d", &g->n, &g->e);
		// 初始化顶点
		for (i = 0; i < g->n; i++) {
			fscanf_s(fp, "%1s", &g->vexs[i], M);
		}

		// 初始化所有边
		for (i = 0; i < g->n; i++) {
			for (j = 0; j < g->n; j++) {
				if (i == j) g->edges[i][j] = 0;
				else g->edges[i][j] = FINITY;
			}
		}
		
		// 初始化有值的边和权值
		for (k = 0; k < g->e; k++) {
			fscanf_s(fp, "%d%d%d", &i, &j, &w);
			g->edges[i][j] = w;
			if (c == 0) g->edges[j][i] = w;
		}
		fclose(
			fp);
	}
	else g->n = 0;
}

void prim(MGraph g, edge* tree) {
	edge x;
	int d, min, j, k, s, v;
	for (v = 1; v <= g.n - 1; v++) {
		tree[v - 1].begin = 0;
		tree[v - 1].end = v;
		tree[v - 1].length = g.edges[0][v];
	}

	for (k = 0; k < g.n - 2; k++) {
		min = tree[k].length;
		// s 为寻找到的最小两栖边的下标
		s = k;
		for (j = k + 1; j < g.n - 1; j++) {
			if (min > tree[j].length) {
				min = tree[j].length;
				s = j;
			}
		}
		v = tree[s].end;
		// 通过交换将当前最小边加入到tree中
		x = tree[s];
		tree[s] = tree[k];
		tree[k] = x;
		
		//由于新顶点的加入修改两栖边的信息
		for (j = k + 1; j < g.n - 2; j++) {
			d = g.edges[v][tree[j].end]; // tree[j].end 表明未加入边集tree中的剩下的顶点
			if (d < tree[j].length) {
				tree[j].length = d;
				tree[j].begin = v; 
			}
		}
	}

	for (j = 0; j < g.n - 1; j++) {
		printf("%c --- %c %d\n", g.vexs[tree[j].begin], g.vexs[tree[j].end], tree[j].length);
	}
	printf("root : %c", g.vexs[0]);
}