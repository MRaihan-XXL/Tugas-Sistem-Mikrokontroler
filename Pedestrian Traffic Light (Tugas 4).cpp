#define HIJAU_KEND 10
#define KUNING_KEND 9
#define MERAH_KEND 8
#define HIJAU_PED1 7
#define MERAH_PED1 6
#define HIJAU_PED2 5
#define MERAH_PED2 4
#define TOMBOL 2

volatile bool tombolTekan = false;
unsigned long waktuSebelumnya = 0;
int tahap = 0;  // 0=normal, 1=pedestrian jalan, 2=kuning

void tekan() {
  tombolTekan = true;
}

void setup() {
  pinMode(HIJAU_KEND, OUTPUT);
  pinMode(KUNING_KEND, OUTPUT);
  pinMode(MERAH_KEND, OUTPUT);
  pinMode(HIJAU_PED1, OUTPUT);
  pinMode(MERAH_PED1, OUTPUT);
  pinMode(HIJAU_PED2, OUTPUT);
  pinMode(MERAH_PED2, OUTPUT);
  pinMode(TOMBOL, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(TOMBOL), tekan, FALLING);

  // Kondisi awal: kendaraan hijau, pedestrian merah
  digitalWrite(HIJAU_KEND, HIGH);
  digitalWrite(KUNING_KEND, LOW);
  digitalWrite(MERAH_KEND, LOW);
  digitalWrite(HIJAU_PED1, LOW);
  digitalWrite(MERAH_PED1, HIGH);
  digitalWrite(HIJAU_PED2, LOW);
  digitalWrite(MERAH_PED2, HIGH);
}

void loop() {
  if (tahap == 0) { // NORMAL
    if (tombolTekan) {
      tombolTekan = false;
      tahap = 1;
      
      digitalWrite(HIJAU_KEND, LOW);
      digitalWrite(MERAH_KEND, HIGH);
      digitalWrite(MERAH_PED1, LOW);
      digitalWrite(HIJAU_PED1, HIGH);
      digitalWrite(MERAH_PED2, LOW);
      digitalWrite(HIJAU_PED2, HIGH);
      
      waktuSebelumnya = millis();
    }
  }
  else if (tahap == 1) { // PEDESTRIAN JALAN
    if (millis() - waktuSebelumnya >= 5000) {
      digitalWrite(HIJAU_PED1, LOW);
      digitalWrite(HIJAU_PED2, LOW);
      digitalWrite(MERAH_PED1, HIGH);
      digitalWrite(MERAH_PED2, HIGH);
      
      digitalWrite(MERAH_KEND, LOW);
      digitalWrite(KUNING_KEND, HIGH);
      
      waktuSebelumnya = millis();
      tahap = 2;
    }
  }
  else if (tahap == 2) { // KUNING
    if (millis() - waktuSebelumnya >= 2000) {
      digitalWrite(KUNING_KEND, LOW);
      digitalWrite(HIJAU_KEND, HIGH);
      tahap = 0;
    }
  }
}
