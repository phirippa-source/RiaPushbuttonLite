#include <RiaPushbuttonLite.h>

// 예: 버튼(스위치)이 12번 핀에 연결되었다고 가정, 버튼(스위치)가 풀업 회로로 구성되었다고 가정했을 때
// 눌리면 GND, LOW / 누르지 않으면 Vcc, HIGH
//     - mode = INPUT_PULLUP
//     - pressedLevel = LOW
//     - debounceMs = 30ms     
// debouncdMs의 값은 버튼(스위치)의 특성에 따라 30ms 보다 작게 설정할 수 있음.
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
