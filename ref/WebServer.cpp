

//#include <WiFi.h>
//#include <WiFiClient.h>
//#include <WebServer.h>
//#include <ESPmDNS.h>
//  WebServer server(80);


//  IPAddress local_IP(192, 168, 86, 77);
//  IPAddress gateway(192, 168, 86, 1);
//  IPAddress subnet(255, 255, 0, 0);
//
//  WiFi.mode(WIFI_STA);
//  WiFi.config(local_IP, gateway, subnet);
//  WiFi.begin("LOF", "welcome!!!");
//
//  server.on("/", drawGraph);
//  server.begin();


//    server.handleClient();


//void drawGraph() {
//  String out = "";
//  out += String("<meta http-equiv='refresh' content='0.75'/><title>GateOpener</title><style>body{background-color:#aaa;margin:0;padding:0;}</style>");
//
//  for (int i = 0; i < 100; i++) {
//    float height = sensorModule.rawReadings[i];
//    height = ((height / 1024) * 100);
//    Serial.println(height);
//    out += String("<div style='width:1%;height:") + height + String("%;background-color:black;float:left;'></div>");
//  }
//  out += "</g>\n</svg>\n";
//
//  server.send(200, "text/html", out);
//}




//  const size_t N = 100;
//  memmove(&this->rawReadings[0], &this->rawReadings[1], (N - 1) * sizeof(this->rawReadings[0]));
//  int houseReading = this->ads.readADC_SingleEnded(0);
//  this->rawReadings[N - 1] = houseReading;
