#include<iostream>
#include<string.h>
#include<cmath>
#define STR_MAX 40
#define tree_MAX 2048
using namespace std;

struct point{
    int  value = -1;
    int index = -1;
};
struct tree{
    point p[tree_MAX];
};
void printTree(tree *,int );
void printAns(tree * ,int);
void initTree(tree *);
bool printNode(tree * ,int,int);
bool cheakTree(tree * ,int,int);
bool cheakNode(tree * ,int,int);
int main(){
    char buffer[STR_MAX];
    tree tree1;
    int goal_index = 0;
    int max_layer = 0;
    
    while(true){
        do{
            cin >> buffer;
            for (int i = 0,layer = 1, carry = 0,n_flag = false;;i++){
                if( i == 0){
                    tree1.p[goal_index].index = 1;
                }
                if (buffer[i] == '-') { // Check for negative sign
                    tree1.p[goal_index].value = 0; // Reset value to 0 before processing
                    n_flag = true ;
                }else if(buffer[i] >= '0' && buffer[i] <= '9'){
                    if(carry == 0){
                        tree1.p[goal_index].value = 0;
                    }else{     
                        tree1.p[goal_index].value *= 10;
                    }
                    tree1.p[goal_index].value += buffer[i] - '0';
                    carry = 1;
                }else if(buffer[i] == 'R' || buffer[i] == 'L'){
                    if(buffer[i] == 'R'){
                        tree1.p[goal_index].index = (tree1.p[goal_index].index * 2) + 1;
                    }else{
                        tree1.p[goal_index].index = (tree1.p[goal_index].index * 2);
                    }
                    if(max_layer < layer){
                        max_layer = layer;
                    }
                    layer++;
                }else if((buffer[i] == ')') && (buffer[i-1] == ',')){
                    tree1.p[goal_index].index = 1;
                }
                if(buffer[i] == ')'){
                    if(carry == 0){
                        tree1.p[goal_index].index = -1;
                    }
                    if(n_flag){
                        tree1.p[goal_index].value *= -1;
                    }
                    break;
                }
            }
            if(!(strcmp(buffer,"()") == 0)){
                goal_index++;
            }
            ///cout << "cmp - " << strcmp(buffer,"()") <<'\n';
        }while (!(strcmp(buffer,"()") == 0));
        if(goal_index == 0){
            break;
        }
        //cout << "MAX_layer\t" <<max_layer<<"\n";
        //printTree(&tree1,(max_layer+1));
        //printAns(&tree1,max_layer);
        if(cheakTree(&tree1,pow(2,max_layer+1),1)){
            cout << "wrong data\n";
        }else{
            printNode(&tree1,pow(2,max_layer + 1 ),1);
            cout << '\n';
        }
        initTree(&tree1);
        goal_index = 0;
        max_layer = 0;
    }
    
    return 0;
}
void printTree(tree * T ,int max_layer){//base_layer = 1
    int goal_index = 1;
    int tab_counter = 0;
    int find_index = 0;
    int now_layer = -1;
    /*for(int i = 0;i < (max_layer - tab_counter);i++){
        cout << '\t';
    }*/
    while(pow(2,tab_counter + 1) <= pow(2,max_layer)){
        tab_counter++;
    }
    while(goal_index <= (pow(2,max_layer)-1)){
        if((pow(2,now_layer+1)) <= goal_index){
            now_layer++;
            cout << '\n';
            //tab_counter = ((tab_counter - 1 ) > 0 )? tab_counter - 1 : 1;
            tab_counter--;
            for(int i = 0 ;i < pow(2,tab_counter) - 1 ;i++){
                cout << '\t';
            }
        }
        while((T->p[find_index].index != goal_index) && (find_index < pow(2,max_layer))){
            find_index++;
        }
        if(T->p[find_index].index == goal_index){
            cout <<T->p[find_index].value <<'\t';
        }else{
            cout << "*\t";
        }
        for(int i = 0 ; i < (pow(2,tab_counter + 1) - 1 ); i++){
            cout << '\t';
        }
        goal_index++;
        find_index = 0;
    }
    cout <<'\n';
}
void printAns(tree * T ,int max_layer){//base_layer = 0
    
    bool error_flag = false;
    bool nfound_flag = false;
    int find_index = 0;
    int goal_index = -1;
    
    //bool bottom_flag = false;
    int group = -1;
    int pre_layer = -1;
    
    //calc total point
    int total_index = 0;

    for(int i = 0;i < tree_MAX ;i++){
        if(T->p[i].index != -1 ){
            total_index ++;
        }else{
            break ;
        }
    }
    /*if(!(((pow(2,max_layer) - 1 ) < total_index) && (total_index <= (pow(2,max_layer + 1) - 1))) ){
        error_flag = true;
    }*/
    //confirn skip goal_index
    goal_index = 1;
    while(goal_index <= total_index){
        while((T->p[find_index].index != goal_index) && (find_index <= total_index)){
            find_index++;
        }
        if((T->p[find_index].index != goal_index)){
            error_flag = true;
            break;
        }
        find_index = 0;
        goal_index ++ ;
    }
    if(!error_flag){
        printNode(T,pow(2,max_layer + 1 ),1);
        cout << '\n';
    }else{
        cout << "wrong data\n";
    }
}
void initTree(tree * T){
    for(int i = 0; i < tree_MAX ; i++){
        T->p[i].index = -1;
        T->p[i].value = -1;
    }
}
bool printNode(tree * T ,int total_index,int node){
    int find_index = 0;
    while((T->p[find_index].index != node) && (find_index <= total_index)){
        find_index++;
    }
    if(T->p[find_index].index == node){
        printNode(T,total_index,node * 2);
        printNode(T,total_index,(node * 2) + 1);
        cout << T->p[find_index].value << " ";
        return 0;
    }else{
        return 1;
    }
}
bool cheakTree(tree * T,int max_index,int node){//max_index =base 1
    int find_index = 0;
    int value = 0;
    bool error_flag = false;
    while((T->p[find_index].index != node) && (find_index <= max_index)){
        find_index++;
    }
    if(T->p[find_index].index == node){
        value = T->p[find_index].value;
    }else{
        value = -1;
    }
    
    if((node * 2) < max_index){
        error_flag |=cheakTree(T,max_index,node * 2);
        error_flag |=cheakTree(T,max_index,node * 2 + 1);
    }
    if(error_flag){
        return 1;
    }
    if(T->p[find_index].index == node){
        return 0;
    }else{
        if( cheakNode(T,max_index,node * 2) || cheakNode(T,max_index,node * 2 +1)){
            return 1;
        }else{
            return 0;
        }
    }
}
bool cheakNode(tree * T,int max_index,int node){//max_index =base 1
    int find_index = 0;
    while((T->p[find_index].index != node) && (find_index <= max_index)){
        find_index++;
    }
    if(T->p[find_index].index == node){
        return 1;
    }else if((node * 2 ) < max_index){
        cheakNode(T,max_index,node * 2);
        cheakNode(T,max_index,(node * 2) + 1);
    }else{
        return 0;
    }
}


//bin complete
//
//#include<iostream>
//#include<string.h>
//#include<cmath>
//#define STR_MAX 40
//#define tree_MAX 2048
//using namespace std;
//
//struct point{
//    int  value = -1;
//    int index = -1;
//};
//struct tree{
//    point p[tree_MAX];
//};
//void printTree(tree *,int );
//void printAns(tree * ,int);
//void initTree(tree *);
//bool leftnode(tree *,int,int);
//bool rightnode(tree *,int,int);
//int main(){
//    char buffer[STR_MAX];
//    tree tree1;
//    int goal_index = 0;
//    int max_layer = 0;
//    
//    while(true){
//        do{
//            cin >> buffer;
//            for (int i = 0,layer = 1, carry = 0,n_flag = false;;i++){
//                if( i == 0){
//                    tree1.p[goal_index].index = 1;
//                }
//                if (buffer[i] == '-') { // Check for negative sign
//                    tree1.p[goal_index].value = 0; // Reset value to 0 before processing
//                    n_flag = true ;
//                }else if(buffer[i] >= '0' && buffer[i] <= '9'){
//                    if(carry == 0){
//                        tree1.p[goal_index].value = 0;
//                    }else{     
//                        tree1.p[goal_index].value *= 10;
//                    }
//                    tree1.p[goal_index].value += buffer[i] - '0';
//                    carry = 1;
//                }else if(buffer[i] == 'R' || buffer[i] == 'L'){
//                    if(buffer[i] == 'R'){
//                        tree1.p[goal_index].index = (tree1.p[goal_index].index * 2) + 1;
//                    }else{
//                        tree1.p[goal_index].index = (tree1.p[goal_index].index * 2);
//                    }
//                    if(max_layer < layer){
//                        max_layer = layer;
//                    }
//                    layer++;
//                }else if((buffer[i] == ')') && (buffer[i-1] == ',')){
//                    tree1.p[goal_index].index = 1;
//                }
//                if(buffer[i] == ')'){
//                    if(carry == 0){
//                        tree1.p[goal_index].index = -1;
//                    }
//                    if(n_flag){
//                        tree1.p[goal_index].value *= -1;
//                    }
//                    break;
//                }
//            }
//            if(!(strcmp(buffer,"()") == 0)){
//                goal_index++;
//            }
//            ///cout << "cmp - " << strcmp(buffer,"()") <<'\n';
//        }while (!(strcmp(buffer,"()") == 0));
//        if(goal_index == 0){
//            break;
//        }
//        //cout << "MAX_layer\t" <<max_layer<<"\n";
//        printTree(&tree1,(max_layer+1));
//        printAns(&tree1,max_layer);
//        initTree(&tree1);
//        goal_index = 0;
//        max_layer = 0;
//    }
//    
//    return 0;
//}
//void printTree(tree * T ,int max_layer){//base_layer = 1
//    int goal_index = 1;
//    int tab_counter = 0;
//    int find_index = 0;
//    int now_layer = -1;
//    while(pow(2,tab_counter + 1) <= pow(2,max_layer)){
//        tab_counter++;
//    }
//    while(goal_index <= (pow(2,max_layer)-1)){
//        if((pow(2,now_layer+1)) <= goal_index){
//            now_layer++;
//            cout << '\n';
//            //tab_counter = ((tab_counter - 1 ) > 0 )? tab_counter - 1 : 1;
//            tab_counter--;
//            for(int i = 0 ;i < pow(2,tab_counter) - 1 ;i++){
//                cout << '\t';
//            }
//        }
//        while((T->p[find_index].index != goal_index) && (find_index < pow(2,max_layer))){
//            find_index++;
//        }
//        if(T->p[find_index].index == goal_index){
//            cout <<T->p[find_index].value <<'\t';
//        }else{
//            cout << "*\t";
//        }
//        for(int i = 0 ; i < (pow(2,tab_counter + 1) - 1 ); i++){
//            cout << '\t';
//        }
//        goal_index++;
//        find_index = 0;
//    }
//    cout <<'\n';
//}
//void printAns(tree * T ,int max_layer){//base_layer = 0
//    
//    bool error_flag = false;
//    bool nfound_flag = false;
//    int find_index = 0;
//    int goal_index = -1;
//    
//    //bool bottom_flag = false;
//    int group = -1;
//    int pre_layer = -1;
//    
//    //calc total point
//    int total_index = 0;
//
//    for(int i = 0;i < tree_MAX ;i++){
//        if(T->p[i].index != -1 ){
//            total_index ++;
//        }else{
//            break ;
//        }
//    }
//    //confirn skip goal_index
//    goal_index = 1;
//    while(goal_index <= total_index){
//        while((T->p[find_index].index != goal_index) && (find_index <= total_index)){
//            find_index++;
//        }
//        if((T->p[find_index].index != goal_index)){
//            error_flag = true;
//            break;
//        }
//        find_index = 0;
//        goal_index ++ ;
//    }
//    if(!error_flag){
//        leftnode(T,total_index,1);
//        cout << '\n';
//    }else{
//        cout << "wrong data\n";
//    }
//}
//void initTree(tree * T){
//    for(int i = 0; i < tree_MAX ; i++){
//        T->p[i].index = -1;
//        T->p[i].value = -1;
//    }
//}
//bool leftnode(tree * T ,int total_index,int node){
//    int find_index = 0;
//    while((T->p[find_index].index != node) && (find_index <= total_index)){
//        find_index++;
//    }
//    if(T->p[find_index].index == node){
//        leftnode(T,total_index,node * 2);
//        rightnode(T,total_index,(node * 2) + 1);
//        cout << T->p[find_index].value << " ";
//        return 0;
//    }else{
//        return 1;
//    }
//}
//bool rightnode(tree * T ,int total_index,int node){
//    int find_index = 0;
//    while((T->p[find_index].index != node) && (find_index <= total_index)){
//        find_index++;
//    }
//    if(T->p[find_index].index == node){
//        leftnode(T,total_index,node *2);
//        rightnode(T,total_index,(node * 2) + 1);
//        cout << T->p[find_index].value << " ";
//        return 0;
//    }else{
//        return 1;
//    }
//}
//