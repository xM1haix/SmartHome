#include <output_helper.h>

class JoyStick
{
private:
        static JoyStick *instance;
        int _pinX;
        int _pinY;
        int _pinSW;
        int _lastX, _lastY;
        bool _lastSW;
        OutputHelper *_outputHelper = OutputHelper::getInstance();
        JoyStick(int pin_x, int pin_y, int pin_sw)
        {
                _pinX = pin_x;
                _pinY = pin_y;
                _pinSW = pin_sw;
                pinMode(_pinX, INPUT);
                pinMode(_pinY, INPUT);
                pinMode(_pinSW, INPUT_PULLUP);
                _lastX = 0;
                _lastY = 0;
                _lastSW = false;
        }

        int _getValue(int pin)
        {
                int value = analogRead(pin) - 2047;
                if (value < -200)
                        return -1;
                else if (value > 200)
                        return 1;
                else
                        return 0;
        }

public:
        JoyStick(const JoyStick &) = delete;
        JoyStick &operator=(const JoyStick &) = delete;

        static JoyStick *getInstance()
        {
                if (instance == nullptr)
                        instance = new JoyStick(39, 36, 21);
                return instance;
        }

        int getX()
        {
                return _getValue(_pinX);
        }

        int getY()
        {
                return _getValue(_pinY);
        }

        bool getSW()
        {
                return !digitalRead(_pinSW);
        }
        void onUpdate()
        {
                int x = getX();
                int y = getY();
                bool sw = getSW();
                if (x != _lastX || y != _lastY || sw != _lastSW)
                {
                        _lastX = x;
                        _lastY = y;
                        _lastSW = sw;
                        _outputHelper->sendMSG("{x:" + String(x) + ", y:" + String(y) + ", sw:" + String(sw) + "}");
                }
        }
};
