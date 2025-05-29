#pragma once

#include <stdint.h>

namespace fizz
{

    class Event
    {
    public:

        enum EventFlag
        {
            None = 0,
            Application = 0x001,
            Window      = 0x002,
            Keyboard    = 0x004,
            Mouse       = 0x008,
            Begin       = 0x010, // Key Press, Window Open, etc.
            End         = 0x020  // Key Release, Window Close, etc.
        };

        // CONSTRUCTOR
        Event() {}

        virtual inline uint32_t GetFlags() const = 0;
        bool HasFlag(const EventFlag& flag) { return (bool)(GetFlags() & flag); }
    };

    // HELPER MACRO
#define __FIZZ_EVENT_FLAGS(x) \
    inline uint32_t GetFlags() const { return (x); }

    class WindowClosedEvent : public Event
    {
    public:
        __FIZZ_EVENT_FLAGS(EventFlag::Window & EventFlag::End)
    };

    class KeyEvent : public Event
    {
        uint32_t m_KeyCode;

    public:
        KeyEvent(const uint32_t& keyCode) : m_KeyCode(keyCode) {}
    };

    class KeyPressedEvent : public KeyEvent
    {
    public:
        KeyPressedEvent(const uint32_t& keyCode) : KeyEvent(keyCode) {}
        __FIZZ_EVENT_FLAGS(EventFlag::Application & EventFlag::Keyboard & EventFlag::Begin)
    };
}
