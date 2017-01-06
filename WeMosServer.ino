/* -*-c++-*- */
/* WeMos DHT Server
 *
 * Connect to WiFi and respond to http requests
 *
 */

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

// Existing WiFi network
const char* ssid     = "CenturyLink5951";
const char* password = "wi987ec6yu7326";
// Note brightness is reversed
const int   ledPin = BUILTIN_LED;  // the onboard LED

// Listen for HTTP requests on standard port 80
ESP8266WebServer server(80);

String brightness = "3";
String httpStr;

void setBrightness() {
  String bright = server.arg("brightness");

  if ( bright == "" ) {
    return;
  }
  brightness = bright;
  if        ( brightness == "3" ) {
    analogWrite(ledPin, 255);
    Serial.println("setting brightness high");
  } else if ( brightness == "2" ) {
    analogWrite(ledPin, 63);
    Serial.println("setting brightness medium");
  } else if ( brightness == "1" ) {
    analogWrite(ledPin, 15);\
    Serial.println("setting brightness low");
  } else if ( brightness == "0" ) {
    Serial.println("setting brightness off");
    analogWrite(ledPin, 0);
  }

}

//
// The addition of onclick=\"this.form.submit()\" eliminated the need for a submit button
void buildHttpString() {
  httpStr =
    "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">\n"
    "<html>\n"
    "  <head>\n"
    "  </head>\n"
    "  <body>\n"
    "    <form action=\"/action\">\n"
    "      <label style=\"font-size: 50px;\"><input type=\"radio\" name=\"brightness\" value=0 style=\"height:35px; width:35px; vertical-align: middle;\" onclick=\"this.form.submit()\"> High</label><br>\n"
    "      <label style=\"font-size: 50px;\"><input type=\"radio\" name=\"brightness\" value=1 style=\"height:35px; width:35px; vertical-align: middle;\" onclick=\"this.form.submit()\"> Medium</label><br>\n"
    "      <label style=\"font-size: 50px;\"><input type=\"radio\" name=\"brightness\" value=2 style=\"height:35px; width:35px; vertical-align: middle;\" onclick=\"this.form.submit()\"> Low</label><br>\n"
    "      <label style=\"font-size: 50px;\"><input type=\"radio\" name=\"brightness\" value=3 style=\"height:35px; width:35px; vertical-align: middle;\" onclick=\"this.form.submit()\"> Off</label><br><br>\n"
    //"      <input type=\"submit\" style=\"font-size: 50px;\" value=\"Set\">\n"
    "    </form>\n"
    "  </body>\n"
    "</html>\n";
  String brightStr = "value="+brightness+" style";
  String checkdStr = "value="+brightness+" checked style";
  httpStr.replace(brightStr, checkdStr);
}

void buildActionHttpString() {
  httpStr = 
    "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">\n"
    "<html>\n"
    "  <head>\n"
    "    <script language=\"JavaScript\">\n"
    "    <!--//\n"
    "      function frmLoad() {\n"
    "        setTimeout(\"back()\", 100);\n"
    "      }\n"
    "      function back() {\n"
    "        window.history.back();\n"
    "      }\n"
    "    //-->\n"
    "    </script>\n"
    "  </head>\n"
    "  <body onload=\"frmLoad();\">\n"
    "    Setting Brightness\n"
    "  </body>\n"
    "</html>\n";
}

void handle_root() {
  //if (server.args() > 0) {
  //  setBrightness();
  //}
  buildHttpString();
  server.send(200, "text/html", httpStr); 
  delay(100);
}

void handle_action() {
  setBrightness();
  buildActionHttpString();
  server.send(200, "text/html", httpStr); 
}

/*
void handleNotFound(){
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}
*/
void setup(void)
{
  analogWriteRange(255);
  analogWriteFreq(500);
  pinMode(ledPin, OUTPUT);

  if        ( brightness == "3" ) {
    analogWrite(ledPin, 0);
  } else if ( brightness == "2" ) {
    analogWrite(ledPin, 63);
  } else if ( brightness == "1" ) {
    analogWrite(ledPin, 127);
  } else if ( brightness == "0" ) {
    analogWrite(ledPin, 255);
  }

  // Open the Arduino IDE Serial Monitor to see what the code is doing
  Serial.begin(57600);

  Serial.println("WeMos Server");
  Serial.println("");

  // Connect to your WiFi network
  WiFi.begin(ssid, password);
  Serial.print("Connecting");

  // Wait for successful connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to: ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("");

  // Handle http requests
  server.on("/", handle_root);

  server.on("/action", handle_action);

  //server.onNotFound(handleNotFound);

  // Start the web server
  server.begin();
  //Serial.println("HTTP server started");
}

void loop(void)
{
  // Listen for http requests
  server.handleClient();
}
