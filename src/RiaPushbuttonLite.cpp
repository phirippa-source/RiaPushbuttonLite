#include "RiaPushbuttonLite.h"

RiaPushbuttonLite::RiaPushbuttonLite(uint8_t pin,
                                     uint8_t mode,
                                     uint8_t pressedLevel,
                                     unsigned long debounceMs)
  : _pin(pin),
    _mode(mode),
    _pressedLevel(pressedLevel == HIGH), // HIGH면 true, LOW면 false
    _debounceMs(debounceMs),
    _lastReading(false),
    _stableState(false),
    _lastDebounceTime(0)
{
}

void RiaPushbuttonLite::begin() {
  pinMode(_pin, _mode);

  // 시작 시점의 pressed 상태로 내부 상태 초기화
  bool nowPressed = readRaw();
  _lastReading = nowPressed;
  _stableState = nowPressed;
  _lastDebounceTime = millis();
}

// 디바운스 없이 "현재 눌렸는지"를 바로 반환
bool RiaPushbuttonLite::readRaw() {
  // 현재 핀 레벨이 pressedLevel과 같은지 비교
  bool levelIsHigh = (digitalRead(_pin) == HIGH); // true=HIGH, false=LOW

  // pressedLevel(true=HIGH, false=LOW)과 같으면 "눌림"으로 취급
  return (levelIsHigh == _pressedLevel);
}

// 디바운스된 "안정된 눌림 상태"를 반환
bool RiaPushbuttonLite::isPressed() {
  bool reading = readRaw();          // 이번에 새로 읽은 raw pressed 상태
  unsigned long now = millis();

  // 읽은 값이 이전과 다르면 "변경 가능성"이 있다고 보고 시간 기록
  if (reading != _lastReading) {
    _lastReading = reading;
    _lastDebounceTime = now;
  }

  // reading 값이 debounceMs 동안 유지되면 그때 안정된 값으로 인정
  if ((now - _lastDebounceTime) >= _debounceMs) {
    _stableState = _lastReading;
  }

  return _stableState;
}
