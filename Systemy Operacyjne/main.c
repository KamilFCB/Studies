/*
    Kamil Wo�(289039) 15.01.2018
    Obowi�zkowe zadanie z pracowni system�w operacyjnych - synchronizacja proces�w
*/
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
 
#define M 100
 
int przedmiot, pojemnosc;
 
 
struct Zasob_wspolny
{
    sem_t dostawca;
    sem_t stanowisko;
    int podzespol_x, podzespol_y, podzespol_z;
    int wyprodukowane, przerwa;
} *zasob;
 
void dostawca()
{
    while(1)
    {
        sem_wait(&zasob->stanowisko);
 
        przedmiot = rand()%3+1;
 
        if(zasob->podzespol_x == 0)
            przedmiot = 1;
        else if(zasob->podzespol_y == 0)
            przedmiot = 2;
        else if(zasob->podzespol_z == 0)
            przedmiot = 3;
 
        pojemnosc = zasob->podzespol_x + (zasob->podzespol_y * 2) + (zasob->podzespol_z * 3);
 
        if(przedmiot == 1)
        {
            int ile = M - pojemnosc;
            if(ile >= 3)
                zasob->podzespol_x += 3;
            else
                zasob->podzespol_x += ile;
            printf("Dostarczy�em podzesp� X! W magazynie znajduje si� %d sztuk podzespo��w X\n", zasob->podzespol_x);
        }
        else if(przedmiot == 2)
        {
            int ile = (int)((M-pojemnosc)/2);
            if(ile >= 3)
                zasob->podzespol_y += 3;
            else
                zasob->podzespol_y += ile;
            printf("Dostarczy�em podzesp� Y! W magazynie znajduje si� %d sztuk podzespo��w Y\n", zasob->podzespol_y);
        }
        else if(przedmiot == 3)
        {
            int ile = (int)((M-pojemnosc)/3);
            if(ile >= 3)
                zasob->podzespol_z += 3;
            else
                zasob->podzespol_z += ile;
            printf("Dostarczy�em podzesp� Z! W magazynie znajduje si� %d sztuk podzespo��w Z\n", zasob->podzespol_z);
        }
 
        sem_post(&zasob->dostawca);
    }
}
 
void pracownik()
{
    while(1)
    {
        sem_wait(&zasob->dostawca);
        if(zasob->podzespol_x >= 1 && zasob->podzespol_y >= 1 && zasob->podzespol_z >= 1)
        {
            if(zasob->przerwa > 0)
            {
                printf("Wznawiam prac� po %d minutach\n", zasob->przerwa);
                zasob->przerwa=0;
            }
            (zasob->podzespol_x)--;
            (zasob->podzespol_y)--;
            (zasob->podzespol_z)--;
            (zasob->wyprodukowane)++;
            printf("Wyprodukowa�em jeden przedmiot, ��cznie %d sztuk\n", zasob->wyprodukowane);
        }
        else
        {
            printf("Brakuje podzespo��w!\n");
            (zasob->przerwa)++;
        }
        sem_post(&zasob->stanowisko);
    }
}
 
int main()
{
    zasob = mmap(NULL, sizeof(struct Zasob_wspolny), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    sem_init(&zasob->dostawca, 1, 5);
    sem_init(&zasob->stanowisko, 1, 5);
    zasob->podzespol_x=10;
    zasob->podzespol_y=10;
    zasob->podzespol_z=10;
    zasob->przerwa=0;
    zasob->wyprodukowane=0;
 
    if(fork() == 0)
    {
        dostawca();
        return 0;
    }
       
    pracownik();
   
    return 0;
}