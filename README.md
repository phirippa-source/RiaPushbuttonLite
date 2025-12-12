# RiaPushbuttonLite

A very simple debounced pushbutton helper library for Arduino.  
아주 단순한, 교육용으로 쓰기 좋은 **디바운스 포함 버튼 헬퍼 라이브러리**입니다.

- Author: Seongpil Kim (phirippa)
- Purpose: Education / beginner-friendly button handling

---

## Features

- 소프트웨어 디바운스 처리
- **간단한 API**
  - `readRaw()` : 디바운스 없는 “지금 당장 눌림 여부”
  - `isPressed()` : 디바운스가 적용된 “안정된 눌림 상태”
- `INPUT_PULLUP` / 외부 풀업 / 풀다운 구성 모두 지원
- UNO R3, UNO R4 WiFi 등 대부분의 Arduino 호환 보드에서 사용 가능

---

## Installation

### 1) Arduino Library Manager (권장)

(Arduino Library Manager에 등재된 후:)

1. Arduino IDE 실행
2. **Tools → Manage Libraries…** (또는 Sketch → Include Library → Manage Libraries…)
3. 검색창에 `RiaPushbuttonLite` 입력
4. 나오는 항목을 선택 후 **Install**

### 2) ZIP 파일로 수동 설치

1. 이 저장소를 ZIP으로 다운로드
2. Arduino IDE에서  
   `Sketch → Include Library → Add .ZIP Library…` 선택
3. 방금 받은 ZIP 파일을 선택

---

## Quick Start

가장 기본적인 예제는 `examples/RiaPushbuttonLite_QuickStart` 스케치입니다.  
풀업 스위치(눌리면 GND)를 버튼으로 사용하고, 버튼이 눌리면 보드 내장 LED가 켜집니다.

```cpp
#include <RiaPushbuttonLite.h>

const uint8_t BUTTON_PIN = 12;
const uint8_t LED_PIN    = LED_BUILTIN;

RiaPushbuttonLite button(BUTTON_PIN, INPUT_PULLUP, LOW, 30);

void setup() {
  pinMode(LED_PIN, OUTPUT);

  Serial.begin(115200);
  while (!Serial) {;}

  button.begin();
}

void loop() {
  bool pressed = button.isPressed();    // 디바운스된 "안정된 눌림" 상태

  digitalWrite(LED_PIN, pressed ? HIGH : LOW);

  delay(10);
}
```

## API Reference
```cpp
RiaPushbuttonLite(uint8_t pin,
                  uint8_t mode = INPUT_PULLUP,
                  uint8_t pressedLevel = LOW,
                  unsigned long debounceMs = 30);
```
* `pin` : 버튼이 연결된 디지털 핀 번호
* `mode` : pinMode()에 들어가는 모드 (예: INPUT, INPUT_PULLUP)
* `pressedLevel` : “버튼이 눌렸을 때의 핀 레벨”
  * 풀업 스위치(눌리면 GND) → LOW
  * 풀다운 스위치(눌리면 VCC) → HIGH
* `debounceMs` : 디바운스에 사용할 시간(ms)
  * 보통 10 ~ 30ms 사이를 권장
