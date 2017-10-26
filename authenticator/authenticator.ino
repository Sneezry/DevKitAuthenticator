#include "Arduino.h";
#include "OledDisplay.h";
#include "AZ3166WiFi.h";
#include "Base32.h";
#include "sha1.h"
#include "TOTP.h"
#include "code.h"

Base32 base32;
TOTP *totp;

unsigned char *hmacKey;
unsigned char* newCode;

unsigned char timeBar[92];
unsigned char issuer[] = "DevKit Auth";
unsigned char secret[] = "GEZDGNBVGY3TQOJQ";
unsigned char account[] = "Sneezry";

long steps = 0;
int timeLeft= 0;

bool isWifiConnected = false;

void setup()
{
  Screen.clean();
  Screen.print(1, "Syncing clock...");

  if(WiFi.begin() == WL_CONNECTED)
  {
    isWifiConnected = true;
    Screen.clean();
    Screen.print(0, (const char *)issuer);
    Screen.print(3, (const char *)account);
  }
  else
  {
    Screen.clean();
    Screen.print(1, " No connection. ");
  }
}

void loop()
{
  if (isWifiConnected)
  {
    base32.fromBase32(secret, sizeof(secret) - 1, (byte*&)hmacKey);
    
    time_t seconds = time(NULL);

    if((long)(seconds / 30) != steps)
    {
      totp = new TOTP(hmacKey, strlen((const char *)hmacKey));
      steps = (long)(seconds / 30);
      newCode = (unsigned char *)totp->getCode((long)seconds);
      showCode(newCode);
      free(totp);
    }

    timeLeft= (long)seconds % 30 + 1;
    int i;
    for (i = 0; i < 92; i++) {
      if (i < timeLeft* 3 + 2)
      {
        timeBar[i] = 0x18;
      }
      else
      {
        timeBar[i] = 0x00;
      }
    }
    Screen.draw(18, 5, 110, 6, timeBar);
  }

  delay(200);
}
