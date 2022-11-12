#include <stdio.h>
#include <math.h>
/*
Making complete graph
by connecting each vertex to the other
*/
void complete_graph(int n,double G[n][n],double C[n][2])
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(i!=j)
            {
                G[i][j] = sqrt(((C[i][0]-C[j][0])*(C[i][0]-C[j][0]))+((C[i][1]-C[j][1])*(C[i][1]-C[j][1])));
            }
        }
    }
    return;
}

/*
User input for coordinates
of the houses
*/
void house_coordinates(int n,double C[n][2],int s)
{
    if(s==1){
        printf("\nFor Houses that give electricity\n\n");
    }
    else{
        printf("\nFor Houses that need electricity\n\n");
    }
    for(int i=0;i<n;i++)
    {
        printf("For House %d\nEnter x coordinate: ",i+1);
        scanf("%lf",&C[i][0]);
        printf("Enter y coordinate: ");
        scanf("%lf",&C[i][1]);
    }
    return;
}

/*
Finding Grid Coordinates
by least distance between each house coordinates
of give and take
*/
void Grid_House_coordinates(int n1,int n2,double C1[n1][2],double C2[n2][2],int *g,int *t)
{
    double min = 99999999999999;
    for(int i=0;i<n1;i++)
    {
        for(int j=0;j<n2;j++)
        {
            double dist = sqrt(((C1[i][0]-C2[j][0])*(C1[i][0]-C2[j][0]))+((C1[i][1]-C2[j][1])*(C1[i][1]-C2[j][1])));
            if(min>dist)
            {
                min = dist;
                *g = i;
                *t = j;
            }
        }
    }
    return;
}

/*
Prims Algorithm-(MST)
for finding the minimum spanning tree
*/
void prims_algorithm(int n,double G[n][n],double MST[n][n],int s)
{
    if(s==1){
        printf("\nFor Houses that give electricity\n\n");
    }
    else{
        printf("\nFor Houses that need electricity\n\n");
    }
    int selected[n],no_edge=0;
    for(int i=0;i<n;i++)
    {
        selected[i] = 0;
        for(int j=0;j<n;j++)
        {
            MST[i][j] = 0;
        }
    }
    selected[0] = 1;
    int x,y;
    while(no_edge<n-1)
    {
        double min = 999999999999999;
        x = 0;
        y = 0;
        for(int i=0;i<n;i++)
        {
            if(selected[i]==1)
            {
                for(int j=0;j<n;j++)
                {
                    if((selected[j]==0) && (G[i][j]>0))
                    {
                        if(min>G[i][j])
                        {
                            min = G[i][j];
                            x = i;
                            y = j;
                        }
                    }
                }
            }
        }
        selected[y] = 1;
        MST[x][y] = G[x][y];
        MST[y][x] = G[x][y];
        printf("%d House is connected to %d House with distance %lf\n",x+1,y+1,min);
        no_edge++;
    }
    return;
}

/*
printing the MST
*/
void print_MST(int n,double MST[n][n],int s)
{
    if(s==1){
        printf("\nThe MST for giving houses here is: \n");
    }
    else{
        printf("\nThe MST for needing houses here is: \n");
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(j==0)
            {
                printf("|");
            }
            printf("%lf ",MST[i][j]);
            if(j==n-1)
            {
                printf("|");
            }
        }
        printf("\n");
    }
    return 0;
}

/*
Main function
*/
int main()
{
    //Taking numbers as user input
    int n1,n2;
    printf("Enter the number of houses with excess solar electricity: ");
    scanf("%d",&n1);
    printf("Enter the number of houses needing electricity: ");
    scanf("%d",&n2);
    //getting coordinates
    double Hg[n1][2],Hn[n2][2];
    house_coordinates(n1,Hg,1);
    house_coordinates(n2,Hn,0);
    //getting complete graph
    double Gg[n1][n1],Gn[n2][n2];
    complete_graph(n1,Gg,Hg);
    complete_graph(n2,Gn,Hn);
    //getting the MST via prims algorithm
    double MSTg[n1][n1],MSTn[n2][n2];
    prims_algorithm(n1,Gg,MSTg,1);
    prims_algorithm(n2,Gn,MSTn,0);
    //Getting house coordinates for placing grid in between
    int G_g,G_t;
    Grid_House_coordinates(n1,n2,Hg,Hn,&G_g,&G_t);
    //getting grid coordinates by placing it in between the houses
    double x = (Hg[G_g][0] + Hn[G_t][0])/2;
    double y = (Hg[G_g][1] + Hn[G_t][1])/2;
    double giving_dist = sqrt((Hg[G_g][0]-x)*(Hg[G_g][0]-x)+(Hg[G_g][1]-y)*(Hg[G_g][1]-y));
    double needing_dist = sqrt((Hn[G_t][0]-x)*(Hn[G_t][0]-x)+(Hn[G_t][1]-y)*(Hn[G_t][1]-y));
    //Final Results of the Algorithm
    printf("\nThe Grid coordinates are: (%lf,%lf)\n",x,y);
    printf("%d-th Giving house is connected to Grid by a distance of %lf\n",G_g+1,giving_dist);
    printf("%d-th Needing house is connected to Grid by a distance of %lf\n",G_t+1,needing_dist);
    printf("\nThe Minimum Spanning trees (Adjacency Matrix) for the components are: \n");
    print_MST(n1,MSTg,1);
    print_MST(n2,MSTn,0);
    return 0;
}
