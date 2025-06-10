// special tree 範例資料
/*
8
0 1 1 0 0 0 1 0
1 0 0 1 0 0 1 0
1 0 0 0 1 0 0 0
0 1 0 0 0 1 0 0
0 0 1 0 0 0 0 1
0 0 0 1 0 0 0 0
1 1 0 0 0 0 0 1
0 0 0 0 1 0 1 0
9
0 1 1 1 0 0 0 0 0
1 0 0 1 0 0 0 0 0
1 0 0 1 1 1 1 0 0
1 1 1 0 0 1 0 0 0
0 0 1 0 0 1 1 1 0
0 0 1 1 1 0 0 0 1
0 0 1 0 1 0 0 1 0
0 0 0 0 1 0 1 0 1
0 0 0 0 0 1 0 1 0
9
0 1 1 0 0 0 1 0 0
1 0 0 1 0 0 1 0 0
1 0 0 0 1 0 0 0 0
0 1 0 0 0 1 0 0 0
0 0 1 0 0 0 0 1 0
0 0 0 1 0 0 0 0 0
1 1 0 0 0 0 0 1 0
0 0 0 0 1 0 1 0 1
0 0 0 0 0 0 0 1 0
8
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
8
1 0 0 0 0 0 0 0
0 1 0 0 0 0 0 0
0 0 1 0 0 0 0 0
0 0 0 1 0 0 0 0
0 0 0 0 1 0 0 0
0 0 0 0 0 1 0 0
0 0 0 0 0 0 1 0
0 0 0 0 0 0 0 1
8
1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1
8
0 1 1 1 1 1 1 1
1 0 1 1 1 1 1 1
1 1 0 1 1 1 1 1
1 1 1 0 1 1 1 1
1 1 1 1 0 1 1 1
1 1 1 1 1 0 1 1
1 1 1 1 1 1 0 1
1 1 1 1 1 1 1 0
3
0 1 1 
1 0 1 
1 1 0 
4
0 1 1 1 
1 0 1 1 
1 1 0 1 
1 1 1 0
4
0 1 0 0
1 0 1 1
0 1 0 0
0 1 0 0

*/
#include <iostream>
#include <cmath>
#define MAX 30

using namespace std;

// 初始化陣列為 -1

/*
-1 -1 
-1 -1
*/
void array_init(int a[][MAX],int size){
    for(int i = 0 ; i <size ;i++){
        for(int j = 0 ; j <size ;j++){
            a[i][j] = -1;
        }  
    }
}

// 輸入 adjacency matrix
void cinArrar(int a[][MAX],int size){
    for(int i = 0 ; i <size ;i++){
        for(int j = 0 ; j <size ;j++){
            cin >> a[i][j];
        }  
    }
}

// 輸出 adjacency matrix（除錯用）
void printArray(int a[][MAX],int size){
    for(int i = 0 ; i < size ;i++){
        for(int j = 0 ; j < size ;j++){
            cout << a[i][j] <<" ";
        }
        cout << endl;  
    }
}

// 判斷 node1 是否能透過某條路徑連到 node2（DFS）
bool nodeConnect(int node1,int node2,int a[][MAX],int size,bool cheakbox[MAX]){
    cheakbox[node1] = true; // 記錄已拜訪節點
    if(a[node1][node2] == 1){ // 直接有邊
        return 1;
    }else{
        // 遍歷其他節點來尋找路徑
        for(int j = 0 ; j <size ;j++){
            if(a[node1][j] == 1  && j != node2 && !cheakbox[j]){
                if(nodeConnect(j,node2,a,size,cheakbox)){
                    return 1;
                }
            }
        }  
    }
    return 0;
}

// 判斷是否為合法樹（所有節點相連 & 無向對稱）
bool checkTree(int a[][MAX],int size){
    // 檢查是否所有節點都連通
    for(int i = 1; i< size;i++){
        bool cheakBox[MAX] ={};
        if(!nodeConnect(0,i,a,size,cheakBox)){
            return 0;
        }
    }
    // 檢查是否為對稱（無向圖）
    for(int i = 0 ; i < size ;i++){
        for(int j = 0 ; j < size ;j++){
                //cout <<"o: "<<i << " " << j << " "<< a[i][j];
           if((a[i][j] != a[j][i]) || ((i == j) && (a[i][j] == 1))){
                //cout <<"i: "<< i << " " << j << " "<< a[i][j];
                return 0;
           }
        } 
    }
    return 1;
}
/*
8
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
*/
bool checkZeroTree(int a[][MAX],int size){

    // 檢查是否為對稱（無向圖）
    for(int i = 0 ; i < size ;i++){
        for(int j = 0 ; j < size ;j++){
           if(a[i][j] == 1 && i != j){
                return 0;
           }
        } 
    }
    return 1;
}
/*
8
0 1 1 1 1 1 1 1
1 0 1 1 1 1 1 1
1 1 0 1 1 1 1 1
1 1 1 0 1 1 1 1
1 1 1 1 0 1 1 1
1 1 1 1 1 0 1 1
1 1 1 1 1 1 0 1
1 1 1 1 1 1 1 0
*/
bool checkFullTree(int a[][MAX],int size){
    if(size == 1){
        return 0;
    }
    // 檢查是否為對稱
    for(int i = 0 ; i < size ;i++){
        for(int j = 0 ; j < size ;j++){
           if(a[i][j] == 0 && i != j){
                return 0;
           }
        } 
    }
    return 1;
}

// 計算非葉節點（degree > 1）的數量，即分支點
int calcBranch(int a[][MAX],int size){
    int counter = 0;
    int branchNum =0;
    for(int i = 0 ; i <size ;i++){
        for(int j = 0 ; j <size ;j++){
            if(a[i][j]){
                counter ++;
            }
        }  
        if(counter > 1){ // degree > 1 則為分支點
            branchNum++;
        }
        counter = 0;
    }
    return branchNum;
}

// 複製陣列 a -> copy
void arrayCopy(int a[][MAX],int copy[][MAX]){
    for(int i = 0 ; i <MAX ;i++){
        for(int j = 0 ; j <MAX ;j++){
            copy[i][j]=a[i][j];
        }  
    }
}

// 模擬二進位減法（如 1111 -> 1110）
// 標記所有為1的值，排列組合

void binArraySub(int a[],int bitn){
    for(int i = bitn,buffer =0; i>=0;i--){
        if(a[i] && buffer){
            a[i]= 1;
            buffer = 1;
        }else if(a[i] || buffer){
            a[i]= 0;
            buffer = 1;
        }else{
            a[i] = 1;
            buffer = 0;
        }
    }
}

// 計算 upper-triangle（不重複邊）中共有幾條邊
int calcArrayBit(int a[][MAX],int size){
    int counter = 0;
    for(int i = 0 ; i <size ;i++){
        for(int j = i + 1 ; j < size ;j++){
            if(a[i][j]){
                counter++;
            }
        }  
    }
    return counter;
}

// 根據 binSub 對應調整 adjacency matrix 中的邊（保留哪些邊）
void branchSub(int a[][MAX],int binSub[MAX*MAX+1],int size,int counter){
    binArraySub(binSub,counter); // 往下一個組合
    
    int counter1 = 1;
    for(int i = 0 ; i <size ;i++){
        for(int j = i+1 ; j <size ;j++){
            if(a[i][j] && j > i){
                a[i][j] = binSub[counter1];
                a[j][i] = binSub[counter1];
                counter1++;
            }
        }  
    }
}

// 主程式
int main(int argc,char *argv[]){
    int minBranch = 1000;  // 最少的分支數（初始化為大數）
    int binSub[MAX*MAX+1] ={};
    int trueBit = 0;
    int maxBit = 0;
    int array[MAX][MAX] = {};
    int copy[MAX][MAX] = {};
    array_init(array,MAX); // 初始圖

    int size = 0;
    cin >> size ;
    while (size != 0)
    {
        array_init(array,MAX); // 初始圖
        cinArrar(array,size); // 輸入圖
        maxBit = pow(2,calcArrayBit(array,size)); // 總共可能組合數
        trueBit = calcArrayBit(array,size);       // 真實可選邊數
        binSub[0] = 0;
        for(int i = 1;i<=trueBit;i++){
            binSub[i] = 1; // 初始全為 1（全選邊）
        }
        arrayCopy(array,copy);
        int b= calcArrayBit(copy, size);
        bool a=checkTree(copy,size);
        if(checkTree(copy,size)  && (calcArrayBit(copy, size) == (size - 1))){ // 是生成樹
            if(minBranch > calcBranch(copy,size)){ // 若分支更少，則更新
                minBranch = calcBranch(copy,size);
            }
        }
        if(checkFullTree(array,size)){
            minBranch = 1;
        }else if(!checkZeroTree(array,size) && checkTree(array,size)){
             // 遍歷每一個邊的組合
            for(int i = 1 ; i < maxBit ;i++){
                arrayCopy(array,copy);
                branchSub(copy,binSub,size,trueBit); // 套用本次邊的組合
                int b= calcArrayBit(copy, size);
                bool a=checkTree(copy,size);
                if(checkTree(copy,size)  && (calcArrayBit(copy, size) == (size - 1))){ // 是生成樹
                    if(minBranch > calcBranch(copy,size)){ // 若分支更少，則更新
                        minBranch = calcBranch(copy,size);
                    }
                }
            }
        }else{
            minBranch = 0;
        }
        

        // 輸出當前最少的分支節點數
        cout <<  minBranch << endl;

        cin >> size;  // 處理下一組圖
        //cout <<"erroroooooooooooooooooooooooo";
        minBranch = 1000;
    }

    return 0;
}
