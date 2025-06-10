#include <iostream>
//#include <windows.h>
#define Grid_MAX 50
using namespace std;
enum position
{
    road,
    wall,
    up_stair,
    E,
    ES,
    S,
    SW,
    W,
    WN,
    N,
    NE,
    down_stair,
    dead_space,
    start1,
    end1
};
struct maze
{
    int height = 0;
    int width = 0;
    int length = 0;
    int maze_grid[Grid_MAX][Grid_MAX][Grid_MAX] = {0};
    int mark[Grid_MAX][Grid_MAX][Grid_MAX] = {0};
};
struct coord
{
    int x = 0;
    int y = 0;
    int z = 0;
};
void readMaze(maze *);
void readMaze(maze *, coord);
void initMaze(maze *);
void action_print(int);
bool checkMazeBorder(maze *, coord *);
bool deadEnd(maze *, coord *);
bool nextPath(maze *, coord *, int);
int main()
{
    maze maze1;
    //maze rem[50];
    coord coord_start, coord_end, player;
    int score = 0;
    //cout << "input height width length\n";
    /*  height  -   //////  z
        width   -   ------  y
        length  -   ||||||  x
    */
    cin >> maze1.height >> maze1.width >> maze1.length;
    
    do{ 
        //cout << "input maze\n";
        for (int i = 0; i < maze1.height; ++i)
        {
            for (int j = 0; j < maze1.width; ++j)
            {
                for (int k = 0; k < maze1.length; ++k)
                {
                    cin >> maze1.maze_grid[i][j][k];
                }
            }
        }
        //cout << "input start point\n";
        cin >> coord_start.z >> coord_start.y >> coord_start.x;
        maze1.maze_grid[coord_start.z - 1][coord_start.y][coord_start.x] = start1;
        //cout << "input end point\n";
        cin >> coord_end.z >> coord_end.y >> coord_end.x;
        maze1.maze_grid[coord_end.z - 1][coord_end.y][coord_end.x] = end1;
        player.x = coord_start.x;
        player.y = coord_start.y;
        player.z = coord_start.z;
        while (maze1.mark[coord_start.z - 1][coord_start.y][coord_start.x] <= 6)
        {
            if (!checkMazeBorder(&maze1, &player))
            {
                maze1.mark[player.z - 1][player.y][player.x]++;
                if (!nextPath(&maze1, &player, up_stair) && maze1.mark[player.z - 1][player.y][player.x] == 1 && (maze1.maze_grid[player.z - 1][player.y][player.x] != down_stair))
                {
                    maze1.maze_grid[player.z][player.y][player.x] = up_stair;
                    player.z++;
                }
                else if (!nextPath(&maze1, &player, E) && maze1.mark[player.z - 1][player.y][player.x] == 2 && (maze1.maze_grid[player.z - 1][player.y][player.x] != W))
                {
                    maze1.maze_grid[player.z - 1][player.y][player.x + 1] = E;
                    player.x++;
                }
                else if (!nextPath(&maze1, &player, S) && maze1.mark[player.z - 1][player.y][player.x] == 3 && (maze1.maze_grid[player.z - 1][player.y][player.x] != N))
                {
                    maze1.maze_grid[player.z - 1][player.y + 1][player.x] = S;
                    player.y++;
                }
                else if (!nextPath(&maze1, &player, W) && maze1.mark[player.z - 1][player.y][player.x] == 4 && (maze1.maze_grid[player.z - 1][player.y][player.x] != E))
                {
                    maze1.maze_grid[player.z - 1][player.y][player.x - 1] = W;
                    player.x--;
                }
                else if (!nextPath(&maze1, &player, N) && maze1.mark[player.z - 1][player.y][player.x] == 5 && (maze1.maze_grid[player.z - 1][player.y][player.x] != S))
                {
                    maze1.maze_grid[player.z - 1][player.y - 1][player.x] = N;
                    player.y--;
                }
                else if (!nextPath(&maze1, &player, down_stair) && maze1.mark[player.z - 1][player.y][player.x] == 6 && (maze1.maze_grid[player.z - 1][player.y][player.x] != up_stair))
                {
                    maze1.maze_grid[player.z - 2][player.y][player.x] = down_stair;
                    player.z--;
                }
                else if (maze1.mark[player.z - 1][player.y][player.x] >= 7)
                {
                    if(maze1.mark[coord_start.z - 1][coord_start.y][coord_start.x] > 6){
                        continue;;
                    }
                    maze1.mark[player.z - 1][player.y][player.x] = 0;
                    switch (maze1.maze_grid[player.z - 1][player.y][player.x])
                    {
                    case up_stair:
                        maze1.maze_grid[player.z - 1][player.y][player.x] = road;
                        player.z--;
                        break;
                    case E:
                        maze1.maze_grid[player.z - 1][player.y][player.x] = road;
                        player.x--;
                        break;
                    case S:
                        maze1.maze_grid[player.z - 1][player.y][player.x] = road;
                        player.y--;
                        break;
                    case W:
                        maze1.maze_grid[player.z - 1][player.y][player.x] = road;
                        player.x++;
                        break;
                    case N:
                        maze1.maze_grid[player.z - 1][player.y][player.x] = road;
                        player.y++;
                        break;
                    case down_stair:
                        maze1.maze_grid[player.z - 1][player.y][player.x] = road;
                        player.z++;
                        break;
                    default:
                        cout << "error";
                        break;
                    }
                }
                if ((player.z == coord_end.z) && (player.y == coord_end.y) && (player.x == coord_end.x))
                {
                    maze1.mark[player.z - 1][player.y][player.x] = 7;
                    score++;
                    //cout<< "score\t" <<score<<"\n";
                    
                }
                /*cout << "player position\t" <<player.z << '\t' << player.y << '\t' << player.x << '\t'; //test read
                action_print(maze1.maze_grid[player.z - 1][player.y][player.x]);
                cout << '\n';
                cout << "mark --- " << maze1.mark[player.z - 1][player.y][player.x] << "\t nextPath -- " << !nextPath(&maze1, &player, up_stair) << '\n';
                deadEnd(&maze1, &player);
                readMaze(&maze1, player);*/
            }
            else
            {
                cout << "error";
            }
        }
        cout << score << '\n';
        score = 0;
        initMaze(&maze1);
        //cout << "input height width length\n";
        /*  height  -   //////  z
            width   -   ------  y
            length  -   ||||||  x
        */
        cin >> maze1.height >> maze1.width >> maze1.length;
    }while ((maze1.height > 0) && (maze1.width > 0) && (maze1.length > 0));


    //readMaze(&maze1);
    return 0;
}
bool checkMazeBorder(maze *maze1, coord *ex1)
{
    if ((0 <= ex1->x && ex1->x < maze1->length) && (0 <= ex1->y && ex1->y < maze1->width) && (1 <= ex1->z && (ex1->z - 1) <= maze1->height))
    {
        return 0;
    }
    else
    {
        if (!(0 <= ex1->x && ex1->x < maze1->length))
        {
            cout << "length error\n";
            cout << "x : " << ex1->x << "\t" << "Maze length : " << maze1->length << "\n";
        }
        if (!(0 <= ex1->y && ex1->y < maze1->width))
        {
            cout << "width error\n";
            cout << "y : " << ex1->y << "\t" << "Maze width : " << maze1->width << "\n";
        }
        if (!(1 <= ex1->z && (ex1->z - 1) <= maze1->height))
        {
            cout << "height error\n";
            cout << "z : " << ex1->z << "\t" << "Maze height : " << maze1->height << "\n";
        }
        return 1;
    }
}
bool nextPath(maze *maze1, coord *player, int move)
{
    bool w_key      = (((maze1->maze_grid[player->z - 1][player->y - 1][player->x] == road) || (maze1->maze_grid[player->z - 1][player->y - 1][player->x] == end1) /*|| (maze1->maze_grid[player->z - 1][player->y - 1][player->x] == start1)*/) && ((player->y - 1) >= 0));
    bool d_key      = (((maze1->maze_grid[player->z - 1][player->y][player->x + 1] == road) || (maze1->maze_grid[player->z - 1][player->y][player->x + 1] == end1) /*|| (maze1->maze_grid[player->z - 1][player->y][player->x + 1] == start1)*/) && ((player->x + 1) < maze1->length));
    bool a_key      = (((maze1->maze_grid[player->z - 1][player->y][player->x - 1] == road) || (maze1->maze_grid[player->z - 1][player->y][player->x - 1] == end1) /*|| (maze1->maze_grid[player->z - 1][player->y][player->x - 1] == start1)*/) && ((player->x - 1) >= 0));
    bool s_key      = (((maze1->maze_grid[player->z - 1][player->y + 1][player->x] == road) || (maze1->maze_grid[player->z - 1][player->y + 1][player->x] == end1) /*|| (maze1->maze_grid[player->z - 1][player->y + 1][player->x] == start1)*/) && ((player->y + 1) < maze1->width));
    bool up_key     = (((maze1->maze_grid[player->z][player->y][player->x] == road) || (maze1->maze_grid[player->z][player->y][player->x] == end1) /*|| (maze1->maze_grid[player->z][player->y][player->x] == start1)*/) && (player->z < maze1->height));
    bool down_key   = (((maze1->maze_grid[player->z - 2][player->y][player->x] == road) || (maze1->maze_grid[player->z - 2][player->y][player->x] == end1) /*|| (maze1->maze_grid[player->z - 2][player->y][player->x] == start1)*/) && ((player->z - 2) >= 0));
    //cout <<"grid inside " << maze1->maze_grid[player->z - 1][player->y][player->x + 1] << '\n';
    //cout << "nextPath --- " << "w_key : " << w_key << " d_key : " << d_key << " a_key : " << a_key << " s_key : " << s_key << " up_key : " << up_key << " down_key : " << down_key << "\n";
    //action_print(move);
    if (up_key && (move == up_stair))
    {
        return 0;
    }
    else if (down_key && (move == down_stair))
    {
        return 0;
    }
    else if (w_key && (move == N))
    {
        return 0;
    }
    else if (d_key && (move == E))
    {
        return 0;
    }
    else if (s_key && (move == S))
    {
        return 0;
    }
    else if (a_key && (move == W))
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
bool deadEnd(maze *maze1, coord *player)
{
    bool w_key = (maze1->maze_grid[player->z - 1][player->y - 1][player->x] == wall) ? true : false;
    bool d_key = (maze1->maze_grid[player->z - 1][player->y][player->x + 1] == wall) ? true : false;
    bool a_key = (maze1->maze_grid[player->z - 1][player->y][player->x - 1] == wall) ? true : false;
    bool s_key = (maze1->maze_grid[player->z - 1][player->y + 1][player->x] == wall) ? true : false;
    bool up_key = ((maze1->maze_grid[player->z][player->y][player->x] == wall) || (player->z >= maze1->height)) ? true : false;
    bool down_key = ((maze1->maze_grid[player->z - 2][player->y][player->x] == wall) || ((player->z - 2) < 0)) ? true : false;
    //cout << "deadend --- " << "w_key : " << w_key << " d_key : " << d_key << " a_key : " << a_key << " s_key : " << s_key << " up_key : " << up_key << " down_key : " << down_key << "\n";
    if (((up_key & down_key) & (!((w_key & d_key & a_key) | (w_key & d_key & s_key) | (w_key & a_key & s_key) | (d_key & a_key & s_key)))) || (!up_key & !down_key) || ((up_key & !down_key) & !(w_key & a_key & d_key & s_key)) || ((!up_key & down_key) & !(w_key & a_key & d_key & s_key)))
    {
        return 0;
    }
    else
    {
        //cout << "\ndeadend\n";
        return 1;
    }
}
void readMaze(maze *m)
{
    // cout << m->height << m->width << m->length << "\n";
    //HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    for (int i = 0; i < m->height; ++i)
    {
        for (int j = 0; j < m->width; ++j)
        {
            for (int k = 0; k < m->length; ++k)
            {
                if (m->maze_grid[i][j][k] == road || m->maze_grid[i][j][k] == wall)
                {
                    //SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
                    cout << m->maze_grid[i][j][k] << '\t'; // num
                }
                else
                {
                    //SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
                    cout << "*\t"; // num
                    // cout << m->maze_grid[i][j][k] << '\t'; //num
                }
            }
            cout << "\n";
        }
        cout << "\n\n";
    }
}
void readMaze(maze *m, coord mark)
{
    // cout << m->height << m->width << m->length << "\n";
    //HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    for (int i = 0; i < m->height; ++i)
    {
        for (int j = 0; j < m->width; ++j)
        {
            for (int k = 0; k < m->length; ++k)
            {
                if (k == mark.x && j == mark.y && i == (mark.z - 1))
                {
                    //SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
                    cout << "*\t"; // num
                    // cout << m->maze_grid[i][j][k] << '\t'; //num
                }
                else if (m->maze_grid[i][j][k] == 0 || m->maze_grid[i][j][k] == 1)
                {
                    //SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
                    cout << m->maze_grid[i][j][k] << '\t'; // num
                }
                else
                {
                    //SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
                    cout << "*\t"; // num
                    // cout << m->maze_grid[i][j][k] << '\t'; //num
                }
            }
            cout << "\n";
        }
        cout << "\n\n";
    }
}
void initMaze(maze *m)
{
    // cout << m->height << m->width << m->length << "\n";

    for (int i = 0; i < Grid_MAX; ++i)
    {
        for (int j = 0; j < Grid_MAX; ++j)
        {
            for (int k = 0; k < Grid_MAX; ++k)
            {
                m->maze_grid[i][j][k] = 0;
                m->mark[i][j][k] = 0;
            }
        }
    }
    m->height = 0;
    m->length = 0;
    m->width = 0;
}
void action_print(int action)
{
    switch (action)
    {
    case road:
        cout << "road";
        break;
    case wall:
        cout << "wall";
        break;
    case up_stair:
        cout << "up_stair";
        break;
    case E:
        cout << "E";
        break;
    case ES:
        cout << "ES";
        break;
    case S:
        cout << "S";
        break;
    case W:
        cout << "W";
        break;
    case WN:
        cout << "WN";
        break;
    case N:
        cout << "N";
        break;
    case NE:
        cout << "NE";
        break;
    case down_stair:
        cout << "down_stair";
        break;
    case dead_space:
        cout << "dead_space";
        break;
    case start1:
        cout << "start1";
        break;
    case end1:
        cout << "end1";
        break;
    default:
        cout << "error";
        break;
    }
}
/*

3 6 7
1 1 1 1 1 1 1
1 0 0 0 0 0 1
1 0 1 1 1 0 1
1 0 1 1 0 0 1
1 1 1 1 0 1 1
1 1 1 1 1 1 1

1 1 1 1 1 1 1
1 1 1 1 1 1 1
1 1 1 1 1 1 1
1 1 1 0 1 1 1
1 1 1 0 0 0 1
1 1 1 1 1 1 1

1 1 1 1 1 1 1
1 1 1 1 1 1 1
1 1 1 1 1 1 1
1 1 0 1 1 1 1
1 1 1 1 1 0 1
1 1 1 1 1 1 1
1 1 1
3 4 5

*/