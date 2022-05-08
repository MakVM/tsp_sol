

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


float distance_vec(vector<int> &vec, multimap<float,float> &points)
{
    float distance = 0;
    for(int i = 0; i<vec.size()-1; i++)
    {

        auto point1 = points.begin();
        auto point2 = points.begin();
        advance(point1,vec[i]);
        advance(point2,vec[i+1]);
        
        float x1 =point1->first;
        float y1 =point1->second;
        float x2 =point2->first;
        float y2 =point2->second;
        distance += dist(x1,y1,x2,y2);
    }
    auto point1 = points.begin();
    auto point2 = points.begin();
    advance(point1,vec[0]);
    advance(point2,vec[vec.size()-1]);
    float x1 =point1->first;
    float y1 =point1->second;
    float x2 =point2->first;
    float y2 =point2->second;
    distance += dist(x1,y1,x2,y2);
    
    return distance;
}


int main() {

    FILE * my_data;
    my_data = fopen("data.txt", "wb");
    if (my_data == NULL)
    {
        perror("Opening Error");
        return 0;
    }
    
    std::ifstream MV_data("tsp_MV.txt");
    std::string line_name;
    std::string line_res;
    while (std::getline(MV_data, line_name))
    {
        std::istringstream iss(line_name);
        string name;
        if (!(iss >> name)) {
            cout<<"flop"<<endl;
            break;
        } // error
        // process pair (a,b)
        cout<<name<<endl;
        
//        std::getline(MV_data, line_res);
//        std::istringstream iss2(line_res);
//        int res;
//        if (!(iss2 >> res)) { break; } // error
//        // process pair (a,b)
//        cout<<res<<endl;
    }
    
    fclose(my_data);
    cout<<"nice"<<endl;
    
    
    
//    int n;
//    cin>> n;
//    //we need a shortest possible route that connects every vertex
//
//    float x,y;
//    multimap<float,float> points;
//
//    for(int i = 0; i<n;i++)
//    {
//        cin>> x;
//        cin>> y;
//        points.insert(pair<float, float> (x,y));
//
//    } //automatically ordered by x-coordinate
//
//
//    vector<int> vec(n);
//    //our initial guess-- ordered by x-coord
//    std::iota (std::begin(vec), std::end(vec), 0);
//
//    //getting the distance
//    float distance = distance_vec(vec, points);
//
//    float new_distance = distance;
//    int count = 0;
//    while(count< pow(n,2))
//    {
//        int random_place1 = rand() % vec.size();
//        int random_place2 = rand() % vec.size();
//        swap(vec[random_place1], vec[random_place2]);
//        new_distance = distance_vec(vec, points);
//        if (new_distance<distance)
//        {
//
//            distance = new_distance;
//            count = 0;
//        }
//        else //swap them back
//        {
//            swap(vec[random_place1], vec[random_place2]);
//        }
//
//        count++;
//    }
//
//    cout<<distance<< " "<< 0<<endl;
//    for(int i = 0; i<n; i++)
//    {
//        cout<<vec[i]<<" ";
//    }
//
    
    return 0;
}
