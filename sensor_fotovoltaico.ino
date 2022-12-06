// C++ code
//
int fotodiodo = 0;

void setup()
{
  pinMode(A0, INPUT);
  Serial.begin(9600);
}

void loop()
{
  while (1 == 1) {
    fotodiodo = analogRead(A0);
    Serial.println(analogRead(A0));
  }
  delay(10); // Delay a little bit to improve simulation performance
}