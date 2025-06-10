//shortpath Dijkstra
#include<iostream>
#define maxVertaxSize 20
#define INFINITY 99
#define start_vertex 0
using namespace std;

//void shortestPath(int,int [][],int [],int,bool[]);
//int chooseMin(int [],int,bool[]);

int chooseMin(int d[],int n,bool selected[]){
    int min = INFINITY;
    int index = 0;
    for(int i = start_vertex ; i < n ; i++){
        if(!selected[i] && d[i]<min){
            min=d[i];
            index=i;
        }
    }
    return index;
}
void shortestPath(int F,int edgecost[][maxVertaxSize],int d[],int n,bool selected[]){

    for(int i = start_vertex ; i < n ; i++){
        d[i]=edgecost[F][i];
        selected[i]=false;
    }
    selected[F]=true;
    d[F]=0;
    for(int i = start_vertex + 1 ; i < n ; i++){
        int t = chooseMin(d,n,selected);
        selected[t]=true;
        for(int j = start_vertex ; j < n ; j++){
            if(!selected[j] && d[t]+edgecost[t][j]<d[j]){
                d[j]=d[t]+edgecost[t][j];
            }
        }
    }
}


int main(int argc,char * argv[]){
    int edgecost[maxVertaxSize][maxVertaxSize] = {};
    int d[maxVertaxSize] = {};
    bool selected[maxVertaxSize] = {};
    int n = maxVertaxSize;
    int f = 1;  // Starting vertex
    int maxVertexPath[maxVertaxSize] = {};
    int maxPath = INFINITY;
    bool disconnected = false;
    //cout << "Enter the number of vertices: \n";
    cin >> n;
    while (n!=0)
    {
        //n= n+1; // Adjusting for 1-based indexing
        ///cin >> f;
        //cout << "Enter the cost matrix: " << endl;
        for(int i = start_vertex ; i < n ; i++){
            for(int j = start_vertex ; j < n ; j++){
                cin >> edgecost[i][j];
                if(edgecost[i][j] == 0){
                    edgecost[i][j] = INFINITY;
                }
            }
        }
        /*while(cin>>f){
            shortestPath(f,edgecost,d,n,selected);
            cout << "Shortest path from vertex " << f << " is: " << endl;
            for(int i = start_vertex ; i < n ; i++){
                cout << "Vertex " << f << " to vertex " << i << " : ";
                if(d[i] == INFINITY){
                    cout << "No path" << endl;
                }else{
                    cout << d[i] << endl;
                }
            }
            
        }*/
        for(int j = start_vertex ; j < n ; j++){
            f=j;
            shortestPath(f,edgecost,d,n,selected);
            //cout << "Shortest path from vertex " << f << " is: " << endl;
            for(int i = start_vertex ; i < n ; i++){
                //cout << "Vertex " << f << " to vertex " << i << " : ";
                if(d[i] == INFINITY){
                    //cout << "No path" << endl;
                    disconnected = true;
                }else{
                    //cout << d[i] << endl;
                    if(d[i] > maxVertexPath[j]){
                        maxVertexPath[j] = d[i];
                    }
                }
            }
            
        } 
        if(disconnected){
            cout << "disconnected";
        }else{
            for(int i = start_vertex ; i < n ; i++){
                if(maxPath > maxVertexPath[i]){
                    maxPath = maxVertexPath[i];
                }
            }
            //cout << "center vertex : ";
            for(int i = start_vertex ; i < n ; i++){
                if(maxPath == maxVertexPath[i]){
                    cout << i << " ";
                }
            }
        }
        cout << endl;
        for(int i = start_vertex ; i < n ; i++){
            maxVertexPath[i] = 0;
        }
        maxPath = INFINITY;
        cin >> n;
        disconnected = false;
        
    }
    

    //system("pause");
    return 0;
}
