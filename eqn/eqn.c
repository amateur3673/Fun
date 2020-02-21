#include <stdio.h>
#include <stdlib.h>
void display(float** a,int row,int col)//hien thi ma tran
{
    int i,j;
    for(i=0;i<row;i++)
    {
        for(j=0;j<col;j++)
        {
            printf("%.2f ",a[i][j]);
        }
        printf("\n");
    }
}
int countzero(float** a,int row,int col,int i)//dem so cac so 0 dau dong i cua ma tran a
{
    int j=0;
    while(a[i][j]==0)j++;
    return j;
}
void exchange(float** a,int row,int col,int i,int j)//trao hai hang i va j cua ma tran a
{
    int k;
    for(k=0;k<col;k++)
    {
        float temp;
        temp=a[i][k];
        a[i][k]=a[j][k];
        a[j][k]=temp;
    }
}
void sort_mat(float** a,int row,int col)//sap xep cac hang ma tran theo thu tu tang dan cua countzero
{
    int i,j;
    for(i=0;i<row-1;i++)
    {
        for(j=i+1;j<row;j++)
        {
            if(countzero(a,row,col,i)>countzero(a,row,col,j))exchange(a,row,col,i,j);
        }
    }
}
void cheo(float** a,int row,int col)//tao ra ma tran bac thang
{
    int i=0,j;
    do
    {
        sort_mat(a,row,col);
        j=i+1;
        while((j<row)&&(countzero(a,row,col,j)==countzero(a,row,col,i)))j++;
        int m=countzero(a,row,col,i);
        float p=a[i][m];
        int k;
        for(k=i+1;k<j;k++)
        {
            float q=a[k][m];
            int t;
            a[k][m]=0;
            for(t=m+1;t<col;t++)a[k][t]=a[k][t]*p/q-a[i][t];
        }
        if(i==row-1)break;
        else i++;
    } while (1);
    
}
int rank(float **a,int row,int col)
{
    int i=0;
    while((i<row)&&(countzero(a,row,col,i)!=col))i++;
    return i;
}
int check_solution(float** a,int rowa,int cola)//kiem tra phuong trinh vo nghiem hay khong
{
    int i=0;
    int value=1;
    for(i=0;i<rowa;i++)
    {
        if(countzero(a,rowa,cola,i)==cola-1)
        {
            value=0;break;
        }
    }
    return value;
}
void find_index(float** a,int *index,int rowa,int cola)//tim tat ca cac chi so cot tu do
{
    int i=0,j=0;
    for(i=0;i<rowa-1;i++)
    {
        int k,m=countzero(a,rowa,cola,i),n=countzero(a,rowa,cola,i+1);
        for(k=m+1;k<n;k++)
        {
            index[j]=k;
            j++;
        }
    }
    for(i=countzero(a,rowa,cola,rowa-1)+1;i<cola-1;i++)
    {
        index[j]=i;
        j++;
    }
}
void simplify1(float** a,float** b,int rowa,int cola)//tao ra mot ma tran b simplify tu a
{
    int i,j=0,k,t;
    for(i=0;i<rowa;i++)
    {
        t=countzero(a,rowa,cola,i);
        for(k=0;k<rowa;k++)b[k][j]=a[k][t];
        j++;
    }
    for(k=0;k<rowa;k++)b[k][rowa]=a[k][cola-1];
}
void simplify2(float** a,float** b,int s,int rowa,int cola)
{
    int i,j=0,k,t;
    for(i=0;i<rowa;i++)
    {
        t=countzero(a,rowa,cola,i);
        for(k=0;k<rowa;k++)b[k][j]=a[k][t];
        j++;
    }
    for(k=0;k<rowa;k++)b[k][rowa]=-a[k][s];
}
void solve(float** result,float** b,float** a,int n,int rowa,int cola,int s)
{
    int i;
    float nghiem;
    nghiem=b[n-1][n]/b[n-1][n-1];
    int j=countzero(a,rowa,cola,n-1);
    result[s][j]=nghiem;
    for(i=0;i<rowa;i++)
    {
        b[i][n-1]=b[i][n]-nghiem*b[i][n-1];
    }
    if(n>1)solve(result,b,a,n-1,rowa,cola,s);
}
int main()
{
    //mo file de doc
    FILE *file;
    file=fopen("input.txt","r");
    if(file==NULL)
    {
        printf("Khong mo duoc file: ");
        return 0;
    }
    int col=0,row=1;
    //lay so cot cua a tran
    do
    {
        float t;
        fscanf(file,"%f",&t);
        col++;
        char ch=fgetc(file);
        if(ch=='\n')break;
    } while (1);
    //lay so hang
    do
    {
        char ch=fgetc(file);
        if(ch=='\n')row++;
        if(ch==EOF)break;
    } while (1);
    row++;
    float **a;
    a=(float**)malloc(row*sizeof(float*));
    int i,j;
    for(i=0;i<row;i++)a[i]=(float*)malloc(col*sizeof(float));
    rewind(file);
    for(i=0;i<row;i++)
    {
        for(j=0;j<col;j++)fscanf(file,"%f",&a[i][j]);
    }
    fclose(file);
    cheo(a,row,col);
    int rowa=rank(a,row,col),cola=col;
    if(check_solution(a,rowa,cola)==0)
    {
        printf("Phuong trinh vo nghiem");
        return 0;
    }
    int *index;//cac chi so cot tu do
    index=(int*)malloc((cola-rowa-1)*sizeof(int));
    find_index(a,index,rowa,cola);
    //thuc hien giai phuong trinh nao
    float **result;
    result=(float**)malloc((cola-rowa)*sizeof(float*));//mang luu ket qua
    for(i=0;i<cola-rowa;i++)result[i]=(float*)malloc((cola-1)*sizeof(float));
    float **b;
    b=(float**)malloc(rowa*sizeof(float*));
    for(i=0;i<rowa;i++)b[i]=(float*)malloc((rowa+1)*sizeof(float));
    for(i=0;i<cola-rowa-1;i++)
    {
        for(j=0;j<cola-rowa-1;j++)
        {
            if(j!=i)result[i][index[j]]=0;
            else result[i][index[i]]=1;
        }
    }
    for(j=0;j<cola-rowa-1;j++)result[cola-rowa-1][index[j]]=0;
    simplify1(a,b,rowa,cola);
    solve(result,b,a,rowa,rowa,cola,cola-rowa-1);
    for(i=0;i<cola-rowa-1;i++)
    {
        simplify2(a,b,index[i],rowa,cola);
        solve(result,b,a,rowa,rowa,cola,i);
    }
    display(result,cola-rowa,cola-1);
}