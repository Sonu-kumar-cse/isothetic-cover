#include<iostream>
#include <cstdlib>
#include<vector>
#include <fstream>
#include<utility>
#include "helper_functions/print_image.cpp"
#include "helper_functions/find_rectangle.cpp"
#include "helper_functions/outer_cover.cpp"


using namespace std;

int main()
{
    string filename="inputs/input4.txt";
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
    cout<<"now hold enter button or press one by one to see the making of isothetic cover";
    getchar();
    cout<<"image with grid points"<<endl;
    

    make_boundary(image,total_rows,total_columns,rectangle,grid_size);

    getchar();
    system("clear");

    print_image(image,total_rows,total_columns,rectangle,grid_size-1);


    vector<vector<pair<int,int> > > outer_covers;

    outer_covers=get_outer_cover(image,total_rows,total_columns,rectangle,grid_size-1);

    ofstream outFile;

    // Open a file for writing
    outFile.open("result/output.txt");

    // Check if the file is open
    if (outFile.is_open()) {
        // Write data to the file
        outFile<<"grid size = "<<grid_size<<endl;
        outFile<<"total outer isothetic covers = "<<outer_covers.size()<<endl<<endl;
        for(int i=0;i<outer_covers.size();i++)
        {
            
            outFile<<"points of outer isothetic cover "<<i+1<<endl;
            for(int j=0;j<outer_covers[i].size();j++)
            {
                outFile<<outer_covers[i][j].first<<" "<<outer_covers[i][j].second<<endl;
            }
            outFile<<endl;

        }


        // Close the file
        outFile.close();

    } else {
        std::cerr << "Failed to open the file for writing!" << std::endl;
    }


    cout<<endl;
    print_image(image,total_rows,total_columns,rectangle,grid_size-1);
    getchar();
    system("clear");
    print_simple_image(image,total_rows,total_columns);
}