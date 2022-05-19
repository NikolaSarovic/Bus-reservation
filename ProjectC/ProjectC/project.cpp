#include "PJ.h";
char zvjezdice[]="*************************************************";
char opcije[]="Na raspolaganju su vam sledece opcije:\n\t1 - Unos rezervacije\n\t2 - Stampanje svih rezervacija\n\t3 - Otkazivanje rezervacije\n\t4 - Din. mem.\n\t0 - Izlaz iz programa";
char lok_rezervacije[]="REZERVACIJE.RTF";
char lok_autobus[]="AUTOBUS.INI";
char crtice[]="----------------------------------------";
char brisanje[]="                                      ";
void interfejs();
void Unos(FILE *bus , FILE *rezervacije);
void Stampanje(FILE *bus , FILE *rezervacije);
void Otkazivanje(FILE *bus , FILE *rezervacije);
void main()
{
	int opcija;
	FILE *bus;
	FILE *rezervacije;
	rezervacije=fopen(lok_rezervacije,"r+");
	bus=fopen(lok_autobus,"rb");
	if(rezervacije==NULL || bus==NULL)
	{
	GenerisiTestneFajlove(1,1,lok_rezervacije,lok_autobus);
	}
	while(1)
	{
		interfejs();
		printf("\n%s\n%s\nUnesite broj opcije koju zelite:\n\t:>",opcije,zvjezdice);
		scanf("%d",&opcija);
		system("cls");
		switch(opcija)
			{
		    case UNOS_REZERVACIJE:
	         Unos(bus , rezervacije);
				  break;
            case STAMPANJE_SVIH_REZERVACIJA:
			Stampanje(bus ,rezervacije);
				  break;
			 case OTKAZIVANJE_REZERVACIJE :
			  Otkazivanje(bus , rezervacije);
				break;
			 case DIN_MEM:
				break;
				
			 case IZLAZ_IZ_PROGRAMA:
				return;
	
			}
		system("pause");
		system("cls");
	};


  
}
void interfejs()
{
	datum  trenutni_datum;
	vrijeme trenutno_vrijeme;
	trenutno_vrijeme=TrenutnoVrijeme(&trenutni_datum);
	
	printf("%s\n\n\t\tBUS++\n\n %d:%d - %d/%d/%d	  by Nikola Sarovic, 1848\n%s ",zvjezdice,trenutno_vrijeme.h,trenutno_vrijeme.m,trenutni_datum.dan,trenutni_datum.mjesec,trenutni_datum.godina,zvjezdice);
}
void Unos(FILE *bus , FILE *rezervacije)
{
	int br_sjedista,br_sjed_u_redu,br_sjed_u_zadnjem_redu,i,j;
	mjesto pom,pom1,niz[25];
	interfejs();
	fseek(bus,0,0);
	fread(&br_sjedista,sizeof(int),1,bus);
	fread(&br_sjed_u_redu,sizeof(int),1,bus);
	fread(&br_sjed_u_zadnjem_redu,sizeof(int),1,bus);
	// Stampanje
	printf("\n\n %s\n |\t\t\t\t\t|\n |\t\t\t\t\t|\n |\tV\t\t\t\t|\n |\t\t\t\t\t|",crtice);
	fseek(rezervacije,0,0);
	for(i=0;i<5;i++)
	{
		printf("\n |\t\t\t\t\t|\n |\t\t\t\t\t|");
		 printf("\n | ");
		 for(j=0;j<2;j++)
		 {
			 fscanf(rezervacije,"%d\n%s%s\n%d",&pom.redni_br,pom.p.ime,pom.p.prezime,&pom.status_mjesta);
			 if(pom.status_mjesta==SLOBODNO)
			 printf("  %02d. S",pom.redni_br);
			 else if(pom.status_mjesta==ZAUZETO)
			 printf("  %02d. Z",pom.redni_br);
		 }
		 printf("\t");
		  for(j=0;j<2;j++)
		 {
			 fscanf(rezervacije,"%d\n%s%s\n%d",&pom.redni_br,pom.p.ime,pom.p.prezime,&pom.status_mjesta);
			 if(pom.status_mjesta==SLOBODNO)
			 printf("  %02d. S",pom.redni_br);
			 else if(pom.status_mjesta==ZAUZETO)
			 printf("  %02d. Z",pom.redni_br);
		 }
		 printf("  |");
	 }
	printf("\n |\t\t\t\t\t|\n |\t\t\t\t\t|");
	printf("\n | ");
	for(i=0;i<5;i++)
	{  
		 fscanf(rezervacije,"%d\n%s%s\n%d",&pom.redni_br,pom.p.ime,pom.p.prezime,&pom.status_mjesta);
		 if(pom.status_mjesta==SLOBODNO)
			 printf("  %02d. S",pom.redni_br);
			 else if(pom.status_mjesta==ZAUZETO)
			 printf("  %02d. Z",pom.redni_br);
	}
	printf("  |");
	printf("\n |\t\t\t\t\t|\n |\t\t\t\t\t|\n %s",crtice);
	//........................................................
	printf("\nUnesite broj sjedista koje zelite da rezervisete\n(S - slobodno, z - zauzeto i ne moze se rezervisati)\n:>");
	scanf("%d",&pom.redni_br);
	pom.status_mjesta=ZAUZETO;
	//Izmjena
	fseek(rezervacije,0,0);
	   for(j=0;j<br_sjedista;j++)
		 {
	     fscanf(rezervacije,"%d\n%s%s\n%d",&pom1.redni_br,pom1.p.ime,pom1.p.prezime,&pom1.status_mjesta);
		 niz[j]=pom1;
         }
	   if(niz[pom.redni_br-1].status_mjesta==SLOBODNO)
	   {
		   printf("\nUnesite ime i prezime putnika:\n:>");
	       scanf("%s %s",pom.p.ime,pom.p.prezime);
		   niz[pom.redni_br-1]=pom;
		  fseek(rezervacije,0,0);
		  for(j=0;j<br_sjedista;j++)
		  {
			 fprintf(rezervacije,"%d\n%-10s %10s\n%d\n",niz[j].redni_br,niz[j].p.ime,niz[j].p.prezime,niz[j].status_mjesta);
		  }
		  printf("\nUSPJESNO STE REZERVISALI SJEDISTE BR. %d.\n",pom.redni_br);
	   }
	   else if(niz[pom.redni_br-1].status_mjesta==ZAUZETO)
		   printf("\nSJEDISTE BR. %d JE VEC ZAUZETO I NE MOZETE GA REZERVISATI!)\n\n",pom.redni_br);


}
void Stampanje(FILE *bus , FILE *rezervacije)
{
	
	int br_sjedista,br_sjed_u_redu,br_sjed_u_zadnjem_redu,i,j;
	mjesto pom;
	FILE *stampa;
	fseek(bus,0,0);
	fread(&br_sjedista,sizeof(int),1,bus);
	stampa=fopen("Ostampano.txt","w");
	fprintf(stampa,"\n\n %s\n |\t\t\t\t\t|\n |\t\t\t\t\t|\n |\tV\t\t\t\t|\n |\t\t\t\t\t|",crtice);
	fseek(rezervacije,0,0);
	for(i=0;i<5;i++)
	{
		fprintf(stampa,"\n |\t\t\t\t\t|\n |\t\t\t\t\t|");
		 fprintf(stampa,"\n | ");
		 for(j=0;j<2;j++)
		 {
			 fscanf(rezervacije,"%d\n%s%s\n%d",&pom.redni_br,pom.p.ime,pom.p.prezime,&pom.status_mjesta);
			 if(pom.status_mjesta==SLOBODNO)
			 fprintf(stampa,"  %02d. S",pom.redni_br);
			 else if(pom.status_mjesta==ZAUZETO)
			 fprintf(stampa,"  %02d. Z",pom.redni_br);
		 }
		 fprintf(stampa,"\t");
		  for(j=0;j<2;j++)
		 {
			 fscanf(rezervacije,"%d\n%s%s\n%d",&pom.redni_br,pom.p.ime,pom.p.prezime,&pom.status_mjesta);
			 if(pom.status_mjesta==SLOBODNO)
			 fprintf(stampa,"  %02d. S",pom.redni_br);
			 else if(pom.status_mjesta==ZAUZETO)
			 fprintf(stampa,"  %02d. Z",pom.redni_br);
		 }
		 fprintf(stampa,"  |");
	 }
	fprintf(stampa,"\n |\t\t\t\t\t|\n |\t\t\t\t\t|");
	fprintf(stampa,"\n | ");
	for(i=0;i<5;i++)
	{  
		 fscanf(rezervacije,"%d\n%s%s\n%d",&pom.redni_br,pom.p.ime,pom.p.prezime,&pom.status_mjesta);
		 if(pom.status_mjesta==SLOBODNO)
			 fprintf(stampa,"  %02d. S",pom.redni_br);
			 else if(pom.status_mjesta==ZAUZETO)
			 fprintf(stampa,"  %02d. Z",pom.redni_br);
	}
	fprintf(stampa,"  |");
	fprintf(stampa,"\n |\t\t\t\t\t|\n |\t\t\t\t\t|\n %s",crtice);
	//........................................................
	 fprintf(stampa,"\n\nBr.Sjedista    Ime\t\t     Prezime");
	 fseek(rezervacije,0,0);
	for(i=0;i<br_sjedista;i++)
	{
		fscanf(rezervacije,"%d\n%s%s\n%d\n",&pom.redni_br,pom.p.ime,pom.p.prezime,&pom.status_mjesta);
	    fprintf(stampa,"\n  %d. \t\t%-10s\t%10s ",pom.redni_br,pom.p.ime,pom.p.prezime);
	}

}

void Otkazivanje(FILE *bus , FILE *rezervacije)
{
	int br_sjedista,br_sjed_u_redu,br_sjed_u_zadnjem_redu,i,j,opcija;
	mjesto pom,pom1,niz[25];
	interfejs();
	fseek(bus,0,0);
	fread(&br_sjedista,sizeof(int),1,bus);
	fread(&br_sjed_u_redu,sizeof(int),1,bus);
	fread(&br_sjed_u_zadnjem_redu,sizeof(int),1,bus);
	// Stampanje
	printf("\n\n %s\n |\t\t\t\t\t|\n |\t\t\t\t\t|\n |\tV\t\t\t\t|\n |\t\t\t\t\t|",crtice);
	fseek(rezervacije,0,0);
	for(i=0;i<5;i++)
	{
		printf("\n |\t\t\t\t\t|\n |\t\t\t\t\t|");
		 printf("\n | ");
		 for(j=0;j<2;j++)
		 {
			 fscanf(rezervacije,"%d\n%s%s\n%d",&pom.redni_br,pom.p.ime,pom.p.prezime,&pom.status_mjesta);
			 if(pom.status_mjesta==SLOBODNO)
			 printf("  %02d. S",pom.redni_br);
			 else if(pom.status_mjesta==ZAUZETO)
			 printf("  %02d. Z",pom.redni_br);
		 }
		 printf("\t");
		  for(j=0;j<2;j++)
		 {
			 fscanf(rezervacije,"%d\n%s%s\n%d",&pom.redni_br,pom.p.ime,pom.p.prezime,&pom.status_mjesta);
			 if(pom.status_mjesta==SLOBODNO)
			 printf("  %02d. S",pom.redni_br);
			 else if(pom.status_mjesta==ZAUZETO)
			 printf("  %02d. Z",pom.redni_br);
		 }
		 printf("  |");
	 }
	printf("\n |\t\t\t\t\t|\n |\t\t\t\t\t|");
	printf("\n | ");
	for(i=0;i<5;i++)
	{  
		 fscanf(rezervacije,"%d\n%s%s\n%d",&pom.redni_br,pom.p.ime,pom.p.prezime,&pom.status_mjesta);
		 if(pom.status_mjesta==SLOBODNO)
			 printf("  %02d. S",pom.redni_br);
			 else if(pom.status_mjesta==ZAUZETO)
			 printf("  %02d. Z",pom.redni_br);
	}
	printf("  |");
	printf("\n |\t\t\t\t\t|\n |\t\t\t\t\t|\n %s",crtice);
	//........................................................
	printf("\nUnesite broj sjedista za koje zelite da otkazete rezervaciju:\n(S - slobodno, z - zauzeto i ne moze se rezervisati)\n:>");
	scanf("%d",&pom.redni_br);
	pom.status_mjesta=SLOBODNO;
	strcpy(pom.p.ime, "N.");
	strcpy(pom.p.prezime, "N.");
	//Izmjena
	fseek(rezervacije,0,0);
	   for(j=0;j<br_sjedista;j++)
		 {
	     fscanf(rezervacije,"%d\n%s%s\n%d",&pom1.redni_br,pom1.p.ime,pom1.p.prezime,&pom1.status_mjesta);
		 niz[j]=pom1;
         }
	   if(niz[pom.redni_br-1].status_mjesta==SLOBODNO)
	   {
		 printf("\nTO MJESTO JE SLOBODNO!\n");
	   }
	   else if(niz[pom.redni_br-1].status_mjesta==ZAUZETO)
		  
	   {
		   printf("Da li zeli da otkaze rezervaciju za putnika  %s %s: (1 - DA  2 - NE)",niz[pom.redni_br-1].p.ime,niz[pom.redni_br-1].p.prezime);
		   scanf("%d",&opcija);
		   if(opcija==1)
		   {
			   niz[pom.redni_br-1]=pom;
			   fseek(rezervacije,0,0);
               for(j=0;j<br_sjedista;j++)
				  {
					 fprintf(rezervacije,"%d\n%-10s %10s\n%d\n",niz[j].redni_br,niz[j].p.ime,niz[j].p.prezime,niz[j].status_mjesta);
				  }
		   
		   }
	   
	   }

}