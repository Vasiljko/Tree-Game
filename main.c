#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct StackNode {
	int id;
	struct StackNode* next;
};

struct Stack {
	int sz;
	struct StackNode* top;
};

struct QueueNode {
	int id;
	struct QueueNode* next;
};

struct Queue {
	int sz;
	struct QueueNode* front;
	struct QueueNode* rear;
};

const int INF = 10000;

struct Stack* createStack() {
	struct Stack* s = malloc(sizeof(struct Stack));
	s->top = NULL;
	s->sz = 0;

	return s;
}

int StackTop(struct Stack* s) {
	return s->top->id;
}

int StackPop(struct Stack* s) {
	int val = s->top->id;
	struct StackNode* tmp = s->top;
	s->top = s->top->next;
	free(tmp);
	s->sz--;

	return val;
}

void StackPush(struct Stack* s, int val) {
	struct StackNode* newNode = malloc(sizeof(struct StackNode));
	newNode->id = val;
	newNode->next = NULL;

	if (s->top == NULL)s->top = newNode;
	else {
		newNode->next = s->top;
		s->top = newNode;
	}
	s->sz++;
}

void deleteStack(struct Stack* s) {
	struct StackNode* cur = s->top;
	while (s->top) {
		cur = s->top->next;
		free(s->top);
		s->top = cur;
	}
}

void printStack(struct Stack* s) {
	struct StackNode* cur = s->top;
	while (cur) {
		printf("%d ", cur->id);
		cur = cur->next;
	}
	printf("\n");
}

struct Queue* createQueue() {
	struct Queue* q = malloc(sizeof(struct Queue));
	q->front = NULL;
	q->rear = NULL;
	q->sz = 0;

	return q;
}

int QueueTop(struct Queue* q) {
	return q->front->id;
}

int QueuePop(struct Queue* q) {
	if (!q->front)return -1;
	int val = q->front->id;

	q->front = q->front->next;
	if (!q->front)q->rear = NULL;

	q->sz--;
	return val;
}

void QueuePush(struct Queue* q, int val) {
	struct QueueNode* newNode = malloc(sizeof(struct QueueNode));
	newNode->id = val;
	newNode->next = NULL;

	if (!q->front) {
		q->front = newNode;
		q->rear = newNode;
	}
	else {
		q->rear->next = newNode;
		q->rear = newNode;
	}
	q->sz++;
}

struct ListNode {
	int id;
	struct ListNode* next;
};

struct Header {
	int exists;
	struct ListNode* list;
	int parent1_sz;
	int* parent1;

	int parent2_0_sz;
	int parent2_1_sz;
	int* parent2_0;
	int* parent2_1;
	
	int visited1;
	int dist1;

	int visited2[2];
	int dist2[2];
};

struct Graph {
	int size;
	struct Header* adj;
};

void printList(struct Header h) {
	struct ListNode* current = h.list;

	while (current) {
		printf("%d ", current->id);
		current = current->next;
	}
	printf("\n");
}

void printGraph(struct Graph* g) {
	for (int i = 0; i < g->size; i++) {
		if (!g->adj[i].exists)continue;

		printf("%d : ", i);
		printList(g->adj[i]);
	}
}

struct Graph* createGraph(int n) {
	struct Graph* g = malloc(sizeof(struct Graph));

	g->size = n;
	g->adj = malloc(sizeof(struct Header) * n);

	for (int i = 0; i < n; i++) {
		g->adj[i].list = malloc(sizeof(struct ListNode));
		g->adj[i].list = NULL;
		g->adj[i].exists = 1;
		g->adj[i].parent1_sz = 0;
		g->adj[i].parent2_0_sz = 0;
		g->adj[i].parent2_1_sz = 0;
		g->adj[i].parent1 = malloc(sizeof(int));
		g->adj[i].parent2_0 = malloc(sizeof(int));
		g->adj[i].parent2_1 = malloc(sizeof(int));
		g->adj[i].visited1 = 0;
		g->adj[i].dist1 = INF;
		g->adj[i].visited2[0] = 0;
		g->adj[i].visited2[1] = 0;
		g->adj[i].dist2[0] = INF;
		g->adj[i].dist2[1] = INF;
	}

	return g;
}

void addListNode(struct Header* h, int ind) {
	struct ListNode* newNode = malloc(sizeof(struct ListNode));
	newNode->id = ind;
	newNode->next = NULL;

	if (!(*h).list) {
		(*h).list = newNode;
		return;
	}

	struct ListNode* current = (*h).list;

	while (current->next)current = current->next;
	current->next = newNode;
}

void deleteList(struct Header* h) {
	struct ListNode* current = (*h).list;
	struct ListNode* next = NULL;

	while (current) {
		next = current->next;
		free(current);
		current = next;
	}

	(*h).list = NULL;
	free((*h).list);
}

void deleteElementFromList(struct Header* h, int id) {
	struct ListNode* current = (*h).list;
	struct ListNode* prev = NULL;

	if (!current)return;

	if (current->id == id) {
		(*h).list = current->next;
		free(current);

		return;
	}

	while (current && current->id != id) {
		prev = current;
		current = current->next;
	}

	if (!current)return;

	prev->next = current->next;
	free(current);
}

void addNode(struct Graph** g) {
	int sz = (*g)->size;
	(*g)->adj = realloc((*g)->adj, sizeof(struct Header) * (sz + 1));
	(*g)->adj[sz].list = malloc(sizeof(struct ListNode));
	(*g)->adj[sz].list = NULL;
	(*g)->adj[sz].exists = 1;
	(*g)->adj[sz].parent1_sz = 0;
	(*g)->adj[sz].parent2_0_sz = 0;
	(*g)->adj[sz].parent2_1_sz = 0;
	(*g)->adj[sz].parent1 = malloc(sizeof(int));
	(*g)->adj[sz].parent2_0 = malloc(sizeof(int));
	(*g)->adj[sz].parent2_1 = malloc(sizeof(int));
	(*g)->adj[sz].visited1 = 0;
	(*g)->adj[sz].dist1 = INF;
	(*g)->adj[sz].visited2[0] = 0;
	(*g)->adj[sz].visited2[1] = 0;
	(*g)->adj[sz].dist2[0] = INF;
	(*g)->adj[sz].dist2[1] = INF;
	(*g)->size++;
}

void addEdge(struct Graph* g, int from, int to) {
	addListNode(&(g->adj[from]), to);
}

void deleteNode(struct Graph** g, int ind) {
	if (!(*g)->adj[ind].exists)return;
	(*g)->adj[ind].exists = 0;
	deleteList(&(*g)->adj[ind]);

	for (int i = 0; i < (*g)->size; i++) {
		deleteElementFromList(&(*g)->adj[i], ind);
	}
}

void deleteEdge(struct Graph** g, int from, int to)	 {
	deleteElementFromList(&(*g)->adj[from], to);
}

void deleteGraph(struct Graph** g) {
	for (int i = 0; i < (*g)->size; i++)deleteNode(&(*g), i);
	free(*g);
}
	
void BFS1(struct Graph* G, int from, int to) {
	struct Queue* q = createQueue();
	for (int i = 0; i < G->size; i++) {
		G->adj[i].dist1 = INF;
		G->adj[i].visited1 = 0;
		G->adj[i].parent1_sz = 0;
		G->adj[i].parent1 = malloc(sizeof(int));
	}

	QueuePush(q, from);
	G->adj[from].dist1 = 0;
	G->adj[from].visited1 = 1;

	while (q->sz != 0) {
		int current = QueuePop(q);
		
		if (G->adj[current].list == NULL)continue;
		struct ListNode* cur = G->adj[current].list;

		while (cur) {
			int id = cur->id;
			if (!G->adj[id].visited1) {
				G->adj[id].dist1 = G->adj[current].dist1 + 1;
				G->adj[id].visited1 = 1;
				G->adj[id].parent1_sz++;
				G->adj[id].parent1[0] = current;
					
				QueuePush(q, id);
			}
			else if (G->adj[id].dist1 == G->adj[current].dist1 + 1) {
				int ok = 1;
				for (int i = 0; i < G->adj[id].parent1_sz; i++) {
					if (G->adj[id].parent1[i] == current)ok = 0;
				}
				if (ok) {
					G->adj[id].parent1 = realloc(G->adj[id].parent1, sizeof(int) * (G->adj[id].parent1_sz + 1));
					G->adj[id].parent1[G->adj[id].parent1_sz] = current;
					G->adj[id].parent1_sz++;
				}
			}
			cur = cur->next;
		}
	}
}

void BFS2(struct Graph* G, int from, int to) {
	struct Queue* q = createQueue();
	for (int i = 0; i < G->size; i++) {
		G->adj[i].dist2[0] = INF;
		G->adj[i].dist2[1] = INF;
		G->adj[i].visited2[0] = 0;
		G->adj[i].visited2[1] = 0;
		G->adj[i].parent2_0_sz = 0;
		G->adj[i].parent2_1_sz = 0;
		G->adj[i].parent2_0 = malloc(sizeof(int));
		G->adj[i].parent2_1 = malloc(sizeof(int));
	}

	QueuePush(q, from+1);
	G->adj[from].dist2[1] = 0;
	G->adj[from].visited2[1] = 1; //if player comes to 'from' again and if next step is of size 1, that means that we came to this state with jump of length 2,
								  //thats why visited2[1] = true
	
	while (q->sz != 0) {
		int current = QueuePop(q);
		

		if (current > 0) {//next step is of length 1
			current--;
			if (G->adj[abs(current)].list == NULL)continue;
			struct ListNode* cur = G->adj[abs(current)].list;

			while (cur) {
				int id = cur->id;
				if (!G->adj[id].visited2[0]) {
					G->adj[id].dist2[0] = G->adj[current].dist2[1] + 1;
					G->adj[id].visited2[0] = 1;
					G->adj[id].parent2_0_sz++;
					G->adj[id].parent2_0[G->adj[id].parent2_0_sz - 1] = current;

					QueuePush(q, -(id+1));
				}
				else if (G->adj[id].dist2[0] == G->adj[current].dist2[1] + 1) {
					int ok = 1;
					for (int i = 0; i < G->adj[id].parent2_0_sz; i++) {
						if (G->adj[id].parent2_0[i] == current)ok = 0;
					}
					if (ok) {
						G->adj[id].parent2_0 = realloc(G->adj[id].parent2_0, sizeof(int) * (G->adj[id].parent2_0_sz + 1));
						G->adj[id].parent2_0[G->adj[id].parent2_0_sz] = current;
						G->adj[id].parent2_0_sz++;
					}
					
				}
				cur = cur->next;
			}
		}
		else {//next step is of length 2
			current = abs(current) - 1;
			if (G->adj[abs(current)].list == NULL)continue;
			struct ListNode* cur = G->adj[abs(current)].list;

			while (cur) {
				int id = cur->id;
				if (G->adj[id].list == NULL) {
					cur = cur->next;
					continue;
				}

				struct ListNode* cur2 = G->adj[id].list;
				while (cur2) {
					int id2 = cur2->id;
					if (!G->adj[id2].visited2[1]) {
						G->adj[id2].dist2[1] = G->adj[current].dist2[0] + 1;
						G->adj[id2].visited2[1] = 1;
						G->adj[id2].parent2_1_sz++;
						G->adj[id2].parent2_1[G->adj[id2].parent2_1_sz-1] = current;

						QueuePush(q, id2 + 1);
					}
					else if (G->adj[id2].dist2[1] == G->adj[current].dist2[0] + 1) {
						int ok = 1;
						for (int i = 0; i < G->adj[id2].parent2_1_sz; i++) {
							if (G->adj[id2].parent2_1[i] == current)ok = 0;
						}
						if (ok) {
							G->adj[id2].parent2_1 = realloc(G->adj[id2].parent2_1, sizeof(int) * (G->adj[id2].parent2_1_sz + 1));
							G->adj[id2].parent2_1[G->adj[id2].parent2_1_sz] = current;
							G->adj[id2].parent2_1_sz++;
						}
					}

					cur2 = cur2->next;
				}

				cur = cur->next;
			}
		}	
	}
}

void generateOnePath1(struct Graph* G, int from, int to) {
	if (G->adj[to].dist1 == INF) {
		printf("Maja can't reach final state\n");
		return;
	}
	printf("One valid path for Maja is : ");
	if (from == to) {
		printf("%d\n", from);
		return;
	}

	int current = to;
	struct Stack* s = createStack();

	while (current != from) {
		StackPush(s, current);
		current = G->adj[current].parent1[0];
	}
	StackPush(s, current);
	printStack(s);
	deleteStack(s);
}

void generateOnePath2(struct Graph* G, int from, int to) {
	if (G->adj[to].dist2[1] == INF && G->adj[to].dist2[0] == INF) {
		printf("Sanja can't reach final state\n");
		return;
	}
	printf("One valid path for Sanja is : ");
	if (from == to) {
		printf("%d\n", from);
		return;
	}

	int parity = 0;
	if (G->adj[to].dist2[1] < G->adj[to].dist2[0])parity = 1;

	int current = to;
	struct Stack* s = createStack();

	while (current != from) {
		StackPush(s, current);
		if (parity == 0) {
			current = G->adj[current].parent2_0[0];
		}
		else {
			current = G->adj[current].parent2_1[0];
		}
		parity = 1 - parity;
	}
	StackPush(s, current);
	printStack(s);
	deleteStack(s);
}

void generateAllPaths1(struct Graph* G, int from, int to) {
	int* val = malloc(sizeof(int) * 2 * G->size);
	int* take = malloc(sizeof(int) * 2 * G->size);
	struct Stack* s = createStack();

	int cur_pos = 0;
	val[cur_pos] = to;
	take[cur_pos] = 1;
	StackPush(s, to);
	printf("All possible paths of minimum length for Maja are:\n");
	while (s->sz != 0) {
		int current = StackTop(s);

		if (current == from) {
			printf("Path: ");
			for (int i = cur_pos; i >= 0; i--) {
				if (take[i])printf("%d ", val[i]);
			}
			printf("\n");
			while (s->sz != 0 && take[cur_pos] == 1) {
				StackPop(s);
				cur_pos--;
			}
			if (cur_pos != -1) {
				take[cur_pos] = 1;
			}
		}
		else {
			for (int i = 0; i < G->adj[current].parent1_sz; i++) {
				StackPush(s, G->adj[current].parent1[i]);
				cur_pos++;
				take[cur_pos] = 0;
				val[cur_pos] = G->adj[current].parent1[i];
			}
			take[cur_pos] = 1;
		}
	}
}

void generateAllPaths2(struct Graph* G, int from, int to) {
	int* val = malloc(sizeof(int) * 2 * G->size);
	int* take = malloc(sizeof(int) * 2 * G->size);
	int* parity = malloc(sizeof(int) * 2 * G->size);

	struct Stack* s = createStack();

	int cur_pos = 0;
	val[cur_pos] = to;
	take[cur_pos] = 1;

	if (G->adj[to].dist2[0] < G->adj[to].dist2[1]) parity[cur_pos] = 1;
	else parity[cur_pos] = 0;

	StackPush(s, to);
	printf("All possible paths of minimum length for Sanja are:\n");
	while (s->sz != 0) {
		int current = StackTop(s);
		if (current == from) {
			printf("Path: ");
			for (int i = cur_pos; i >= 0; i--) {
				if (take[i])printf("%d ", val[i]);
			}
			printf("\n");
			while (s->sz != 0 && take[cur_pos] == 1) {
				StackPop(s);
				cur_pos--;
			}
			if (cur_pos != -1) {
				take[cur_pos] = 1;
			}
		}
		else {
			if (parity[cur_pos] == 1) {
				for (int i = 0; i < G->adj[current].parent2_0_sz; i++) {
					StackPush(s, G->adj[current].parent2_0[i]);
					cur_pos++;
					take[cur_pos] = 0;
					parity[cur_pos] = 0;
					val[cur_pos] = G->adj[current].parent2_0[i];
				}
				take[cur_pos] = 1;
			}
			else {
				for (int i = 0; i < G->adj[current].parent2_1_sz; i++) {
					StackPush(s, G->adj[current].parent2_1[i]);
					cur_pos++;
					take[cur_pos] = 0;
					parity[cur_pos] = 1;
					val[cur_pos] = G->adj[current].parent2_1[i];
				}
				take[cur_pos] = 1;
			}
		}
	}
}

int main() {
	struct Graph* G = malloc(sizeof(struct Graph));

	while (1) {
		printf("1. Create empty graph with N nodes\n");
		printf("2. Add new node\n");
		printf("3. Delete existing node\n");
		printf("4. Add new edge\n");
		printf("5. Delete existing edge\n");
		printf("6. Print graph\n");
		printf("7. Delete graph\n");
		printf("8. Play the game\n");
		printf("0. Exit\n");

		int choice;
		scanf("%d", &choice);
		if (!choice)break;

		if (choice == 1) {
			int n;
			printf("Input number of nodes\n");
			scanf("%d", &n);
			G = createGraph(n);
		}
		else if (choice == 2) {
			printf("New node with id %d is added\n", G->size);
			addNode(&G);
		}
		else if (choice == 3) {
			printf("Input id of the node\n");
			int id;
			scanf("%d", &id);
			deleteNode(&G, id);
		}
		else if (choice == 4) {
			printf("Input the edge a->b\n");
			int a, b;
			scanf("%d %d", &a, &b);
			addEdge(G, a, b);
		}
		else if (choice == 5) {
			printf("Input a->b that should be deleted\n");
			int a, b;
			scanf("%d %d", &a, &b);
			deleteEdge(&G, a, b);
		}
		else if (choice == 6) {
			printGraph(G);
		}
		else if (choice == 7) {
			deleteGraph(&G);
		}
		else {
			printf("Input start and end state from 0 to %d\n", G->size-1);
			int from, to;
			scanf("%d %d", &from, &to);

			BFS1(G, from, to);
			BFS2(G, from, to);
			
			int distance1 = G->adj[to].dist1;
			int distance2 = min(G->adj[to].dist2[0], G->adj[to].dist2[1]);

			if (distance1 != INF && distance2 != INF) {
				if (distance1 < distance2) {
					printf("Maja needs %d moves and Sanja needs %d moves. Maja wins\n", distance1, distance2);
				}
				else if (distance1 > distance2) {
					printf("Maja needs %d moves and Sanja needs %d moves. Sanja wins\n", distance1, distance2);
				}
				else {
					printf("They both need %d move(s). Draw\n", distance1);
				}
			}
			else if (distance1 != INF) {
				printf("Sanja can't reach final state. Maja wins in %d steps\n", distance1);
			}
			else if (distance2 != INF) {
				printf("Maja can't reach final state. Sanja wins in %d steps\n", distance2);
			}
			else {
				printf("No winner\n");
			}
			printf("\n");
			generateOnePath1(G, from, to);
			printf("\n");
			generateOnePath2(G, from, to);
			printf("\n");
			if (distance1 != INF) {
				generateAllPaths1(G, from, to);
				printf("\n");
			}
			if (distance2 != INF) {
				generateAllPaths2(G, from, to);
				printf("\n");
			}
		}
	}
	
	return 0;
}

/*
0 1
0 6
1 2
1 5
2 4
5 4
4 3
3 0
3 2

from 0 to 5
2 paths for Maja
4 paths for Sanja




	addEdge(G, 0, 1);
	addEdge(G, 0, 4);
	addEdge(G, 0, 8);
	addEdge(G, 1, 3);
	addEdge(G, 1, 2);
	addEdge(G, 2, 1);
	addEdge(G, 2, 3);
	addEdge(G, 2, 4);
	addEdge(G, 3, 5);
	addEdge(G, 4, 5);
	addEdge(G, 4, 6);
	addEdge(G, 5, 7);
	addEdge(G, 6, 7);
	addEdge(G, 6, 9);
	addEdge(G, 7, 8);
	addEdge(G, 9, 8);

from 2 to 7
3 paths for Maja
2 paths for Sanja

*/
