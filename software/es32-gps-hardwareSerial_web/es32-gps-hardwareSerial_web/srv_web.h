#ifndef DEV_WEB_H
#define DEV_WEB_H

void handleNotFound() {
  digitalWrite(PIN_LED, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += g_websrv.uri();
  message += "\nMethod: ";
  message += (g_websrv.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += g_websrv.args();
  message += "\n";
  for (uint8_t i = 0; i < g_websrv.args(); i++) {
    message += " " + g_websrv.argName(i) + ": " + g_websrv.arg(i) + "\n";
  }
  g_websrv.send(404, "text/plain", message);
  digitalWrite(PIN_LED, 0);
}

void handleRoot()
{

  String szHtml = "<!doctype html><html lang=\"en\">\n<head>\n";
  szHtml += "\n<style>";
  szHtml += "\nlegend{ padding: 0.2em 0.5em;  border:1px solid green;  color:green;  font-size:90%;  text-align:right;}";
  szHtml += "\nfieldset{margin-bottom:1rem;border:1px solid green;    -moz-border-radius:8px;    -webkit-border-radius:8px;      border-radius:8px;  }";
  szHtml += "\n.fldTitle{width:140px; display: inline-block;}";
  szHtml += "\n.fldData{min-width:30em;display: inline-block; }";
  szHtml +="\n.button {color: #444444;     background: #F3F3F3;    border: 1px #DADADA solid;    padding: 5px 10px;    border-radius: 2px;    font-weight: bold;    font-size: 9pt;    outline: none;}";
  szHtml += "\n</style>";
  szHtml += "\n</head>\n<body>\n";
  szHtml += "\n<h3>Simple example integrate gps in web site</h3>";
szHtml += "\n<a class=\"button\" href=\"/\">Refresh</a><br/>";
  szHtml += "\n<fieldset><legend>GPS DATA:</legend>";

  szHtml += "\n<span class=\"fldTitle\">Location</span>";
  szHtml += "<span class=\"fldData\">" + String( g_DL_GpsLatiLong) + "  [Lat, Long]</span></br>";

  szHtml += "\n<span class=\"fldTitle\">Altitude</span>";
  szHtml += "<span class=\"fldData\">" + String( g_DL_GpsAltitud) + "</span></br>";

  szHtml += "\n<span class=\"fldTitle\">GPS Date Time</span>";
  szHtml += "<span class=\"fldData\">" + String( g_DL_GpsDateTime) + "</span></br>";

  szHtml += "\n<span class=\"fldTitle\">Satellites</span>";
  szHtml += "<span class=\"fldData\">" + String( g_DL_GpsSatellites) + "</span></br>";
szHtml+="<p>The Altitude is not precise, may be variation on a few meters</p>";
   szHtml += "\n</fieldset>";

  szHtml += "\n<fieldset><legend>GPS flags:</legend>";

  szHtml += "\n<span class=\"fldTitle\">Read Count to Fill</span>";
  szHtml += "<span class=\"fldData\">" + String( g_dev_gps_iCountFill) + "</span></br>";

  szHtml += "\n<span class=\"fldTitle\">Is Connected</span>";
  szHtml += "<span class=\"fldData\">" + String( g_dev_gpsIsConnected) + "</span></br>";

  szHtml += "\n<span class=\"fldTitle\">Is Read Altitude</span>";
  szHtml += "<span class=\"fldData\">" + String( g_dev_gpsIsReadAltitude) + "</span></br>";

  szHtml += "\n<span class=\"fldTitle\">Is Read Location</span>";
  szHtml += "<span class=\"fldData\">" + String( g_dev_gpsIsReadLocation) + "</span></br>";

  szHtml += "\n<span class=\"fldTitle\">Is Read Time</span>";
  szHtml += "<span class=\"fldData\">" + String( g_dev_gpsIsReadTime) + "</span></br>";
  szHtml += "\n<span class=\"fldTitle\">Is Read Date</span>";
  szHtml += "<span class=\"fldData\">" + String( g_dev_gpsIsReadDate) + "</span></br>";
  szHtml += "\n</fieldset>";
  szHtml += "\n<h5>Hardware</h5>";
  szHtml += "\n<ul>";
  szHtml += "\n<li> ESP32</li>";
  szHtml += "\n<li> NEO 6M GPS</li>";
  szHtml += "\n</ul>";

  szHtml += "\n<h5>Software</h5>";
  szHtml += "\n<ul>";
  szHtml += "\n<li> Arduino ID</li>";
  szHtml += "\n<li> Plugin ESP32</b>https://dl.espressif.com/dl/package_esp32_index.json</li>";
  szHtml += "\n<li> TinyGPS++.h</li>";
  szHtml += "\n<li> HardwareSerial.h</li>";

  szHtml += "\n</ul>";

  szHtml += "\n</body>\n</html>";

  g_websrv.send(200, "text / html", szHtml);
  digitalWrite(PIN_LED, 0);
}
void fncSrv_Web_setup()
{
  g_websrv.on("/", handleRoot);
  g_websrv.onNotFound(handleNotFound);
  g_websrv.begin();
#ifdef DEBUG
  Serial.println("HTTP server started");
#endif
}
#endif
