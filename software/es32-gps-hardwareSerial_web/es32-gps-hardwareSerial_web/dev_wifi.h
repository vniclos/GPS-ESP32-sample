
#ifndef DEV_WIFI_H
#define DEV_WIFI_H




void fncDev_Wifi_setup()
{


  if (!WiFi.config(g_wifi_ip, g_wifi_gateway, g_wifi_subnet, g_wifi_primaryDNS, g_wifi_secondaryDNS)) {
#ifdef DEBUG
    Serial.println("STA Failed to configure");
#endif
  }
#ifdef DEBUG
  Serial.print("Connecting to ");
  Serial.println(g_wifi_siid);
#endif
  WiFi.begin(g_wifi_siid, g_wifi_pwd);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
#ifdef DEBUG
    Serial.print(".");
#endif
  }
  if (MDNS.begin(g_wifi_host)) {
#ifdef DEBUG
    Serial.print("MDNS started on ");
    Serial.print(g_wifi_host);
    Serial.println(".local");
#endif
  }

#ifdef DEBUG
  Serial.println("");
  Serial.println("WiFi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("ESP Mac Address: ");
  Serial.println(WiFi.macAddress());
  Serial.print("Subnet Mask: ");
  Serial.println(WiFi.subnetMask());
  Serial.print("Gateway IP: ");
  Serial.println(WiFi.gatewayIP());
  Serial.print("DNS: ");
  Serial.println(WiFi.dnsIP());
#endif

}
#endif
