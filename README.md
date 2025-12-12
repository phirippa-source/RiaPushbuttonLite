# RiaPushbuttonLite

A very simple debounced pushbutton helper library for Arduino.  
아주 단순한, 교육용으로 쓰기 좋은 **디바운스 포함 버튼 헬퍼 라이브러리**입니다.

- Author: Seongpil Kim (phirippa)  
- Purpose: Education / beginner-friendly button handling

---

## Features
https://github.com/phirippa-source/RiaPushbuttonLite/tree/main
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

    #include <RiaPushbuttonLite.h>
    
    const uint8_t BUTTON_PIN = 12;
    const uint8_t LED_PIN    = LED_BUILTIN;
    
    // 풀업 스위치(눌리면 GND), 눌림 레벨 LOW, 디바운스 30ms
    RiaPushbuttonLite button(BUTTON_PIN, INPUT_PULLUP, LOW, 30);
    
    void setup() {
      pinMode(LED_PIN, OUTPUT);
    
      Serial.begin(115200);
      while (!Serial) {;}
    
      button.begin();
    }
    
    void loop() {
      // 디바운스가 적용된 "안정된 눌림" 상태
      bool pressed = button.isPressed();
    
      digitalWrite(LED_PIN, pressed ? HIGH : LOW);
    
      delay(10);  // 너무 빠른 시리얼 출력 방지용
    }

---

## API Reference

### Constructor

    RiaPushbuttonLite(uint8_t pin,
                      uint8_t mode = INPUT_PULLUP,
                      uint8_t pressedLevel = LOW,
                      unsigned long debounceMs = 30);

- `pin` : 버튼이 연결된 디지털 핀 번호  
- `mode` : `pinMode()`에 들어가는 모드 (예: `INPUT`, `INPUT_PULLUP`)  
- `pressedLevel` : “버튼이 눌렸을 때의 핀 레벨”
  - 풀업 스위치(눌리면 GND) → `LOW`
  - 풀다운 스위치(눌리면 VCC) → `HIGH`
- `debounceMs` : 디바운스에 사용할 시간(ms)  
  - 보통 10 ~ 30ms 사이를 권장

---

### `void begin()`

    void begin();

- 내부에서 `pinMode(pin, mode);`를 호출하고  
- 디바운스 관련 내부 상태를 초기화합니다.  
- **반드시 `setup()`에서 한 번 호출**해야 합니다.

예:

    void setup() {
      Serial.begin(115200);
      button.begin();
    }

---

### `bool readRaw()`

    bool readRaw();

- 디바운스 없이 “지금 당장 눌렸는지”를 반환합니다.
- 반환 값:
  - `true`  : 현재 읽은 핀 레벨이 `pressedLevel`과 같음 (눌림)
  - `false` : 그 외 (눌리지 않음)
- 채터링(입력 튀는 현상)을 그대로 볼 수 있기 때문에
  - 디버깅용
  - 디바운스 전/후 비교 학습용으로 유용합니다.

예:

    void loop() {
      bool raw = button.readRaw();
      Serial.println(raw ? "RAW PRESSED" : "RAW RELEASED");
      delay(10);
    }

---

### `bool isPressed()`

    bool isPressed();

- 디바운스가 적용된 **“안정된 눌림 상태”**를 반환합니다.
- 버튼 입력이 `debounceMs` 동안 일정하게 유지되어야 상태가 바뀝니다.
- 보통 `loop()` 안에서 바로

    if (button.isPressed()) {
      // 버튼이 "안정적으로 눌려 있는" 상태일 때 실행할 코드
    }

처럼 사용하는 것을 권장합니다.

예:

    void loop() {
      if (button.isPressed()) {
        digitalWrite(LED_BUILTIN, HIGH);
      } else {
        digitalWrite(LED_BUILTIN, LOW);
      }
    }

---

## Examples

Arduino IDE에서:

- **File → Examples → RiaPushbuttonLite → RiaPushbuttonLite_QuickStart**

---

## License

(원하는 라이선스를 명시하세요. 예: MIT, Apache-2.0 등)

예:

    MIT License
    Copyright (c) 2025 Seongpil Kim
    ...

---

## Version History

- **v0.1.1** – 초기 공개 버전, Arduino Library Manager 등록용  
- (필요에 따라 이후 변경 사항 추가)
