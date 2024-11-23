#pragma once

#include "esphome/core/component.h"
#include "esphome/components/i2c/i2c.h"

namespace esphome {
namespace ns2009 {

#define DEFAULT_NS2009_ADDR 0x48
#define THRESHOLD_Z 150
#define NS2009_READ_X 0xC0
#define NS2009_READ_Y 0xD0
#define NS2009_READ_Z 0xE0
#define CALIBRATE_MIN_X 200
#define CALIBRATE_MIN_Y 400
#define CALIBRATE_MAX_X 3850
#define CALIBRATE_MAX_Y 3920
#define SCREEN_SIZE_X 240
#define SCREEN_SIZE_Y 320

class NS2009Component : public Component, public i2c::I2CDevice {
 public:
  void setup() override;
  void loop() override;
  void dump_config() override;
  float get_setup_priority() const override { return setup_priority::DATA; }

  int raw_x{0}, x{0}, raw_y{0}, y{0}, raw_z{0};
  bool touched{false};
  bool flip_x{false};
  bool flip_y{false};

  void calibrate(int min_x, int max_x, int min_y, int max_y);
  void set_flip_x(bool flip) { this->flip_x = flip; }
  void set_flip_y(bool flip) { this->flip_y = flip; }

 protected:
  int min_x_{CALIBRATE_MIN_X};
  int max_x_{CALIBRATE_MAX_X}; 
  int min_y_{CALIBRATE_MIN_Y};
  int max_y_{CALIBRATE_MAX_Y};

  unsigned int read_register_(unsigned char command);
  int map_data_(int data, int in_min, int in_max, int out_min, int out_max);
  bool check_touched_();
  void scan_();
};

}  // namespace ns2009
}  // namespace esphome
