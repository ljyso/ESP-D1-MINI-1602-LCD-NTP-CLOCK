#include <LiquidCrystal.h>
#include <TimeLib.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <DYWiFiConfig.h>
#include "DHT.h"
#define DHTPIN D7//DHT11连接D7引脚
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);

DYWiFiConfig wificonfig;
ESP8266WebServer webserver(80);
#define DEF_WIFI_SSID     "XXX"
#define DEF_WIWI_PASSWORD "XXXXXXXX"
#define AP_NAME "WIFI CLOCK" //dev

static const char ntpServerName[] = "ntp.sjtu.edu.cn"; //NTP服务器，上海交通大学
const int timeZone = 8;                                //时区，北京时间为+8
//-----------------------------------------------------------------------------
WiFiUDP Udp;
unsigned int localPort = 8888; // 用于侦听UDP数据包的本地端口
int temptimes=0;
LiquidCrystal lcd(D6, D5, D1, D2, D3, D4); //LCD1602连接引脚
//定义温度计模型
byte temp[8] = {
	0B00100,
	0B01010,
	0B01010,
	0B01010,
	0B01010,
	0B10001,
	0B11111,
	0B01110
};

//定义湿度logo字符
byte humi[8] = {
	0B00000,
	0B00100,
	0B01110,
	0B11111,
	0B11111,
	0B11111,
	0B01110,
	0B00000
};
byte heart[8] = {
	0B00000,
	0B01010,
	0B11111,
	0B11111,
	0B11111,
	0B01110,
	0B00100,
	0B00000
};
time_t getNtpTime();
void sendNTPpacket(IPAddress &address);
void digitalClockDisplay();
void sendCommand(int command, int value);
void initdisplay();

void setup() {
  dht.begin();
  lcd.begin(16, 2);
  Serial.begin(115200);
  lcd.createChar(1, temp);
  lcd.createChar(2, humi);
  lcd.createChar(3, heart);
  lcd.setCursor(4,0);
  lcd.print("NTP CLOCK  ");
  lcd.setCursor(4, 1);
  lcd.print("Degin by LJY  ");
  lcd.write(3);
  delay(3000);
  lcd.clear();
  lcd.home();
  lcd.print("   WIFI CLOCK  ");
  lcd.setCursor(0,1);
  lcd.print("  192.168.4.1 ");
  delay(5000);
  lcd.clear();
  lcd.home();
  lcd.print("Connecting WiFi...  ");
  lcd.setCursor(0,1);
  lcd.print("  NTP CLOCK       ");
  while (!Serial)
      continue;
  Serial.println("lcd 1602 NTP Clock version v1.0 degin by ljy");
  Serial.print("Connecting WiFi...");
  wificonfig.begin(&webserver, "/");
  DYWIFICONFIG_STRUCT defaultConfig = wificonfig.createConfig();
  strcpy(defaultConfig.SSID, DEF_WIFI_SSID);
  strcpy(defaultConfig.SSID_PASSWORD, DEF_WIWI_PASSWORD);
  strcpy(defaultConfig.HOSTNAME, AP_NAME);
  strcpy(defaultConfig.APNAME, AP_NAME);
  wificonfig.setDefaultConfig(defaultConfig);
  wificonfig.enableAP();
  while (WiFi.status() != WL_CONNECTED)
  {
    wificonfig.handle();
    //Serial.println("Waiting for Connection...");
  }
  
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.println("Starting UDP");
    Udp.begin(localPort);
    Serial.print("Local port: ");
    Serial.println(Udp.localPort());
    Serial.println("waiting for sync");
    setSyncProvider(getNtpTime);
    setSyncInterval(300);     //每300秒同步一次时间
}

time_t prevDisplay = 0; 


void loop()
{
    if (timeStatus() != timeNotSet){
        if (now() != prevDisplay){ //时间改变时更新显示
            prevDisplay = now();
            digitalClockDisplay();

        }
    }
}

void digitalClockDisplay()
{
    int years, months, days, hours, minutes, seconds, weekdays;
    years = year(); 
    months = month(); 
    days = day(); 
    hours = hour(); 
    minutes = minute(); 
    seconds = second(); 
    weekdays = weekday();
    Serial.printf("%d/%d/%d %d:%d:%d Weekday:%d\n", years, months, days, hours, minutes, seconds, weekdays);
    lcd.clear();
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    lcd.setCursor(0,0);
    lcd.print( years);
    lcd.print("-");
    lcd.print(months);
    lcd.print("-");
    lcd.print(days);
    lcd.print(" ");
    lcd.print(weekdays);
    lcd.print(" ");
    lcd.write(2);
    lcd.print(h);
    lcd.setCursor(0,1);
    lcd.print(hours);
    lcd.print(":");
    lcd.print(minutes);
    lcd.print(":");
    lcd.print(seconds);
    lcd.setCursor(9,1);
    lcd.write(1);
    lcd.print(t);
}




/*-------- NTP 代码 ----------*/

const int NTP_PACKET_SIZE = 48;     // NTP时间在消息的前48个字节里
byte packetBuffer[NTP_PACKET_SIZE]; // 输入输出包的缓冲区

time_t getNtpTime()
{
    IPAddress ntpServerIP; // NTP服务器的地址

    while (Udp.parsePacket() > 0); // 丢弃以前接收的任何数据包
    Serial.println("Transmit NTP Request");
    // 从池中获取随机服务器
    WiFi.hostByName(ntpServerName, ntpServerIP);
    Serial.print(ntpServerName);
    Serial.print(": ");
    Serial.println(ntpServerIP);
    sendNTPpacket(ntpServerIP);
    uint32_t beginWait = millis();
    while (millis() - beginWait < 1500){
        int size = Udp.parsePacket();
        if (size >= NTP_PACKET_SIZE){
            Serial.println("Receive NTP Response");
            Udp.read(packetBuffer, NTP_PACKET_SIZE); // 将数据包读取到缓冲区
            unsigned long secsSince1900;
            // 将从位置40开始的四个字节转换为长整型，只取前32位整数部分
            secsSince1900 = (unsigned long)packetBuffer[40] << 24;
            secsSince1900 |= (unsigned long)packetBuffer[41] << 16;
            secsSince1900 |= (unsigned long)packetBuffer[42] << 8;
            secsSince1900 |= (unsigned long)packetBuffer[43];
            Serial.println(secsSince1900);
            Serial.println(secsSince1900 - 2208988800UL + timeZone * SECS_PER_HOUR);
            return secsSince1900 - 2208988800UL + timeZone * SECS_PER_HOUR;
        }
    }
    Serial.println("No NTP Response :-("); //无NTP响应
    return 0;                              //如果未得到时间则返回0
}

// 向给定地址的时间服务器发送NTP请求
void sendNTPpacket(IPAddress &address)
{
    memset(packetBuffer, 0, NTP_PACKET_SIZE);
    packetBuffer[0] = 0b11100011; // LI, Version, Mode
    packetBuffer[1] = 0;          // Stratum, or type of clock
    packetBuffer[2] = 6;          // Polling Interval
    packetBuffer[3] = 0xEC;       // Peer Clock Precision
    // 8 bytes of zero for Root Delay & Root Dispersion
    packetBuffer[12] = 49;
    packetBuffer[13] = 0x4E;
    packetBuffer[14] = 49;
    packetBuffer[15] = 52;
    Udp.beginPacket(address, 123); //NTP需要使用的UDP端口号为123
    Udp.write(packetBuffer, NTP_PACKET_SIZE);
    Udp.endPacket();
}

