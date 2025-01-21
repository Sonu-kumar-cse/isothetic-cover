#include <iostream>
#include <fstream>
#include <cstdint>
#include <vector>


std::vector<uint8_t> getDataO(std::fstream &output_bmp,int offset,int i,int j,int grid_size,std::vector<int> &rect,int rowsize,int height,int width)
{
    std::vector<uint8_t> color_rgb(3);
    int a_offset=offset+(i+rect[1])*rowsize+(j+rect[0])*3;

    output_bmp.seekg(a_offset,std::ios::beg);
    output_bmp.read(reinterpret_cast<char*>(color_rgb.data()),3);
    return color_rgb;
} 


std::vector<uint8_t> getDataI(std::ifstream &input_bmp,int offset,int i,int j,int grid_size,std::vector<int> &rect,int rowsize,int height,int width)
{
    std::vector<uint8_t> color_rgb(3);
    int a_offset=offset+(i+rect[1])*rowsize+(j+rect[0])*3;

    input_bmp.seekg(a_offset,std::ios::beg);
    input_bmp.read(reinterpret_cast<char*>(color_rgb.data()),3);
    return color_rgb;
} 


void setcolor_rgb(std::fstream &output_bmp,int offset,int i,int j,int grid_size,std::vector<int> &rect,int rowsize,int height,int width,std::vector<u_int8_t> color_rgb)
{
    int a_offset=offset+(i+rect[1])*rowsize+(j+rect[0])*3;
    
    output_bmp.seekg(a_offset,std::ios::beg);
    for(int i=0;i<color_rgb.size();i++)
    {
        output_bmp.write(reinterpret_cast<char*>(&color_rgb[i]),1);
    }
}

bool checkIsvisited(std::fstream &output_bmp,int offset,int i,int j,int grid_size,std::vector<int> &rect,int rowsize,int height,int width)
{
    std::vector<uint8_t> color_rgb=getDataO(output_bmp,offset,i,j,grid_size,rect,rowsize,height,width);
    int blue=(int)color_rgb[0];
    int green=(int)color_rgb[1];
    int red=(int)color_rgb[2];

    if(blue==255 && green==0 && red==0) return true;

    return false;
}

void markVisited(std::fstream &output_bmp,int offset,int i,int j,int grid_size,std::vector<int> &rect,int rowsize,int height,int width)
{
    std::vector<u_int8_t> color_rgb(3);
    color_rgb[0]=255;
    color_rgb[1]=0;
    color_rgb[2]=0;
    setcolor_rgb(output_bmp,offset,i,j,grid_size,rect,rowsize,height,width,color_rgb);
}

int getType(std::vector<bool> ugb_occ)
{
    int count=0;
    for(int i=0;i<ugb_occ.size();i++)
    {
        if(ugb_occ[i]) count++;
    }
    if(count==1) return 1;
    if(count==3) return -1;
    if(count==4) return 0;
    if((ugb_occ[0] && ugb_occ[2]) || (ugb_occ[1] && ugb_occ[3])) return -1;
    return 0;
}

void make_cover_line(std::fstream &output_bmp,int offset,int p,int q,int m,int n,int grid_size,std::vector<int> &rect,int rowsize,int height,int width)
{
    if(q==n)
    {
        if(p>m)
        {
            for(int i=p-1;i>m;i--)
            {
                std::vector<u_int8_t> color_rgb(3);
                color_rgb[0]=0;
                color_rgb[1]=0;
                color_rgb[2]=0;
                setcolor_rgb(output_bmp,offset,i,q,grid_size,rect,rowsize,height,width,color_rgb);
               
            }
        }
        else{
            for(int i=p+1;i<m;i++)
            {
                std::vector<u_int8_t> color_rgb(3);
                color_rgb[0]=0;
                color_rgb[1]=0;
                color_rgb[2]=0;
                setcolor_rgb(output_bmp,offset,i,q,grid_size,rect,rowsize,height,width,color_rgb);
               
            }
        }
    }
    else{
        if(q<n)
        {
            for(int i=q+1;i<n;i++)
            {
                std::vector<u_int8_t> color_rgb(3);
                color_rgb[0]=0;
                color_rgb[1]=0;
                color_rgb[2]=0;
                setcolor_rgb(output_bmp,offset,p,i,grid_size,rect,rowsize,height,width,color_rgb);
               
            }
            
        }
        else{
            for(int i=q-1;i>n;i--)
            {
                std::vector<u_int8_t> color_rgb(3);
                color_rgb[0]=0;
                color_rgb[1]=0;
                color_rgb[2]=0;
                setcolor_rgb(output_bmp,offset,p,i,grid_size,rect,rowsize,height,width,color_rgb);
               
            }
        }
    }
}


std::vector<bool> get_ugb_occ(std::ifstream &input_bmp,int offset,int i,int j,int grid_size,std::vector<int> &rect,int rowsize,int height,int width)
{
    std::vector<bool> ugb_occ(4,false);
    int m=rect[3]-rect[1]+1;
    int n=rect[2]-rect[0]+1;
    if(i+grid_size<m && j+grid_size<n)
    {
       for(int k=i;k<=i+grid_size;k++)
       {
            std::vector<u_int8_t> color_rgb=getDataI(input_bmp,offset,k,j,grid_size,rect,rowsize,height,width);
            int blue=(int)color_rgb[0];
            int green=(int)color_rgb[1];
            int red=(int)color_rgb[2];
            if(!(blue==255 && green==255 && red==255))
            {
                ugb_occ[3]=true;
                break;
            }
            color_rgb=getDataI(input_bmp,offset,k,j+grid_size,grid_size,rect,rowsize,height,width);
            blue=(int)color_rgb[0];
            green=(int)color_rgb[1];
            red=(int)color_rgb[2];
            if(!(blue==255 && green==255 && red==255))
            {
                ugb_occ[3]=true;
                break;
            }
       }
       if(!ugb_occ[3])
            for(int k=j;k<=j+grid_size;k++)
            {
                std::vector<u_int8_t> color_rgb=getDataI(input_bmp,offset,i,k,grid_size,rect,rowsize,height,width);
                int blue=(int)color_rgb[0];
                int green=(int)color_rgb[1];
                int red=(int)color_rgb[2];
                if(!(blue==255 && green==255 && red==255))
                {
                    ugb_occ[3]=true;
                    break;
                }
                color_rgb=getDataI(input_bmp,offset,i+grid_size,k,grid_size,rect,rowsize,height,width);
                blue=(int)color_rgb[0];
                green=(int)color_rgb[1];
                red=(int)color_rgb[2];
                if(!(blue==255 && green==255 && red==255))
                {
                    ugb_occ[3]=true;
                    break;
                }
            } 
    }
    if(i+grid_size<m && j-grid_size>=0)
    {
        for(int k=i;k<=i+grid_size;k++)
       {
            std::vector<u_int8_t> color_rgb=getDataI(input_bmp,offset,k,j,grid_size,rect,rowsize,height,width);
            int blue=(int)color_rgb[0];
            int green=(int)color_rgb[1];
            int red=(int)color_rgb[2];
            if(!(blue==255 && green==255 && red==255))
            {
                ugb_occ[2]=true;
                break;
            }
            color_rgb=getDataI(input_bmp,offset,k,j-grid_size,grid_size,rect,rowsize,height,width);
            blue=(int)color_rgb[0];
            green=(int)color_rgb[1];
            red=(int)color_rgb[2];
            if(!(blue==255 && green==255 && red==255))
            {
                ugb_occ[2]=true;
                break;
            }
       }
       if(!ugb_occ[2])
            for(int k=j-grid_size;k<=j;k++)
            {
                std::vector<u_int8_t> color_rgb=getDataI(input_bmp,offset,i,k,grid_size,rect,rowsize,height,width);
                int blue=(int)color_rgb[0];
                int green=(int)color_rgb[1];
                int red=(int)color_rgb[2];
                if(!(blue==255 && green==255 && red==255))
                {
                    ugb_occ[2]=true;
                    break;
                }
                color_rgb=getDataI(input_bmp,offset,i+grid_size,k,grid_size,rect,rowsize,height,width);
                blue=(int)color_rgb[0];
                green=(int)color_rgb[1];
                red=(int)color_rgb[2];
                if(!(blue==255 && green==255 && red==255))
                {
                    ugb_occ[2]=true;
                    break;
                }
            } 

    }
    if(i-grid_size>=0 && j-grid_size>=0)
    {
        for(int k=i-grid_size;k<=i;k++)
       {
            std::vector<u_int8_t> color_rgb=getDataI(input_bmp,offset,k,j,grid_size,rect,rowsize,height,width);
            int blue=(int)color_rgb[0];
            int green=(int)color_rgb[1];
            int red=(int)color_rgb[2];
            if(!(blue==255 && green==255 && red==255))
            {
                ugb_occ[1]=true;
                break;
            }
            color_rgb=getDataI(input_bmp,offset,k,j-grid_size,grid_size,rect,rowsize,height,width);
            blue=(int)color_rgb[0];
            green=(int)color_rgb[1];
            red=(int)color_rgb[2];
            if(!(blue==255 && green==255 && red==255))
            {
                ugb_occ[1]=true;
                break;
            }
       }
       if(!ugb_occ[1])
            for(int k=j-grid_size;k<=j;k++)
            {
                std::vector<u_int8_t> color_rgb=getDataI(input_bmp,offset,i,k,grid_size,rect,rowsize,height,width);
                int blue=(int)color_rgb[0];
                int green=(int)color_rgb[1];
                int red=(int)color_rgb[2];
                if(!(blue==255 && green==255 && red==255))
                {
                    ugb_occ[1]=true;
                    break;
                }
                color_rgb=getDataI(input_bmp,offset,i-grid_size,k,grid_size,rect,rowsize,height,width);
                blue=(int)color_rgb[0];
                green=(int)color_rgb[1];
                red=(int)color_rgb[2];
                if(!(blue==255 && green==255 && red==255))
                {
                    ugb_occ[1]=true;
                    break;
                }
            } 
    }
    if(i-grid_size>=0 && j+grid_size<n)
    {
        for(int k=i-grid_size;k<=i;k++)
       {
            std::vector<u_int8_t> color_rgb=getDataI(input_bmp,offset,k,j,grid_size,rect,rowsize,height,width);
            int blue=(int)color_rgb[0];
            int green=(int)color_rgb[1];
            int red=(int)color_rgb[2];
            if(!(blue==255 && green==255 && red==255))
            {
                ugb_occ[0]=true;
                break;
            }
            color_rgb=getDataI(input_bmp,offset,k,j+grid_size,grid_size,rect,rowsize,height,width);
            blue=(int)color_rgb[0];
            green=(int)color_rgb[1];
            red=(int)color_rgb[2];
            if(!(blue==255 && green==255 && red==255))
            {
                ugb_occ[0]=true;
                break;
            }
       }
       if(!ugb_occ[0])
            for(int k=j;k<=j+grid_size;k++)
            {
                std::vector<u_int8_t> color_rgb=getDataI(input_bmp,offset,i,k,grid_size,rect,rowsize,height,width);
                int blue=(int)color_rgb[0];
                int green=(int)color_rgb[1];
                int red=(int)color_rgb[2];
                if(!(blue==255 && green==255 && red==255))
                {
                    ugb_occ[0]=true;
                    break;
                }
                color_rgb=getDataI(input_bmp,offset,i-grid_size,k,grid_size,rect,rowsize,height,width);
                blue=(int)color_rgb[0];
                green=(int)color_rgb[1];
                red=(int)color_rgb[2];
                if(!(blue==255 && green==255 && red==255))
                {
                    ugb_occ[0]=true;
                    break;
                }
            } 
    }
    return ugb_occ;
}



void trace_o_cover(std::ifstream &input_bmp,std::fstream &output_bmp,int offset,int i,int j,std::vector<int> &rect,int rowsize,int height,int width,int grid_size,int type)
{
    markVisited(output_bmp,offset,i,j,grid_size,rect,rowsize,height,width);
    int direction=2;
    bool is_hole=false;
    if(type==-1) 
    {
        is_hole=true;
    }
    int curr_i=i;
    int curr_j=j;
    int next_i=curr_i,next_j=curr_j;

    std::cout<<curr_i<<" "<<curr_j<<std::endl;

    if(is_hole) type*=-1;

    direction=(direction+type)%4;
    std::cout<<direction<<" "<<type<<std::endl;
    if(direction==0) next_j+=grid_size;
    else if(direction==1) next_i-=grid_size;
    else if(direction==2) next_j-=grid_size;
    else next_i+=grid_size;
    make_cover_line(output_bmp,offset,curr_i,curr_j,next_i,next_j,grid_size,rect,rowsize,height,width);
    curr_i=next_i;
    curr_j=next_j;
    // std::cout<<curr_i<<" "<<curr_j<<std::endl;
    

    while(!(curr_i==i && curr_j==j))
    {
        
        markVisited(output_bmp,offset,curr_i,curr_j,grid_size,rect,rowsize,height,width);
        std::vector<bool> ugb_occ=get_ugb_occ(input_bmp,offset,curr_i,curr_j,grid_size,rect,rowsize,height,width);
        type=getType(ugb_occ);
        // std::cout<<direction<<" "<<type<<std::endl;

        if(is_hole) {
            
            type*=-1;
        }
        direction=(direction+type)%4;
        if(direction==-1)direction=3;
        if(direction==0) next_j+=grid_size;
        else if(direction==1) next_i-=grid_size;
        else if(direction==2) next_j-=grid_size;
        else next_i+=grid_size;
    
        make_cover_line(output_bmp,offset,curr_i,curr_j,next_i,next_j,grid_size,rect,rowsize,height,width);

        curr_i=next_i;
        curr_j=next_j;
        

        // std::cout<<curr_i<<" "<<curr_j<<std::endl;
    }
    

}

void clearBlueLines(std::ifstream &input_bmp,std::fstream &output_bmp,int offset,std::vector<int> &rect,int rowsize,int height,int width,int grid_size)
{
    int m=rect[3]-rect[1]+1;
    int n=rect[2]-rect[0]+1;
    for(int i=0;i<m;i+=grid_size)
    {
        for(int j=0;j<n;j+=grid_size)
        {
            if(checkIsvisited(output_bmp,offset,i,j,grid_size,rect,rowsize,height,width))
            {   
                
                std::vector<u_int8_t> color_rgb(3);
                color_rgb[0]=255;
                color_rgb[1]=255;
                color_rgb[2]=255;
                
                std::vector<u_int8_t> color_rgb_left=getDataO(output_bmp,offset,i,j-1,grid_size,rect,rowsize,height,width);
                std::vector<u_int8_t> color_rgb_right=getDataO(output_bmp,offset,i,j+1,grid_size,rect,rowsize,height,width);
                std::vector<u_int8_t> color_rgb_top=getDataO(output_bmp,offset,i-1,j,grid_size,rect,rowsize,height,width);
                std::vector<u_int8_t> color_rgb_bottom=getDataO(output_bmp,offset,i+1,j,grid_size,rect,rowsize,height,width);
                if((color_rgb_left[0]==0 && color_rgb_left[1]==0 && color_rgb_left[2]==0) || (color_rgb_right[0]==0 && color_rgb_right[1]==0 && color_rgb_right[2]==0)  ||  (color_rgb_top[0]==0 && color_rgb_top[1]==0 && color_rgb_top[2]==0) || (color_rgb_bottom[0]==0 && color_rgb_bottom[1]==0 && color_rgb_bottom[2]==0))
                {
                    color_rgb[0]=0;
                    color_rgb[1]=0;
                    color_rgb[2]=0;
                }
                setcolor_rgb(output_bmp,offset,i,j,grid_size,rect,rowsize,height,width,color_rgb);
            }
        }
    }   
}



void create_outer_cover(std::ifstream &input_bmp,std::fstream &output_bmp,int offset,std::vector<int> &rect,int rowsize,int height,int width,int grid_size)
{
    int m=rect[3]-rect[1]+1;
    int n=rect[2]-rect[0]+1;
    
    for(int i=0;i<m;i+=grid_size)
    {
        for(int j=0;j<n;j+=grid_size)
        {
            if(!checkIsvisited(output_bmp,offset,i,j,grid_size,rect,rowsize,height,width))
            { 
                std::vector<bool> ugb_occ=get_ugb_occ(input_bmp,offset,i,j,grid_size,rect,rowsize,height,width);
                int type=getType(ugb_occ);
                
                if(type==1 || type==-1)
                {
                    
                    for(int ugb_i=0;ugb_i<ugb_occ.size();ugb_i++)std::cout<<ugb_occ[ugb_i]<< " ";
                    std::cout<<std::endl;
                    std::cout<<type<<std::endl;
                    trace_o_cover(input_bmp,output_bmp,offset,i,j,rect,rowsize,height,width,grid_size,type);
                    
                   
                }
                markVisited(output_bmp,offset,i,j,grid_size,rect,rowsize,height,width);
                
            }
            // markVisited(output_bmp,offset,i,j,grid_size,rect,rowsize,height,width);
        }
    }
    //clear blue lines
    clearBlueLines(input_bmp,output_bmp,offset,rect,rowsize,height,width,grid_size);
    

    return;
}