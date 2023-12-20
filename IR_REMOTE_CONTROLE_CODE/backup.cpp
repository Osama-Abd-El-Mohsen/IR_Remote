
#include "D:\Projects\Electronics2\IR_REMOTE_CONTROLE\src\IR_REMOTE_VALUES.h"\

#include <Arduino.h>
#include <IRremote.hpp>
#include <HID-Project.h>
#include <HID-Settings.h>

int irReceive();

#define IR_LED_PIN 2
#define MOUSE_STEP 20
#define IR_MODE2_PIN 4
#define IR_MODE1_PIN 6
#define IR_RECEIVE_PIN 7

int MODE = 0;
void setup()
{
  pinMode(IR_LED_PIN, OUTPUT);
  pinMode(IR_MODE1_PIN, OUTPUT);
  pinMode(IR_MODE2_PIN, OUTPUT);
  Mouse.begin();
  Serial.begin(9600);
  Keyboard.begin();
  Consumer.begin();
  IrReceiver.begin(IR_RECEIVE_PIN);
}

void loop()
{
  if (MODE == 0)
  {
    digitalWrite(IR_MODE1_PIN, HIGH);
    digitalWrite(IR_MODE2_PIN, LOW);
    switch (irReceive())
    {
    case REMOTE_ENTER_KEY:
      Keyboard.write(KEY_ENTER);
      Keyboard.releaseAll();
      break;
    case REMOTE_RIGHT_KEY:
      Keyboard.write(KEY_RIGHT_ARROW);
      break;
    case REMOTE_LEFT_KEY:
      Keyboard.write(KEY_LEFT_ARROW);
      break;
    case REMOTE_UP_KEY:
      Keyboard.write(KEY_UP_ARROW);
      break;
    case REMOTE_DOWN_KEY:
      Keyboard.write(KEY_DOWN_ARROW);
      break;
    case REMOTE_STAR_KEY:
      Keyboard.write(KEY_F5);
      break;
    case REMOTE_HASH_KEY:
      Keyboard.write(KEY_ESC);
      break;
    case REMOTE_1_KEY:
      Keyboard.write(KEY_BACKSPACE);
      break;
    case REMOTE_2_KEY:
      Keyboard.write(KEY_MENU);
      break;
    case REMOTE_3_KEY:
      Keyboard.press(KEY_RIGHT_ALT);
      Keyboard.write(KEY_TAB);
      break;
    case REMOTE_4_KEY:
      Consumer.write(MEDIA_VOLUME_UP);
      break;
    case REMOTE_5_KEY:
      Keyboard.press(KEY_RIGHT_ALT);
      Keyboard.write(KEY_F4);
      Keyboard.releaseAll();
      break;
    // case REMOTE_6_KEY:
    //   Consumer.write(MEDIA_FAST_FORWARD);
    //   break;
    case REMOTE_7_KEY:
      Consumer.write(MEDIA_VOLUME_DOWN);
      break;
    case REMOTE_8_KEY:
      Consumer.write(MEDIA_VOLUME_MUTE);
      break;
    case REMOTE_9_KEY:
      Consumer.write(MEDIA_PLAY_PAUSE);
      break;

    case REMOTE_0_KEY:
      MODE = 1;
      break;
    }
  }
  else if (MODE == 1)
  {
    digitalWrite(IR_MODE1_PIN, LOW);
    digitalWrite(IR_MODE2_PIN, HIGH);
    switch (irReceive())
    {
    case REMOTE_ENTER_KEY:
      Mouse.click();
      Keyboard.releaseAll();
      break;
    case REMOTE_RIGHT_KEY:
      Mouse.move(MOUSE_STEP, 0);
      break;
    case REMOTE_LEFT_KEY:
      Mouse.move(-MOUSE_STEP, 0);
      break;
    case REMOTE_UP_KEY:
      Mouse.move(0, -MOUSE_STEP);
      break;
    case REMOTE_DOWN_KEY:
      Mouse.move(0, +MOUSE_STEP);
      break;
    case REMOTE_STAR_KEY:
      Keyboard.write(KEY_F5);
      break;
    case REMOTE_HASH_KEY:
      Keyboard.write(KEY_ESC);
      break;
    case REMOTE_1_KEY:
      Keyboard.write(KEY_BACKSPACE);
      break;
    case REMOTE_2_KEY:
      Mouse.click(MOUSE_RIGHT);

      break;
    case REMOTE_3_KEY:
      Keyboard.press(KEY_RIGHT_ALT);
      Keyboard.write(KEY_TAB);
      break;
    case REMOTE_4_KEY:
      Consumer.write(MEDIA_VOLUME_UP);
      break;
    case REMOTE_5_KEY:
      Keyboard.press(KEY_RIGHT_ALT);
      Keyboard.write(KEY_F4);
      Keyboard.releaseAll();
      break;
    case REMOTE_6_KEY:
      Mouse.move(0, 0, 5);
      break;
    case REMOTE_7_KEY:
      Consumer.write(MEDIA_VOLUME_DOWN);
      break;
    case REMOTE_8_KEY:
      Consumer.write(MEDIA_VOLUME_MUTE);
      break;
    case REMOTE_9_KEY:
      Mouse.move(0, 0, -5);
      break;
    case REMOTE_0_KEY:
      MODE = 0;
      break;
    }
  }
}

int irReceive()
{
  int received{0};

  if (IrReceiver.decode())
  {
    digitalWrite(IR_LED_PIN, HIGH);
    received = IrReceiver.decodedIRData.command;
    delay(100);
    digitalWrite(IR_LED_PIN, LOW);
    //    Serial.print("ID = 0x");
    //    Serial.println(received,HEX);
    IrReceiver.resume();
  }
  return received;
}
