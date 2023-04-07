## Descrizione generale
  Il problema richiedeva l’analisi in blocchi di 50 righe di 2 file, i cui nomi vengono passati come input al 
  programma insieme alcune opzioni.
## Librerie utilizzate
  • stdio.h : utilizzata per gestione input/output; <br />
  • stdbool.h : per implementare le variabili booleane usate, si sarebbe potuto evitare ed usare un int;<br />
  • unistd.h : per sfruttare la funzione getopt();<br />
  • stdlib.h : per EXIT_FAILURE e EXIT_SUCCESS;<br />
  • string.h : per sfruttare funzioni come strcmp(), strcpy() e strlen()<br />
  
## Costanti utilizzate
  • DIM_BLOCCO con valore 50 che rappresenta la dimensione di un singolo blocco da 50 righe;<br />
  • MAX_LINEE con valore 200 che rappresenta il numero massimo di caratteri che può essere scritto <br />
  su una riga;
  • MAX_LEN_NAME_FILE con valore 50 che rappresenta la lunghezza massima consentita per il nome <br />
  dei due file passati come input al programma 
## Funzioni dichiarate
  • controlloOpzioni(int , char*[] , bool[]): rappresenta la funzione utilizzata per leggere le opzioni 
  passate al programma e assegna il valori corrispondenti alle varie opzioni all’array options.
  Il vettore options è un vettore di boolean e per ogni posizione si rappresenta un opzione
  options = [ g, s, d, u, v, o ]. In questa funzione è stata effettuata una copia del contenuto nella 
  prima cella di opzioni poiché getopt() su Linux effettua una permutazione della stringa e quindi le 
  opzioni possono essere posizionate anche dopo il nome dei due file, invece su Windows non 
  effettua la permutazione e richiede che le opzioni si trovino come primo elemento;
  La funzione controlla se sono state passate delle opzioni, in caso negativo restituisce un messaggio 
  di errore e termina l’esecuzione. Controlla anche se sono state passate delle opzioni mutuamente 
  esclusive come d ed u e gestisce il caso in cui v sia stata passata da solo senza u oppure d;<br />
  • gestione_stampe_gs(char [], char [], bool [], bool ): rappresenta la funzione usata per gestire le 
  stampe relative alle opzioni g ed s;<br />
  • gestione_stampe_du(char [], char [] , char [], char [], int ): rappresenta la funzione usata per gestire 
  le stampe relative alle opzioni d ed u combinate con l’opzione v
 
## Variabili dichiarate
  Per le variabili dichiarate nel dettaglio e la loro utilità nel programma consultare i commenti nel
  codice allegato dell’homework.
## File di test disponibili
  NUMERO_RIGHE = righe nel file [10, 50, 80,100,210]<br />
  diverso1_NUMERO_RIGHE diverso2_NUMERO_RIGHE sono due file differenti <br />
  diverso1_NUMERO_RIGHE uguale1_NUMERO_RIGHE sono due file uguali <br />
  vuoto1 vuoto2 sono due file vuoti TUTTI I FILE HANNO ESTENSIONE .txt <br />
## Funzionamento programma 
  Il programma dichiara diverse variabili necessarie per l’esecuzione del programma, dopo di che richiama la 
  funzione controlloOpzioni(), che in caso di problemi con le opzioni termina il programma. 
  Attraverso la funzione strcpy() salvo i nomi dei due file passati come input in argv[1] e argv[2] nelle variabili 
  nome_file1 e nome_file2, apro con la funzione fopen() i due file in modalità “r” cioè lettura. 
  Successivamente si controlla se file1 e file2, i due puntatori che tengono riferimento ai due file, sono NULL, 
  significa che ci sia stato un problema e si termina il processo del programma con un exit(EXIT_FAILURE).
  Si inizia il caricamento del testo 50 righe alla volta, per farlo si sfrutta un ciclo while che controlla se la 
  variabile fine_file == true, all’interno del ciclo si esegue un ciclo for da 0 a DIM_BLOCCO. All’interno di 
  questo ciclo for andiamo ad eseguire un fgets() sui due file e mettiamo il risultato di questi due fgets() nelle 
  variabili *b1 e *b2 (char*, poiché fgets() ritorna NULL in caso il file si abbia un errore oppure in questo caso 
  termina il file oppure il puntatore di singola_rigaX ), quindi controlla se uno tra *b1 e *b2 è uguale a NULL 
  allora si imposta fine_file = false in modo da far terminare successivamente il ciclo while e un break per 
  terminare il ciclo for. 
  Se le varibili *b1 e *b2 sono diverse da NULL allora si alloca memoria attraverso la funzione malloc() in 
  righe1[riga] in modo che possa contenere la riga letta dal file, dopo di che con la funzione strcpy() copiamo 
  la stringa puntata da singola_rigaX in righeX[riga].
  Dopo aver finito la lettura delle prime 50 righe oppure meno in caso il file termini prima, controlliamo se 
  uno dei due file è vuoto oppure entrambi. Se entrambi i file sono vuoti allora saranno uguali, se solo uno 
  dei due è vuoto si stampa il nome di quale dei due file è vuoto e che i due file sono differenti.
  Attraverso strcmp() si confrontano le due stringhe delle righe in analisi, se sono diverse viene impostata a 
  true la variabile booleana diversi usata come flag poi per gestire le opzioni g ed s, si controlla se abbiamo le 
  opzioni d ed v oppure u ed u attivate, in caso solo d od u siano attive allora si stampa solo il numero di riga
  veramente effettivo nel file e non nel blocco, calcolandolo come # riga nel blocco + (# blocco
  analizzato*DIM_BLOCCO) +1, oppure si richiama la funzione gestione_stampa_du a cui passiamo il nome 
  dei due file, le singole righe lette e il numero di riga effettivo. 
  Dopo di che alla fine di queste operazioni viene incrementata la variabile blocco che rappresenta il numero 
  di blocchi ( da 50 righe ) letti. Alla fine del ciclo while principale che rappresenta la fine della lettura dei file, 
  si richiama la funzione gestione_stamoe_gs a cui passiamo i nomi dei file, il vettore delle opzioni e il 
  booleano diversi. La funzione controlla se deve effettivamente stampare l’output nel caso in cui le opzioni g 
  ed s siano attivate.
  In caso una riga sia terminale e in un file non sia terminale, anche se la stringa leggibile dall’utente è uguale, 
  le righe saranno differenti poiché una conterrà uno ‘\n’ finale e questo le fa considerare due righe 
  differenti. 
## Come utilizzare il programma
  Il programma prende in input il nome dei due file separati da spazio, dopo di che sempre separate da spazio 
  prende in input le opzioni scelte tra [ g, s, d, u, v, o ], considerando le varie mutue esclusione imposte. 
  Anche le varie opzioni dovranno avere tra di loro uno spazio.
  In caso si utilizzi l’opzione -o sarà necessario, dopo aver inserito uno spazio, indicare il nome del file che 
  sarà utilizzato per reindirizzare l’output. I file che si vogliono utilizzare come parametri di input su cui 
  eseguire il programma si dovranno trovare all’interno della cartella in cui si sta eseguendo il processo 
  relativo al programma.
  Il programma calcola il diff tra la riga i-esima del file F1 e la riga i-esima del file F2, restituendo un output che dipende dalle opzioni passate da riga di comando. Le opzioni disponibili sono: <br />
  ●	-g: se F1 ed F2 sono diversi in almeno una riga restituisce la stringa ”F1 ed F2 sono differenti”. Al posto di F1 ed F2 vanno restituiti i nomi dei file elaborati <br />
  ●	-s: se F1 ed F2 sono uguali in tutte le righe restituisce la stringa “F1 ed F2 sono uguali”. Al posto di F1 ed F2 vanno restituiti i nomi dei file elaborati <br />
  ●	-d: restituisce I numeri delle righe differenti<br />
  ●	-u: restituisce I numeri delle righe uguali<br />
  ●	-v: combinato con –d o –u stampa le righe che differiscono o che sono uguali. Il formato di output deve essere:<br />
                #Riga, FILENAME F1: <riga di F1 che differisce o che e’ uguale><br />
                #Riga, FILENAME F2: <riga di F2 che differisce o che e’ uguale><br />
  ●	-o NOME_FILE_OUTPUT: ridireziona l’output su di un file di testo. <br />

## Prove effettuate
  Il programma è stato testato con tutti i file indicati sopra nella sezione “File di test disponibili”, sarebbero 
  troppe le possibili combinazioni provate, per questo nello spazio sottostante si indicano alcuni semplici test 
  del programma.
  • Eseguendo il programma con parametri diverso1_10.txt diverso2_10.txt -u -v avremo come output:<br />
  2, diverso1_10.txt: 2<br />
  2, diverso2_10.txt: diversa<br />
  4, diverso1_10.txt: diversa<br />
  4, diverso2_10.txt: 4<br />
  5, diverso1_10.txt: diversa<br />
  5, diverso2_10.txt: 5<br />
  7, diverso1_10.txt: diversa<br />
  7, diverso2_10.txt: 7<br />
  • Eseguendo il programma con parametri diverso1_10.txt e vuoto1.txt -u -v avremo come output:<br />
  Il file vuoto1.txt vuoto -> I DUE FILE SONO DIFFERENTI<br />
  • Eseguendo il programma con parametri diverso1_10.txt diverso2_210.txt -g avremo come output:<br />
  diverso1_10.txt ed diverso2_210.txt sono diversi<br />
