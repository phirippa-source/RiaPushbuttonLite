#include <RiaPushbuttonLite.h>

// 예: Zumo USER 버튼이 12번 핀, 풀업 스위치(눌리면 GND)
//     - mode = INPUT_PULLUP
//     - pressedLevel = LOW
//     - debounceMs = 30ms
RiaPushbuttonLite button(12, INPUT_PULLUP, LOW, 30);

void setup() {
  Serial.begin(115200);
  button.begin();

  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println("RiaPushbuttonLite SimpleButtonTest start");
}

void loop() {
  // 디바운스된 눌림 상태
  bool pressed = button.isPressed();

  // 눌리면 LED ON, 아니면 OFF
  digitalWrite(LED_BUILTIN, pressed ? HIGH : LOW);

  // 시리얼 모니터 출력 (상태 확인용)
  Serial.print("Button: ");
  Serial.println(pressed ? "PRESSED" : "RELEASED");

  delay(50);
}
