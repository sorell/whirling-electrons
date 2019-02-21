class SoftTimer
{
public:
    static unsigned int const INFINITE = -1;
    static unsigned int const STOPPED = 0;
    static unsigned int const ONESHOT = 1;

    SoftTimer() {}
    SoftTimer(unsigned long const periodMs, unsigned int const shots = INFINITE) { init(periodMs, shots); }
    ~SoftTimer() {}
    
    void init(unsigned long const periodMs, unsigned int const shots = INFINITE) { 
        _periodMs = periodMs;
        reinit(shots);
    }

    void reinit(unsigned int const shots = INFINITE) {
        _shots = shots;
        _nextTrigMs = millis() + _periodMs;
    }

    int hasExpired(void) {
        if (_shots > 0) {
            if ((int) millis() - (int) _nextTrigMs >= 0) {
                if (_shots != INFINITE) {
                    _shots--;
                }
                _nextTrigMs += _periodMs;
                return 1;
            }
        }
        return 0;
    }

    void stop(void) { _shots = 0; }

    int shotsLeft(void) const { return _shots; }

    void addShots(unsigned int const shots) { _shots += shots; }

private:
    unsigned int _shots;
    unsigned long _periodMs;
    unsigned long _nextTrigMs;
};
