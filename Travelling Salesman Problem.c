#include<stdio.h>
#include<limits.h>

#define MAX_N 16
#define INF 1e9

int n;
int cost[MAX_N][MAX_N];
int memo[1<< MAX_N][MAX_N];

int min(int a, int b){
	return (a<b)? a:b;
}

int tsp(int mask, int pos){
	if(mask == (1 << n) - 1){
		return (cost[pos][0]!= -1)? cost[pos][0] : INF;	}

	if(memo[mask][pos] != -1){
		return memo[mask][pos];
	}

	int ans = INF;
	for(int next = 0; next < n; next++){
		if (!(mask & (1 << next))){
			if(cost[pos][next]!= -1){
				int newCost = cost[pos][next] + tsp(mask | (1 << next), next);
				ans = min(ans, newCost);
			}
		}
	}
	return memo[mask][pos] = ans;
}

int main(){
	if(scanf("%d", &n)!= 1) return 0;
	for(int i = 0; i<n; i++){
		for(int j=0; j<n; j++){
			scanf("%d", &cost[i][j]);
		}
	}
	for(int i = 0; i<(1 <<n); i++){
		for(int j = 0; j<n; j++){
			memo[i][j] = -1;
		}
	}
	int result = tsp(1, 0);
	if(result >= INF){
		printf("-1\n");
	}else{
		printf("%d\n", result);
	}
	return 0;
}
