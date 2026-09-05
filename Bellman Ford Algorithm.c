#include <stdio.h>
#include <stdlib.h>

#define INF 1000000000


typedef struct {
    int u, v, w;
} Edge;


void printPath(int current, int src, int parent[]) {
    if (current == src) {
        printf("%d", src);
        return;
    }
    printPath(parent[current], src, parent);
    printf("->%d", current);
}

int main() {
    int V, E;
    if (scanf("%d", &V) != 1) return 0;
    if (scanf("%d", &E) != 1) return 0;

    Edge* edges = (Edge*)malloc(E * sizeof(Edge));
    for (int i = 0; i < E; i++) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
    }

    int src;
    scanf("%d", &src);

    int* dist = (int*)malloc((V + 1) * sizeof(int));
    int* parent = (int*)malloc((V + 1) * sizeof(int));

    
    for (int i = 1; i <= V; i++) {
        dist[i] = INF;
        parent[i] = -1;
    }
    dist[src] = 0;

    
    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = edges[j].u;
            int v = edges[j].v;
            int w = edges[j].w;

            if (dist[u] != INF && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
            }
        }
    }

    
    for (int j = 0; j < E; j++) {
        int u = edges[j].u;
        int v = edges[j].v;
        int w = edges[j].w;

        if (dist[u] != INF && dist[u] + w < dist[v]) {
            printf("Negative cycle detected\n");
            free(edges);
            free(dist);
            free(parent);
            return 0;
        }
    }

    
    for (int i = 1; i <= V; i++) {
        if (i == src) continue;

        if (dist[i] == INF) {
            printf("%d INF None\n", i);
        } else {
            printf("%d %d ", i, dist[i]);
            printPath(i, src, parent);
            printf("\n");
        }
    }

    free(edges);
    free(dist);
    free(parent);
    return 0;
}
