#include <LiquidCrystal.h>

//wybór wejść do obsługi LCD. Są przypisywane do kolejnych wejść
// wyświetlacza : RS, E, sygnały z danymi
LiquidCrystal lcd(2,3,4,5,6,7); 

float histereza = 2.0; 
float min_t = 27.0;
float max_t = 32.0;
int cnt = 0;     // zmienna pomocnicza

void setup() { 
  lcd.begin(16,2); // 16 znakow,2 wiersze
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temperatura:");
  pinMode(13,OUTPUT);
  pinMode(12,OUTPUT);
}

void loop() {
  float temp = ((analogRead(A5)*5.0)/1024.0)*100;
  if (temp <= min_t-(histereza/2))
  {
    digitalWrite(13, HIGH);
    digitalWrite(12, LOW);
    if(temp<min_t && cnt >= 10){ 
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("UWAGA!");
      lcd.setCursor(0,1);
      lcd.print("Tem. ponizej MIN");
      delay(3000);
      lcd.clear();
      cnt = 0;
    }
  }
  if (temp >= max_t+(histereza/2))
  {
    digitalWrite(12, HIGH);
    digitalWrite(13, LOW);
    if(temp > max_t && cnt >= 10){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("UWAGA!");    
      lcd.setCursor(0,1);
      lcd.print("Tem. powyzej MAX");
      delay(3000);
      lcd.clear();
      cnt = 0;
    }
  }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temperatura:");  
  lcd.setCursor(0,1);
  lcd.print(temp);
  lcd.print(" 'C");
  delay(500);
  cnt++;
  if (cnt >= 20)
  {
    cnt = 0;
  }
}
