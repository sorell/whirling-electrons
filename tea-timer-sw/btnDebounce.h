#ifndef _SS_BTNDEBOUNCE_H
#define _SS_BTNDEBOUNCE_H

class BtnDebounce
{
public:
    static uint8_t constexpr ALLOW_CONT = 0x2;

    BtnDebounce(uint8_t const pin, uint8_t const params, unsigned long const periodMs = 30)
    : _btnState(WAITING), _pin(pin), _periodMs(periodMs), _btnParams(params)
    {
        if (periodMs > 255) {
            // Can't fit over 255 in uint8_t
            while (1);
        }
    }
    
    bool isPressed() { 
        unsigned long const now = millis();
        bool const btnIsActive = digitalRead(_pin) == wantedIo();

        if (_btnState == COOLING) {
            if ((!btnIsActive  ||  allowCont())  &&  expired(now)) {
                _btnState = WAITING;
            }
        }
        else {
            if (_btnState == WAITING) {
                if (btnIsActive) {
                    _btnState = TRIGGERED;
                    _nextTrigMs = now + _periodMs;
                }
            }
            else {  // _btnState == TRIGGERED
                if (!btnIsActive) {
                    _btnState = WAITING;
                }
                else if (expired(now)) {
                    _btnState = COOLING;
                    _nextTrigMs = now + _periodMs;
                    return true;
                }
            }
        }
        return false;
    }

protected:
    bool expired(unsigned long const now) const {
        return (int) (now - _nextTrigMs) > 0;
    }
    bool allowCont() const {
        return _btnParams & ALLOW_CONT;
    }
    uint8_t wantedIo() const {
        return _btnParams & 0x1;
    }

private:
    static uint8_t constexpr WAITING = 0;
    static uint8_t constexpr TRIGGERED = 1;
    static uint8_t constexpr COOLING = 2;

    unsigned long _nextTrigMs;
    uint8_t _btnState;

protected:
    uint8_t const _pin;
    uint8_t const _periodMs;
    uint8_t const _btnParams;
};

#endif  // #ifndef _SS_BTNDEBOUNCE_H

