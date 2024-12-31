#include<iostream>
#include<vector>

using namespace std;


vector<vector<int> > find_rect(vector<vector<int> > &image, int n,int m)
{
    
    vector<vector<int> > rect;
    int top,bottom,left,right;
    top=n;
    bottom=0;
    left=m;
    right=0;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            if(image[i][j]==0)
            {
                if(i<top)top=i;
                if(i>bottom)bottom=i;
            }
        }
    }
    for(int j=0;j<m;j++)
    {
        for(int i=0;i<n;i++)
        {
            if(image[i][j]==0)
            {
                if(j>right)right=j;
                if(j<left)left=j;
            }
        }
    }
    vector<int> temp;
    temp.push_back(top);
    temp.push_back(left);
    rect.push_back(temp);
    temp.pop_back();
    temp.pop_back();
    temp.push_back(bottom);
    temp.push_back(right);
    rect.push_back(temp);




    return rect;
}