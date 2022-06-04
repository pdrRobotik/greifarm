#include <FtduinoSimple.h>
#include <AccessNode.h>

int i3Wert = 0;
RobotikInterConnect* ric;
int counter = 0;
bool isClicked = false;


void setup() {
  ric = new RobotikInterConnect("greifarm");

    ftduino.motor_set(Ftduino::M1, Ftduino::RIGHT);
    while (!ftduino.input_get(Ftduino::I2)) delay(1);
    ftduino.motor_set(Ftduino::M1, Ftduino::OFF);

    ftduino.motor_set(Ftduino::M2, Ftduino::LEFT);
    while (!ftduino.input_get(Ftduino::I6)) delay(1);
    ftduino.motor_set(Ftduino::M2, Ftduino::OFF);

    ftduino.motor_set(Ftduino::M3, Ftduino::RIGHT);
    while (!ftduino.input_get(Ftduino::I7)) {
      
    }
    ftduino.motor_set(Ftduino::M3, Ftduino::OFF);

    ftduino.output_set(Ftduino::O8, Ftduino::HI);
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
  ric->send("debug","websocket","OK");
  String result = ric->read_wait();
    
    ftduino.output_set(Ftduino::O8, Ftduino::HI);
    
    if (result == "r") {
      ftduino.motor_set(Ftduino::M2, Ftduino::RIGHT);
      delay(10300);
      ftduino.motor_set(Ftduino::M2, Ftduino::OFF);
    } else if (result == "g") {
      ftduino.motor_set(Ftduino::M2, Ftduino::RIGHT);
      delay(7000);
      ftduino.motor_set(Ftduino::M2, Ftduino::OFF);
    } else if (result == "b") {
      ftduino.motor_set(Ftduino::M2, Ftduino::RIGHT);
      delay(2500);
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
    ftduino.output_set(Ftduino::O7, Ftduino::OFF);
    ftduino.output_set(Ftduino::O8, Ftduino::OFF);

    //Arm hoch
    delay(3000);
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
    while (!ftduino.input_get(Ftduino::I7)) {
      ftduino.motor_set(Ftduino::M3, Ftduino::RIGHT);
    }
    ftduino.motor_set(Ftduino::M3, Ftduino::OFF);

  delay(1);
}
