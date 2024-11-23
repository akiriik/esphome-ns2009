#pragma once

#include "esphome/core/component.h"
#include "esphome/components/i2c/i2c.h"

namespace esphome {
namespace ns2009 {

#define NS2009_READ_X 0xC0
#define NS2009_READ_Y 0xD0
#define NS2009_READ_Z 0xE0
#define TOUCH_THRESHOLD 150

class NS2009Touchscreen : public Component, public i2c::I2CDevice {
 public:
  void setup() override;
  void loop() override;
  void dump_config() override;
  float get_setup_priority() const override { return setup_priority::DATA; }

  // Julkiset muuttujat kosketuksen lukemiseen
  bool touched = false;
  int x = 0;
  int y = 0;

 protected:
  uint16_t read_register_(uint8_t reg);
  
  uint16_t raw_x_{0};
  uint16_t raw_y_{0};
  uint16_t raw_z_{0};
};

}  // namespace ns2009
}  // namespace esphome
