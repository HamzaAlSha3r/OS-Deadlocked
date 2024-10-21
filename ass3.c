#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>
/*hamza al shaer

id :1211162

sec4*/
// Read the input files (request && Allocation && Available)
void read_file (int num_proc , int num_resource , int Allocation[num_proc][num_resource] , int request[num_proc][num_resource] ,int Available[num_resource] ){
    // read request matrix
    FILE *file1 = fopen("request.csv", "r");
    int row1 =0 ;
    int colume1=0;
    char bufer1 [2000];
    while (fgets(bufer1,2000,file1)){
        colume1=0;
        row1++;
        if(row1==1)continue;
        char * data = strtok(bufer1,", ");
        if(colume1==0){
            data= strtok(NULL, ", ");
            colume1++;
        }
        while (data!=NULL){
            if(colume1<=num_resource){
                request[row1-2][colume1-1]= atoi(data);
                colume1++;
            }
            data= strtok(NULL, ", ");
        }
    }
    fclose(file1);

    // read allocation matrix
    FILE *file2 = fopen("allocation.csv", "r");
    int row2 =0 ;
    int colume2=0;
    char bufer2 [2000];
    while (fgets(bufer2,2000,file2)){
        colume2=0;
        row2++;
        if(row2==1)continue;
        char * data = strtok(bufer2,", ");
        if(colume2==0){
            data= strtok(NULL, ", ");
            colume2++;
        }
        while (data!=NULL){
            if(colume2<=num_resource){
                Allocation[row2-2][colume2-1]= atoi(data);
                colume2++;
            }
            data= strtok(NULL, ", ");
        }
    }
    fclose(file2);

    // read Available array
    FILE *file3 = fopen("available.csv", "r");
    int row3 =0 ;
    int colume3=0;
    char bufer3 [2000];
    while (fgets(bufer3,2000,file3)){
        colume3=0;
        row3++;
        if(row3==1)continue;
        char * data = strtok(bufer3,", ");
        while (data!=NULL){
            if(colume3<=num_resource){
                Available[colume3]= atoi(data);
                colume3++;
            }
            data= strtok(NULL, ", ");
        }
    }
    fclose(file3);
}
// to get num of process and resourcess
bool get_numProc_numReso_consistant(int *num_proc , int *num_resource){
    FILE *file1 = fopen("request.csv", "r");
    int row1 =0;
    int colume1 =0;
    char bufer1[2000];
    while (fgets(bufer1,2000,file1)) {
        colume1 = 0;
        row1++;
        if (row1 == 1)continue;
        char * data = strtok(bufer1,", ");
        if(colume1==0)
            data = strtok(NULL,", ");

        while (data!=NULL){
            colume1++;
            data = strtok(NULL,", ");
        }
    }
    fclose(file1);
    FILE *file2 = fopen("allocation.csv", "r");
    int row2 =0;
    int colume2 =0;
    char bufer2[2000];
    while (fgets(bufer2,2000,file2)) {
        colume2 = 0;
        row2++;
        if (row2 == 1)continue;
        char * data = strtok(bufer2,", ");
        if(colume2==0)
            data = strtok(NULL,", ");

        while (data!=NULL){
            colume2++;
            data = strtok(NULL,", ");
        }
    }
    fclose(file2);
    FILE *file3 = fopen("available.csv", "r");
    int row3 =0;
    int colume3 =0;
    char bufer3[2000];
    while (fgets(bufer3,2000,file3)) {
        colume3=0;
        row3++;
        if (row3 == 1)continue;
        char * data = strtok(bufer3,", ");
        while (data!=NULL){
            colume3++;
            data = strtok(NULL,", ");
        }
    }
    fclose(file3);
    // cheack consistant
    if((row1-1 == row2-1) && (colume1==colume2) && (colume1==colume3)){
        *num_proc=row1-1;
        *num_resource=colume1;
        return true;
    }else{
        return false;
    }
}
int main() {
     int num_proc =10, num_resource=5 , done =0 , count = 0 , j=0 , flag = 1;
     bool Finish[num_proc] , deadLock = false , cheack = true , temp = false , consistant =false;
     // get diminsion and check if consistant
     consistant= get_numProc_numReso_consistant(&num_proc , &num_resource);
     int Allocation [num_proc][num_resource] , request [num_proc][num_resource] , save [num_proc];
     int Available [num_resource] , work[num_resource];
     // if is consistant read data and check if has dead lock
     if(consistant ==  true){
         printf("is consistant state ... \n");
         //  Read the input files, and verify that the dimensions are consistent.
         read_file(num_proc , num_resource , Allocation , request ,Available );
         // copy avaliable array to rk
         for(int i =0; i<num_resource ;i++) work[i]=Available[i];
         for(int i=0 ; i<num_proc ; i++){
             Finish[i]=false;
             save[i]=0;
         }
         while (flag != 0){
             flag=0;
             for(int i = 0 ; i < num_proc ; i++){
                 cheack=true;
                 for(int k = 0 ; k<num_resource ; k++){
                     if(request[i][k]>work[k])cheack=false;
                 }
                 if(Finish[i]==false && cheack==true){
                     flag=1;
                     done++;
                     save[j] = i ;
                     j++;
                     Finish[i]=true;
                     for(int f =0 ; f <num_resource ;f++) work[f]+=Allocation[i][f];
                     break;
                 }
             }
         }
         if(done==num_proc){ // not fount deadlock (safe state)
             printf("series of process executions without deadlock : \n");
             for (int i =0 ; i<num_proc ;i++)
                 printf("P%d  ",save[i]+1);
         }else{
             printf("list the processes that are deadlocked : \n");
             for(int i =0 ;i<num_proc ;i++){
                 if(Finish[i]==false){
                     printf("P%d  ",i+1);
                 }
             }
         }
     }else{
         printf("no it is not consistant state ...\n");
     }

    return 0;
}
