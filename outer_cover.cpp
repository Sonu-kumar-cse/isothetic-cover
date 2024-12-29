#include<iostream>
#include<vector>
#include "helper_functions/print_o_cover.cpp"
using namespace std;


vector<bool> checktype(vector<vector<int> > &image,int n,int m,vector<vector<int> > &rect,int grid_size,int p,int q)
{
    vector<bool> ugb_occupancy(4,false);
    //for 1 ugb top right
    if(p-grid_size>=rect[0][0] && q+grid_size<=rect[1][1])
    {
        for(int i=p-grid_size;i<=p;i++)
        {
            if(image[i][q]==0)
            {
                ugb_occupancy[0]=true;
                break;
            }
            if(image[i][q+grid_size]==0)
            {
                ugb_occupancy[0]=true;
                break;
            }
        }
        if(!ugb_occupancy[0])
        {
            for(int i=q;i<=q+grid_size;i++)
            {
                if(image[p][i]==0)
                {
                    ugb_occupancy[0]=true;
                    break;
                }
                if(image[p-grid_size][i]==0)
                {
                    ugb_occupancy[0]=true;
                    break;
                }
            }

        }
    }
    //for 2 ugb top left
    if(p-grid_size>=rect[0][0] && q-grid_size>=rect[0][1])
    {
        for(int i=p-grid_size;i<=p;i++)
        {
            if(image[i][q]==0)
            {
                ugb_occupancy[1]=true;
                break;
            }
            if(image[i][q-grid_size]==0)
            {
                ugb_occupancy[1]=true;
            }
        }
        if(!ugb_occupancy[1])
        {
            for(int i=q-grid_size;i<=q;i++)
            {
                if(image[p][i]==0)
                {
                    ugb_occupancy[1]=true;
                    break;
                }
                if(image[p-grid_size][i]==0)
                {
                    ugb_occupancy[1]=true;
                }
            }
        }
    }
    //for 3 ugb bottom left
    if(p+grid_size<=rect[1][0] && q-grid_size>=rect[0][1])
    {
        for(int i=p;i<=p+grid_size;i++)
        {
            if(image[i][q]==0)
            {
                ugb_occupancy[2]=true;
                break;
            }
            if(image[i][q-grid_size]==0)
            {
                ugb_occupancy[2]=true;
            }
        }
        if(!ugb_occupancy[2])
        {
            for(int i=q-grid_size;i<=q;i++)
            {
                if(image[p][i]==0)
                {
                    ugb_occupancy[2]=true;
                    break;
                }
                if(image[p+grid_size][i]==0)
                {
                    ugb_occupancy[2]=true;
                }
            }   
        }
    }
    //for 4 ugb bottom right
    if(p+grid_size<=rect[1][0] && q+grid_size<=rect[1][1])
    {
        for(int i=p;i<=p+grid_size;i++)
        {
            if(image[i][q]==0)
            {
                ugb_occupancy[3]=true;
                break;
            }
            if(image[i][q+grid_size]==0)
            {
                ugb_occupancy[3]=true;
            }
        }
        if(!ugb_occupancy[3])
        {
            for(int i=q;i<=q+grid_size;i++)
            {
                if(image[p][i]==0)
                {
                    ugb_occupancy[3]=true;
                    break;
                }
                if(image[p+grid_size][i]==0)
                {
                    ugb_occupancy[3]=true;
                }
            }
        }
    }
    return ugb_occupancy;
    
}


int get_type(vector<bool> &ugb_occ)
{
    int count=0;
    for(int i=0;i<4;i++)
        if(ugb_occ[i])count++;
    if(count==1)return 1;
    if(count==3)return -1;
    if(count==2)
    {
        if((ugb_occ[0] && ugb_occ[2]) || (ugb_occ[1] && ugb_occ[3])) return -1;
        else return 0;
    }
    return 0;
}

void change_image_cover(vector<vector<int> > &image,int p,int q,int m,int n)
{
    if(q==n)
    {
        if(p>m)
        {
            for(int i=p;i>=m;i--)
            {
                image[i][q]=4;
            }
        }
        else{
            for(int i=p;i<=m;i++)
            {
                image[i][q]=4;
            }
        }
    }
    else{
        if(q<n)
        {
            for(int i=q;i<=n;i++)
            {
                image[p][i]=4;
            }
            
        }
        else{
            for(int i=q;i>=n;i--)
            {
                image[p][i]=4;
            }
        }
    }
}


void start_tracing(vector<vector<int> > &image,int n,int m,vector<vector<int> > &rect,int grid_size,vector<vector<bool> > &visited,int p,int q,int first_row,int first_col,vector<vector<int> > ocover)
{
    int direction=2;
    visited[(p-first_row)/grid_size][(q-first_col)/grid_size]=true;
    vector<bool> ugb_occ1=checktype(image,n,m,rect,grid_size,p,q);
    int curr_p=p;
    int curr_q=q;
    int type=get_type(ugb_occ1);
    int next_p,next_q;
    next_p=p;
    next_q=q;
    
    direction=(direction+type)%4;
    if(direction==0) next_q+=grid_size;
    else if(direction==1) next_p-=grid_size;
    else if(direction==2) next_q-=grid_size;
    else next_p+=grid_size;
    
    change_image_cover(image,curr_p,curr_q,next_p,next_q);
    getchar();
    system("clear");
    print_image_cover(image,n,m,rect,grid_size);

    cout<<endl<<curr_p<<" "<<curr_q<<" to "<<next_p<<" "<<next_q <<" direction="<<direction<<" ";
    for(int i=0;i<4;i++)
    {
        cout<<ugb_occ1[i];
    }
    cout<<endl;

    curr_p=next_p;
    curr_q=next_q;
    
    while(curr_p!=p || curr_q!=q)
    {
       visited[(curr_p-first_row)/grid_size][(curr_q-first_col)/grid_size]=true;
        vector<bool> ugb_occ=checktype(image,n,m,rect,grid_size,curr_p,curr_q);
     
        type=get_type(ugb_occ);
      
        next_p=curr_p;
        next_q=curr_q;

        direction=(direction+type)%4;
        if(direction==0) next_q+=grid_size;
        else if(direction==1) next_p-=grid_size;
        else if(direction==2) next_q-=grid_size;
        else next_p+=grid_size;
    
        
        cout<<endl<<curr_p<<" "<<curr_q<<" to "<<next_p<<" "<<next_q <<" direction="<<direction<<" ";
        for(int i=0;i<4;i++)
        {
            cout<<ugb_occ[i];
        }
        cout<<endl;

        change_image_cover(image,curr_p,curr_q,next_p,next_q);
        getchar();
        system("clear");
        print_image_cover(image,n,m,rect,grid_size);

        curr_p=next_p;
        curr_q=next_q;

    }


}

vector<vector<int> > get_outer_cover(vector<vector<int> > &image,int n,int m,vector<vector<int> > &rect,int grid_size)
{
    vector<vector<int> > ocover;
    
    int tototal_grid_rows=(rect[1][0]-rect[0][0])/grid_size +1;
    int tototal_grid_cols=(rect[1][1]-rect[0][1])/grid_size +1;
    int first_row=rect[0][0];
    int first_col=rect[0][1];

    vector<vector<bool> > visited(tototal_grid_rows,vector<bool>(tototal_grid_cols,false));
    
    for(int i=0;i<tototal_grid_rows;i++)
    {
    
        for(int j=0;j<tototal_grid_cols;j++)
        {
            vector<bool> ugb_occu;
            
            if(!visited[i][j])
            {
                visited[i][j]=true;
                ugb_occu=checktype(image,n,m,rect,grid_size,(i*grid_size)+first_row,(j*grid_size)+first_col);
                int count=0;
                for(int k=0;k<4;k++)
                    if(ugb_occu[k])count++;

                
                if(count==0 || count==4)continue;
                else{
                    start_tracing(image,n,m,rect,grid_size,visited,(i*grid_size)+first_row,(j*grid_size)+first_col,first_row,first_col,ocover);
                    goto label;
                }
            }

        }
    }
    label:
    return ocover;

}
