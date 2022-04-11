

#include <iostream>
#include <map>
#include <math.h>
#include <vector>
#include <iterator>

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
    cout<< distance<<endl;
    
    
    
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
