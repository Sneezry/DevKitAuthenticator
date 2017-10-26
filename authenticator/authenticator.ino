#include "Arduino.h";
#include "OledDisplay.h";
#include "AZ3166WiFi.h";
#include "Base32.h";
#include "sha1.h"
#include "TOTP.h"
#include "code.h"

bool isWifiConnected = false;
Base32 base32;
unsigned char *hmacKey;
unsigned char issuer[] = "DevKit Auth";
unsigned char secret[] = "GEZDGNBVGY3TQOJQ";
unsigned char account[] = "Sneezry";
unsigned char* newCode;
long steps = 0;
int remain = 0;
unsigned char remainBar[92];
TOTP *totp;

void setup()
{
  pinMode(USER_BUTTON_A, INPUT);
  pinMode(USER_BUTTON_B, INPUT);

  Screen.clean();
  Screen.print(1, "Connecting WiFi...\r\n");

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
    Screen.print(1, "No WiFi.\r\n");
  }
}

void loop()
{
  // if (digitalRead(USER_BUTTON_A) == LOW)
  // {
  //   //Button A is pressed
  // }

  // if (digitalRead(USER_BUTTON_B) == LOW)
  // {
  //   //Button B is pressed
  // }

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

    remain = (long)seconds % 30 + 1;
    int i;
    for (i = 0; i < 92; i++) {
      if (i < remain * 3 + 2)
      {
        remainBar[i] = 0x18;
      }
      else
      {
        remainBar[i] = 0x00;
      }
    }
    Screen.draw(18, 5, 110, 6, remainBar);
	}

  delay(200);
}
