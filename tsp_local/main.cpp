

#include <iostream>
#include <map>
#include <math.h>

using namespace std;


int distance(pair<int,int> &p1, pair<int,int> &p2)
{
    int dist;
    
    dist = sqrt( pow((p1.first - p2.first),2) + pow((p1.second - p2.second),2) );
    return dist;
}


int main() {

    int n;
    cin>> n;
    //we need a shortest possible route that connects every vertex
    
    int x,y;
    multimap<int,int> points;
    
    for(int i = 0; i<n;i++)
    {
        cin>> x;
        cin>> y;
        points.insert(pair<int, int> (x,y));
        
    } //automatically ordered by x-coordinate
    
    
    
    multimap<int, int>::iterator itr;
    for (itr = points.begin(); itr != points.end(); ++itr) {
            cout << '\t' << itr->first << '\t' << itr->second
                 << '\n';
        }
    //cout distance(length of cycle) 0
    //vertices numbered in the cycle??
    
    return 0;
}
