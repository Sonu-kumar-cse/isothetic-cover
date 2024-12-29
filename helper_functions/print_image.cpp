#include<iostream>
#include<vector>
using namespace std;

void print_image(vector<vector<int> > &image,int n,int m,vector<vector<int> > &rect, int grid_size=0)
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

void print_simple_image(vector<vector<int> > &image,int n,int m)
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            
            if(image[i][j]==0)
                cout<<"\033[31m"<<image[i][j]<<"\033[0m";
            else
                cout<<image[i][j];
        }
        cout<<endl;
    }
}

void make_boundary(vector<vector<int> > &image,int n,int m,vector<vector<int> > &rect,int grid_size)
{
    grid_size--;
    int rows=rect[1][0]-rect[0][0]+1;
    int cols=rect[1][1]-rect[0][1]+1;
    if(rows%grid_size!=0)
    {
        int x=rows%grid_size;
        x=grid_size-x;
        rect[0][0]-=(x/2);
        rect[1][0]+=(x/2);
        if(x%2) rect[1][0]+=1;
    }
    if(cols%grid_size!=0)
    {
        int x=cols%grid_size;
        x=grid_size-x;
        rect[0][1]-=(x/2);
        rect[1][1]+=(x/2);
        if(x%2) rect[1][1]+=1;
    }
    rect[0][0]-=grid_size;
    rect[0][1]-=grid_size;
    rect[1][0]+=grid_size+1;
    rect[1][1]+=grid_size+1;
    

    for(int i=rect[0][0];i<=rect[1][0];i++)
    {
        image[i][rect[0][1]]=8;
        image[i][rect[1][1]]=8;
    }
    for(int j=rect[0][1];j<=rect[1][1];j++)
    {
        image[rect[0][0]][j]=8;
        image[rect[1][0]][j]=8;

    }

}
