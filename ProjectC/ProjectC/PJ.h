#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//-----------------DEFINICIJE-----------------
#define UNOS_REZERVACIJE 1
#define STAMPANJE_SVIH_REZERVACIJA 2
#define OTKAZIVANJE_REZERVACIJE 3
#define DIN_MEM 4
#define IZLAZ_IZ_PROGRAMA 0

#define SLOBODNO 1
#define ZAUZETO 2
//--------------------------------------------


//-----------------STRUKTURE------------------
typedef struct
{
	char ime[25];
	char prezime[25];
	int broj_indexa;
	char smjer[50];
	int godina_studija;
	char datum_rodjenja[30];
	char datum_upisa[30];
	int broj_polozenih_ispita;
	char ocijene[48];
	float projek_osnovne_studije;
	float projsek_strukovne_studije;
	float prosjek;
}student;

typedef struct
{
	student student_info;
	int sifra_predmeta;
	int dio_ispita;
}prijava;

typedef struct
{
	char ime[25];
	char prezime[25];
	char funkcija[30];
	float staz;
	char JMBG[14];
}radnik;

typedef struct
{
	int h;
	int m;
	int s;
}vrijeme;

typedef struct
{
	int dan;
	int mjesec;
	int godina;
}datum;

typedef struct
{
	char ime[16];
	char prezime[16];
}putnik;

typedef struct
{
	int redni_br;
	putnik p;
	int status_mjesta;
}mjesto;

typedef struct
{
	int br_sjedista;
	int br_sjedista_u_redu;
	int br_sjedista_u_zadnjem_redu;
}autobus;
//--------------------------------------------

//------------------FUNKCIJE------------------
//Ova fukcija vam služi samo da vidite jeste li dobro kreirali
//projekat. Ako pozovete ovu funkciju iz main funkcije na
//displeju cete vidjeti poruku o uspješnom pokrtetanju.
void Test();
//Ova funkcija generise testne fajlove formatirane u skladu sa tekstom zadatka.
//	generisi_rezervacije - 0 ili 1 (0-Ne, 1-Da)
//	generisi_autobus - 0 ili 1 (0-Ne, 1-Da)
//	lok_rezervacije[] - putanja na kojoj ce se generisati rezervacije
//	lok_autobus[] - putanja na kojoj ce se generisati autobus
void GenerisiTestneFajlove(int generisi_rezervacije, int generisi_autobus, char lok_rezervacije[], char lok_autobus[]);
//Ova funkcija vraca trenutno vrijeme (sat, minut i sekund)
//	danasnji_datum - pokazivac na mem. lkaciju u koju ce biti upisano 
//					 danasnji datum (dan, mjesec i godina)
vrijeme TrenutnoVrijeme(datum *danasnji_datum);
//Ova funkcija otvara fajl na zadanoj lokaciji na zadani nacin.
//Prednost je samo što provjerava da li fajl ne postoji,
//ako ne postiji pokuša da ga kreira. Ako ni to ne uspije znaci
//da lokacija nije dobra i štampa obavještenje.
//	lokacija - putanja do fajla koji želite da otvorite
//	argumenti - nacin na koji želite da otvorite fajl (npr. "r+")
FILE *OtvoriiliKreirajFajl(char lokacija[], char argumenti[]);
//--------------------------------------------

//---------------IMPLEMENTACIJE---------------
void Test()
{
	FILE *test;
	printf("Ova funkcija je pozvana iz header fajla PJ.h\n\n");
	test = fopen("test123.txt", "w");
	fprintf(test, "Zdravo");
	fclose(test);
}

void GenerisiTestneFajlove(int generisi_rezervacije, int generisi_autobus, char lok_rezervacije[], char lok_autobus[])
{
	FILE *rezervacije, *bus;
	autobus a = {25, 4, 5};
	mjesto a_mjesto;
	int i;

	if(generisi_autobus)
	{
		bus = fopen(lok_autobus, "wb");
		fwrite(&a, sizeof(autobus), 1, bus);
		fclose(bus);
	}

	if(generisi_rezervacije)
	{
		rezervacije = fopen(lok_rezervacije, "w");
		for(i=0; i<a.br_sjedista; i++)
		{
			a_mjesto.redni_br = (i+1);
			strcpy(a_mjesto.p.ime, "N.");
			strcpy(a_mjesto.p.prezime, "N.");
			a_mjesto.status_mjesta = SLOBODNO;
			fprintf(rezervacije, "%d\n%s %s\n%d\n", a_mjesto.redni_br, a_mjesto.p.ime, a_mjesto.p.prezime, a_mjesto.status_mjesta);
		}
		fclose(rezervacije);
	}
}

vrijeme TrenutnoVrijeme(datum *danasnji_datum)
{
	time_t t;
	struct tm *v;
	vrijeme rez;

	time(&t);
	v = localtime(&t);
	
	rez.h = v->tm_hour;
	rez.m = v->tm_min;
	rez.s = v->tm_sec;
	danasnji_datum->dan = v->tm_mday;
	danasnji_datum->mjesec = v->tm_mon+1;
	danasnji_datum->godina = 1900 + v->tm_year;

	return rez;
}

FILE *OtvoriiliKreirajFajl(char lokacija[], char argumenti[])
{
	FILE *baza;
	baza = fopen(lokacija, argumenti);
	if(baza == NULL)
	{
		baza = fopen(lokacija, "w");
		if(baza == NULL)
		{
			printf("\n\n\t\tGRESKA: Problem prilikom otvaranja fajla. Vjerovatno putanja:\n\t\t\t%s\n\t\tne postoji.\n\n", lokacija);
			return(NULL);
		}
		fclose(baza);
		baza = fopen(lokacija, argumenti);
	}
	return(baza);
}