#include <LiquidCrystal.h>
#include <Keypad.h>
int pirsensor = 0; 

int a = 0, b = 0, c = 0, d = 0;  
int var = 0;
int C1 = 7, C2 = 7, C3 = 2, C4 = 3; //definizione della password
char f = '*'; //variabile che nasconde i caratteri della password
int volte = 0,sbagliata = 0; 
int possibilita = 3;
int crtl = 0;

const byte righe = 4; //dichiarazioni variabili per il funzionamento del tastierino numerico
const byte colonne = 4; 
char chiave[righe][colonne]=  //mappa dei caratteri sul tastierino
{
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
  
};
byte pinRighe[righe] = {2, 12, 11, 10}; 
byte pinColonne[colonne] = {9, 8, 7, 6}; 
Keypad keypad = Keypad( makeKeymap(chiave), pinRighe, pinColonne, righe, colonne );

LiquidCrystal lcd (A0, A1, A2, A3, A4, A5); //configura connessione con lo schermo LCD

void setup()
{
  Serial.begin(9600); //imposta la velocità in bit dei dati al secondo

  
  pinMode(3, OUTPUT); //Configurazioni Pin, in modo che si comportino come INPUT oppure OUTPUT
  pinMode(4, OUTPUT);
  pinMode(5, INPUT);
  
  
  
 lcd.begin(16, 2); //Indica il numero di colonne e di righe
 lcd.setCursor(3, 0); //Imposta cursore dello schermo LCD
 lcd.print("Benvenuto"); //stampa nello schermo le scritte
 lcd.setCursor(1, 1);
 lcd.print("L-C-D Allarme");
 delay(4000); //ritardo in ms
 
 lcd.clear(); //pulisce lo schermo
 lcd.setCursor(1, 0);
 lcd.print("Allarme spento");
 delay(2000);
 lcd.clear();
  

}


void loop()
 
{ 
 
  char key = keypad.getKey();//legge in input il valore del tasto cliccato sul tastierino
  if(!key)//se non si sta inserendo la password
  {
     
    lcd.setCursor(0, 0);
    lcd.print("inserisci codice");//stampa nello schermo le scritte
    delay(200);
  }
  
 
  if(key) //se rileva un input dal tastierino avvia il ciclo per selezionare la password, e per verificarne la corretezza 
    
  {
    lcd.setCursor(6+var, 1); //imposta posizionamento cursore
    lcd.print(key), lcd.setCursor(6+var, 1), lcd.print(f); //lcd.print(key) permette di visualizzare i valori premuti nel tastierino
    key = key - 48; //conversione variabile char key in interi
    var++;
    
    switch(var) //il sistema legge la password inserita
    {
      case 1:
      a = key;
      break;
      case 2:
      b = key;
      break;
      case 3:
      c = key;
      break;
      case 4:
      d = key;
      delay(100);  
      if(a == C1 && b == C2 && c == C3 && d == C4) //Se la password è corretta
      {
        lcd.clear();
        lcd.setCursor(4, 0);
        lcd.print("Password");
        lcd.setCursor(5, 1);
        lcd.print("Valida");
        
        delay(1000); //aspetta 1 secondo
        lcd.clear(); //pulisce lo schermo
        delay(1000); 
        if(crtl == 0){ //se l'allarme è disattivato
          
          crtl=1;
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Allarme attivato");
          delay(2000);
        }
        else{ //se è l'allarme è attivato  
        crtl = 0;
        lcd.setCursor(4, 0);
        lcd.print("Allarme");
        lcd.setCursor(3, 1);
        lcd.print("Disattivato");
         delay(2000);
        }
      }
      else//Se la password è errata
      {
        lcd.clear();
        lcd.setCursor(4, 0);
        lcd.print("Password");
        lcd.setCursor(4, 1);
        lcd.print("Invalida");
        delay(1000); 
        lcd.clear();
        delay(1000);
        
      }
      
     
      
      if(a == C1 && b == C2 && c == C3 && d == C4)
      {
        volte = 0;
        possibilita = 3; 
        
      }
      else //se la password è sbagliata
      {
        volte++; //sistema di sicurezza, max tentativi per indovinare la password: 3
        possibilita--; 
        lcd.setCursor(2, 0);
        lcd.print("Hai ancora :");
        lcd.setCursor(13, 0);
        lcd.print(possibilita); //stampa nello schermo il numero di possibilià rimanenti
        lcd.setCursor(2, 1);
        lcd.print("Possibilita'");
        delay(1000);
        if(possibilita == 0)//se si sono terminati i tentativi
        {
          lcd.clear();
          lcd.setCursor(3, 0);
          lcd.print("Contatta");
          lcd.setCursor(2, 1);
          lcd.print("Assistenza");
          
        }
          delay(1300);
       lcd.clear();
      }
      while(volte >= 3)//se si sono terminati i tentativi
      {
        lcd.clear();
        lcd.setCursor(2, 0);
        lcd.print("Attenzione");
        lcd.setCursor(4, 1);
        lcd.print("Intrusi");
        digitalWrite(3, HIGH);//accende il led
        digitalWrite(4, HIGH);//da suonare l'allarme
        tone(4, 1000, 18000);//durata e suono emesso dall'allarme
        //lcd.clear();
        delay(500);
        
      }
     
      var = 0;
      lcd.clear();
      
      
      break; //esce dal blocco
    }
      
  }
 else
 { 
   if(crtl == 1)
   { //se l'allarme è acceso
   pirsensor = digitalRead(5);//rilevazione movimento
  if(pirsensor == HIGH)//se c'è un movimento
  {
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
    tone(4, 1000, 2000); 
  }
  else //se l'allarme è spento
  {
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
 
  }
 }    
}
  
}
//Elia Renzoni, Federico Mantoni, Alessio Biagioli, Zenobi Pietro
