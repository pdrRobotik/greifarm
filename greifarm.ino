#include <FtduinoSimple.h>
//#include <AccessNode.h>

int i3Wert = 0;

void setup() {
  Serial.begin(9600);

    while (!ftduino.input_get(Ftduino::I2)) {
      ftduino.motor_set(Ftduino::M1, Ftduino::RIGHT);
    }
    ftduino.motor_set(Ftduino::M1, Ftduino::OFF);

    while (!ftduino.input_get(Ftduino::I6)) {
      ftduino.motor_set(Ftduino::M2, Ftduino::LEFT);
    }
    ftduino.motor_set(Ftduino::M2, Ftduino::OFF);

    while (!ftduino.input_get(Ftduino::I7)) {
      ftduino.motor_set(Ftduino::M3, Ftduino::RIGHT);
    }
    ftduino.motor_set(Ftduino::M3, Ftduino::OFF);
}
void loop() {
  // put your main code here, to run repeatedly:
  run();
}

//

void run() {
  if (!ftduino.input_get(Ftduino::I2)) {
    ftduino.motor_set(Ftduino::M1, Ftduino::RIGHT);
  }
  ftduino.motor_set(Ftduino::M1, Ftduino::OFF);

  if (!ftduino.input_get(Ftduino::I6)) {
    ftduino.motor_set(Ftduino::M2, Ftduino::LEFT);
  }
  ftduino.motor_set(Ftduino::M2, Ftduino::OFF);

  if (!ftduino.input_get(Ftduino::I7)) {
    ftduino.motor_set(Ftduino::M3, Ftduino::RIGHT);
  }
  ftduino.motor_set(Ftduino::M3, Ftduino::OFF);


  // a = 1 -> rot I3
  // a = 2 -> grün I4
  // a = 3 -> blau I5

  if (ftduino.input_get(Ftduino::I3) || ftduino.input_get(Ftduino::I4) || ftduino.input_get(Ftduino::I5)) {
    int a; 
    a = 0;
    //Arm zu Position
    if (ftduino.input_get(Ftduino::I3)) {
      a = 1;
    } else if (ftduino.input_get(Ftduino::I4)) {
      a = 2;
    } else if (ftduino.input_get(Ftduino::I5)) {
      a = 3;
    }

    if (a == 1) {
      ftduino.motor_set(Ftduino::M2, Ftduino::LEFT);
      delay(10000);  //anpassen
      ftduino.motor_set(Ftduino::M2, Ftduino::OFF);
    } else if (a == 2) {
      ftduino.motor_set(Ftduino::M2, Ftduino::RIGHT);
      delay(5000);  //anpassen
      ftduino.motor_set(Ftduino::M2, Ftduino::OFF);
    } else if (a == 3) {
      ftduino.motor_set(Ftduino::M2, Ftduino::RIGHT);

      ftduino.motor_set(Ftduino::M2, Ftduino::OFF);
    }

    //Arm runter
    while (!ftduino.input_get(Ftduino::I1)) {
      ftduino.motor_set(Ftduino::M1, Ftduino::LEFT);
    }
    ftduino.motor_set(Ftduino::M1, Ftduino::OFF);

    //Pneumatik an (greifen)
    ftduino.output_set(Ftduino::O7, Ftduino::HI);
    delay(1000);

    //Arm hoch
    while (!ftduino.input_get(Ftduino::I2)) {
      ftduino.motor_set(Ftduino::M1, Ftduino::RIGHT);
    }


    //drehen
    ftduino.motor_set(Ftduino::M3, Ftduino::LEFT);
    delay(4900);  //anpassen
    ftduino.motor_set(Ftduino::M3, Ftduino::OFF);

    //Arm runter
    ftduino.motor_set(Ftduino::M1, Ftduino::LEFT);
    delay(3500);
    ftduino.motor_set(Ftduino::M1, Ftduino::OFF);



    //Pneumatik aus (loslassen)
    ftduino.output_set(Ftduino::O7, Ftduino::LO);

    //Arm hoch
    while (!ftduino.input_get(Ftduino::I2)) {
      ftduino.motor_set(Ftduino::M1, Ftduino::RIGHT);
    }
    ftduino.motor_set(Ftduino::M1, Ftduino::OFF);

    //Arm einziehen
    while (!ftduino.input_get(Ftduino::I6)) {
      ftduino.motor_set(Ftduino::M2, Ftduino::LEFT);
    }
    ftduino.motor_set(Ftduino::M2, Ftduino::OFF);

    //zurück (drehen)
    ftduino.motor_set(Ftduino::M3, Ftduino::RIGHT);
    delay(4900);  //anpassen
    ftduino.motor_set(Ftduino::M3, Ftduino::OFF);
  }

  delay(1);
}