
#include "hpa.h"

void setup() {
  Serial.begin(9600);
  while (!Serial);
  
  HPA::xreal x = HPA::xreal(12.0);
  
  Serial.println(x._2double());
  Serial.println(HPA::xONE._2float());
  Serial.println(HPA::xTWO._2float());
  Serial.println((HPA::xTWO + HPA::xONE)._2double());
  
}

void loop () {
  
};