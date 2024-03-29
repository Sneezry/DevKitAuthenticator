https://github.com/Cathedrow/Cryptosuite/

Cryptosuite is a cryptographic library for Arduino (including SHA and HMAC-SHA)

It currently supports secure hashing and hashed message authentication using SHA-1, SHA-256, HMAC-SHA-1 and HMAC-SHA-256.

Installation:
  Make a 'libraries' directory with your Arduino sketches folder if you do not already have one.
  Copy the 'Sha' directory into that directory.
  Restart Arduino to rescan for new libraries.

Using SHA-1:
  #include "sha1.h"
  ...
  uint8_t *hash;
  Sha1.init();
  Sha1.print("This is a message to hash");
  hash = Sha1.result();

  The hash result is then stored in hash[0], hash[1] .. hash[19].

Using HMAC-SHA-1:
  #include "sha1.h"
  ...
  uint8_t *hash;
  Sha1.initHmac("hash key",8); // key, and length of key in bytes
  Sha1.print("This is a message to hash");
  hash = Sha1.resultHmac();

  The hash result is then stored in hash[0], hash[1] .. hash[19].

Using SHA-256:
  #include "sha256.h"
  ...
  uint8_t *hash;
  Sha256.init();
  Sha256.print("This is a message to hash");
  hash = Sha256.result();

  The hash result is then stored in hash[0], hash[1] .. hash[31].

Using HMAC-SHA-256:
  #include "sha256.h"
  ...
  uint8_t *hash;
  Sha256.initHmac("hash key",8); // key, and length of key in bytes
  Sha256.print("This is a message to hash");
  hash = Sha256.resultHmac();

  The hash result is then stored in hash[0], hash[1] .. hash[31].


Verification:
  The provided example code tests against published test vectors.
  SHA-1: FIPS 180-2, RFC3174 compliant
  HMAC-SHA-1: FIPS 198a compliant
  SHA-256: FIPS 180-2, RFC4231 compliant
  HMAC-SHA-256:  RFC4231 compliant