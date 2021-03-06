#include <Arduino.h>

// this constant won't change.  It's the pin number
// of the sensor's output:
const int trigPin = PA2;
const int echoPin = PA1;

long microsecondsToInches(long microseconds);
long microsecondsToCentimeters(long microseconds);

void setup()
{
    // make sure we start with a high level when the pin is set to output
    digitalWrite(trigPin, HIGH);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    Serial_begin(9600);
}

void loop()
{
    // establish variables for duration of the ping,
    // and the distance result in inches and centimeters:
    long duration, inches, cm;

    // The HC-04 is triggered by a falling edge on the trigger input. The
    // following low period has to be at least 10us long.
    digitalWrite(trigPin, LOW);

    // approx. 450us later the Echo pins gets high. It stays high until the echo
    // is received. Maximum timeout is 200ms (no echo received)
    duration = pulseInLong(echoPin, HIGH, 200000L);
    digitalWrite(trigPin, HIGH);

    // convert the time into a distance
    inches = microsecondsToInches(duration);
    cm = microsecondsToCentimeters(duration);

    Serial_print_u(duration);
    Serial_print_s("us\t");
    Serial_print_u(inches);
    Serial_print_s("in\t");
    Serial_print_u(cm);
    Serial_println_s("cm");

    // maximum is one measurement every 20ms
    delay(100);
}

long microsecondsToInches(long microseconds)
{
    // According to Parallax's datasheet for the PING))), there are
    // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
    // second).  This gives the distance travelled by the ping, outbound
    // and return, so we divide by 2 to get the distance of the obstacle.
    // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
    return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
    // The speed of sound is 340 m/s or 29 microseconds per centimeter.
    // The ping travels out and back, so to find the distance of the
    // object we take half of the distance travelled.
    //
    // The exact value for speed sound depends on the air temperature:
    // v = (331.5 + 0.6*temp/°C) m/s
    // v(temp=20°C) = (331.5 + 0.6*20)m/s = 343.5m/s
    return microseconds / 29 / 2;
}
