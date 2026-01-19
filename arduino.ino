#include <Tic.h>
#include <Wire.h>

TicI2C tic1(12); TicI2C tic2(13); TicI2C tic3(14); TicI2C tic4(15);

void setup() {
  Serial.begin(115200);
  Wire.begin();
  Wire.setClock(400000);

 
  tic1.exitSafeStart(); tic2.exitSafeStart();
  tic3.exitSafeStart(); tic4.exitSafeStart();
  
  Serial.println("BRIDGE_READY");
}

void loop() {
  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();
    if (cmd == "GET_ALL_POS") {
      long p1 = tic1.getCurrentPosition();
      long p2 = tic2.getCurrentPosition();
      long p3 = tic3.getCurrentPosition();
      long p4 = tic4.getCurrentPosition();
      
      Serial.print("ALL_POS ");
      Serial.print(p1); Serial.print(" ");
      Serial.print(p2); Serial.print(" ");
      Serial.print(p3); Serial.print(" ");
      Serial.println(p4);
    } 

    else if (cmd.startsWith("SET_VEL")) {
      int m; long vel;
      if (sscanf(cmd.c_str(), "SET_VEL %d %ld", &m, &vel) == 2) {
        if (m == 1) tic1.setTargetVelocity(vel);
        else if (m == 2) tic2.setTargetVelocity(vel);
        else if (m == 3) tic3.setTargetVelocity(vel);
        else if (m == 4) tic4.setTargetVelocity(vel);
      }
    }

    else if (cmd.startsWith("RESET_POS")) {
      int m; long p;
      if (sscanf(cmd.c_str(), "RESET_POS %d %ld", &m, &p) == 2) {
        if (m == 1) tic1.haltAndSetPosition(p);
        else if (m == 2) tic2.haltAndSetPosition(p);
        else if (m == 3) tic3.haltAndSetPosition(p);
        else if (m == 4) tic4.haltAndSetPosition(p);
        Serial.println("OK_RESET");
      }
    }
    else if (cmd == "INIT") {
      tic1.exitSafeStart(); tic2.exitSafeStart();
      tic3.exitSafeStart(); tic4.exitSafeStart();
      Serial.println("OK_INIT");
    }
  }
}
