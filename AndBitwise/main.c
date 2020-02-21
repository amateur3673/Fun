// This is just a simple program i've encountered
//Problem: Given two integers N and K, find 2 integers A,B, where A<B from the set of S={1,2,..,N} such that
//the value of A&B is as high as possible but less then K.
//That's the problem, it's kinda simple, we gonna do it with few lines of code
//The 2 integers N and K is scanned from keyboard by scanf command in C
#include <stdio.h>
#include <stdlib.h>
int numberOfDigit(int N){
    //calculate the number of digit to store N in binary form
    //This algorithm takes a complexity of O(log2(n))
    int digit_numb=0;
    while(N>0){
        N/=2;
        digit_numb++;
    }
    return digit_numb;
}
int binary2Decimal(int* arr,int digit_numb){
    //we convert the binary arr to decimal
    //It suppose to take a complexity of O(log2(n))
    int result=0;
    int i;
    int exp2=1;
    for(i=digit_numb-1;i>=0;i--){
        if(arr[i]==1)result+=exp2;
        exp2*=2;
    }
    return result;
}
int* decimal2Binary(int n,int digit_numb){
    //convert from decimal to binary, this suppose to take an O(log2(n)) complexity
    int* result=(int*)malloc(digit_numb*sizeof(int));
    int i=digit_numb-1;
    while(n>0){
        result[i]=n%2;
        n/=2;
        i--;
    }
    while(i>0){
        result[i]=0;
        i--;
    }
    return result;
}
void displayBinary(int* arr,int digit_numb){
    //to print out the binary string
    int i;
    for(i=0;i<digit_numb;i++)printf("%d",arr[i]);
    printf("\n");
}
int main(){
    int N,K;
    printf("Please enter N: ");
    scanf("%d",&N);
    printf("Please enter K: ");
    scanf("%d",&K);
    //if you use 2 for loop to find A and B like selection sort, you'll end up with O(n^2) al, that's the worst
    //We only use a few tricks to get a better solution
    //firstly, we must convert the set S into binary
    //to convert S into binary, we must calculate how many bit to store all elements of S, and it turns out that
    //we need the number of digit of N.
    int digit_numb=numberOfDigit(N);
    //we set the threshold number is a number of 0111..1, which means its value is 2^(digit_numb-1)-1
    int i;
    int threshold=1;
    for(i=0;i<digit_numb-1;i++)threshold*=2;
    threshold--;
    if(K<=threshold){
        //if K<=threshold, then we can choose A&B=K-1, where A=K-1 and B=threshold, you can prove your self that A&B=K-1
        printf("We found 2 number: %d %d\n",K-1,threshold);
        printf("A and B is: %d\n",K-1);
    }
    else{
        int iter;
        if(K>N)iter=N;
        else iter=K-1;
        //we must found A and B satisfy A&B=start, if not, decrease start
        while(iter>=threshold){
            //we convert iter to a binary form
            int* binary_arr=decimal2Binary(iter,digit_numb);//take only O(log2(n))
            //There's a property of and bitwise, that is a&b is always smaller than both a,b.
            //So to get a&b=iter, the smallest value of a and b must be iter, assume a<b, so a>=iter, we set a=iter
            //we gonna find the second smallest value b that satisfy a&b=iter
            //we gonna loop from the tail of binary string, find the first zero we met and replace it by 1
            //after that, check if it exceeds N, then decrease the iter, else, we found a and b
            for(i=digit_numb-1;i>=0;i--){
                if(binary_arr[i]==0){
                    binary_arr[i]=1;//replace by 1
                    break;//break of the loop
                }
            }
            if(i<0){
                //in this case, iter is 11...1, we must decrese iter by 1
                iter--;
            }
            else{
                int val=binary2Decimal(binary_arr,digit_numb);//take O(log2(n))
                if(val>N)iter--;
                else{
                   printf("We found 2 values of A and B: %d %d\n",iter,val);
                   printf("A and B is: %d\n",iter);
                   return 0;
               }
            }
            free(binary_arr);//we free binary_arr to save memory
            //in the worst case our loop takes O(n/2)
        }
        printf("We found 2 values of A and B are %d %d\n",threshold-1,threshold);
        printf("A and B is: %d\n",threshold-1);
    }
    //if you combined all, our algorithm only takes O(nlog2(n)), that's way better than coding like selection sort
    return 0;
}