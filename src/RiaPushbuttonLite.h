#ifndef RIA_PUSHBUTTON_LITE_H
#define RIA_PUSHBUTTON_LITE_H

#include <Arduino.h>

// 아주 단순한 "눌렸냐?" 전용 버튼 라이브러리 (디바운스 포함)
class RiaPushbuttonLite {
public:
  // pin         : 버튼이 연결된 핀 번호
  // mode        : pinMode에 사용할 모드 (기본값: INPUT_PULLUP)
  // pressedLevel: "눌렸을 때의 핀 레벨" (LOW 또는 HIGH)
  //               - 기본값 LOW: 풀업 스위치(눌리면 GND)와 잘 맞음
  // debounceMs  : 디바운스 시간(ms), 기본 30ms
  RiaPushbuttonLite(uint8_t pin,
                    uint8_t mode = INPUT_PULLUP,
                    uint8_t pressedLevel = LOW,
                    unsigned long debounceMs = 30);

  // 핀 모드 설정 및 내부 상태 초기화
  void begin();

  // 디바운스 없이 "지금 당장 눌렸냐?"를 반환
  // - true  : 현재 읽은 핀 레벨이 pressedLevel과 같음 (눌림)
  // - false : 눌리지 않음
  bool readRaw();

  // 디바운스 처리된 "안정된 눌림 상태"를 반환
  // - true  : 일정 시간(debounceMs) 이상 "눌린 상태"가 유지됨
  // - false : 그렇지 않음
  bool isPressed();

private:
  uint8_t _pin;
  uint8_t _mode;
  bool    _pressedLevel;     // "눌렸을 때 레벨": false=LOW, true=HIGH
  unsigned long _debounceMs; // 디바운스 기준 시간(ms)

  // 디바운스용 내부 상태
  bool _lastReading;         // 마지막으로 읽은 (raw pressed) 상태
  bool _stableState;         // 디바운스된 "안정된 pressed 상태"
  unsigned long _lastDebounceTime; // 마지막으로 값이 변했다고 본 시각(ms)
};

#endif // RIA_PUSHBUTTON_LITE_H




