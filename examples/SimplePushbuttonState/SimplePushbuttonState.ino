#include <RiaPushbuttonLite.h>

// 예: 2번 핀, 풀다운 스위치(눌리면 Vcc:HIGH)
//     - mode = INPUT
//     - pressedLevel = HIGH
//     - debounceMs = 20ms
unsigned int debounceMs = 20;
RiaPushbuttonLite button(2, INPUT, HIGH, debounceMs);

void setup() {
  Serial.begin(115200);
  button.begin();

  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println("RiaPushbuttonLite SimpleButtonTest start");
}

void loop() {
  // 디바운스된 눌림 상태
  int btn_state = button.isPressed();
  digitalWrite(LED_BUILTIN, btn_state);
  
  // 시리얼 모니터 출력 (상태 확인용)
  Serial.println(btn_state ? "btn state = HIGH" : "stn state = LOW");

  delay(50);
}
