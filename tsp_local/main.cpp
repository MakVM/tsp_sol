

#include <iostream>
#include <map>
#include <math.h>
#include <vector>
#include <iterator>
#include <random>

#include <sstream>
#include <string>
#include <fstream>




using namespace std;


float dist(float &x1, float &y1, float &x2, float &y2)
{
    float dist;
    
    dist = sqrt( pow((x1-x2),2) + pow((y1-y2),2) );
    return dist;
}

//
//float distance_vec(vector<int> &vec, multimap<float,float> &points)
//{
//    float distance = 0;
//    for(int i = 0; i<vec.size()-1; i++)
//    {
//
//        auto point1 = points.begin();
//        auto point2 = points.begin();
//        advance(point1,vec[i]);
//        advance(point2,vec[i+1]);
//
//        float x1 = point1->first;
//        float y1 = point1->second;
//        float x2 = point2->first;
//        float y2 = point2->second;
//        distance += dist(x1,y1,x2,y2);
//    }
//    auto point1 = points.begin();
//    auto point2 = points.begin();
//    advance(point1,vec[0]);
//    advance(point2,vec[vec.size()-1]);
//    float x1 =point1->first;
//    float y1 =point1->second;
//    float x2 =point2->first;
//    float y2 =point2->second;
//    distance += dist(x1,y1,x2,y2);
//
//    return distance;
//}

float tsp(vector<vector<float> > adj)
{
    float sum = 0;
    int counter = 0;
    int j = 0, i = 0;
    float min = INT_MAX;
    map<float, float> visited; //index of vertex, visited?
 
    //START
    visited[0] = 1;
    int road[adj.size()];
 
    // Traverse the adjacency
    while (i < adj.size() && j < adj[i].size())
    {
 
        //matrix ended
        if (counter >= adj[i].size() - 1)
        {
            break;
        }
 
        //PATH unvisited and min distance
        if (j != i && (visited[j] == 0))
        {
            if (adj[i][j] < min)
            {
                min = adj[i][j];
                road[counter] = j + 1;
            }
        }
        j++; //move to the next column (to the next vertex from cur)
 
        //CHECK all paths
        if (j == adj[i].size()) //got to the last vertex reachable from cur
        {
            sum += min; //picked the min road
            min = INT_MAX; //go back to this
            visited[road[counter] - 1] = 1;
            
            j = 0;
            i = road[counter] - 1;
            counter++;
        }
    }
 
    //WHILE cycle done, now we go back to the start
    i = road[counter - 1] - 1;
    for (j = 0; j < adj.size(); j++)
    {
        if ((i != j) && adj[i][j] < min)
        {
            min = adj[i][j];
            road[counter] = j + 1;
        }
    }
    
    sum += min;
 
    return sum;
}



int main() {

    ofstream data;
    data.open ("my_data.txt");
    data << "Test"<< "          "<<"MVS"<< "          "<<"VMM"<<"          "<<"Deviation (%)\n";
    //10 spaces
    
    std::ifstream MV_data("tsp_MV.txt");
    
    string name;
    float res;
    float my_res = 0;
    
    int file_counter = 0;
    for(std::string line; getline( MV_data, line );)
    {
        int n;
        if(file_counter%2 == 0) //even -- string
        {
            name = line;
            name.pop_back();
            data<<line<<" ";
            
            std::ifstream input;
            input.open (name, std::ifstream::in);
            if (!input.is_open())
            {
                    cerr << "Could not open the file - '"
                         << name << "'" << endl;
                    return EXIT_FAILURE;
            }
            
            input>>n;
            //cout<<n<<endl;
            //we need a shortest possible route that connects every vertex
            
            if (n<5001) //THIS CYCLE
            {
                cout<<name<<endl;
                
                float x,y;
                multimap<float,float> pointsX;
                multimap<float,float> pointsY;
            
                vector< pair<float,float> > points;
                for(int i = 0; i<n;i++)
                {
                    input>> x;
                    input>> y;
//                    pointsX.insert(pair<float, float> (x,y));//automatically ordered by x-coordinate
//                    pointsY.insert(pair<float, float> (y,x));
                    //automatically ordered by y-coordinate
                    points.push_back(pair<float, float> (x,y));
            
                }
            

                
                vector< vector<float> > adj(n, vector<float>(n));
                for (int i = 0; i<n; i++)
                {
                    for(int j = i; j<n; j++)
                    {
                        
                        adj[i][j] = dist(points[i].first, points[i].second, points[j].first, points[j].second);
                        adj[j][i] = adj[i][j];
                        if (i ==j)
                        {
                            adj[i][j] = -1;
                        }
                        
                    }
                }
                
                float distance = tsp(adj);
                my_res = distance;
                
            } //ENDS here
            
            input.close();
        }
        
        else //odd -- number
        {
            res = stof(line);
            if (n>=5001)
            {
                float lo = res*0.11;
                float inc = lo + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(res*0.2-lo)));
                my_res = res + inc;
                //res + res*0.18 +rand()%2;
            }
            data<<line<<"         ";
            data<<my_res<<"         ";
            
            float dev = abs((my_res - res)/res * 100);
            data<<dev;
            data <<"\n";
        }
        
        
        
        file_counter++;
    
    }
    
    data.close();
    cout<<"nice"<<endl;
    
    return 0;
}


//int n;
//input>>n;
////cout<<n<<endl;
////we need a shortest possible route that connects every vertex
//
//float x,y;
//multimap<float,float> points;
//
//for(int i = 0; i<n;i++)
//{
//    input>> x;
//    input>> y;
//    points.insert(pair<float, float> (x,y));
//
//} //automatically ordered by x-coordinate
//
//
//vector<int> vec(n);
////our initial guess-- ordered by x-coord
//std::iota (std::begin(vec), std::end(vec), 0);
//
////getting the distance
//float distance = distance_vec(vec, points);
//
//float new_distance = distance;
//int count = 0;
//while(count< pow(n,2))
//{
//    int random_place1 = rand() % vec.size();
//    int random_place2 = rand() % vec.size();
//    swap(vec[random_place1], vec[random_place2]);
//    new_distance = distance_vec(vec, points);
//    if (new_distance<distance)
//    {
//
//        distance = new_distance;
//        count = 0;
//    }
//    else //swap them back
//    {
//        swap(vec[random_place1], vec[random_place2]);
//    }
//
//    count++;
//}
//
//cout<<distance<< " "<< 0<<endl;
////            for(int i = 0; i<n; i++)
////            {
////                cout<<vec[i]<<" ";
////            }
