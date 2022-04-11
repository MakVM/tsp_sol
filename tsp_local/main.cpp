

#include <iostream>
#include <map>
#include <math.h>
#include <vector>
#include <iterator>
#include <random>

using namespace std;


float dist(float &x1, float &y1, float &x2, float &y2)
{
    float dist;
    
    dist = sqrt( pow((x1-x2),2) + pow((y1-y2),2) );
    return dist;
}

float distance_cycle(vector<vector<int>> &graph, multimap<float,float> &points)
{
    float distance = 0;
    for(int i = 0; i<graph.size(); i++)
    {
        for(int j = 0; j<graph.size(); j++)
        {
            if(graph[i][j] == 1)
            {
                auto point1 = points.begin();
                auto point2 = points.begin();
                advance(point1,i);
                advance(point2,j);
                
                float x1 =point1->first;
                float y1 =point1->second;
                float x2 =point2->first;
                float y2 =point2->second;
                distance += dist(x1,y1,x2,y2);
            }
        }
    }
    
    return distance;
}

vector<vector<int>> changed_three(vector<vector<int>> graph)
{
    for(int c = 0; c<3; c++)
    {
        int random_vertex = rand() % graph.size();
        int random_dest = rand() % graph.size();
        
        //making sure it doesn't lead to itself:
        while (random_dest == random_vertex)
        {
            random_dest = rand() % graph.size();
        }
        
        for(int j = 0; j<graph.size(); j++)
        {
            if(graph[random_vertex][j] == 1)
            {
                graph[random_vertex][j] = 0;
            }
        }
        graph[random_vertex][random_dest] = 1;
    }
    
    return graph;
}

bool still_hamiltonian(vector<vector<int>> &graph)
{
    //check that there's ONLY one 1 per column
    for(int j = 0; j<graph.size(); j++)
    {
        int check = 0;
        for(int i = 0; i<graph.size(); i++)
        {
            if(graph[i][j] == 1)
            {
                check ++;
            }
        }
        if(check != 1)
        {
            return false;
        }
    }
    return true;
}


int main() {

    int n;
    cin>> n;
    //we need a shortest possible route that connects every vertex
    
    float x,y;
    multimap<float,float> points;
    
    for(int i = 0; i<n;i++)
    {
        cin>> x;
        cin>> y;
        points.insert(pair<float, float> (x,y));
        
    } //automatically ordered by x-coordinate
    
    vector<vector<int>> graph(n, vector<int>(n, 0));
    
    
    //initial guess
    graph[n-1][0] = 1;
    for(int i = 0; i<n-1; i++)
    {
        for(int j = 0; j<n; j++)
        {
            if(j == i+1)
            {
                graph[i][j] = 1;
            }
        }
    }

    //getting the distance
    float distance = distance_cycle(graph, points);
    float new_distance = distance;
    //cout<< distance<<endl;
    
    int count = 0;
    while(count < pow(n,2))
    {
        graph = changed_three(graph);

        if (still_hamiltonian(graph))
        {
            for(int i = 0; i<n; i++)
            {
                for(int j = 0; j<n; j++)
                {
        
                    cout<<graph[i][j]<<" ";
                }
                cout<<endl;
            }
            new_distance = distance_cycle(graph, points);
        }
        
        if (new_distance < distance)
        {
            distance = new_distance;
            count = 0;
        }
        count ++;
    }
    cout<<"The optimal length is:::"<<endl;
    cout<<new_distance<<endl;
    
//    multimap<float, float>::iterator itr;
//    for (itr = points.begin(); itr != points.end(); ++itr)
//    {
//            cout << '\t' << itr->first << '\t' << itr->second
//                 << '\n';
//        }
    
    //    for(int i = 0; i<n; i++)
    //    {
    //        for(int j = 0; j<n; j++)
    //        {
    //
    //            cout<<graph[i][j]<<" ";
    //        }
    //        cout<<endl;
    //    }
    
    
    //cout distance(length of cycle) 0
    //vertices numbered in the cycle??
    
    return 0;
}
