#pragma once

#include "esphome/components/climate_ir/climate_ir.h"

namespace esphome {
namespace mitsubishi {

// Temperature
const uint8_t MITSUBISHI_TEMP_MIN = 16;  // Celsius
const uint8_t MITSUBISHI_TEMP_MAX = 31;  // Celsius

// Fan speeds
enum SetFanSpeed {
  MITSUBISHI_FAN_1 = 0x01,
  MITSUBISHI_FAN_2 = 0x02,
  MITSUBISHI_FAN_3 = 0x03,
  MITSUBISHI_FAN_4 = 0x04,
  MITSUBISHI_FAN_5 = 0x05,
};

// Enum to represent horizontal directios
enum HorizontalDirection {
  HORIZONTAL_DIRECTION_LEFT = 0x10,
  HORIZONTAL_DIRECTION_MLEFT = 0x20,
  HORIZONTAL_DIRECTION_MIDDLE = 0x30,
  HORIZONTAL_DIRECTION_MRIGHT = 0x40,
  HORIZONTAL_DIRECTION_RIGHT = 0x50,
  HORIZONTAL_DIRECTION_SPLIT = 0x80,
};

// Enum to represent vertical directions
enum VerticalDirection {
  VERTICAL_DIRECTION_AUTO = 0x00,
  VERTICAL_DIRECTION_UP = 0x08,
  VERTICAL_DIRECTION_MUP = 0x10,
  VERTICAL_DIRECTION_MIDDLE = 0x18,
  VERTICAL_DIRECTION_MDOWN = 0x20,
  VERTICAL_DIRECTION_DOWN = 0x28,
};

class MitsubishiClimate : public climate_ir::ClimateIR {
 public:
  MitsubishiClimate()
      : climate_ir::ClimateIR(
        MITSUBISHI_TEMP_MIN, MITSUBISHI_TEMP_MAX, 1.0f, true, false,{
          climate::CLIMATE_FAN_AUTO, climate::CLIMATE_FAN_LOW,
          climate::CLIMATE_FAN_MEDIUM, climate::CLIMATE_FAN_HIGH
        },
        {climate::CLIMATE_SWING_OFF, climate::CLIMATE_SWING_BOTH,
          climate::CLIMATE_SWING_VERTICAL, climate::CLIMATE_SWING_HORIZONTAL
        }
      ) {}

  void set_fan_low(SetFanSpeed fan_low) { this->fan_low_ = fan_low; }

  void set_fan_medium(SetFanSpeed fan_medium) { this->fan_medium_ = fan_medium; }

  void set_fan_hi(SetFanSpeed fan_hi) { this->fan_hi_ = fan_hi; }

  void set_horizontal_default(HorizontalDirection horizontal_direction) {
    this->default_horizontal_direction_ = horizontal_direction;
  }
  void set_vertical_default(VerticalDirection vertical_direction) {
    this->default_vertical_direction_ = vertical_direction;
  }

 protected:
  // Transmit via IR the state of this climate controller.
  void transmit_state() override;
  // Handle received IR Buffer
  bool on_receive(remote_base::RemoteReceiveData data) override;
  bool parse_state_frame_(const uint8_t frame[]);

  // SetFanSpeed
  SetFanSpeed fan_low_;
  SetFanSpeed fan_medium_;
  SetFanSpeed fan_hi_;

  // Horizontal and Vertical
  HorizontalDirection default_horizontal_direction_;
  VerticalDirection default_vertical_direction_;
};

}  // namespace mitsubishi
}  // namespace esphome
