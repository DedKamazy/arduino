#include <Arduino.h>

#include <MsTimer2.h>

#include <TM1637.h>

TM1637 disp(3, 2);

int data[4] = {1, 2, 3, 0};
bool point = true;

unsigned long timestat = 0; //Начало отсчета до смены секунды
unsigned long timesys = 0;  //Системное время
int timespeed = 100;        //?Скорость смены секунды поменять на 1000
bool runsys = true;
void setup()
{
  
  disp.init();
  disp.set(3);
  void timerInterrupt(); //!Без этой хубалды ругаеться в настройке Timer2
  disp.clearDisplay();
  MsTimer2::set(100, timerInterrupt); // Перерисовывать дисплей будет каждые 100 мили сек
  MsTimer2::start();
  timestat = (timesys = millis()) + timespeed;
}

void loop()
{

  if (timestat <= timesys && runsys == true)
  {
    timestat = (timesys = millis()) + timespeed;
    point = !point;

    if (data[3] == 0)
    {
      data[3] = 9;

      if (data[2] == 0)
      {
        data[2] = 5;

        if (data[1] == 0)
        {
          data[1] = 9;

          if (data[0] == 0)
          {
          }
          else
          {
            data[0] = data[0] - 1;
          }
        }
        else
        {
          data[1] = data[1] - 1;
        }
      }
      else
      {
        data[2] = data[2] - 1;
      }
    }
    else
    {
      data[3] = data[3] - 1;
    }
  }

  if (data[0] == 0 && data[1] == 0 && data[2] == 0 && data[3] == 0)
    runsys = false;
}

void timerInterrupt() //*Вывод информации на дисплей.
{
  timesys = millis();
  disp.clearDisplay();
  disp.point(point);
  disp.display(0, data[0]);
  disp.display(1, data[1]);
  disp.display(2, data[2]);
  disp.display(3, data[3]);
}