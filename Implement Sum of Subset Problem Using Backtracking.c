#include<stdio.h>
#include<stdlib.h>
#define MAX_ELEMENTS 100
#define MAX_SUBSETS 1000

int arr[MAX_ELEMENTS];
int n, target;

int results[MAX_SUBSETS]
[MAX_ELEMENTS];
int result_sizes[MAX_SUBSETS];
int result_count = 0;

int current_path[MAX_ELEMENTS];

void backtrack(int start_index, int current_sum, int path_size){
	if(current_sum == target){
		for(int i = 0; i<path_size; i++){
			results[result_count][i] = current_path[i];
		}
		result_sizes[result_count] = path_size;
		result_count++;
		return;
	}
	for(int i = start_index; i<n; i++){
		current_path[path_size] = arr[i];
		backtrack(i+1, current_sum + arr[i], path_size +1);
	}
	
}
int main(){
	if(scanf("%d", &n)!= 1) return 0;

	for(int i=0; i<n; i++){
		scanf("%d", &arr[i]);
	}
	scanf("%d", &target);

	backtrack(0, 0, 0);
	if(result_count == 0){
		printf("-1\n");
	}else{
		for(int i = result_count-1; i>=0; i--){
			for(int j = 0; j<result_sizes[i]; j++){
				printf("%d%s", results[i][j],  (j==result_sizes[i]-1)? " " : " ");
			}
				printf("\n");
			}
		}
		return 0;
	}
