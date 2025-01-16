#include <iostream>
#include <fstream>
#include <cstdint>
#include <vector>
using namespace std;

vector<int> get_rectangle(std::fstream &output_bmp,std::ifstream &input_bmp,int offset,int rowsize,int height,int width,int grid_size)
{
    vector<int> rect;
    rect.push_back(0);
    rect.push_back(0);
    rect.push_back(width-1);
    rect.push_back(height-1);
    int top=height-1;
    int left=width-1;
    int right=0;
    int bottom=0;
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            std::vector<uint8_t> color_rgb(3);
            int a_offset=offset+i*rowsize+j*3;
            input_bmp.seekg(a_offset,std::ios::beg);
            input_bmp.read(reinterpret_cast<char*>(color_rgb.data()),3);
            if(!(color_rgb[0]==255 && color_rgb[1]==255 && color_rgb[2]==255 ))
            {
                if(i<top)top=i;
                if(i>bottom)bottom=i;
                if(j<left)left=j;
                if(j>right)right=j;
            }
        }
    }
    

    // for(int i=top;i<=bottom;i++)
    // {
    //     int a_offset=offset+(i+rect[1])*rowsize+(j+rect[0])*3;
    //     std::vector<uint8_t> color_rgb(3);
    //     output_bmp.seekg(a_offset,std::ios::beg);
    //     for(int i=0;i<color_rgb.size();i++)
    //     {
    //         output_bmp.write(reinterpret_cast<char*>(&color_rgb[i]),1);
    //     }
    // }
    // for(int i=left;i<=right;i++);
    // {

    // }

    if((bottom-top+1)%grid_size!=0)
    {
        int x=(bottom-top+1)%grid_size;
        x=grid_size-x;
        bottom+=x/2;
        top-=x/2;
        if(x%2) bottom++;
    }
    
    if((right-left+1)%grid_size!=0)
    {
        int x=(right-left+1)%grid_size;
        x=grid_size-x;
        right+=x/2;
        left-=x/2;
        if(x%2) right++;
    }
    
    left-=grid_size;
    right+=grid_size;
    top-=grid_size;
    bottom+=grid_size;

    bottom++;
    right++;
    rect[0]=left;
    rect[1]=top;
    rect[2]=right;
    rect[3]=bottom;

    return rect;
}


