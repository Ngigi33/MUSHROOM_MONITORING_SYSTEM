#include <Arduino.h>
#include <WiFi.h>
#include <Firebase_ESP_Client.h>

//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

#define WIFI_SSID "THINKBOOK"
#define WIFI_PASSWORD "12345678"

// Insert Firebase project API Key
#define API_KEY "AIzaSyDhfwnEzxEbJcWolzLGX8Ai74Rkqmrvn7U"
#define DATABASE_URL "https://mushroom-monitoring-database-default-rtdb.europe-west1.firebasedatabase.app/"

// Insert Authorized Email and Corresponding Password
#define USER_EMAIL "albertngigi3@gmail.com"
#define USER_PASSWORD "Albert18684"

//Define Firebase Data object
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

// Variable to save USER UID
String uid;

// Variables to save database paths
String databasePath;
String tempPath;
String humPath;

unsigned long sendDataPrevMillis = 0;
unsigned long timerDelay = 180000;
int count = 0;
bool signupOK = false;


// Initialize WiFi
void initWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
  Serial.println();
}

// Write float values to the database
void sendFloat(String path, float value) {
  if (Firebase.RTDB.setFloat(&fbdo, path.c_str(), value)) {
    Serial.print("Writing value: ");
    Serial.print(value);
    Serial.print(" on the following path: ");
    Serial.println(path);
    Serial.println("PASSED");
    Serial.println("PATH: " + fbdo.dataPath());
    Serial.println("TYPE: " + fbdo.dataType());
  } else {
    Serial.println("FAILED");
    Serial.println("REASON: " + fbdo.errorReason());
  }
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  initWiFi();

  /* Assign the api key (required) */
  config.api_key = API_KEY;
  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;


  // Assign the user sign in credentials
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;


  Firebase.reconnectWiFi(true);
  fbdo.setResponseSize(4096);

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; /*see addons/TokenHelper.h*/

  /* Assign the maximum retry of token generation*/
  config.max_token_generation_retry = 5;

  // Initialize the library with the Firebase authen and config
  Firebase.begin(&config, &auth);

  // Getting the user UID might take a few seconds
  Serial.println("Getting User UID");
  while ((auth.token.uid) == "") {
    Serial.print('.');
    delay(1000);
  }
  // Print user UID
  uid = auth.token.uid.c_str();
  Serial.print("User UID: ");
  Serial.print(uid);

  // Update database path
  databasePath = "/UsersData/" + uid;

  // Update database path for sensor readings
  tempPath = databasePath + "/temperature";  // --> UsersData/<user_uid>/temperature
  humPath = databasePath + "/humidity";      // --> UsersData/<user_uid>/humidity
  //presPath = databasePath + "/pressure";     // --> UsersData/<user_uid>/pressure
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Firebase.ready() && (millis() - sendDataPrevMillis > timerDelay || sendDataPrevMillis == 0)) {
    sendDataPrevMillis = millis();

    sendFloat(tempPath, 0.01 + random(0, 100));
    sendFloat(humPath, 0.01 + random(0, 100));



    // // Write an Int number on the database path test/int
    // if (Firebase.RTDB.setInt(&fbdo, "test/int", count)) {
    //   Serial.println("PASSED");
    //   Serial.println("PATH: " + fbdo.dataPath());
    //   Serial.println("TYPE: " + fbdo.dataType());
    // } else {
    //   Serial.println("FAILED");
    //   Serial.println("REASON: " + fbdo.errorReason());
    // }
    // count++;

    // // Write an Float number on the database path test/float
    // if (Firebase.RTDB.setFloat(&fbdo, "test/float", 0.01 + random(0, 100))) {
    //   Serial.println("PASSED");
    //   Serial.println("PATH: " + fbdo.dataPath());
    //   Serial.println("TYPE: " + fbdo.dataType());
    // } else {
    //   Serial.println("FAILED");
    //   Serial.println("REASON: " + fbdo.errorReason());
    // }
  }
}
