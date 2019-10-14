
#include <LiquidCrystal.h>
LiquidCrystal monEcran(7,6,5,4,3,2); // on crée l'objet �cran
#include <FastLED.h>
#define NUM_LEDS 16
#define DATA_PIN 40
#define CLOCK_PIN 13
CRGB leds[NUM_LEDS];

// Initialisation des boutons. //

boolean boutonBleu, boutonRouge, boutonJaune, boutonVert, boutonHaut, boutonBas, boutonGauche, boutonDroite;
const int boutonBleuPin=24, boutonRougePin=23, boutonJaunePin=25, boutonVertPin=22, boutonHautPin=26, boutonBasPin=27, boutonGauchePin=28, boutonDroitePin=29;

//

void setup() {
  Serial.begin(9600);
  pinMode(boutonBleuPin, INPUT);
  pinMode(boutonRougePin, INPUT);
  pinMode(boutonJaunePin, INPUT);
  pinMode(boutonVertPin, INPUT);
  pinMode(boutonHautPin, INPUT);
  pinMode(boutonBasPin, INPUT);
  pinMode(boutonGauchePin, INPUT);
  pinMode(boutonDroitePin, INPUT);
  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
  randomSeed(analogRead(0));//initialise la séquence aléatoire
  
// Permet d'éteindre toutes les leds
  for (int i=0; i<16;i=i+1){
    leds[i]=(0,0,0);
    FastLED.show();
//
  }
}

void loop() {
  int compte=0;
  
  // Initialisation des matrices. //
  char* totalEssai[10][4];
  int totalNoirs[10];
  int totalBlancs[10];
  int totalCor[10];
  
  monEcran.begin(16,2); //on initialise la communication avec 16 colonnes et deux lignes
  monEcran.clear(); // on efface l'écran
  monEcran.setCursor(3,0);
  monEcran.print("Hellooooo!"); 
  delay (1500);
  monEcran.clear();
  monEcran.setCursor(0,0);
  monEcran.print("Multijoueur ?");
  monEcran.setCursor(2,1);
  monEcran.print("Vert / Rouge");
  char *code [4];
  
  boolean choisi=0; // Permet de sortir de la boucle lorsque le code solution est choisi. //
  
  while (choisi==0){
    boutonVert=digitalRead(boutonVertPin);
    boutonRouge=digitalRead(boutonRougePin);

// Lorsque l'on appuie sur le bouton rouge pour jouer en mode solo. //
  if (boutonRouge==1){
    
    monEcran.clear();
    monEcran.print("Solo");
    delay(1500);  
  
// Permet de définir le code à trouver de manière aléatoire. // 
  char *couleur[] = {"R","V","B","J"}; // Notre bouton jaune étant défectueux, nous avons décidé de l'enlever du code à trouver. (char* couleur []= {"R","V","B"})

  for (int i=0; i<4; i=i+1){
    long a=random(0,4); // retourne valeurs entre min (0) et max-1(4-1). Et donc  a=random(0,3); car le bouton est défectueux. //
    code[i] = couleur[a];
    //
  }
  choisi=1; // Code couleur solution est défini, on sort de la boucle. //
  }

// Lorsqu'on appuie sur le bouton vert on décide de jouer en mutlijoueur. //
  else if (boutonVert==1){
    monEcran.clear();
    monEcran.print("Multijoueur");
    monEcran.clear();
    monEcran.print("Vous allez");
    monEcran.setCursor(0,1);
    monEcran.print("pouvoir choisir");
    delay(1500);
    monEcran.clear();
    monEcran.print("un code !");
    monEcran.setCursor(0,1);
    monEcran.print("Prêt ?");
    delay(1500);
    monEcran.clear();

    int i = 0 ;

    // Permet d'éteindre toutes les leds. //
    for (int i=0; i<16;i=i+1){
        leds[i]=(0,0,0);
        FastLED.show();
    }
    
// L'adversaire doit définir le code manuellement. //

    boolean fait = 0 ;// Permet de ne pas passer à la led suivante tant que celle ci n'est pas allumée. //

    while (i<4){
     monEcran.setCursor(0,0);   
     monEcran.print("Led ");
     //monEcran.setCursor(0,1);
     monEcran.print(i+1);
     boutonHaut = digitalRead(boutonHautPin);
     boutonBas = digitalRead(boutonBasPin);
     boutonGauche = digitalRead(boutonGauchePin);
     boutonDroite = digitalRead(boutonDroitePin);
     boutonBleu = digitalRead(boutonBleuPin);
     boutonRouge = digitalRead(boutonRougePin);
     boutonJaune = digitalRead(boutonJaunePin);
     boutonVert = digitalRead(boutonVertPin);
     
// On passe à la led suivante avec les boutons de direction. //
     if ((boutonBas||boutonHaut||boutonDroite||boutonGauche)==1 && i!=3 && fait==1 ){
        i=i+1; 
        fait = 0 ;
        delay(100);
        monEcran.clear();
     }  

// On valide la solution une fois que toutes les leds sont allumées grace aux boutons directionnels. //

     else if ((boutonBas||boutonHaut||boutonDroite||boutonGauche)==1 && i==3 &&fait==1){
      break;
     }  

// On sélectionne le code couleur avec les boutons de couleur. //
     else if (boutonBleu==1){
        code[i]="B";
        monEcran.setCursor(0,1);
        monEcran.print("B");
        delay(1000);
        monEcran.clear();
        leds[2+i] = CRGB(0,0,100);
        FastLED.show();
        fait = 1 ;
      }
      
      else if (boutonRouge==1){
        code[i]="R";
        monEcran.setCursor(0,1);
        monEcran.print("R");
        delay(1000);
        monEcran.clear();
        leds[2+i] = CRGB(100,0,0);
        FastLED.show();
        fait = 1 ;
      }
      else if (boutonJaune==1){
        code[i]="J";
        monEcran.setCursor(0,1);
        monEcran.print("J");
        delay(1000);
        monEcran.clear();
        leds[2+i] = CRGB(100,75,0);
        FastLED.show();
        fait = 1 ;
      }
      else if (boutonVert==1){
        code[i]="V";
        monEcran.setCursor(0,1);
        monEcran.print("V");
        delay(1000);
        monEcran.clear();
        leds[2+i] = CRGB(0,100,0);
        FastLED.show();
        fait = 1 ;
      }    
    }
    choisi=1;
    }
  }

// Une fois le code solution définit on peut passer au jeu. //

    monEcran.setCursor(0,0);
    monEcran.print("C'est parti !");
    delay(2000);
    monEcran.clear();
    
// 

  int compteur = 0;// Compteur général, il permet de compter le nombre d'essais, (ici 10 possibles).//
  int blancs = 0;

  while (compteur<10 && blancs<4){
    monEcran.clear();
    
// Permet d'éteindre toutes les leds

    for (int i=0; i<8;i=i+1){
      leds[i]=(0,0,0);
      FastLED.show();
    }

//
      blancs = 0;
      int noirs = 0;

// Permet à l'utilisateur de proposer un code couleur. //

    char* essai[4];
    int i=0;
    boolean fait = 0; // permet de ne pas passer à la led suivante sans avoir remplie celle en cours.
    while (i<4){
      boutonHaut = digitalRead(boutonHautPin);
      boutonBas = digitalRead(boutonBasPin);
      boutonGauche = digitalRead(boutonGauchePin);
      boutonDroite = digitalRead(boutonDroitePin);
      boutonBleu = digitalRead(boutonBleuPin);
      boutonRouge = digitalRead(boutonRougePin);
      boutonJaune = digitalRead(boutonJaunePin);
      boutonVert = digitalRead(boutonVertPin);
      monEcran.setCursor(0,0);
      monEcran.print("Un code ?");
      monEcran.setCursor(0,1);
      monEcran.print(i+1);
      int a = 2+i; //13-i

// Les boutons directionnnels permettent de passer à la led suivante, et les boutons de couleur permettent de sélectionner la couleur choisie. //
      if ((boutonDroite||boutonHaut||boutonBas||boutonGauche)==1 && i!=3 && fait==1){
        i=i+1;
        monEcran.clear();
        monEcran.setCursor(0,0);
        monEcran.print(i+1);
        delay(1000);
        monEcran.clear();
        fait=0;
      }
      else if (boutonBleu==1){
        essai[i]="B";
        monEcran.clear();
        monEcran.setCursor(0,0);
        monEcran.print(i+1);
        monEcran.setCursor(0,1);
        monEcran.print("B");
        delay(1000);
        monEcran.clear();
        leds[a] = CRGB(0,0,100);
        FastLED.show();
        fait=1;
      }
      else if (boutonRouge==1){
        essai[i]="R";
        monEcran.clear();
        monEcran.setCursor(0,0);
        monEcran.print(i+1);
        monEcran.setCursor(0,1);
        monEcran.print("R");
        delay(1000);
        monEcran.clear();
        leds[a] = CRGB(100,0,0);
        FastLED.show();
        fait=1;
      }
      else if (boutonJaune==1){
        essai[i]="J";
        monEcran.clear();
        monEcran.setCursor(0,0);
        monEcran.print(i+1);
        monEcran.setCursor(0,1);
        monEcran.print("J");
        delay(1000);
        monEcran.clear();
        leds[a] = CRGB(0,0,0);
        leds[a] = CRGB(100,75,0);
        FastLED.show();
        fait=1;
      }
      else if (boutonVert==1){
        essai[i]="V";
        monEcran.clear();
        monEcran.setCursor(0,0);
        monEcran.print(i+1);
        monEcran.setCursor(0,1);
        monEcran.print("V");
        delay(1000);
        monEcran.clear();
        leds[a] = CRGB(0,100,0);
        FastLED.show();
        fait=1;
      }
      
// Lorsque toutes les leds sont allumées peut valider avec un des boutons de directions. // 
      else if (i==3 && (boutonHaut||boutonGauche) == 1 && fait==1){// condition pour sortir de la boucle
        i=4;
      }
    }

// Permet l'interraction avec les boutons.//

    boutonHaut = digitalRead(boutonHautPin);
    boutonBas = digitalRead(boutonBasPin);
    boutonGauche = digitalRead(boutonGauchePin);
    boutonDroite = digitalRead(boutonDroitePin);
    boutonBleu = digitalRead(boutonBleuPin);
    boutonRouge = digitalRead(boutonRougePin);
    boutonJaune = digitalRead(boutonJaunePin);
    boutonVert = digitalRead(boutonVertPin);

// Permet de compter le nombre de pions blancs et noirs. // 

    noirs=0;
    blancs=0;
    for (int i=0; i<4; i=i+1){
      if (code[i] == essai[i]){
        blancs=blancs+1;
      }
    }
    char* code2[4];
    for (int b=0; b<4; b=b+1){
      code2[b]=code[b];
    }
    
    int noirs1=0;
    for (int i=0; i<4; i=i+1){
      boolean in = false;
      for (int a=0; a<4 ;a=a+1){
        if (essai[i] == code2[a]){
          code2[a] = "N";
          in = true;
          break;
        }
      }
      if (in==1){
        noirs = noirs+1;
      }
    }
    noirs = noirs - blancs ;

//
    
// Permet de sauvegarder les essais précédents avec les corrections (blancs et noirs) dans une matrice. //
    
    for (int i=0;i<4;i=i+1){
      totalEssai[compteur][i]= essai[i];
    }

    totalNoirs[compteur] = noirs;
    totalBlancs[compteur] = blancs;

//

// Permet d'afficher les leds de correction à la bonne place. //

    int ledCor[4] = {0,1,6,7}; 
    for (i=0; i<noirs ; i=i+1){
      leds[ledCor[i]] = CRGB(150,0,120);
    }
    for (i = noirs ; i< noirs+blancs ; i=i+1){
      leds[ledCor[i]] = CRGB(100,100,100);
    }
    FastLED.show();
    delay(2000);

//
    
    if (blancs==4){ // Si il y a 4 pions blancs, soit que la proposition est juste, on sort de la boucle.
      break;
      
    }

// Permet d'afficher les essais précédents pour pouvoir trouver le code de départ. //
    monEcran.clear();
    monEcran.setCursor(0,0);
    monEcran.print("Anciens essais");

    // On efface la ligne de led du haut. //
    for (int i=8; i<16;i=i+1){
      leds[i]=(0,0,0);
    }    
    FastLED.show();  
    //
          
    boolean sortie=1; // Condition pour faire tourner la boucle while qui suit. Ne réapparait pas de le code ensuite mais nécessaire pour while. //

    while (sortie==1){
      
      // Interractions avec les boutons. //
      boutonHaut = digitalRead(boutonHautPin);
      boutonBas = digitalRead(boutonBasPin);
      boutonGauche = digitalRead(boutonGauchePin);
      boutonDroite = digitalRead(boutonDroitePin);
      boutonBleu = digitalRead(boutonBleuPin);
      boutonRouge = digitalRead(boutonRougePin);
      boutonJaune = digitalRead(boutonJaunePin);
      boutonVert = digitalRead(boutonVertPin);
      //

      // Affiche le numéro de l'essai présent sur la ligne de led. //
      monEcran.setCursor(0,1);
      monEcran.print(compte+1);
      //

    // Lorsque l'on appuie sur un bouton de direction on passe à l'essai suivant. //
    
      // Tant que le compteur qui permet d'afficher les essais précédents (compte) est inférieur au compteur principal, compte augmente de 1. //
      if ((boutonHaut||boutonGauche||boutonDroite||boutonBas)==1 && compte<compteur){
        compte=compte+1;
        
        delay(500); // Ce delay permet à l'arduino de s'arrêter dès que l'on appuie sur le bouton et donc de ne prendre en compte qu'on seule fois cette boucle. //
        
        // Permet d'éteindre les leds de la ligne du dessus.//
        for (int i=8; i<16;i=i+1){
          leds[i]=(0,0,0);
        }
        FastLED.show();
        //
        
      }
      // Si compte est arrivé à la valeur du compteur principal il ne peut plus augmenter car l'essai qui suit n'a pas été encore proposé. //
      // Il revient alors à 0. //
      else if ((boutonHaut||boutonGauche||boutonDroite||boutonBas)==1 && compte==compteur){
        compte=0;
        delay(500);
        // Eteint la 2ieme ligne de led. //
        for (int i=8; i<16;i=i+1){
          leds[i]=(0,0,0);
        }
        FastLED.show();
      }

      //Permet d'afficher maintenant la correction de l'essai demandé. //
      for (int i=0; i<4; i=i+1){
        if (totalEssai[compte][i]=="R"){
          leds[13-i]=CRGB(100,0,0);
        }
        else if (totalEssai[compte][i]=="V"){
          leds[13-i]=CRGB(0,100,0);
        }
        else if (totalEssai[compte][i]=="B"){
          leds[13-i]=CRGB(0,0,100);
        }
        else if (totalEssai[compte][i]=="J"){
          leds[13-i]=CRGB(100,75,0);
        }
      }
      int ledCor2[4]={15,14,9,8};
      for (int i=0; i<totalNoirs[compte] ; i=i+1){
        leds[ledCor2[i]] = CRGB(150,0,120);
      }
      for (int i = totalNoirs[compte] ; i< (totalNoirs[compte]+totalBlancs[compte]) ; i=i+1){
        leds[ledCor2[i]] = CRGB(100,100,100);
      }
      FastLED.show();

      // On sort de la boucle quand on appuie sur un bouton de couleur. //
      // La visualisation des essais précédents est alors terminée pour ce tour.//
      if ((boutonVert||boutonBleu||boutonRouge||boutonJaune)==1){
        break;
      }
      //
      
    }

    // On passe au prochain essai. //
    monEcran.clear();
    monEcran.setCursor(0,0);
    if (blancs!=4){
      monEcran.print("Essai suivant");
      delay(2000);
    }

    // Le compteur principal augmente d'un tour. //
    compteur=compteur+1;
  }

  // Une fois sorti de la boucle principale on observe si le compteur est = ou < à 10. //
  // Si il est < à 10 cela signifie que à un tour l'utilisateur à obtenu 4 blancs soit le bon code, il a gagné. //
  if (compteur<10){
    monEcran.clear();
    monEcran.setCursor(0,0);
    monEcran.print("Well done!");

    // On éteint les leds. //
    for (int i=0;i<16;i=i+1){
      leds[i]=CRGB(0,0,0);
    }
    FastLED.show();

    // Permet de faire la petite animation de fin avec les leds. //
    for (int a=0;a<3;a=a+1){
    for (int i=0;i<16;i=i+1){
      leds[i]=CRGB(100,100,100);
      FastLED.show();
      delay(100);
      leds[i]=CRGB(0,0,0);
    }
    }

  // Sinon l'utilisateur à usé tous ses tours et à donc perdu.
  }
  else {
    
    // On éteint les leds. //
    for (int i=0;i<16;i=i+1){
      leds[i]=CRGB(0,0,0);
    }
    FastLED.show();
    
    monEcran.clear();
    monEcran.setCursor(0,0);
    monEcran.print("Perdu...");
    monEcran.setCursor(0,1);
    monEcran.print("Bon code :");

    // On affiche sur les leds le code qu'il aurait dû trouver.//
    for (int i=0; i<4; i=i+1){
        if (code[i]=="R"){
          leds[2+i]=CRGB(100,0,0);
        }
        else if (code[i]=="V"){
          leds[2+i]=CRGB(0,100,0);
        }
        else if (code[i]=="B"){
          leds[2+i]=CRGB(0,0,100);
        }
        else if (code[i]=="J"){
          leds[2+i]=CRGB(100,75,0);
        }
      }
      FastLED.show();
      delay(4000);
  }

  // On éteint toutes les leds. //
  for (int i=0;i<16;i=i+1){
      leds[i]=CRGB(0,0,0);
    }
    FastLED.show();
    delay(3000);

    // La boucle va donc revenir au début du jeu. //
}
    
