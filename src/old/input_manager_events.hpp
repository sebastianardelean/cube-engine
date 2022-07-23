#pragma once

enum InputManagerEvent : uint8_t {
  Event_NoEvent = 0,
  Event_Quit,
  Event_KeyDown,
  Event_KeyUp,
  Event_MouseMotion,
  Event_MouseButtonDown,
  Event_MouseButtonUp,
  Event_MouseWheelUp,
  Event_MouseWheelDown,
  Event_MouseWheelLeft,
  Event_MouseWheelRight

};

enum MouseButton : uint8_t {
  MouseButton_Left = 0,
  MouseButton_Right,
  MouseButton_Middle
};

struct EventMessage {
  EventMessage() { eventType = Event_NoEvent; }
  EventMessage(const InputManagerEvent event) : eventType(event) {}

  [[nodiscard]] InputManagerEvent GetEventType() const { return eventType; }

protected:
  InputManagerEvent eventType;
};

struct QuitEventMessage : public EventMessage {
  QuitEventMessage() : EventMessage(Event_Quit) {}
};

struct KeyDownEventMessage : public EventMessage {
  KeyDownEventMessage(const int8_t readKey) : EventMessage(Event_KeyDown) {
    key = readKey;
  }

  int8_t key;
};

struct KeyUpEventMessage : public EventMessage {
  KeyUpEventMessage(const int8_t readKey) : EventMessage(Event_KeyUp) {
    key = readKey;
  }

  int8_t key;
};

struct MouseMotionEventMessage : public EventMessage {
  MouseMotionEventMessage(const int32_t posX, const int32_t posY)
      : EventMessage(Event_MouseMotion) {
    x = posX;
    y = posY;
  }
  int32_t x;
  int32_t y;
};

struct MouseButtonDownEventMessage : public EventMessage {
  MouseButtonDownEventMessage(const MouseButton b, const int32_t posX,
                              const int32_t posY)
      : EventMessage(Event_MouseButtonDown) {
    button = b;
    x = posX;
    y = posY;
  }

  MouseButton button;
  int32_t x;
  int32_t y;
};

struct MouseButtonUpEventMessage : public EventMessage {
  MouseButtonUpEventMessage(const MouseButton b, const int32_t posX,
                            const int32_t posY)
      : EventMessage(Event_MouseButtonUp) {
    button = b;
    x = posX;
    y = posY;
  }

  MouseButton button;
  int32_t x;
  int32_t y;
};

struct MouseWheelUpEventMessage : public EventMessage {
  MouseWheelUpEventMessage(const int32_t posY)
      : EventMessage(Event_MouseWheelUp) {
    x = 0;
    y = posY;
  }

  int32_t x;
  int32_t y;
};

struct MouseWheelDownEventMessage : public EventMessage {
  MouseWheelDownEventMessage(const int32_t posY)
      : EventMessage(Event_MouseWheelDown) {
    x = 0;
    y = posY;
  }

  int32_t x;
  int32_t y;
};

struct MouseWheelLeftEventMessage : public EventMessage {
  MouseWheelLeftEventMessage(const int32_t posX)
      : EventMessage(Event_MouseWheelLeft) {
    x = posX;
    y = 0;
  }

  int32_t x;
  int32_t y;
};

struct MouseWheelRightEventMessage : public EventMessage {
  MouseWheelRightEventMessage(const int32_t posX)
      : EventMessage(Event_MouseWheelRight) {
    x = posX;
    y = 0;
  }

  int32_t x;
  int32_t y;
};
