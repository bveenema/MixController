#pragma once

#define THIS_PRODUCT_ID 1111
#define THIS_PRODUCT_VERSION 1004
PRODUCT_ID(7951);
PRODUCT_VERSION(4);

#define MOTORA_ENABLE_PIN D0
#define MOTORA_DIR_PIN D1
#define MOTORA_STEP_PIN D2
#define MOTORA_ASSERT_PIN D3

#define MOTORB_ENABLE_PIN D4
#define MOTORB_DIR_PIN D5
#define MOTORB_STEP_PIN D6
#define MOTORB_ASSERT_PIN D7

#define BUTTON_PIN A0
#define ERROR_LED_PIN A1
#define REMOTE_PIN A2

struct prom {
  bool version;
  uint16_t flowRate;
  uint16_t ratioA;
  uint16_t ratioB;
  uint32_t autoReverseA;
  uint32_t autoReverseB;
  uint16_t stepsPerMlA;
  uint16_t stepsPerMlB;
  uint32_t volume;
};

const uint32_t settingsAddr = 0;

const prom default_settings = {
  0,
  3000,
  200,
  100,
  0,
  0,
  128,
  128,
  3785
};