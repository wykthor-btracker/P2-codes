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
typedef struct rua {
  int *init;
  int *end;
}rua;

typedef struct carro {
  int *pos;
  int moving;
  int *dir;
  int id;
} carro;
carro *newCar(int *pos, int *dir, int id,int moving)
{
  carro *newCar = malloc(sizeof(carro));
  newCar->pos = pos;
  newCar->dir = dir;
  newCar->moving = moving;
  newCar->id = id;
  return newCar;
}
int **newMap(int size){                       //O mapa será preenchido com as variáveis acima,
  int i;                                      //Permitindo a independência dos carros, que serão
  int **newMap = malloc(sizeof(int*)*size);   //Criados como vetores relativos ao mapa somente
  for(i=0;i<size;i++)                         //Por descreverem a mesma posição.
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

void randomSpot(carro *carro,int **map,int size)
{
  while(map[carro->pos[0]][carro->pos[1]]!=RUA)
  {
    carro->pos[0] = rand()%size;
    carro->pos[1] = rand()%size;
  }
}
int *newVec(int x, int y)
{
	int *newVec = malloc(sizeof(int)*2);
	newVec[0] = x;
	newVec[1] = y;
	return newVec;
}
rua *ruaNova()
{
	rua *newRua = malloc(sizeof(rua));
	newRua->init = NULL;
	newRua->end = NULL;
	return newRua;
}
rua *ruaVertical(int **map, int size,int sentido,rua *outraRua)
{
  int i,coluna = rand()%(size-1);
  if(outraRua->init != NULL && outraRua->end != NULL)
  {
    while(!(coluna!=outraRua->init[1] && coluna != 0)) { coluna = rand()%(size-1); }
  }
  for(i=0;i<size;i++)
  {
    map[i][coluna] = RUA;
  }
  rua *newRua = malloc(sizeof(rua));
  if(sentido)
  {
	  newRua->init = newVec(0,coluna);
	  newRua->end = newVec(size-1,coluna);
  }
  else
  {
	  newRua->init = newVec(size-1,coluna);
	  newRua->end = newVec(0,coluna);
  }
  return newRua;
}

rua *ruaHorizontal(int **map, int size,int sentido,rua *outraRua)
{
  int i,linha = rand()%(size-1);
  if(outraRua->init != NULL && outraRua->end != NULL)
  {
    while(!(linha!=outraRua->init[0] && linha != 0)) { linha = rand()%(size-1); }
  }
  for(i=0;i<size;i++)
  {
    map[linha][i] = RUA;
  }
  rua *newRua = malloc(sizeof(rua));
  if(sentido)
  {
	  newRua->init = newVec(linha,0);
	  newRua->end = newVec(linha,size-1);
  }
  else
  {
	  newRua->init = newVec(linha,size-1);
	  newRua->end = newVec(linha,0);
  }
  return newRua;
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
void cruzamento(int **map, int size,int street)
{
  int *pos = calloc(sizeof(int),2);
  pos[0] = 0;
  pos[1] = street;
  int found = 0;
  int up[2] = {-1,0};
  int down[2] = {1,0};
  int left[2] = {0,-1};
  int right[2] = {0,1};
  while(!found)
  {
    if( ((!outOfBounds(movement(pos,up)  ,size)      && ((checkSpot(movement(pos,up),map)    == RUA) || checkSpot(movement(pos,up),map) == SEMAFORO)) || outOfBounds(movement(pos,up),size))    &&
        ((!outOfBounds(movement(pos,down),size)      && ((checkSpot(movement(pos,down),map)  == RUA) || checkSpot(movement(pos,down),map) == SEMAFORO))|| outOfBounds(movement(pos,down),size))    &&
        ((!outOfBounds(movement(pos,left),size)      && ((checkSpot(movement(pos,left),map)  == RUA) || checkSpot(movement(pos,left),map) == SEMAFORO))|| outOfBounds(movement(pos,left),size))    &&
        ((!outOfBounds(movement(pos,right),size)     && ((checkSpot(movement(pos,right),map) == RUA) || checkSpot(movement(pos,right),map) == SEMAFORO))|| outOfBounds(movement(pos,right),size)))
    {
      if(map[pos[0]][pos[1]] != SEMAFORO)
      {
        map[pos[0]][pos[1]]=SEMAFORO;
        found=1;
      }
      else pos[0]++;
    }
    else
    {
      pos[0]++;
    }
  }
}
int compRua(rua *ruaA, rua *ruaB)
{
	return(ruaA->init == ruaB->init && ruaA->end == ruaB->end);
}
int main()
{
  srand(time(0));
  int i,size = 10;
  int pos[2] = {0,0};
  carro *carro = newCar(pos,pos,1,1);
  int **mapa = newMap(size);
  rua *stud = ruaNova();
  rua *ruaLeste = ruaHorizontal(mapa,size,1,stud);
  rua *ruaSul = ruaVertical(mapa,size,1,stud);
  rua *ruaOeste = ruaHorizontal(mapa,size,0,ruaLeste);
  rua *ruaNorte = ruaVertical(mapa,size,0,ruaSul);
  for(i=0;i<2;i++)
  {
	  cruzamento(mapa,size,ruaNorte->init[1]);
	  cruzamento(mapa,size,ruaSul->init[1]);
  }
  showMap(mapa,size);
  printf("Rua 1: (%d,%d)\nRua 2: (%d,%d)\nRua 3: (%d,%d)\nRua 4: (%d,%d)\n",ruaLeste->init[0],ruaLeste->init[1],ruaOeste->init[0],ruaOeste->init[1],ruaSul->init[0],ruaSul->init[1],ruaNorte->init[0],ruaNorte->init[1]);
  //printf("Carro (%d,%d)\n",carro[0],carro[1]);
  return 0;
}
