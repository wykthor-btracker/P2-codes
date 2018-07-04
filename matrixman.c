#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define DEBUG if(0)
//Reserved keywords for map flags.
#define SEMAFORO 1
#define CASA 0
#define RUA 2
#define SEMAFOROOCUPADO 3   //Quer dizer que a posição do semáforo tem um carro.
#define RUAOCUPADA 4        //idem.
//end of reserved area
int **newMap(int size){                        //O mapa será preenchido com as variáveis acima,
  int i,j;                                  //Permitindo a independência dos carros, que serão
  int **newMap = malloc(sizeof(int*)*size); //Criados como vetores relativos ao mapa somente
  for(i=0;i<size;i++)                       //Por descreverem a mesma posição.
  {
    newMap[i] = calloc(sizeof(int),size);
  }
  return newMap;
}

void showMap(int **map,int size)
{
  int i,j;
  for(i=0;i<size;i++)
  {
    for(j=0;j<size;j++)
    {
      printf("%d",map[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

int *newCar(int x, int y, int dirX, int dirY, int id)
{
  int *newCar = malloc(sizeof(int)*5);
  newCar[0] = x;
  newCar[1] = y;
  newCar[2] = dirX;
  newCar[3] = dirY;
  newCar[4] = id;
  return newCar;
}
void randomSpot(int *car,int **map,int size)
{
  while(map[car[0]][car[1]]!=RUA)
  {
    car[0] = rand()%size;
    car[1] = rand()%size;
  }
}

void ruaVertical(int **map, int size)
{
  int i,coluna = rand()%size;
  for(i=0;i<size;i++)
  {
    map[i][coluna] = RUA;
  }
}
void ruaHorizontal(int **map, int size)
{
  int i,linha = rand()%size;
  for(i=0;i<size;i++)
  {
    map[linha][i] = RUA;
  }
}
int checkSpot(int *pos,int **map)
{
  return(map[pos[0]][pos[1]]);
}
int *movement(int *vec1, int *vec2)
{
  int *res = calloc(sizeof(int),2);
  res[0] = vec1[0]+vec2[0];
  res[1] = vec1[1]+vec2[1];
  return res;
}
int outOfBounds(int *vec,int size)
{
  return(!(vec[0]>=0 && vec[0]<size && vec[1]>=0 && vec[1]<size));
}
void showPos(int *vec)
{
  printf("(%d,%d)\n",vec[0],vec[1]);
}
void cruzamento(int **map, int size)
{
  int *pos = calloc(sizeof(int),2);
  pos[0] = rand()%size;
  pos[1] = rand()%size;
  int found = 0;
  int up[2] = {-1,0};
  int down[2] = {1,0};
  int left[2] = {0,-1};
  int right[2] = {0,1};
  while(!found)
  {
    while(map[pos[0]][pos[1]]!=RUA)
    {
      pos[0] = rand()%size;
      pos[1] = rand()%size;
    }
    if( (!outOfBounds(movement(pos,up)  ,size)      && checkSpot  (movement(pos,up),map)    == RUA)    &&
        (!outOfBounds(movement(pos,down),size)      && checkSpot  (movement(pos,down),map)  == RUA)    &&
        (!outOfBounds(movement(pos,left),size)      && checkSpot  (movement(pos,left),map)  == RUA)    &&
        (!outOfBounds(movement(pos,right),size)     && checkSpot  (movement(pos,right),map) == RUA))
    {
      if(map[pos[0]][pos[1]] != SEMAFORO)
      {
        map[pos[0]][pos[1]]=SEMAFORO;
        found=1;
      }
    }
    else
    {
      pos[0] = rand()%size;
      pos[1] = rand()%size;
    }
  }
}
int main()
{
  srand(time(0));
  int size = 10;
  int *carro = newCar(0,0,1,0,0);
  int **mapa = newMap(size);
  ruaHorizontal(mapa,size);
  showMap(mapa,size);  
  ruaVertical(mapa,size);
  showMap(mapa,size);
  cruzamento(mapa,size);
  showMap(mapa,size);
  randomSpot(carro,mapa,size);
  showMap(mapa,size);
  printf("Carro (%d,%d)\n",carro[0],carro[1]);
  return 0;
}
