#include <Adafruit_Fingerprint.h>
#include <ESP8266WiFi.h>
#include <LiquidCrystal_I2C.h>


#define enroll_pushBtn 12b
#define buzzer 13
#define LEDR_PIN_VIN	15
#define FINGERPRINTSCANNER_3V3_PIN_RX	0
#define FINGERPRINTSCANNER_3V3_PIN_TX	2



//lcd 
LiquidCrystal_I2C lcd(0x27, 16, 2);
//fingerprint
SoftwareSerial fingerPrint(FINGERPRINTSCANNER_3V3_PIN_RX,FINGERPRINTSCANNER_3V3_PIN_TX);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&fingerPrint);


//wifi credintials
const char* ssid     = "BELL4G-9188";  
const char* password = "JGT6J67L9J8";
// const char* ssid     = "AndroidAPD001";  
// const char* password = "chameesha1";  
const char* host = "api.pushingbox.com";


String member = "";
int flag = 0;

uint8_t id;

void setup() {
//beginning 
  Wire.begin(D2, D1);
  lcd.begin();
  Serial.begin(115200);

  pinMode(enroll_pushBtn, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);
  pinMode(LEDR_PIN_VIN, OUTPUT);
  digitalWrite(buzzer, LOW);

  
  //to enroll
  if(digitalRead(enroll_pushBtn) == 0){
      digitalWrite(LEDR_PIN_VIN, HIGH);
      digitalWrite(buzzer, HIGH);//buzzer noice
      delay(500);
      digitalWrite(LEDR_PIN_VIN, LOW);
      digitalWrite(buzzer, LOW);
      lcd.clear();

      // Serial.begin(9600);
      while (!Serial); 
      delay(100);
      Serial.println("\n\nAdafruit Fingerprint sensor enrollment");

      // set the data rate for the sensor serial port
      fingerPrint.begin(57600);
      
      if (finger.verifyPassword()) {
        Serial.println("Found fingerprint sensor!");
      } else {
        Serial.println("Did not find fingerprint sensor :(");
        while (1) { delay(1); }
      }


  }



  lcd.clear();
  lcd.print("Welcome");
  lcd.setCursor(0,1);
  lcd.print(" Students");
  delay(2000);
  lcd.clear();
  Serial.println("Mark your Attendence");
  lcd.setCursor(0, 0);
  Serial.print("Connecting to WiFi...       ");
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  lcd.setCursor(0, 0);
  digitalWrite(LEDR_PIN_VIN, HIGH);
  lcd.print("WiFi connected          ");
  digitalWrite(LEDR_PIN_VIN, LOW);
  lcd.setCursor(0, 1);
  lcd.print("IP:");
  lcd.setCursor(4, 1);
  lcd.print(WiFi.localIP());
  delay(1500);

  while (!Serial);
  delay(100);
  Serial.println("\n\n Waiting for Fingerprint Sensor");
  lcd.setCursor(0, 0);
  lcd.print("    Waiting for           ");
  lcd.setCursor(0, 1);
  lcd.print("      Sensor              ");
  delay(1500);
  finger.begin(57600);

  if (finger.verifyPassword())
  {
    digitalWrite(LEDR_PIN_VIN, HIGH);
    Serial.println("Found Successfully");
    digitalWrite(LEDR_PIN_VIN, LOW);
    lcd.setCursor(0, 0);
    lcd.print("Sensor found!         ");
    lcd.setCursor(0, 1);
    lcd.print("                      ");
    
    delay(1500);
  } else
  {
    Serial.println("Fingerprint sensor not found!!!");
    lcd.setCursor(0, 0);
    lcd.print("Sensor Not found!         ");
    lcd.setCursor(0, 1);
    lcd.print("                      ");
    while (1)
    {
      delay(1);
    }
  }
  

}




void loop() {
  // mrking attendence
  int fingerprintID = getFingerprintID();
  delay(50);
  if (fingerprintID == 1)
  {
    digitalWrite(LEDR_PIN_VIN, HIGH);
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);
    lcd.clear();

    Serial.println("AS2019952-Chameesha");
    lcd.setCursor(0, 0);
    lcd.print("AS2019952-Chameesha         ");
    lcd.setCursor(0, 1);
    lcd.print("                       ");
    connecthost("AS2019952");
    flag = 0;
  }
  else if (fingerprintID == 2)
  {
    digitalWrite(LEDR_PIN_VIN, HIGH);
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);
    lcd.clear();

    Serial.println("AS2019937-Ravi");
    lcd.setCursor(0, 0);
    lcd.print("AS2019937-Ravi          ");
    lcd.setCursor(0, 1);
    lcd.print("                       ");
    connecthost("AS2019937");
    flag = 0;
  }
  else if (fingerprintID == 3)
  {
    digitalWrite(LEDR_PIN_VIN, HIGH);
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);
    lcd.clear();
    
    Serial.println("AS2019953-Tamasha");
    lcd.setCursor(0, 0);
    lcd.print("AS2019953-Tamasha           ");
    lcd.setCursor(0, 1);
    lcd.print("                       ");
    connecthost("AS2019953");
    flag = 0;
  }else if (fingerprintID == 4)
  {
    digitalWrite(LEDR_PIN_VIN, HIGH);
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);
    lcd.clear();
    
    Serial.println("AS2019944-Dilakshi");
    lcd.setCursor(0, 0);
    lcd.print("AS2019944-Dilakshi           ");
    lcd.setCursor(0, 1);
    lcd.print("                       ");
    connecthost("AS2019944");
    flag = 0;
  }else if (fingerprintID == 5)
  {
    digitalWrite(LEDR_PIN_VIN, HIGH);
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);
    lcd.clear();
    
    Serial.println("AS2019945-Sandy");
    lcd.setCursor(0, 0);
    lcd.print("AS2019945-Sandy           ");
    lcd.setCursor(0, 1);
    lcd.print("                       ");
    connecthost("AS2019945");
    flag = 0;
  }else
  {
    digitalWrite(LEDR_PIN_VIN, LOW);
    Serial.println("Waiting for valid finger!!!");
    lcd.setCursor(0, 0);
    lcd.print(" Place a Valid       ");
    lcd.setCursor(0, 1);
    lcd.print("     Finger           ");
  }
   checkKeys();
   delay(300);

}





//----------------------------------------------------------------

//related to marking attendence
int getFingerprintID()
{
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;

  return finger.fingerID;
}

void connecthost(String data)
{
  if (flag == 0)
  {
    member = data;
    flag = 1;
    Serial.print("connecting to ");
    Serial.println(host);
    WiFiClient client;
    const int httpPort = 80;
    if (!client.connect(host, httpPort)) 
    {
      Serial.println("connection failed");
      return;
    }

    // We now create a URL for the request
    String url = "/pushingbox?";
    url += "devid=";
    url += "v3447D9B5ED8ED1C";
    url += "&Name=" + String(member);

    Serial.print("Requesting URL: ");
    Serial.println(url);
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n\r\n");
    unsigned long timeout = millis();
    while (client.available() == 0) {
      if (millis() - timeout > 5000) {
        Serial.println(">>> Client Timeout !");
        client.stop();
        return;
      }
    }
    while (client.available()) {
      String line = client.readStringUntil('\r');
      Serial.print(line);
      Serial.print("Data Sent!");
    }

    Serial.println();
    Serial.println("closing connection");
  }
}


//check key
void checkKeys()

{

   if(digitalRead(enroll_pushBtn) == 0)

   {

    lcd.clear();

    lcd.print("Ready to Enroll");
    delay(1000);
    while(digitalRead(enroll_pushBtn) == 0);
    Enroll();

   }

}
//----------------------------------------------------------------

//related to enrollment
uint8_t readnumber(void) {
  uint8_t num = 0;
  
  while (num == 0) {
    while (! Serial.available());
    num = Serial.parseInt();
  }
  return num;
}

//enroll loop part is in enroll()

void Enroll(){
  digitalWrite(LEDR_PIN_VIN, HIGH);
  Serial.println("Ready to enroll a fingerprint!");
  lcd.clear();
  lcd.print("Enter ID");
  Serial.println("Please type in the ID # (from 1 to 127) you want to save this finger as...");
  id = readnumber();
  if (id == 0) {// ID #0 not allowed, try again!
     return;
  }
  Serial.print("Enrolling ID #");
  Serial.println(id);
  
  while (!  getFingerprintEnroll() );
}


uint8_t getFingerprintEnroll() {

  int p = -1;
  lcd.clear();
  lcd.print("Place Finger");
  Serial.print("Waiting for valid finger to enroll as #"); Serial.println(id);
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      digitalWrite(LEDR_PIN_VIN, LOW);
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println(".");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      break;
    default:
      Serial.println("Unknown error");
      break;
    }
  }

  // OK success!

  p = finger.image2Tz(1);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  lcd.clear();
  lcd.print("Remove Finger");
  Serial.println("Remove finger");
  delay(2000);
  p = 0;
  while (p != FINGERPRINT_NOFINGER) {
    p = finger.getImage();
  }
  Serial.print("ID "); Serial.println(id);
  p = -1;
  lcd.clear();
  lcd.print("Place again!");
  Serial.println("Place same finger again");
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("    Enrollment     ");
      lcd.setCursor(0, 1);
      lcd.print("   Successfull !        ");
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.print(".");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      break;
    default:
      Serial.println("Unknown error");
      break;
    }
  }

  // OK success!

  p = finger.image2Tz(2);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  
  // OK converted!
  Serial.print("Creating model for #");  Serial.println(id);
  
  p = finger.createModel();
  if (p == FINGERPRINT_OK) {
    Serial.println("Prints matched!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_ENROLLMISMATCH) {
    Serial.println("Fingerprints did not match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   
  
  Serial.print("ID "); Serial.println(id);
  p = finger.storeModel(id);
  if (p == FINGERPRINT_OK) {
    Serial.println("Stored!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
    Serial.println("Could not store in that location");
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
    Serial.println("Error writing to flash");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   
}