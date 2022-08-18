#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


// COSTANTI DICHIARATE PER LE VARIE DIMENSIONI  
// DIM_BLOCCO = Dimensione di un blocco di righe da 50 righe 
#define DIM_BLOCCO 50
//MAX_LINEE= Lunghezza massima di una riga del file 
#define MAX_LINEE 200
// MAX_LEN_NAME_FILE = Lunghezza massima del nome dei file 
#define MAX_LEN_NAME_FILE 50


//  Dichiarazione funzione che prende in input argc e argv ed effettua i controlli sulle opzioni + redirezione output su un file con opt -o 
void  controlloOpzioni(int , char*[] , bool[]);
/*  Dichiarazione funzione che prende in input i nomi dei due file da cui si sta leggendo, l'array che contiene el opzioni passate e il booleano che indica se i due file sono differenti
	Controlla le opzioni e stampa il testo relativo ai comandi g ed s */
void gestione_stampe_gs(char [], char [], bool [], bool );
/* Dichiarazione funzione che prende in input il nome dei due file, le due righe di testo e il numero delle righe analizzate
   Effettua le stampe richieste dalle opzioni d ed u quando sono combinate con il comando v  */
void gestione_stampe_du(char [], char [] , char [], char [], int );






int main (int argc, char *argv[]){
	
	// nome_file1 e nomefile2 contengono i nomi dei 2 file letti come parametri del comando 
	char nome_file1[50];
	char nome_file2[50];
	//FILE che rappresentano i due file che verranno successivamente aperti 
    FILE *file1 = NULL;
    FILE *file2 = NULL;
    // Booleano che indica la fine di un file 
	bool fine_file = true;
	// righe1 e righe2 rappresentano i due blocchi da 50 righe ciascuno da leggere volta per volta 
	char *righe1[DIM_BLOCCO] = {NULL};
	char *righe2[DIM_BLOCCO]= {NULL};
	// singola_riga1 e singola_riga2 rappresentano le singole righe lette dai 2 file 
	char singola_riga1[MAX_LINEE];
	char singola_riga2[MAX_LINEE];
	// Array di booleani utilizzati per la gestione delle opzione e dei controlli options[ g, s, d, u, v, o ]
	bool options[6] = {false, false, false, false, false, false};
	// Numero di blocchi analizzati 
	int blocco = 0 ;
	// Numero di riga mentre si scorre tra le 50 
	int riga = 0;
	// Booleano che indica se i due file sono diversi in almeno una riga 
	bool diversi = false;
	
	
	//Varibili usate per ottenere il risultato delle due fgets quando si sta leggendo il file 
	char *b1 = NULL;
	char *b2 = NULL;
	
	
	// Richiamo funzione che effettua il controllo sulle opzioni passate e inizializza il vettore options 
	controlloOpzioni(argc, argv, options);
	
  
	// Salvo il nome dei due file all'interno di due variabili apposite 
	strcpy (nome_file1, argv[1]);
    strcpy (nome_file2, argv[2]);
	

	// Apertura dei due file
    file1 = fopen(nome_file1, "r"  );
	file2 = fopen(nome_file2, "r");
	
	
		
	// Controllo che i due file siano stati aperti correttamente oppure stampo errore e termino programma 
	if(file1 == NULL || file2 == NULL){
		printf("ERRORE NELL'APERTURA DEI FILE. Provare a passare i nomi completi (inclusa l'estensione) di 2 file");
		exit(EXIT_FAILURE);
	}
	
	
	// Variabile usate come contatore per i cicli 
	int x=0;

	/*Caricamento in blocchi da 50 righe dei 2 file 
	Continua ad eseguire il ciclo while finchè non si individua la fine di un file che implica che fine_file = false e il break del ciclo while
	Il ciclo while viene stoppato a causa della var booleana fine_file == false 
	*/
while(fine_file ){
	
	
		for(riga = 0; riga<DIM_BLOCCO; riga++ ){
		/* Si controlla se uno dei due file termina, per effettuare il controllo si sfrutta il parametro di ritorno dell'fgets che in caso incontra
			la terminazione di un file ritorna NULL. Se uno dei due file ? terminato allora si termina il caricamento 
			( terminando il ciclo for e uscendo dal ciclo while attraverso il booleano fine_file)
		*/
	

		// In modo da poter capire quale file eventualmente sia vuoto
		b1 = fgets(singola_riga1, MAX_LINEE, file1);
		b2 = fgets(singola_riga2, MAX_LINEE, file2);
		 
		 //Controllo se uno dei due file è terminato oppure anche se vuoto
		 if(b1 == NULL || b2 == NULL){
		 	fine_file = false;
		 	break;
		 }else{
			
				// Inserimento nei due blocchi da 50 righe associati a ciascun file delle due singole righe dei file
					righe1[riga] = malloc(MAX_LINEE +1);
					strcpy(righe1[riga], singola_riga1);
				
					righe2[riga] = malloc(MAX_LINEE +1);
					strcpy(righe2[riga], singola_riga2);
			}
	}

		
		// Gestione del caso in cui uno più file siano vuoti
		if(blocco == 0 && riga == 0){
			
			if(b1 == NULL && b2 == NULL){
				// Se i due file sono vuoti allora sono uguali
				printf("Il due file sono vuoti -> SONO UGUALI");
				exit(EXIT_FAILURE);
			}else if (b1 == NULL){
				// Se solo il primo dei due file è vuoto allora sono differenti
				printf("Il file %s vuoto -> I DUE FILE SONO DIFFERENTI", nome_file1);
				exit(EXIT_FAILURE);
			}else if(b2 == NULL){
				// Se solo il secondo dei due file è vuoto allora sono differenti
				printf("Il file %s vuoto -> I DUE FILE SONO DIFFERENTI", nome_file2);
				exit(EXIT_FAILURE);
			}
			
			
		}

		
		/*
		Per ogni riga dei due blocchi caricati, viene effettuato il confronto tra le due righe ( strcmp(righe1[x], righe2[x])  ) 
		In caso le due righe siano differenti, viene inpostato diversi = true in modo da poter salvare che i due file hanno almeno una riga differente 
		Dopo di che si controllano le eventuali opzioni passate:
			- in caso si abbia -d ( options[2] ) e non -v (options[4) si stampa il numero di righe differenti  
			- in caso si abbia -d ( options[2] ) e -v (options[4) si richiama la funzione di stampa  " gestione_stampe_du "
			- in caso si abbia -u ( options[3] ) e non -v (options[4) si stampa il numero di righe uguali 
			- in caso si abbia -u ( options[3] ) e -v (options[4) si richiama la funzione di stampa  " gestione_stampe_du "
		*/
		for(x = 0; x<riga; x++){


			// Confronto le due stringhe e controlllo le opzioni attive e richiamo le funzioni nel caso necessario 
			if (strcmp(righe1[x], righe2[x]) ){
					diversi = true;
					if(options[2] && !options[4]){
						printf("%i\n",  x + (blocco*DIM_BLOCCO) +1);
					}else if(options[2] && options[4]){
						//I numeri di riga sono incrementati di 1 poichè se no si partirebbe da 0
						gestione_stampe_du(nome_file1, nome_file2, righe1[x], righe2[x], x + (blocco*DIM_BLOCCO) +1);
					}
				
			}else{
					if(options[3] && !options[4]){
						printf("%i\n",  x + (blocco*DIM_BLOCCO) +1);
					}else if (options[3] && options[4] ){
						gestione_stampe_du(nome_file1, nome_file2,  righe1[x], righe2[x], x + (blocco*DIM_BLOCCO) +1 );
					}
			}
			
		}
	
		// Incremento il numero di blocchi analizzati dal programma in modo da sapere il vero numero di riga nel file 
		blocco++;		
	}

	// Richiamo funzione gestione_stampe_gs 
	gestione_stampe_gs(nome_file1, nome_file2, options, diversi);
	
	return(0);
	
}


/*
Funzione che gestisce la stampa relativa alle opzioni d/u in  caso i loro flag siano true nell'array options  con l'opazione v attiva 
*/

void gestione_stampe_du(char nomeFile1[], char nomeFile2[], char riga1[], char riga2[], int riga){

	printf("%i, %s: %s", riga, nomeFile1, riga1);

	//  Controllo se la riga1 contiene la sottostringa "\n" in modo da formattare correttamente l'output
	if(strstr(riga1, "\n") == NULL){
		printf("\n");
	}
	
	printf("%i, %s: %s\n", riga, nomeFile2, riga2);
	
	//  Controllo se la riga1 contiene la sottostringa "\n" in modo da formattare correttamente l'output
	if(strstr(riga1, "\n") == NULL){
		printf("\n");
	}
}


/*
Funzione che controlla le opzioni passate (options[0] == g e options[1] == s ) e se i due file hanno righe diverse (diversi == true)
 e gestisce l'eventuale stampa se i due file sono diversi o uguali ( solo se le opzioni g/s sono state effettivamente passate)
*/
void gestione_stampe_gs(char nomeFile1[], char nomeFile2[], bool options[], bool diversi ){
	
	if(options[0] && diversi){
		printf("%s ed %s sono diversi", nomeFile1, nomeFile2);
	}else if(options[1] && !diversi ){
		printf("%s ed %s sono uguali", nomeFile1, nomeFile2);
	}
	exit(EXIT_SUCCESS);
}


/*
Funzione che crea un vettore contenente le varie opzioni lette dalla riga di comando e 
in caso di opzione -o reindirizza lo standard output sul file passato come parametro dell'opzione
*/
void controlloOpzioni(int dim, char *argv[], bool options[]){
	  
	/*Per far funzionare getopt su windows copiamo argv dal contenuto precedente alla prima opzione 
	 SE L'HOMEWORK AVESSE DOVUTO FUNZIONARE SOLO SU LINUX  NON SAREBBE STATO NECESSARIO POICHE' LINUX PERMUTA LA STRINGA 
	 E NON NECESSITA CHE LA PRIMA SRTINGA SIA PER FORZA UN OPZIONE
	 WINDOWS LE CHIEDE COME PRIME STRINGHE IN ARGV QUINDI AVENDO PRIMA IL NOME DEI 2 FILE RITORNA SUBITO -1 E SMETTE DI CONTROLLARE LA STRINGA 
	*/
    int dim_array_opzioni = dim -2;
	char *opzioni[dim_array_opzioni];
	int st = 2;
	int x = 0;
	int c;
	
	while(x< dim_array_opzioni ){
		opzioni[x] = argv[st];
		st+=1;
		x++;
	}

	// Variabile utilizzata per controllare che si abbia almeno un opzione  
	bool parametri_presenti = false;
	
 	// 	Setto i valori relative alle varie opzioni in options 
  	while ((c = getopt (dim_array_opzioni, opzioni, "gsduvo:")) != -1){
  		parametri_presenti = true;
	    switch (c)
	      {
	      case 'g':
	        options[0] = true;
	        break;
	      case 's':
	        options[1] = true;
	        break;
	      case 'd':
			 options[2] = true;
	        break;
	      case 'u':
			 options[3] = true;
	        break; 
	      case 'v':
			 options[4] = true;
	        break;
	      case 'o':
	      	/* optarg contine il parametro dell'opzione
	      	   Reindirizzerò l'output delle altre funioni sul file indicato come parametro 
	      	*/
	      	//printf("%s", optarg);
	    	freopen(optarg, "a+", stdout); 
			options[5] = true;
	        break;
	      case '?':
	      	exit(EXIT_FAILURE);
	        break;
		  case ':':
		  	exit(EXIT_FAILURE);
	      default:
	      	printf("INTERCETTA");
	        abort ();
	      }
	}	
   
   // Stampa errore in caso non sia stato passato nessun opzione al programma 
   	if (!parametri_presenti){
   		printf("Il programma per funzione deve ricevere: file1 file2 opzione");
   		exit(EXIT_FAILURE);
	   }
   
   	// Gestione dei casi in cui si passino contemporaneamente le opzioni d e u 
   	if(options[2] && options[3]){
   		printf("Mutuamente esclusivi d e u ");
   		exit(EXIT_FAILURE);
	}else if( options[4] ){
		// Gestisce il caso in cui l'opzione -v non sia accoppiata con l'opzione -u o -d 
		if ( !options[2] && !options[3]){
			printf("L'opzione -v deve essere accoppiato all'opzione -u oppure al  -d ");
			exit(EXIT_FAILURE);
		}
	}

}



