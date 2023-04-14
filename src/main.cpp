#include <Arduino.h>

#define phase1 2
#define phase2 3
#define phase3 4
#define seqFault 5 //Pin will be HIGH only if Phase Sequence is wrong "RYB"
unsigned long t1_start, t1_end, t2_start, t2_end, t3_start, t3_end;

void Measure () {
  while (!digitalRead(phase1)) {
    t1_start = micros();
  }
  while (!digitalRead(phase2)) {
    t1_end = micros();
  }
  /*
  /////////////////////////////////////////////
  while (!digitalRead(phase3)) {
    t2_end = micros();
  }
  ////////Uncomment for using all 3 phases/////
  /////////////////////////////////////////////
  */
}

void setup() {
  pinMode(phase1, INPUT);
  pinMode(phase2, INPUT);
  //Uncomment for using all 3 phases
  //pinMode(phase3, INPUT);
  pinMode(seqFault, OUTPUT);
  Serial.begin(9600);
  Serial.println("Loading..");
}


int calculatioins(int g) {
  unsigned int k = 0;
  //To complete number of counts
  g=g+1;
  //To convert  into seconds
  float pf = (float)g / 1000000;
  //To convert seconds into degrees
  pf = pf * 50 * 360; //here frequency = 50hz
  k = pf;
  return k;
}

void loop() {
  Measure();
  int phaseABangle = calculatioins(t1_end - t1_start);
  ////Uncomment for using all 3 phases
 // int phaseACangle = calculatioins(t2_end - t2_start);

  ///////////////////////////////////////////////////Uncomment for using all 3 phases
  Serial.print("0,"); Serial.println(phaseABangle);// Serial.print(","); Serial.println(phaseACangle);

///////////////////////////////////////////////////Uncomment for using all 3 phases
/////////////////////////Remove this Statement and uncomment next one.
//////////////////////    \/ \/ \/ \/ \/ \/ \/ \/ //////////////////////////
  if (phaseABangle <=122 && phaseABangle >= 100 /*&& phaseACangle <=122*/){
    Serial.println("Sequence Okay - RYB");
    digitalWrite(seqFault, LOW);
  }
  else{
    Serial.println("Sequence Wrong - RBY");
    digitalWrite(seqFault, HIGH);
  }

  delay(500);


}