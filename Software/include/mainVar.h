#ifndef MAINVAR_H_
#define MAINVAR_H_

//=======================Macros

#define onBoardLED 2
#define userLED 15

#define btn_touch 13

//=======================Variable declarations

const char* ssid = "Honigtopf";
const char* pw = "Bretter8989+1";

const uint8_t port = 80;

extern volatile boolean secFlag;
extern boolean prevSecFlag;
extern boolean ledFlag;

hw_timer_t *timer1 = NULL;

const uint16_t gmtOffset_sec = 3600;
const uint16_t daylightOffset_sec = 3600;
const char* ntpServer = "pool.ntp.org";

boolean newTime = false;

//=======================Function declarations

void IRAM_ATTR onSecTimer();

String SendHTML(uint8_t led1stat);
void handle_onConnect();
void handle_noInt();
void handle_resumeInt();
void handle_ledOn();
void handle_ledOff();
void handle_NotFound();

void printTime();

#endif