#include <joystick.h>
#include <output_helper.h>

JoyStick *JoyStick::instance = nullptr;
OutputHelper *OutputHelper::instance = nullptr;
OutputHelper *output = OutputHelper::getInstance();
JoyStick *joyStick = JoyStick::getInstance();
void setup()
{
}

void loop()
{
  output->updateCounter();
  joyStick->onUpdate();
  delay(100);
}
