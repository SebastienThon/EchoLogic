// ECHO-LOGIC
// Emet avec ggwave des mots en rapport avec la permaculture ou le permacomputing

#include <ggwave.h>
#include <ShiftRegister74HC595.h>
#define SDI 0
#define SCLK 1
#define LOAD 2
#define DIGITS 2
// create shift register object (number of shift registers, data pin, clock pin, latch pin)
ShiftRegister74HC595 sr(DIGITS, SDI, SCLK, LOAD);

int value, digit1, digit2, digit3, digit4;
uint8_t digits[] = {
  B11000000,  //0
  B11111001,  //1
  B10100100,  //2
  B10110000,  //3
  B10011001,  //4
  B10010010,  //5
  B10000010,  //6
  B11111000,  //7
  B10000000,  //8
  B10010000,  //9
  B11111111   // vide
};

// Pin configuration
const int kPinLed0 = 13;
const int kPinSpeaker = 5;

const int samplesPerFrame = 128;
const int sampleRate = 6000;

// Global GGwave instance
GGWave ggwave;

char txt[64];
#define P(str) (strcpy_P(txt, PSTR(str)), txt)

const char* permaculture_words[] = {
    "-deforestation",
    "-cyberattaque",
    "-erosion des sols",
    "-pollution de l'air",
    "-dechets toxiques",
    "-cybercriminalite",
    "-surpeche",
    "-changement climatique",
    "-surconsommation",
    "-biodiversite en peril",
    "-elevage intensif",
    "-rechauffement global",
    "-degradation des sols",
    "-securite informatique",
    "-epuisement des ressources",
    "-malware",
    "-phishing",
    "-virus informatique",
    "-perte de biodiversite",
    "-effet de serre",
    "-contamination des eaux",
    "-usurpation d'identite",
    "-incendies de foret",
    "-piratage de donnees",
    "-acidification des oceans",
    "-rejets polluants",
    "-intelligence malveillante",
    "-risques de hacking",
    "-perte des habitats",
    "-epuisement des forets",
    "-fraude en ligne",
    "-chocs climatiques",
    "-permafrost en fonte",
    "-surexploitation",
    "-extinction des especes",
    "-dechets nucleaires",
    "-dechets plastiques",
    "-contamination des sols",
    "-attaques par ransomware",
    "-epidemies zoonotiques",
    "-extraction minieres",
    "-rejets toxiques",
    "-pillage de ressources",
    "-dereglement climatique",
    "-effondrement des recifs",
    "-failles de securite",
    "-braconnage",
    "-disparition des abeilles",
    "-exploitation illegale",
    "-fuites de donnees",
    "-trafic de faune",
    "-emissions de CO2",
    "-pollution sonore",
    "-surproduction",
    "-deboisement",
    "-detournement de fonds",
    "-attaques de phishing",
    "-epuisement aquiferes",
    "-pollution lumineuse",
    "-fuite d'informations",
    "-risques ecotoxiques",
    "-biopiraterie",
    "-minage illegal",
    "-erosion des cotes",
    "-extinctions massives",
    "-exploitation enfants",
    "-destruction coraux",
    "-changement oceanique",
    "-espionnage industriel",
    "-rechauffement rapide",
    "-dechets electroniques",
    "-vulnerabilites systeme",
    "-pollution des sols",
    "-surexploitation eaux",
    "-abus de surveillance",
    "-manque de reglement",
    "-exploitation exces",
    "-hausses temperature",
    "-epuisement minerais",
    "-risques nucleaires",
    "-phishing vocal",
    "-contamination aliments",
    "-explosions chimiques",
    "-pollution genetique",
    "-perte de glace",
    "-piratage reseaux",
    "-destruction habitats",
    "-abus miniers",
    "-extinction pollinis.",
    "-demat. non securee",
    "-emission methane",
    "-surexploitation marine",
    "-perte de mangroves",
    "-virus logiciels",
    "-superficial erosion",
    "-epuisement poissons",
    "-extinction plantes",
    "-contamination eau",
    "-surveillance abuse",
    "-risques biologiques",
    "-extraction dangereuse",
    "-cybermenace",
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


// Helper function to output the generated GGWave waveform via a buzzer
void send_text(GGWave& ggwave, uint8_t pin, const char* text, GGWave::TxProtocolId protocolId) {
  Serial.print(F("Sending text: "));
  Serial.println(text);

  ggwave.init(text, protocolId);
  ggwave.encode();

  const auto& protocol = GGWave::Protocols::tx()[protocolId];
  const auto tones = ggwave.txTones();
  const auto duration_ms = protocol.txDuration_ms(ggwave.samplesPerFrame(), ggwave.sampleRateOut());

  for (auto& curTone : tones) {
    const auto freq_hz = (protocol.freqStart + curTone) * ggwave.hzPerSample();
    tone(pin, freq_hz);
    uint8_t numberToPrint[] = { random(0,256), random(0,256) };
    sr.setAll(numberToPrint);
    delay(duration_ms);
  }


  noTone(pin);
  digitalWrite(pin, LOW);
}


void affiche_mot_aleatoire() {
  int randomIndex = random(0, 100);  // Tirer un indice aléatoire

   send_text(ggwave, kPinSpeaker, P(permaculture_words[randomIndex]), GGWAVE_PROTOCOL_MT_FASTEST);
//  send_text(ggwave, kPinSpeaker, P(permaculture_words[randomIndex]), GGWAVE_PROTOCOL_MT_FAST);
}


/*
 * @brief shows number on the Seven Segment Display
 * @param "num" is integer
 * @return returns none
 * Usage to show 18: showNumber(18);
 * Written by Ahmad Shamshiri on Sep 17, 2019. 
 * in Ajax, Ontario, Canada
 * www.Robojax.com 
 */
void showNumber(int num) {
  digit2 = num % 10;
  digit1 = (num / 10) % 10;

  if(digit1 == 0)
  {
    digit1 = 10;
  }
  //Send them to 7 segment displays
  uint8_t numberToPrint[] = { digits[digit1], digits[digit2] };
  sr.setAll(numberToPrint);
}


//Le programme d affichage
void setup() {
  Serial.begin(115200);

  randomSeed(analogRead(3));

  pinMode(kPinLed0, OUTPUT);
  pinMode(kPinSpeaker, OUTPUT);

  tone(kPinSpeaker,262,5000);

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
  //  GGWave::Protocols::tx().only(GGWAVE_PROTOCOL_MT_FAST);

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
  int randNumber = random(30, 99);

  for (int i = randNumber; i >= 0; i--) {
    showNumber(i);
    delay(1000);
  }

  affiche_mot_aleatoire();  // Affiche un mot aléatoire lié à la permaculture

  // Eteint l'affichage
  uint8_t numberToPrint[] = { digits[10], digits[10] };
  sr.setAll(numberToPrint);

  delay(30000);  // Attente de 30 secondes avant d'afficher un nouveau mot
}
