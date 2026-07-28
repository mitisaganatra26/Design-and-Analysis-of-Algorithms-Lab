#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
struct Edge{
int src, dest, weight;
};
struct Subset {
int parent;
int rank;
};
int findRoot(struct Subset subsets[], int i){
	if (subsets[i].parent != i)
		subsets[i].parent = findRoot(subsets, subsets[i].parent);
	return subsets[i].parent;
}
void unionSets(struct Subset subsets[], int x, int y){
	int rootX = findRoot(subsets, x);
	int rootY = findRoot(subsets, y);

	if (subsets[rootX].rank < subsets[rootY].rank)
		subsets[rootX].parent = rootY;
	else if (subsets[rootX].rank > subsets[rootY].rank)
		subsets[rootY].parent = rootX;
	else{
		subsets[rootY].parent = rootX;
		subsets[rootX].rank++;
	}
}
int compareEdges(const void* a, const void* b){
	struct Edge *a1 = (struct Edge *)a;
	struct Edge *b1 = (struct Edge *)b;

	if (a1->weight != b1->weight)
		return a1->weight - b1->weight;

	if(a1->src != b1->src)
		return a1->src - b1->src;

	return a1->dest - b1->dest;
}
void kruskalMST(int **cost, int V) {

	int maxEdges = V * (V-1)/2;
	struct Edge* edges = (struct Edge*)malloc(maxEdges * sizeof(struct Edge));
	int edgeCount = 0;

	for(int i = 0; i<V; i++){
		for(int j = i+1; j<V; j++){
			if (cost[i][j] != 9999){
				edges[edgeCount].src = i;
				edges[edgeCount].dest = j;
				edges[edgeCount].weight = cost[i][j];
				edgeCount++;
			}
		}
	}
	qsort(edges, edgeCount, sizeof(struct Edge), compareEdges);
	struct Subset* subsets = (struct Subset*)malloc(V* sizeof(struct Subset));
	for (int v = 0; v<V; ++v){
	subsets[v].parent = v;
	subsets[v].rank = 0;
}
int mstCost = 0;
int selectedEdges = 0;
int edgeIndex = 0;

while(selectedEdges < V -1 && edgeIndex < edgeCount){
	struct Edge nextEdge = edges[edgeIndex++];

	int x = findRoot(subsets, nextEdge.src);
	int y = findRoot(subsets, nextEdge.dest);

	if (x != y){
		printf("Edge %d:(%d, %d) cost:%d\n", selectedEdges, nextEdge.src, nextEdge.dest, nextEdge.weight);
		mstCost += nextEdge.weight;
		selectedEdges++;
		unionSets(subsets, x, y);
	}
}
	printf("Minimum cost= %d\n", mstCost);

	free(edges);
	free(subsets);


}
int main() {
    int V;
    printf("No of vertices: ");
    scanf("%d", &V);

    int **cost = (int **)malloc(V * sizeof(int *));
    for (int i = 0; i < V; i++)
        cost[i] = (int *)malloc(V * sizeof(int));

    printf("Adjacency matrix:\n");
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            scanf("%d", &cost[i][j]);

    kruskalMST(cost, V);

    for (int i = 0; i < V; i++)
        free(cost[i]);
    free(cost);

    return 0;
}
