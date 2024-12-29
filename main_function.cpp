#include<iostream>
#include <cstdlib>
#include<vector>
#include <fstream>
#include "helper_functions/print_image.cpp"
#include "helper_functions/find_rectangle.cpp"
#include "outer_cover.cpp"


using namespace std;

int main()
{
    string filename="inputs/input1.txt";
    fstream input(filename);
    if (!input.is_open()) {
        cerr << "Error: Could not open the file " << filename << endl;
        return 1;
    }
    int total_rows,total_columns;
    input>>total_rows>>total_columns;
   

    vector<vector<int> > image(total_rows,vector<int>(total_columns));
    for(int i=0;i<total_rows;i++)
        for(int j=0;j<total_columns;j++)input>>image[i][j];
    
    
     
    vector<vector<int> > rectangle;
    system("clear");
    print_simple_image(image,total_rows,total_columns);
    getchar();
    system("clear");
    rectangle=find_rect(image,total_rows,total_columns);
    
    cout<<"enter grid size :"; 
    int grid_size;
    cin>>grid_size;
  
    

    make_boundary(image,total_rows,total_columns,rectangle,grid_size);

    print_image(image,total_rows,total_columns,rectangle,grid_size-1);

    get_outer_cover(image,total_rows,total_columns,rectangle,grid_size-1);
    cout<<endl;
    print_image(image,total_rows,total_columns,rectangle,grid_size-1);
}