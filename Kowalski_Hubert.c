
//pole zwykle - pz  -1                DOROBIC WCZYTANIE PLANSZY Z PLIKU I ZAPIS DO
//sciany - sc - 2
//typ jedzenia jablko - j - 3
//typ jedzenia banan - b - 4
//typ jedzenia kokos - k - 5
//ZALOZENIE:MINIMALNY ROZMIAR POLA GRY TO 5X5; MAKSYMALNY 1000X1000
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define POLE_ZWYKLE 1
#define SCIANA 2
#define JABLKO 3
#define BANAN 4
#define KOKOS 5
#define START 6
#define META 7

int menu();
int dajinta(int min,int max);
int tworzplansze(int *hh, int *ll,int **tab);
void losujelement(int h,int l,int ilosc,int rodzaj,int **tab);
void zapisplanszydopliku(int h,int l,int **tab);
void instrukcja();
void menugrazwykla();

int menu() //menu glowne
{
    int a;
    system("cls");
    printf("MENU\n\n");
    printf("1.Gra zwykla i tworzenie planszy\n");
    printf("2.Gra automatyczna\n");
    printf("3.Instrukcja\n");
    printf("4.Wyjscie\n");
    printf("\n\n\nWcisnij numer podany przy akcji, ktora chcesz wykonac\n");
    a=dajinta(1,4);
    system("cls");
    return a;
}

int dajinta(int min,int max) //chroni program przed wywaleniem sie w przypadku podania innego znaku niz liczba z podanego zakresu int
{
    char temp[100];
    int i,ok;
    do
    {
        ok=0;
        for (i=0; i<100; i++) temp[i]=0; //bo domyslnie znajduja sie tam "smieci"
        scanf("%s",temp);
        for (i=0; i<100; i++)
        {
            if (((temp[i]<48)||(temp[i]>58)||(atoi(temp)>max)||(atoi(temp)<min))&& (temp[i]!=0))
            {
                printf("Podaj liczbe calkowita z zakresu %d-%d\n",min,max);
                ok=1;
                break;
            }
        }
    }
    while (ok==1);
    return atoi(temp); //przeksztalca chara na inta

}

int tworzplansze(int* hh, int* ll,int **tab) //stworzenie planszy (jako dwuwymiarowa tablica dynamiczna tab)
{

    int a,z,p,h,l,j,b,k,more,is,ij,ik,ib;

    system("cls");

    printf("Podaj wysokosc pola gry\n");
    h=dajinta(5,1000);


    printf("Podaj szerokosc pola gry\n");
    l=dajinta(5,1000);

    printf("Liczba punktow za jedzenie musi nalezec do przedzialu (1-dluzszy bok planszy)\n");

    if (l>=h) more=l; //okreslenie, ktory bok jest dluzszy <-w tym przypadku szerokosc lub oba sa rowne
    else more=h; //<-w tym wysokosc

    printf("Podaj liczbe punktow otrzymywanych za zjedzenie jablka\n"); //punktacja za jablko
    j=dajinta(1,more);


    printf("Podaj liczbe punktow otrzymywanych za zjedzenie banana\n"); //punktacja za banana
    b=dajinta(1,more);


    printf("Podaj liczbe punktow otrzymywanych za zjedzenie kokosa\n"); //punktacja za kokosa
    k=dajinta(1,more);


    printf("Podaj poczatkowa liczbe punktow\n");
    p=dajinta(1,more);


    printf("Pamietaj, ze ilosc scian musi nalezec do przedzialu [0-(ilosc pol/2)]\n");

    printf("Podaj ilosc scian, ktore zostana rozlosowane na planszy\n"); //ilosc scian
    is=dajinta(0,h*l/2); //postanowilem ograniczyc ilosc scian do makymalnie polowy pol na planszy dla zachowania grywalnosci

    printf("Pamietaj, ze ilosc jablek musi nalezec do przedzialu [0-((ilosc pol-ilosc scian)/3)]\n");

    printf("Podaj ilosc jablek, ktore zostana rozlosowane na planszy\n"); //ilosc jablek
    ij=dajinta(0,(h*l-is)/3); //postanowilem ograniczyc ilosc jablek do makymalnie trzeciej czesci pol na planszy minus ilosc scian dla zachowania grywalnosci

    printf("Pamietaj, ze ilosc bananow musi nalezec do przedzialu [0-((ilosc pol-ilosc scian)/3)]\n");

    printf("Podaj ilosc bananow, ktore zostana rozlosowane na planszy\n"); //ilosc bananow
    ib=dajinta(0,(h*l-is)/3); //postanowilem ograniczyc ilosc bananow do makymalnie trzeciej czesci pol na planszy minus ilosc scian dla zachowania grywalnosci

    printf("Pamietaj, ze ilosc kokosow musi nalezec do przedzialu [0-((ilosc pol-ilosc scian)/3)]\n");

    printf("Podaj ilosc kokosow, ktore zostana rozlosowane na planszy\n"); //ilosc kokosow
    ik=dajinta(0,(h*l-is)/3); //postanowilem ograniczyc ilosc kokosow do makymalnie trzeciej czesci pol na planszy minus ilosc scian dla zachowania grywalnosci






    for (a=0; a<h; a++)
    {
        for (z=0; z<l; z++) tab[a][z]=POLE_ZWYKLE;
    }; //wypelnienie tablicy polami zwyklymi

    tab[0][0]=START; //lewy gorny rog staje sie polem startu
    tab[h-1][l-1]=META; //prawy dolny rog staje sie polem mety
    losujelement(h,l,is,SCIANA,tab);//losowanie scian
    losujelement(h,l,ij,JABLKO,tab);//losowanie jablek
    losujelement(h,l,ib,BANAN,tab);//losowanie bananow
    losujelement(h,l,ik,KOKOS,tab);//losowanie kokosów

    for (a=0; a<h; a++)      //CZASOWO
    {
        for (z=0; z<l; z++)
        {

            printf("%d ",tab[a][z]);

        }
        printf("\n");
    }

    *hh=h;
    *ll=l;

    return 0;
}
void losujelement(int h,int l,int ilosc,int rodzaj,int **tab) //losowanie elementu na dane pole
{

    int temp2,temp3,czas,a,z;


    czas=time(NULL);
    srand(czas);

    for (a=0; a<ilosc; a++)
    {
        do
        {
            temp2=rand()%h;
            temp3=rand()%l;
        }
        while (tab[temp2][temp3]!=POLE_ZWYKLE);
        tab[temp2][temp3]=rodzaj;
    } //losowanie elementu



}
void instrukcja() //instrukcja
{
    int b;
    system("cls");//czysci ekran
    printf("DUSZEK jest gra, ktorej celem jest przejscie tytulowym duszkiem z lewego gornego\
do prawego dolnego rogu pola gry.Na poczatku gry otrzymujesz pule punktow\n\
(mniejsza od dlugosci wiekszego boku planszy).\
Ruch na pole puste kosztuje jeden punkt,\
zas ruch na pole z jedzeniem skutkuje konsumpcja i dodaniem liczby punktow zaleznej od rodzaju posilku.\n\n \
       POWODZENIA! :) \n\n\n");
    printf("Nacisnij 1 by powrocic do MENU lub 0 by zamknac gre\n");
    b=dajinta(0,1);
    if (b==1) main();
    else exit(0);
}

 void zapisplanszydopliku(int h,int l,int **tab) //zapisanie planszy do pliku
    {
        FILE *plik;
        int a,b;
        char nazwa[150];

        printf("Podaj nazwe pliku do ktorego zostanie zapisana plansza\n");
        printf("Nazwa Twojego pliku nie moze przekroczyc 150 znakow!\n\n");
        printf("Pamietaj, aby plik konczyl sie rozszerzeniem .txt\n");

        scanf("%149s",&nazwa);

        plik = fopen(nazwa, "w");

        if (plik==NULL)
        {
            printf("Blad otwarcia pliku\n\n");
            printf("Wcisnij dowolny przycisk by powrocic do glownego menu\n");
            getch();
            main();
        }
        else
        {
            for  (a=0; a<h; a++)
            {
                for(b=0; b<l; b++)
                {
                    fprintf(plik,"%d ",tab[a][b]);
                }
                fprintf(plik,"\n",tab[a][b]);
            }




        }
        fclose(plik);
    }


void menugrazwykla() //menu gry zwyklej
{

    int a,c;
    printf("PAMIETAJ, ZE POLE GRY MOZE PRZYJMOWAC ROZMIARY OD 5X5 DO 1000X1000\n\n\n");

    printf("Chcesz utworzyc wlasna plansze czy wczytac ja z pliku?\n\n");
    printf("1.Stworz wlasna plansze i rozpocznij gre\n");
    printf("2.Wczytaj plansze z pliku\n");
    printf("3.Stworz wlasna plansze i zapisz ja do pliku\n");
    printf("4.Powrot do MENU\n");
    printf("5.Zamknij gre");

    printf("\n\n\nWcisnij numer podany przy akcji, ktora chcesz wykonac\n");
    c=dajinta(1,5);

    int h,l,**tab;


tab= malloc(h* sizeof(int *)); //inicjalizacja dwuwymiarowej tablicy dynamicznej

    for(a=0; a<h;a++)
    {
        tab[a] = malloc(l* sizeof(int));

    }

    if (c==5) exit(0);
    if (c==4) main();
    if (c==3)
    {
        tworzplansze(&h,&l,tab);
        int a,z;

        for(a=0;a<h;a++){for (z=0;z<l;z++)   {printf("%d ",tab[a][z]);} printf("\n");}
        zapisplanszydopliku(h,l,tab);
    }
    if (c==1) tworzplansze(&h,&l,tab);

}



int main() //funkcja glowna
{
    system("cls");
    printf("Witaj w grze DUSZEK!\n\n\n\nWcisnij dowolny przycisk aby rozpoczac");
    getch();
    int x;
    x=menu();
    if (x==4) exit(0);
    if (x==1) menugrazwykla();
//if (x==2) graautomatyczna;
    if (x==3) instrukcja();

    return 0;
}
