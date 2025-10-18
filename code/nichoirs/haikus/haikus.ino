// Chaque mot d'un haïku est séparé par une durée aléatoire entre 3 et 10 sec.
// Arrivé au point, la durée qui sépare du haïku suivant est aléatoire entre 30 et 64 secondes.
// A chaque lecture d'un mot, le moteur se met en marche pour faire tourner le disque vinyle.


// Exemple de code Module Max7219 reseau de 8x8 LEDS
// http://tiptopboards.free.fr/arduino_forum/viewtopic.php?f=2&t=6#
// Revision 19 08 2013

#include <ggwave.h>


#define in1 4
#define in2 8
#define in3 9
#define in4 10

int dl = 10; // temps entre les pas, minimum 10 ms

// Pin configuration
const int kPinLed0    = 13;
const int kPinSpeaker = 5;


const int samplesPerFrame = 128;
const int sampleRate      = 6000;

// Global GGwave instance
GGWave ggwave;

char txt[64];
#define P(str) (strcpy_P(txt, PSTR(str)), txt)


//Cablage du module (gnd et +V) utilise 3 pins
int Max7219_pinCLK = 2;
int Max7219_pinCS = 1;
int Max7219_pinDIN = 0;


const char* haikus[] = {
  "*Brume", "*matinale", "*sur", "*le", "*lac", "*silencieux.",
  "*Papillons", "*dansent", "*gracieusement", "*au", "*vent", "*d'ete.",
  "*Sous", "*les", "*cerisiers", "*les", "*petales", "*tombent", "*doucement.",
  "*Riviere", "*murmurante", "*parmi", "*les", "*pierres", "*anciennes.",
  "*Feuilles", "*d'automne", "*tourbillonnent", "*dans", "*le", "*vent", "*frais.",
  "*Soleil", "*couchant", "*embrase", "*l'horizon", "*dore.",
  "*Chants", "*d'oiseaux", "*reveillent", "*la", "*foret", "*endormie.",
  "*Lune", "*eclaire", "*doucement", "*la", "*clairiere", "*paisible.",
  "*Pluie", "*douce", "*caresse", "*les", "*fleurs", "*epanouies.",
  "*Etoiles", "*scintillent", "*dans", "*le", "*ciel", "*nocturne.",
  "*Rosee", "*du", "*matin", "*brille", "*sur", "*les", "*brins", "*d'herbe.",
  "*Ecureuil", "*frele", "*bondit", "*parmi", "*les", "*feuilles", "*mortes.",
  "*Montagne", "*lointaine", "*se", "*decoupe", "*dans", "*le", "*ciel", "*bleu.",
  "*Le", "*vent", "*chuchote", "*dans", "*les", "*pins", "*centenaires.",
  "*Mer", "*d'argent", "*sous", "*le", "*clair", "*de", "*lune", "*paisible.",
  "*Ruisseau", "*chantant", "*glisse", "*sur", "*les", "*cailloux", "*polis.",
  "*Ombres", "*dans", "*la", "*foret", "*dansent", "*avec", "*la", "*lumiere.",
  "*Hibou", "*solitaire", "*chante", "*a", "*la", "*nuit", "*naissante.",
  "*Nenuphars", "*flottent", "*calmes", "*sur", "*l'etang", "*miroitant.",
  "*Horizon", "*flou", "*au", "*crepuscule", "*s'eteint", "*doucement.",
  "*Le", "*givre", "*d'hiver", "*couvre", "*les", "*champs", "*endormis.",
  "*Odeurs", "*de", "*pins", "*dans", "*la", "*chaleur", "*de", "*l'ete.",
  "*Grillons", "*chantent", "*doucement", "*dans", "*la", "*nuit", "*chaude.",
  "*Rivage", "*calme", "*ou", "*les", "*vagues", "*se", "*brisent", "*doucement.",
  "*Arbre", "*ancien", "*ecoute", "*le", "*temps", "*qui", "*passe", "*lentement.",
  "*Papillon", "*blanc", "*vole", "*entre", "*les", "*fleurs", "*sauvages.",
  "*Brouillard", "*d'automne", "*cache", "*les", "*collines", "*lointaines.",
  "*Neige", "*eclatante", "*couvre", "*les", "*sommets", "*paisibles.",
  "*Lac", "*gele", "*reflete", "*la", "*pale", "*lumiere", "*du", "*jour.",
  "*Les", "*bruits", "*de", "*la", "*riviere", "*chantent", "*la", "*nature.",
  "*Chene", "*majestueux", "*s'etend", "*vers", "*le", "*ciel", "*bleu.",
  "*Cerf", "*dans", "*la", "*clairiere", "*observe", "*en", "*silence.",
  "*Rayons", "*du", "*soleil", "*traversent", "*la", "*foret", "*sombre.",
   "*Serveur", "*frugal", "*ronronne", "*avec", "*la", "*pluie.",
  "*Panneaux", "*solaires", "*tièdes", "*boivent", "*la", "*lumière.",
  "*Vent", "*dans", "*les", "*ailettes", "*refroidit", "*le", "*cœur.",
  "*Code", "*comme", "*lichens", "*s'accroche", "*au", "*rocher.",
  "*Graines", "*de", "*données", "*reposent", "*dans", "*la", "*terre.",
  "*Réseau", "*maillé", "*chuchote", "*entre", "*les", "*chênes.",
  "*Vieilles", "*cartes", "*mères", "*chauffent", "*les", "*fourmis.",
  "*Écran", "*e-ink", "*pâle", "*boit", "*l'aube", "*froide.",
  "*Courant", "*alternatif", "*imite", "*le", "*clapotis.",
  "*Algorithmes", "*lents", "*suivent", "*les", "*saisons.",
  "*CRON", "*de", "*la", "*rosée", "*réveille", "*les", "*nœuds.",
  "*Soudure", "*parfumée", "*résine", "*et", "*pin", "*murmurent.",
  "*Ventilateurs", "*éteints", "*respirent", "*la", "*nuit.",
  "*Serveurs", "*au", "*grenier", "*écoutent", "*les", "*pluies.",
  "*Cycles", "*du", "*compost", "*bouclent", "*nos", "*boucles.",
  "*Git", "*branche", "*et", "*branche", "*dans", "*le", "*verger.",
  "*Souris", "*sans", "*pile", "*court", "*sur", "*l'écorce.",
  "*Forêt", "*de", "*capteurs", "*veille", "*sans", "*parler.",
  "*Ondes", "*courtes", "*portent", "*le", "*chant", "*des", "*grues.",
  "*Batterie", "*au", "*sel", "*rêve", "*près", "*des", "*algues.",
  "*Turbines", "*et", "*bernaches", "*se", "*partagent", "*le", "*ciel.",
  "*Clavier", "*de", "*bois", "*claque", "*dans", "*la", "*cabane.",
  "*Programme", "*diurne", "*s'endort", "*au", "*coucher.",
  "*Lent", "*processeur", "*compte", "*les", "*étoiles.",
  "*Câbles", "*enterrés", "*caressés", "*par", "*les", "*taupes.",
  "*Soleil", "*d'hiver", "*compile", "*les", "*ombres.",
  "*Radio", "*amateur", "*salue", "*les", "*sommets.",
  "*Mémoire", "*flash", "*dort", "*dans", "*une", "*coquille.",
  "*Script", "*à", "*manivelle", "*relance", "*la", "*brise.",
  "*Recyclage", "*profond", "*fait", "*naître", "*des", "*oiseaux.",
  "*Nuit", "*hors", "*ligne", "*respire", "*avec", "*la", "*forêt.",
  "*Lune", "*réfléchie", "*sur", "*le", "*panneau.",
  "*Colibri", "*teste", "*le", "*débogueur", "*des", "*fleurs.",
  "*Brise", "*compile", "*lentement", "*les", "*pins.",
  "*Serveur", "*au", "*rameau", "*héberge", "*des", "*mousses.",
  "*Capsule", "*LoRa", "*réveille", "*le", "*pré.",
  "*Pluie", "*versionnée", "*merge", "*les", "*ruisseaux.",
  "*Tortue", "*routeur", "*porte", "*son", "*réseau.",
  "*Chamane", "*du", "*cloud", "*écoute", "*les", "*cailloux.",
  "*Gravier", "*et", "*bits", "*grincent", "*sous", "*le", "*pas.",
  "*Houblon", "*grimpe", "*le", "*mât", "*antenne.",
  "*Énergie", "*sobre", "*tisse", "*nos", "*outils.",
  "*Silence", "*cache", "*un", "*daemon", "*heureux.",
  "*Neige", "*sur", "*les", "*claviers", "*éteints.",
  "*Vieux", "*ThinkPad", "*tiède", "*à", "*la", "*bergerie.",
  "*Capteurs", "*ouverts", "*partagent", "*la", "*rosée.",
  "*Biosphère", "*et", "*BIOS", "*rient", "*ensemble.",
  "*Compost", "*de", "*codes", "*nourrit", "*demain.",
  "*Rivière", "*hors", "*cache", "*flux", "*permanent.",
  "*Graines", "*hashées", "*attendent", "*le", "*dégel.",
  "*Matin", "*sans", "*wifi", "*plus", "*clair.",
  "*Soleil", "*de", "*mai", "*recharge", "*les", "*abeilles.",
  "*Vent", "*pair", "*à", "*pair", "*dans", "*les", "*épis.",
  "*Porte", "*série", "*ouvre", "*le", "*ciel.",
  "*Sève", "*pulse", "*comme", "*une", "*horloge.",
  "*Écureuil", "*hacker", "*vole", "*des", "*graines.",
  "*Étoiles", "*faibles", "*pilotent", "*le", "*voilier.",
  "*Lacs", "*en", "*RAID", "*miroirs", "*dupliqués.",
  "*Montagne", "*aircooling", "*apaise", "*les", "*circuits.",
  "*Verger", "*low-tech", "*compile", "*du", "*cidre.",
  "*Chouette", "*nocturne", "*ping", "*la", "*vallée.",
  "*Cigales", "*clock", "*vibrent", "*au", "*crépuscule.",
  "*Racines", "*maillées", "*réparent", "*la", "*panne.",
  "*Plumes", "*en", "*ASCII", "*tracent", "*le", "*vent.",
  "*Ruche", "*ouverte", "*partage", "*les", "*trames.",
  "*Brouillard", "*diffuse", "*la", "*bande", "*passante.",
  "*Aube", "*sobre", "*efface", "*les", "*logs."
};

int haiku_index = 0;
int pas_moteur = 0;

unsigned char randNumber = 30;


//Définition des pixels a eclairer
//0-9 puis A-Z soit 10+26 = 36 caractères

unsigned char disp1[38][8] = {
  { 0x3C, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x3C },  //0
  { 0x10, 0x30, 0x50, 0x10, 0x10, 0x10, 0x10, 0x10 },  //1
  { 0x7E, 0x2, 0x2, 0x7E, 0x40, 0x40, 0x40, 0x7E },    //2
  { 0x3E, 0x2, 0x2, 0x3E, 0x2, 0x2, 0x3E, 0x0 },       //3
  { 0x8, 0x18, 0x28, 0x48, 0xFE, 0x8, 0x8, 0x8 },      //4
  { 0x3C, 0x20, 0x20, 0x3C, 0x4, 0x4, 0x3C, 0x0 },     //5
  { 0x3C, 0x20, 0x20, 0x3C, 0x24, 0x24, 0x3C, 0x0 },   //6
  { 0x3E, 0x22, 0x4, 0x8, 0x8, 0x8, 0x8, 0x8 },        //7
  { 0x0, 0x3E, 0x22, 0x22, 0x3E, 0x22, 0x22, 0x3E },   //8
  { 0x3E, 0x22, 0x22, 0x3E, 0x2, 0x2, 0x2, 0x3E },     //9
  { 0x8, 0x14, 0x22, 0x3E, 0x22, 0x22, 0x22, 0x22 },   //A
  { 0x3C, 0x22, 0x22, 0x3E, 0x22, 0x22, 0x3C, 0x0 },   //B
  { 0x3C, 0x40, 0x40, 0x40, 0x40, 0x40, 0x3C, 0x0 },   //C
  { 0x7C, 0x42, 0x42, 0x42, 0x42, 0x42, 0x7C, 0x0 },   //D
  { 0x7C, 0x40, 0x40, 0x7C, 0x40, 0x40, 0x40, 0x7C },  //E
  { 0x7C, 0x40, 0x40, 0x7C, 0x40, 0x40, 0x40, 0x40 },  //F
  { 0x3C, 0x40, 0x40, 0x40, 0x40, 0x44, 0x44, 0x3C },  //G
  { 0x44, 0x44, 0x44, 0x7C, 0x44, 0x44, 0x44, 0x44 },  //H
  { 0x7C, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x7C },  //I
  { 0x3C, 0x8, 0x8, 0x8, 0x8, 0x8, 0x48, 0x30 },       //J
  { 0x0, 0x24, 0x28, 0x30, 0x20, 0x30, 0x28, 0x24 },   //K
  { 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x7C },  //L
  { 0x81, 0xC3, 0xA5, 0x99, 0x81, 0x81, 0x81, 0x81 },  //M
  { 0x0, 0x42, 0x62, 0x52, 0x4A, 0x46, 0x42, 0x0 },    //N
  { 0x3C, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x3C },  //O
  { 0x3C, 0x22, 0x22, 0x22, 0x3C, 0x20, 0x20, 0x20 },  //P
  { 0x1C, 0x22, 0x22, 0x22, 0x22, 0x26, 0x22, 0x1D },  //Q
  { 0x3C, 0x22, 0x22, 0x22, 0x3C, 0x24, 0x22, 0x21 },  //R
  { 0x0, 0x1E, 0x20, 0x20, 0x3E, 0x2, 0x2, 0x3C },     //S
  { 0x0, 0x3E, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8 },         //T
  { 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x22, 0x1C },  //U
  { 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x24, 0x18 },  //V
  { 0x0, 0x49, 0x49, 0x49, 0x49, 0x2A, 0x1C, 0x0 },    //W
  { 0x0, 0x41, 0x22, 0x14, 0x8, 0x14, 0x22, 0x41 },    //X
  { 0x41, 0x22, 0x14, 0x8, 0x8, 0x8, 0x8, 0x8 },       //Y
  { 0x0, 0x7F, 0x2, 0x4, 0x8, 0x10, 0x20, 0x7F },      //Z
};


void avance_moteur()
{
  if( pas_moteur == 0)
  {
  digitalWrite(in1, HIGH); 
    digitalWrite(in2, LOW); 
    digitalWrite(in3, LOW); 
    digitalWrite(in4, HIGH);
  }
  else if ( pas_moteur == 1)
  {
    digitalWrite(in1, HIGH); 
    digitalWrite(in2, HIGH); 
    digitalWrite(in3, LOW); 
    digitalWrite(in4, LOW);
  }
  else if ( pas_moteur == 2)
  {
    digitalWrite(in1, LOW); 
    digitalWrite(in2, HIGH); 
    digitalWrite(in3, HIGH); 
    digitalWrite(in4, LOW);
  }
  else if ( pas_moteur == 3)
  {
    digitalWrite(in1, LOW); 
    digitalWrite(in2, LOW); 
    digitalWrite(in3, HIGH); 
    digitalWrite(in4, HIGH);
  }

  pas_moteur = pas_moteur + 1;
  if( pas_moteur >= 4)
  {
    pas_moteur = 0;
  }
}

// Helper function to output the generated GGWave waveform via a buzzer
void send_text(GGWave& ggwave, uint8_t pin, const char* text, GGWave::TxProtocolId protocolId) {
  Serial.print(F("Sending text: "));
  Serial.println(text);

  ggwave.init(text, protocolId);
  ggwave.encode();

  const auto& protocol = GGWave::Protocols::tx()[protocolId];
  const auto tones = ggwave.txTones();
  const auto duration_ms = protocol.txDuration_ms(ggwave.samplesPerFrame(), ggwave.sampleRateOut());

  int row, col;
  for (auto& curTone : tones) {
    const auto freq_hz = (protocol.freqStart + curTone) * ggwave.hzPerSample();
    tone(pin, freq_hz);


    row = 1 + random(6);
    col = 1 + random(6);
    affiche_led(row, col);
    delay(duration_ms);
/*
    for( int i=0; i<4; i++ )
    {
      avance_moteur();
      delay(duration_ms/4);
    }
    */
  }

  randNumber = row * 8 + col;

  noTone(pin);
  digitalWrite(pin, LOW);
}



//Ecriture d'un caractere 8x8
void Write_Max7219_byte(unsigned char DATA) {
  unsigned char i;
  digitalWrite(Max7219_pinCS, LOW);
  for (i = 8; i >= 1; i--) {
    digitalWrite(Max7219_pinCLK, LOW);
    digitalWrite(Max7219_pinDIN, DATA & 0x80);  // Extracting a bit data
    DATA = DATA << 1;
    digitalWrite(Max7219_pinCLK, HIGH);
  }
}

//Ecriture elementaire d une seule rangee
void Write_Max7219(unsigned char address, unsigned char dat) {
  digitalWrite(Max7219_pinCS, LOW);
  Write_Max7219_byte(address);  //address，code of LED
  Write_Max7219_byte(dat);      //data，figure on LED
  digitalWrite(Max7219_pinCS, HIGH);
}


void affiche_led(unsigned char row, unsigned char col) {
  // Conversion des colonnes en un masque de bits pour chaque ligne
  unsigned char row_data[8] = { 0 };  // Tableaux pour stocker les données des lignes

  // Allume la LED correspondante pour led1
  row_data[row] |= (1 << (7 - col));  // 7 - col1 pour correspondre au format MAX7219

  // Envoie les données à la matrice LED via MAX7219
  for (unsigned char i = 0; i < 8; i++) {
    Write_Max7219(i + 1, row_data[i]);  // i+1 car les lignes sont numérotées de 1 à 8 dans le MAX7219
  }
}



void efface_leds() {
  // Conversion des colonnes en un masque de bits pour chaque ligne
  unsigned char row_data[8] = { 0 };  // Tableaux pour stocker les données des lignes

  // Envoie les données à la matrice LED via MAX7219
  for (unsigned char i = 0; i < 8; i++) {
    Write_Max7219(i + 1, row_data[i]);  // i+1 car les lignes sont numérotées de 1 à 8 dans le MAX7219
  }
}


void affiche_horloge(unsigned char led1, unsigned char led2) {
  // Calcul des coordonnées pour led1
  unsigned char row1 = led1 / 8;
  unsigned char col1 = led1 % 8;

  // Calcul des coordonnées pour led2
  unsigned char row2 = led2 / 8;
  unsigned char col2 = led2 % 8;

  // Conversion des colonnes en un masque de bits pour chaque ligne
  unsigned char row_data[8] = { 0 };  // Tableaux pour stocker les données des lignes

  // Allume la LED correspondante pour led1
  row_data[row1] |= (1 << (7 - col1));  // 7 - col1 pour correspondre au format MAX7219

  // Allume la LED correspondante pour led2
  row_data[row2] |= (1 << (7 - col2));

  // Envoie les données à la matrice LED via MAX7219
  for (unsigned char i = 0; i < 8; i++) {
    Write_Max7219(i + 1, row_data[i]);  // i+1 car les lignes sont numérotées de 1 à 8 dans le MAX7219
  }
}


void affiche_mot_aleatoire() {                                   
  send_text(ggwave, kPinSpeaker, P(haikus[haiku_index]), GGWAVE_PROTOCOL_MT_FASTEST);
  //  send_text(ggwave, kPinSpeaker, P(permaculture_words[randomIndex]), GGWAVE_PROTOCOL_MT_FAST);
}


//Initialisation du module Max 7219
void Init_MAX7219(void) {
  Write_Max7219(0x09, 0x00);  //decoding ：BCD
  Write_Max7219(0x0a, 0x03);  //brightness
  Write_Max7219(0x0b, 0x07);  //scanlimit；8 LEDs
  Write_Max7219(0x0c, 0x01);  //power-down mode：0，normal mode：1
  Write_Max7219(0x0f, 0x00);  //test display：1；EOT，display：0
}


//Le programme d affichage
void setup() {
  Serial.begin(115200);
  randomSeed(analogRead(3));

  //Pins a utiliser
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  pinMode(Max7219_pinCLK, OUTPUT);
  pinMode(Max7219_pinCS, OUTPUT);
  pinMode(Max7219_pinDIN, OUTPUT);
  delay(50);  //Initialiser
  Init_MAX7219();

  pinMode(kPinLed0, OUTPUT);
  pinMode(kPinSpeaker, OUTPUT);

  tone(kPinSpeaker,330,5000);

  // Initialize "ggwave"
 // {
    Serial.println(F("Trying to initialize the ggwave instance"));

    ggwave.setLogFile(nullptr);

    auto p = GGWave::getDefaultParameters();

    // Adjust the "ggwave" parameters to your needs.
    // Make sure that the "payloadLength" parameter matches the one used on the transmitting side.
    p.payloadLength = 27;
    p.sampleRateInp = sampleRate;
    p.sampleRateOut = sampleRate;
    p.sampleRate = sampleRate;
    p.samplesPerFrame = samplesPerFrame;
    p.sampleFormatInp = GGWAVE_SAMPLE_FORMAT_I16;
    p.sampleFormatOut = GGWAVE_SAMPLE_FORMAT_U8;
    p.operatingMode = GGWAVE_OPERATING_MODE_TX | GGWAVE_OPERATING_MODE_TX_ONLY_TONES | GGWAVE_OPERATING_MODE_USE_DSS;

    // Protocols to use for TX
    GGWave::Protocols::tx().only(GGWAVE_PROTOCOL_MT_FASTEST);
    //    GGWave::Protocols::tx().only(GGWAVE_PROTOCOL_MT_FAST);

    // Sometimes, the speaker might not be able to produce frequencies in the Mono-tone range of 1-2 kHz.
    // In such cases, you can shift the base frequency up by changing the "freqStart" parameter of the protocol.
    // Make sure that in the receiver (for example, the "Waver" app) the base frequency is shifted by the same amount.
    // Here we shift the frequency by +48 bins. Each bin is equal to 48000/1024 = 46.875 Hz.
    // So the base frequency is shifted by +2250 Hz.
    //     GGWave::Protocols::tx()[GGWAVE_PROTOCOL_MT_FASTEST].freqStart += 48;
    //     GGWave::Protocols::tx()[GGWAVE_PROTOCOL_MT_FAST].freqStart += 48;

    // Initialize the ggwave instance and print the memory usage
    ggwave.prepare(p);
    Serial.println(ggwave.heapSize());

    Serial.println(F("Instance initialized successfully!"));
//  }
}


void loop() {
 

  for (unsigned char i = 0; i <= randNumber; i++) {
    affiche_horloge(i, randNumber);
    delay(1000);
  }


  affiche_mot_aleatoire();  // Affiche un mot aléatoire lié à la permaculture

  const char * chaine = haikus[haiku_index];
  if (strlen(chaine) > 0 && chaine[strlen(chaine) - 1] == '.')
  {
    for (int i = 0; i < 15; i++) {

      affiche_led(randNumber / 8, randNumber % 8);
      delay(1000);
      efface_leds();
      delay(1000);
    }
  }

  haiku_index = haiku_index + 1;
  if( haiku_index >= 221 )
  {
    haiku_index = 0;
  }

}
