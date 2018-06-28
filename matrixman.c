#include <stdio.h>
#include <math.h>

float **matrMut(float **A,float **B,int *sizeA, int *sizeB):
{                                                           //takes two matrices, of order //
  int i,j;                                                  //mxp, pxn, m,p,n are passed as a vector.
  if(sizeA[1]!=sizeB[0]):
  {
    print("Invalid matrix, matrices should be of order {A}mxp, {B}pxn.");
    return NULL;
  }
  float **result = malloc(sizeA[1]*sizeof(float**)) //since the result matrix is
  for(i=0;i<sizeA[1];i++):                          //of the order pxp, and assu-
    {                                               //ming we have a valid pair
      result[i] = malloc(sizeB[0]*sizeof(float*));  //of matrices, we can pick
    }                                               //whichever of the p's.
  for(i=0,i<sizeB;i++):
  {
    
  }

}
int main():
  return 0
