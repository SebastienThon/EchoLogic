// ECHO-LOGIC
// Emet avec ggwave des mots en rapport avec la permaculture et le permacomputing

#include <ggwave.h>

// Pin configuration
const int kPinLed0 = 13;
const int kPinSpeaker = 5;

const int samplesPerFrame = 128;
const int sampleRate = 6000;

// Global GGwave instance
GGWave ggwave;

char txt[64];
#define P(str) (strcpy_P(txt, PSTR(str)), txt)

//Cablage du module (gnd et +V) utilise 3 pins
int Max7219_pinCLK = 2;
int Max7219_pinCS = 1;
int Max7219_pinDIN = 0;

const char* permaculture_words[] = {
  "agriculture durable",
  "biodiversite",
  "compostage",
  "design permaculturel",
  "eau de pluie",
  "foret comestible",
  "agroforesterie",
  "ecoconstruction",
  "economie circulaire",
  "jardinage naturel",
  "compost",
  "culture en butte",
  "sol fertile",
  "poulailler",
  "zerodechet",
  "vermicompostage",
  "permaculture",
  "biotope",
  "ecosysteme",
  "semences paysannes",
  "pollinisation",
  "abondance",
  "autonomie",
  "recyclage",
  "elevage extensif",
  "culture associee",
  "biodynamie",
  "paillage",
  "engrais vert",
  "toilette seche",
  "fleurs comestibles",
  "energie renouvelable",
  "auto construction",
  "maraichage",
  "culture perenne",
  "ecosysteme",
  "zone tampon",
  "rotation des cultures",
  "zone humide",
  "jardin foret",
  "foresterie",
  "ecoquartier",
  "terre crue",
  "toit vegetalise",
  "sol vivant",
  "bocage",
  "haies",
  "biomimetisme",
  "synergie",
  "piscine ecologique",
  "cloture vegetale",
  "bois mort",
  "energies douces",
  "eau de source",
  "eco conception",
  "etang naturel",
  "poulailler mobile",
  "composteur",
  "recolte d eau",
  "semences libres",
  "autoproduction",
  "circuit court",
  "economies d energie",
  "abri naturel",
  "zone comestible",
  "hydroponie",
  "elevage respectueux",
  "circulation d energie",
  "couverture du sol",
  "climat tampon",
  "zone fraicheur",
  "eco geste",
  "refuge animal",
  "abri vegetal",
  "bioclimatisme",
  "terre vegetale",
  "tourbiere",
  "jardin ressource",
  "abri insectes",
  "biotope aquatique",
  "haies melliferes",
  "moulin a vent",
  "energie solaire",
  "alimentation durable",
  "zones de capture",
  "conservation du sol",
  "eco bati",
  "flore locale",
  "faune aquatique",
  "jardin medicinal",
  "ombrage",
  "taille douce",
  "elevage en pature",
  "engrais naturels",
  "faune utilitaire",
  "symbiose",
  "biotope protege",
  "accueil faune",
  "gestion durable",
  "gestion eau",
  "potager partage",
  "culture fruitiere",
  "+low tech",
  "+open source",
  "+reduction empreinte",
  "+code efficace",
  "+sobriete numerique",
  "+minimalisme",
  "+eco conception",
  "+energie durable",
  "+maintenance durable",
  "+usage optimisé",
  "+zero data waste",
  "+refroidissement passif",
  "+stockage reduit",
  "+recyclage materiel",
  "+durabilite informatique",
  "+self hosting",
  "+serveurs verts",
  "+architecture simple",
  "+eco hardware",
  "+open data",
  "+faible consommation",
  "+basse puissance",
  "+matériel open source",
  "+partage de ressources",
  "+logiciel low tech",
  "+cloud sobre",
  "+économie circulaire",
  "+infrastructure verte",
  "+alternatives au cloud",
  "+ordinateur open source",
  "+autonomie numerique",
  "+design sobre",
  "+optimisation code",
  "+code asynchrone",
  "+modularité",
  "+applications legeres",
  "+service minimal",
  "+stockage frugal",
  "+processeurs basse conso",
  "+memoire frugale",
  "+infrastructures locales",
  "+reseau local",
  "+fabrication locale",
  "+reparation facile",
  "+materiel durable",
  "+consommation reduite",
  "+logiciel modulaire",
  "+reutilisation materielle",
  "+design pour reparation",
  "+low power servers",
  "+adaptation energie",
  "+serveurs locaux",
  "+partage hardware",
  "+code vert",
  "+data light",
  "+data cleaning",
  "+utilisation passive",
  "+solutions peer to peer",
  "+eco web",
  "+efficacite energetique",
  "+monitoring energetique",
  "+collaboration locale",
  "+formats ouverts",
  "+usages responsables",
  "+efficience energetique",
  "+basses frequences",
  "+impact carbone reduit",
  "+transparence écologique",
  "+materiaux eco friendly",
  "+design minimal",
  "+contenu lean",
  "+optimisation hardware",
  "+efficacite software",
  "+approche permacoding",
  "+sobriete energetique",
  "+cloud personnel",
  "+basse resolution",
  "+design ecologique",
  "-deforestation",
    "-cyberattack",
    "-soil erosion",
    "-air pollution",
    "-toxic waste",
    "-cybercrime",
    "-overfishing",
    "-climate change",
    "-overconsumption",
    "-biodiversity at risk",
    "-intensive livestock",
    "-global warming",
    "-soil degradation",
    "-information security",
    "-resource depletion",
    "-malware",
    "-phishing",
    "-computer virus",
    "-biodiversity loss",
    "-greenhouse effect",
    "-water contamination",
    "-identity theft",
    "-wildfires",
    "-data breach",
    "-ocean acidification",
    "-pollutant discharges",
    "-malicious AI",
    "-hacking risks",
    "-habitat loss",
    "-forest depletion",
    "-online fraud",
    "-climate shocks",
    "-thawing permafrost",
    "-overexploitation",
    "-species extinction",
    "-nuclear waste",
    "-plastic waste",
    "-soil contamination",
    "-ransomware attacks",
    "-zoonotic outbreaks",
    "-mining extraction",
    "-toxic discharges",
    "-resource plundering",
    "-climate disruption",
    "-reef collapse",
    "-security vulnerabilities",
    "-poaching",
    "-bee decline",
    "-illegal exploitation",
    "-data leaks",
    "-wildlife trafficking",
    "-CO2 emissions",
    "-noise pollution",
    "-overproduction",
    "-logging",
    "-embezzlement",
    "-phishing attacks",
    "-aquifer depletion",
    "-light pollution",
    "-information leakage",
    "-ecotoxicity risks",
    "-biopiracy",
    "-illegal mining",
    "-coastal erosion",
    "-mass extinctions",
    "-child exploitation",
    "-coral destruction",
    "-ocean change",
    "-industrial espionage",
    "-rapid warming",
    "-electronic waste",
    "-system vulnerabilities",
    "-soil pollution",
    "-water overexploitation",
    "-surveillance abuse",
    "-lack of regulation",
    "-excessive exploitation",
    "-rising temperatures",
    "-mineral depletion",
    "-nuclear risks",
    "-voice phishing",
    "-food contamination",
    "-chemical explosions",
    "-genetic pollution",
    "-ice loss",
    "-network hacking",
    "-habitat destruction",
    "-mining abuses",
    "-pollinator extinction",
    "-insecure digitization",
    "-methane emissions",
    "-marine overexploitation",
    "-mangrove loss",
    "-software viruses",
    "-surface erosion",
    "-fish depletion",
    "-plant extinction",
    "-water pollution",
    "-biological risks",
    "-hazardous extraction",
    "-cyberthreat"
};

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
    //    Serial.println(freq_hz);
    //    affiche_horloge(((int)(freq_hz/100))%64, ((int)freq_hz)%64);

    row = 1 + random(6);
    col = 1 + random(6);
    affiche_led(row, col);
    delay(duration_ms);
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


void affiche_chaine(const char* message) {
  int index;

  // Boucle sur chaque caractère de la chaîne
  for (int k = 0; message[k] != '\0'; k++) {
    char c = message[k];

    // Vérifie si le caractère est un chiffre (0-9)
    if (c >= '0' && c <= '9') {
      index = c - '0';  // Indice dans le tableau disp1 pour les chiffres
    }
    // Vérifie si le caractère est une lettre majuscule (A-Z)
    else if (c >= 'A' && c <= 'Z') {
      index = c - 'A' + 10;  // Les lettres commencent à l'indice 10 dans disp1
    }
    // Si le caractère n'est pas pris en charge, le remplace par un espace (vide)
    else {
      index = -1;  // Affiche un vide pour les caractères non supportés
    }

    // Si l'index est valide, affiche le caractère correspondant
    if (index != -1) {
      // Affiche le caractère en utilisant Write_Max7219
      for (int i = 0; i < 8; i++) {
        Write_Max7219(i + 1, disp1[index][i]);
      }
    } else {
      // Affiche un caractère vide (toutes les LED éteintes) si non supporté
      for (int i = 0; i < 8; i++) {
        Write_Max7219(i + 1, 0x00);  // 0x00 signifie toutes les LED éteintes
      }
    }

    // Attendre pour que l'utilisateur puisse lire le caractère
    delay(300);  // Délai de 500 ms entre chaque caractère
  }
}

void affiche_mot_aleatoire() {
  int randomIndex = random(0, 179);  // Tirer un indice aléatoire
                                     //   affiche_chaine(permaculture_words[randomIndex]);  // Afficher le mot correspondant

  send_text(ggwave, kPinSpeaker, P(permaculture_words[randomIndex]), GGWAVE_PROTOCOL_MT_FASTEST);
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
  pinMode(Max7219_pinCLK, OUTPUT);
  pinMode(Max7219_pinCS, OUTPUT);
  pinMode(Max7219_pinDIN, OUTPUT);
  delay(50);  //Initialiser
  Init_MAX7219();

  pinMode(kPinLed0, OUTPUT);
  pinMode(kPinSpeaker, OUTPUT);

  tone(kPinSpeaker,440,5000);

  // Initialize "ggwave"
  {
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
  }
}


void loop() {

  for (unsigned char i = 0; i <= randNumber; i++) {
    affiche_horloge(i, randNumber);
    delay(1000);
  }

  affiche_mot_aleatoire();  // Affiche un mot aléatoire lié à la permaculture

  int randDuration = (int)(5+random(20));

  for (int i = 0; i < randDuration; i++) {

    affiche_led(randNumber / 8, randNumber % 8);
    delay(1000);
    efface_leds();
    delay(1000);
  }
}
