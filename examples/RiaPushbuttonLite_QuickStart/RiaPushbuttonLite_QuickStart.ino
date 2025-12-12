#include <RiaPushbuttonLite.h>
// 버튼(스위치)가 아두이노 12번 핀과 그라운드 사이에 연결되어 있다고 가정
const uint8_t BUTTON_PIN = 12;

// 보드 내장 LED (UNO R4 WiFi, UNO R3 등 대부분 보드에서 동작)
const uint8_t LED_PIN = LED_BUILTIN;

// 버튼(스위치) 회로에 풀다운 또는 풀업 저항이 없다고 가정하고 
// BUTTON_PIN을 INPUT_PULLUP으로 설정, 따라서 버튼 스위치가 눌리면 LOW
// 즉, BUTTON_PIN의 상태가 LOW일 때 버튼(스위치)이 눌린 것으로 판단.
RiaPushbuttonLite button(BUTTON_PIN, INPUT_PULLUP, LOW, 30); // 디바운스를 위해 30ms 설정

void setup() {
  pinMode(LED_PIN, OUTPUT);

  Serial.begin(115200);
  while (!Serial) {
    ; // 시리얼 모니터 연결 대기 (UNO R4 WiFi 등)
  }

  button.begin();

  Serial.println("RiaPushbuttonLite Quick Start");
  Serial.println("버튼을 눌러 내장 LED를 켜보세요.");
}

void loop() {
  // 디바운스가 적용된 안정된 버튼 상태
  bool pressed = button.isPressed();

  // 버튼이 눌려 있으면 LED ON, 아니면 OFF
  digitalWrite(LED_PIN, pressed ? HIGH : LOW);

  // 상태를 시리얼로 출력 (디버깅용)
  Serial.print("Button: ");
  Serial.println(pressed ? "PRESSED" : "RELEASED");

  delay(10);  // 너무 빠른 출력 방지용 (디바운스와는 별개)
}
