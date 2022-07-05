#include <Keypad.h>
#include<Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd1(0x27, 16, 2); // << Address 1
LiquidCrystal_I2C lcd2(0x26, 20, 4); // << Address 2
volatile unsigned long count = 0 ;
long prior_count = 0;
#define chieudai 9
char Data[chieudai];
int dongia = 15000 ;  //VND
volatile float litbp;
float solit;
byte data_count = 0;
const byte rows = 4; //số hàng
const byte columns = 4; //số cột
long sotien  ;
long tienbp;
int button = 13;// chân nút nhấn
int flag = 0;
//Định nghĩa các giá trị trả về
char keys[rows][columns] =
{
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'F', '0', 'E', 'L'},
};

byte rowPins[rows] = {8, 7, 6, 5}; //Cách nối chân với Arduino (R1-R2-R3-R4)

byte columnPins[columns] = {9, 10, 11, 12}; //(C1-C2-C3-C4)

//cài đặt thư viện keypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, columnPins, rows, columns);

void pulse() {

  count = count + 1 ;
}
void setup() {
  lcd1 .init();
  lcd2.init();

  lcd1.backlight();
  lcd2.backlight();

  lcd1.setCursor(0, 0);

  lcd2.setCursor(0, 0);
  lcd2.print("So lit: ");

  lcd2.setCursor(0, 1);
  lcd2.print("So tien: ");

  lcd2.setCursor(0, 2);
  lcd2.print("Don gia: ");


  Serial.begin(9600);//bật serial, baudrate 9600
  pinMode(13, INPUT);


}




void loop() {


  char key = keypad.getKey();
 


    if ( key == 'A') {
      delay(700);
      if ( key == 'A') {
        flag = 1;
        lcd1.clear();
        lcd1.print("Nhap so lit :");
        data_count = 0;
        cleardata();
        while (flag) {
          key = keypad.getKey();
          if (key) {
            Data[data_count] = key;
            lcd1.setCursor(data_count , 1);
            lcd1.print(Data[data_count]);
            data_count++;
          }
          if (key == 'L') {
            lcd1.setCursor(data_count - 1 , 1);
            lcd1.print("Lit");
            float a = atoi(Data);
            litbp = a ;
            //Serial.print(litbp);
            flag = 0;
          }
        }
      }
    }

    if ( key == 'B') {
      delay(700);
      if ( key == 'B') {
        flag = 1;
        lcd1.clear();
        lcd1.print("Nhap so tien :");
        data_count = 0;
        cleardata();
        while (flag) {
          key = keypad.getKey();
          if (key) {
            Data[data_count] = key;
            lcd1.setCursor(data_count , 1);
            lcd1.print(Data[data_count]);
            data_count++;
          }
          if ( key == 'L') {
            lcd1.setCursor(data_count - 1, 1);
            lcd1.print(".");
            lcd1.setCursor(data_count, 1);
            lcd1.print("0");
            lcd1.setCursor(data_count + 1, 1);
            lcd1.print("0");
            lcd1.setCursor(data_count + 2, 1);
            lcd1.print("0");
            lcd1.setCursor(data_count + 3, 1);
            lcd1.print("VND");
            Serial.print(Data);
            litbp = (float)atoi(Data) / 15 ;
            //Serial.print(litbp);
            cleardata();
            flag = 0;
          }
        }
      }
    }

   
    if ( key == 'C') {
      delay(700);
      if ( key == 'C') {
        litbp = 9999;
      }
    }
 
   
    bomxang();
    sei();
  }


  void cleardata() {
    while (data_count != 0) {
      Data[data_count--] = 0;

    }
  }
  void bomxang() {
    if (digitalRead(button) == HIGH) {
      attachInterrupt(digitalPinToInterrupt(2), pulse, RISING);
      unsigned long new_count = count;
      if ( new_count != prior_count) {
         
        solit = new_count / 120.0 ;
        sotien = solit * dongia;
        lcd2.setCursor(8, 0);
        lcd2.print(solit);
        lcd2.setCursor(9, 1);
        lcd2.print(sotien);
        lcd2.setCursor(9, 2);
        lcd2.print(dongia);
        Serial.print(solit);
        Serial.print(' ');
        Serial.print(litbp);
        Serial.print('-');
        if (litbp <= solit ) {
          Serial.print(litbp);
          cli();

 
        }

      }
    }
  }
