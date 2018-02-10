#include <stdio.h>
#include <stdlib.h>
struct node
{
    int lc,lm,rc,rm,boat;

};
int top=-1;
struct node state[256];
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void push(int lc, int lm, int rc, int rm, int boat)
{   ++top;
    state[top].lc=lc;
    state[top].lm=lm;
    state[top].rc=rc;
    state[top].rm=rm;
    state[top].boat=boat;

}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
int check(int i, int j)
{
   if(state[i].boat==0&&state[j].boat==1){

    if(state[i].lc-state[j].lc==2&&state[i].lm-state[j].lm==0&&state[i].rc-state[j].rc==-2&&state[i].rm-state[j].rm==0)
        return 1;
    else if(state[i].lc-state[j].lc==1&&state[i].lm-state[j].lm==0&&state[i].rc-state[j].rc==-1&&state[i].rm-state[j].rm==0)
        return 1;
    else if(state[i].lc-state[j].lc==0&&state[i].lm-state[j].lm==2&&state[i].rc-state[j].rc==0&&state[i].rm-state[j].rm==-2)
        return 1;
    else if(state[i].lc-state[j].lc==0&&state[i].lm-state[j].lm==1&&state[i].rc-state[j].rc==0&&state[i].rm-state[j].rm==-1)
        return 1;
    else if(state[i].lc-state[j].lc==1&&state[i].lm-state[j].lm==1&&state[i].rc-state[j].rc==-1&&state[i].rm-state[j].rm==-1)
        return 1;
   }
   if(state[i].boat==1&&state[j].boat==0){
     if(state[i].lc-state[j].lc==-2&&state[i].lm-state[j].lm==0&&state[i].rc-state[j].rc==2&&state[i].rm-state[j].rm==0)
        return 1;
    else if(state[i].lc-state[j].lc==0&&state[i].lm-state[j].lm==-2&&state[i].rc-state[j].rc==0&&state[i].rm-state[j].rm==2)
        return 1;
    else if(state[i].lc-state[j].lc==-1&&state[i].lm-state[j].lm==0&&state[i].rc-state[j].rc==1&&state[i].rm-state[j].rm==0)
        return 1;
    else if(state[i].lc-state[j].lc==0&&state[i].lm-state[j].lm==-1&&state[i].rc-state[j].rc==0&&state[i].rm-state[j].rm==1)
        return 1;
    else if(state[i].lc-state[j].lc==-1&&state[i].lm-state[j].lm==-1&&state[i].rc-state[j].rc==1&&state[i].rm-state[j].rm==1)
        return 1;

   }

    return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
int DFS(int **G)
{
    int closed[54],open[54],parent[54],path[54];
    int topo=-1, topc=-1, topp=-1;
    int i, temp,j;
    for(i=0;i<54;i++)
        {closed[i]=0; parent[i]=-1;}

    int start=52, target=1;
    open[++topo]=start;
    while(topo!=-1)
    {
        temp=open[topo--];
        if(temp==target){
              j = target;
              while(j!=start)
              {


                    path[++topp]=j;
                    j=parent[j];
              }


            path[++topp]=start;
            for(i=topp;i>=0;i--)
                {   j=path[i];
                    printf("LC=%d   LM=%d |||||||| RC=%d   RM=%d   \n",state[j].lc, state[j].lm, state[j].rc, state[j].rm);
                  if(state[j].boat==0)
                    printf("Boat going from LEFT to RIGHT\n");
                  else if(state[j].boat==1&&i!=0)
                    printf("Boat going from RIGHT to LEFT\n");
                else
                    printf("Boat stops on RIGHT\n");
                }


            return 1;}
        else
        {
          for(i=0;i<54;i++)
                if(G[temp][i]==1&&!presentin(open,i,topo)&&!presentin(closed,i,topc))
                {open[++topo]=i; parent[i]=temp;}
          closed[++topc]=temp;

        }
    }

   return 0;

}
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
int presentin(int *arr, int n, int top)
{
    int i, flag=0;
    for(i=0;i<=top;i++)
    {
        if(arr[i]==n)
        {
            flag=1;
            break;
        }
    }
    return flag;
}

int main()
{
    int lc,lm,rc,rm,boat;
    for(lc=0;lc<=3;lc++)
        for(lm=0;lm<=3;lm++)
            for(rc=0;rc<=3;rc++)
                for(rm=0;rm<=3;rm++)
                    for(boat=0;boat<=1;boat++)
    {
       if((lc+lm+rc+rm==6)&&((lm!=0&&lm>=lc)||(lm==0))&&((rm!=0&&rm>=rc)||(rm==0)))
            {//printf("%d %d %d %d\n",lc,lm,rc,rm);
            push(lc,lm,rc,rm,boat);
            }
    }

    int i,j;
    for(i=0;i<=top;i++)
    {
        printf("%d %d %d %d boat posn %d", state[i].lc,state[i].lm, state[i].rc, state[i].rm, state[i].boat);
        printf("\n");
    }
    printf("%d\n", top);
    int **G= (int **)malloc(54*sizeof(int *));
    for(i=0;i<54;i++)
    {
        G[i]=(int *)malloc(54*sizeof(int));

    }

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
    for(i=0;i<54;i++)
        for(j=0;j<54;j++)
        {
            if(check(i,j)==1)
                G[i][j]=1;
            else
                G[i][j]=0;
        }

    for(i=0;i<54;i++)
    {

        for(j=0;j<54;j++)
    {
        printf("%d ", G[i][j]);
    }
    printf("\n");
    }

    printf("%d\n", DFS(G));
}
