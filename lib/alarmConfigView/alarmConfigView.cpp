
#include "alarmConfigView.h"
#include "globals.h"
#include "utils.h"
#include "alarm.h"

static bool changedValue = false;

static int hours = alarmTime.hour();
static int minutes = alarmTime.minute();

static void setAlarmConfigDisplay();
static void updateDisplayTime();
static void handleAlarmConfigInputs();

void alarmConfigViewLoop()
{
    if (currentView != currentDisplay)
    {
        lcd.clear();
        hours = alarmTime.hour();
        minutes = alarmTime.minute();
        setAlarmConfigDisplay();
        currentDisplay = currentView;
    }
    handleAlarmConfigInputs();
    updateDisplayTime();
}
void setAlarmConfigDisplay()
{
    lcd.setCursor(0, 0);
    lcd.print("7-");
    lcd.write(0);
    lcd.print("  5-Hrs 3-Min");
    lcd.setCursor(0, 1);
    String horaString = formatTime(hours, minutes);
    lcd.print("  [" + horaString + "]");
    lcd.setCursor(11, 1);
    lcd.print("1-OK");
}

void updateDisplayTime()
{
    if (changedValue)
    {
        lcd.setCursor(3, 1);
        changedValue = false;
        String horaString = formatTime(hours, minutes);
        lcd.print(horaString);
    }
}

void handleAlarmConfigInputs()
{
    if (pressOut(PIN_PAD_7))
    {
        currentView = MENU_VIEW;
    }
    if (pressOut(PIN_PAD_1))
    {
        alarmTime = DateTime(dateTime.year(), dateTime.month(), dateTime.day(), hours, minutes, 0);
        currentView = MENU_VIEW;
    }
    if (pressOut(PIN_PAD_5))
    {
        hours = (hours + 1) % 24;
        changedValue = true;
    }
    if (pressOut(PIN_PAD_3))
    {
        minutes = (minutes + 1) % 60;
        changedValue = true;
    }
};
