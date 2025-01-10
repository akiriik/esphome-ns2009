#include "ns2009.h"
#include "esphome/core/log.h"

namespace esphome {
namespace ns2009 {

static const char *const TAG = "ns2009";

void NS2009Component::setup() {
  ESP_LOGCONFIG(TAG, "Setting up NS2009...");
}

void NS2009Component::dump_config() {
  ESP_LOGCONFIG(TAG, "NS2009:");
  LOG_I2C_DEVICE(this);
  if (this->fast_reads_) {
    ESP_LOGCONFIG(TAG, "  Fast reads enabled");
  }
}

uint8_t NS2009Component::read_byte_(uint8_t a_register) {
  uint8_t ret;
  this->write(&a_register, 1);
  this->read(&ret, 1);
  return ret;
}

void NS2009Component::loop() {
  uint8_t x_low = this->read_byte_(REG_X);
  uint8_t x_high = this->read_byte_(REG_X);
  uint8_t y_low = this->read_byte_(REG_Y);
  uint8_t y_high = this->read_byte_(REG_Y);

  // Yhdistetään bitit
  uint16_t x_raw = (x_high << 8) | x_low;
  uint16_t y_raw = (y_high << 8) | y_low;

  // Muunnetaan arvot floateiksi
  this->x = x_raw;
  this->y = y_raw;

  // Jos fast_reads ei ole päällä, lisätään pieni viive
  if (!this->fast_reads_) {
    delayMicroseconds(100);  // Pienennetty 10ms -> 100µs
  }
}

}  // namespace ns2009
}  // namespace esphome
