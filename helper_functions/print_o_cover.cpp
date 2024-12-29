#include<iostream>
#include<vector>
using namespace std;

void print_image_cover(vector<vector<int> > &image,int n,int m,vector<vector<int> > &rect, int grid_size=0)
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            
            if(i>=rect[0][0] && i<=rect[1][0] && j>=rect[0][1] && j<=rect[1][1] && grid_size!=0 && (i-rect[0][0])%grid_size==0 && (j-rect[0][1])%grid_size==0)
            {

                cout<<"\033[32m"<<image[i][j]<<"\033[0m";
            }
            else if(image[i][j]==4) cout<<"\033[34m"<<image[i][j]<<"\033[0m";
            else if(image[i][j]==0)
                cout<<"\033[31m"<<image[i][j]<<"\033[0m";
            else if(image[i][j]==8)
                cout<<"\033[33m"<<image[i][j]<<"\033[0m";
            else
                cout<<image[i][j];
        }
        cout<<endl;
    }
}
