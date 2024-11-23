#pragma once

#include "esphome/core/component.h"
#include "esphome/components/i2c/i2c.h"
#include "esphome/components/touchscreen/touchscreen.h"

namespace esphome {
namespace ns2009 {

#define NS2009_READ_X 0xC0
#define NS2009_READ_Y 0xD0
#define NS2009_READ_Z 0xE0
#define TOUCH_THRESHOLD 150

class NS2009Touchscreen : public touchscreen::Touchscreen, public i2c::I2CDevice {
public:
  void setup() override;
  void loop() override;
  void dump_config() override;
  float get_setup_priority() const override { return setup_priority::DATA; }

protected:
  uint16_t read_register_(uint8_t reg);
  bool read_touch_point_();
  
  uint16_t raw_x_{0};
  uint16_t raw_y_{0};
  uint16_t raw_z_{0};
  
  static constexpr uint16_t min_x_ = 410;
  static constexpr uint16_t max_x_ = 3780;
  static constexpr uint16_t min_y_ = 360;
  static constexpr uint16_t max_y_ = 3770;
  static constexpr uint16_t screen_width_ = 320;
  static constexpr uint16_t screen_height_ = 240;
};

}  // namespace ns2009
}  // namespace esphome
