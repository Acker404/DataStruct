#include<iostream>
#define MAX 20

using namespace std;
bool markup(bool *already_common_edge,bool *point_common,int position,int point){
    if(!already_common_edge[position]){//nomark point
        already_common_edge[position] = true;
        for(int j = 0 ;j < point ; j++){
            if(point_common[j]){
                already_common_edge[j] = true;
            }
        }
        //cout << position << " ";
        return 0;
    }
    return 1;
}
int main(int argc,char* argv[]){
    int point = 0;//total point
    int point_max = 0;
    int point_buffer = 0;
    int start_point = 0;
    int seqence[MAX] = {}; //由小到大，因為要找最多節點
    int point_num[MAX][2] = {};//[0] 存位置 [1] 存節點數
    bool point_common[MAX][MAX] = {};//輸入陣列
    bool already_common_edge[MAX] = {};//答案卡
    while(true){
        //input
        //cout << "plaese input point digit\n";
        cin >> point;
        if(point == -1){
            break;
        }
        //cout << "plaese input point common edge\n";
        for(int i = 0 ;i < point ; i++){
            point_num[i][0]=i;
            for(int j = 0 ;j < point ; j++){
                cin >> point_common[i][j];
                if(point_common[i][j]){
                    point_num[i][1]++;
                }
            }
        } 

        //compare
        for(int i = 0 ;i < point ; i++){
            point_num[i][0]=i;
            for(int j = i ,buffer = 0;j < point ; j++){
                if(point_num[i][1] >  point_num[j][1] ){
                    buffer = point_num[i][1];
                    point_num[i][1] = point_num[j][1];
                    point_num[j][1] = buffer;
                    buffer = point_num[i][0];
                    point_num[i][0] = point_num[j][0];
                    point_num[j][0] = buffer;
                }
            }
            seqence[i] = point_num[i][0];
        } 
        //deal
        while(start_point < point){
            for(int i =0 ; i < point ; i++){
                already_common_edge[i] = 0 ;
            }
            //markup
            
            /*if(!already_common_edge[start_point]){//nomark point
                for(int j = 0 ;j < point ; j++){
                    if(point_common[start_point][j]){
                        already_common_edge[j] = true;
                    }
                    already_common_edge[start_point] = true;
                }
                point_buffer++;
            }
            for(int i = 0 ;i < point ; i++){
                if(!already_common_edge[i]){//nomark point
                    for(int j = 0 ;j < point ; j++){
                        if(point_common[i][j]){
                            already_common_edge[j] = true;
                        }
                        already_common_edge[i] = true;
                    }
                    point_buffer++;
                }
            }
            */
        if(!markup(already_common_edge,point_common[seqence[start_point]],seqence[start_point],point)){//if nomark point mark
                point_buffer++;
            }
            for(int i = 0 ;i < point ; i++){
                if(!markup(already_common_edge,point_common[seqence[i]],seqence[i],point)){// if nomark point mark
                    point_buffer++;
                }
            }
            //cout << "\n";
            for(int i = 0 ;i < point ; i++){// answer
                if(already_common_edge[i]){
                    if((i+1) == point){
                        point_max = point_buffer > point_max ? point_buffer : point_max;
                        //cout << "SUCCESS\n";
                    }
                }else{
                    //cout << "FAIL\n";
                    break;
                }
            }
            
            for(int i =0 ; i < MAX ; i++){
                already_common_edge[i] = 0;
            }
            point_buffer = 0;
            start_point++;    
        }
        cout<< point_max << "\n";
        //init
        point = 0;
        point_max = 0;
        point_buffer = 0;
        start_point = 0;
        for(int i = 0 ;i < MAX ; i++){
            already_common_edge[i] = false;
            seqence[i] = 0; 
            point_num[i][0] = 0;
            point_num[i][1] = 0;
            for(int j = 0 ;j < MAX ; j++){  
                
                point_common[i][j] = false;
            }
        }
    }
    
    

    
    return 0;
}