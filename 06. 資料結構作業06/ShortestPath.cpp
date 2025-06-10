// Shortest Path (最短路徑)
/*
輸入格式說明：
6                          // 節點數量為 6
5 4 1 7 2 3                // 各節點的權重（nodeWeight）
0 3 0 0 0 2               // 鄰接矩陣（圖的邊的權重），0 表示沒有邊
3 0 5 0 3 1
0 5 0 0 2 0
0 0 0 0 0 0
0 3 2 0 0 4
2 1 0 0 4 0
5                          // 起點節點編號
0                          // 未使用
*/

#include<iostream>
#include<limits.h>
#define MAX 20
using namespace std;


// 所有點對之間最短距離計算函式（改良版 Floyd-Warshall 演算法）
// 加上每個中繼點的權重（nodeWeight[k]）
void allcosts(int cost[][MAX], int distance[][MAX], int nodeWeight[], int n){
    int i, j, k;
    // 初始化 distance 矩陣為原始成本矩陣
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++) 
            distance[i][j] = cost[i][j];

    // 三重迴圈進行動態規劃更新距離
    for (k = 0; k < n; k++) {
        for (i = 0; i < n; i++){
            for (j = 0; j < n; j++){
                // 如果經由節點 k 能得到更短的路徑，則更新
                if (((distance[i][k] + distance[k][j] + nodeWeight[k]) < distance[i][j]) && ((distance[i][k] != INT_MAX) && (distance[k][j] != INT_MAX))){
                    distance[i][j] = distance[i][k] + distance[k][j] + nodeWeight[k];
                }
            }
        }
    }
}   

// 輸出 2D 陣列，格式化顯示（∞ 表示不可達）
void printArray(int array[MAX][MAX], int size){
    for (int i = 0; i < size ; i++){
        for (int j = 0; j < size ; j++){
            if (array[i][j] == INT_MAX){
                cout << "\u221E\t";  // Unicode 無限符號
            } else {
                cout << array[i][j] << "\t";
            }
        }
        cout << endl;
    }
}

// 根據起點輸出所有到其他點的最短距離
void printAns(int array[][MAX], int start, int size){
    for (int i = 0; i < size; i++){
        if (start == i){
            cout << "0 ";
        } else if (array[start][i] == INT_MAX){
            cout << "infinity ";
        } else {
            cout << array[start][i] << " ";
        }
    }
    cout << endl;
}

int main(int argc, char *argv[]){
    int weight[MAX] = {};         // 每個節點的權重（nodeWeight）
    int node[MAX][MAX] = {};      // 鄰接矩陣（邊的成本）
    int dist[MAX][MAX] = {};      // 所有點對最短距離矩陣
    int u, v = 0;                 // 起點 u，v 未使用
    int nodeSize = 0;             // 節點數量

    // 讀入節點數
    cin >> nodeSize;

    while (nodeSize > 0)
    {

        // 讀入每個節點的權重
        for (int i = 0; i < nodeSize; i++){
            cin >> weight[i];
        }

        // 讀入鄰接矩陣，並將 0（表示無連接）轉為 INT_MAX
        for (int i = 0; i < nodeSize; i++){
            for (int j = 0; j < nodeSize; j++){
                cin >> node[i][j];
                if (node[i][j] == 0){
                    node[i][j] = INT_MAX;
                }
            }
        }

        // 讀入起點
        cin >> u;

        // 計算所有點對最短距離
        allcosts(node, dist, weight, nodeSize);

        // 輸出從起點出發到所有點的最短距離
        printAns(dist, u, nodeSize);

        // 可取消註解以顯示完整距離矩陣
        // printArray(dist, nodeSize);

        // 讀入節點數
        cin >> nodeSize;
    }

    return 0;
}
