# RiaPushbuttonLite

A very simple debounced pushbutton helper library for Arduino.

- Author: **Seongpil Kim**
- Purpose: Education / beginner-friendly button handling
- Features:
  - Software debouncing
  - Simple API: `readRaw()` and `isPressed()`
  - Works with INPUT_PULLUP (default) and external pull-up/pull-down

## Installation

### As a normal Arduino library

1. Download this repository as a ZIP.
2. In Arduino IDE: **Sketch → Include Library → Add .ZIP Library…**
3. Select the downloaded ZIP file.

(Arduino Library Manager에 등록된 이후에는 Library Manager에서 `RiaPushbuttonLite`를 검색해서 설치할 수 있습니다.)

## Usage

```cpp
#include <RiaPushbuttonLite.h>

// 예: 12번 핀, 보드 내부 풀업 저항을 활성화 해서 풀업 스위치(눌리면 GND)를 사용한다고 가정
// - mode = INPUT_PULLUP
// - pressedLevel = LOW
// - debounceMs = 30ms (상황에 따라 다르지만 10ms< debouncdeMe < 30ms )
RiaPushbuttonLite button(12, INPUT_PULLUP, LOW, 30);

void setup() {
  Serial.begin(115200);
  button.begin();
}

void loop() {
  bool raw     = button.readRaw();    // 디바운스 없는 "즉시 눌림" 상태
  bool pressed = button.isPressed();  // 디바운스된 "안정된 눌림" 상태

  Serial.print("RAW=");
  Serial.print(raw ? "PRESSED" : "RELEASED");
  Serial.print(" | PRESSED=");
  Serial.println(pressed ? "PRESSED" : "RELEASED");

  delay(50);
}
