/******************************************************************************

Persian Calendar, simple Persian calendar
Copyright (C) 2014 GitHub user "Hossein"

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

******************************************************************************/

#include "CtDate.h"

#include "CtCommon.h"

extern "C" {
void gregorian_to_jalali(int *j_y, int *j_m, int *j_d, int  g_y, int  g_m, int  g_d);
void jalali_to_gregorian(int *g_y, int *g_m, int *g_d, int  j_y, int  j_m, int  j_d);
}

namespace Ct {
namespace Date {

const char PersianDate::daysInMonth_Jalali[13] =     { 0,
                                                       31, 31, 31, 31, 31, 31,
                                                       30, 30, 30, 30, 30, 29 };

const char PersianDate::daysInMonth_LeapJalali[13] = { 0,
                                                       31, 31, 31, 31, 31, 31,
                                                       30, 30, 30, 30, 30, 30 };

const int PersianDate::JalaliLeapYears_33YearModel[33] =
                                      { 0, 1, 0, 0, 0,   //   0 [ 1]  2   3   4
                                        1, 0, 0, 0, 1,   // [ 5]  6   7   8 [ 9]
                                        0, 0, 0, 1, 0,   //  10  11  12 [13] 14
                                        0, 0, 1, 0, 0,   //  15  16 [17] 18  19
                                        0, 0, 1, 0, 0,   //  20  21 [22] 23  24
                                        0, 1, 0, 0, 0,   //  25 [26] 27  28  29
                                        1, 0, 0       }; // [30] 31  32

void PersianDate::GregorianToJalali(const QDate& date, int& y, int& m, int& d)
{
    gregorian_to_jalali(&y, &m, &d, date.year(), date.month(), date.day());
}

void PersianDate::JalaliToGregorian(QDate& date, int y, int m, int d)
{
    int g_y, g_m, g_d;
    jalali_to_gregorian(&g_y, &g_m, &g_d, y, m, d);
    date = QDate(g_y, g_m, g_d);
}

bool PersianDate::isJalaliDateValid(int y, int m, int d)
{
    if (m < 1 || m > 12)
        return false;

    if (d < 1 || d > daysInMonth_LeapJalali[m])
        return false;

    if (!isJalaliDateInRange(y, m, d))
        return false;

    if (m == 12 && d == 30 && JalaliLeapYears_33YearModel[y % 33] != 1)
        return false;

    return true;
}

int PersianDate::numberOfDaysInJalaliMonth(int y, int m)
{
    if (m < 1 || m > 12 || y < 0 || y > 9999)
        return 0;

    if (JalaliLeapYears_33YearModel[y % 33])
        return daysInMonth_LeapJalali[m];
    else
        return daysInMonth_Jalali[m];
}

bool PersianDate::isJalaliDateInRange(int y, int m, int d)
{
    Q_UNUSED(m)
    Q_UNUSED(d)
    //Match from 1279/01/01 to 1473/12/29
    if (y < 1279 || y > 1473)
        return false;
    return true;
}

bool PersianDate::isGregorianDateInRange(const QDate& date)
{
    //Match from 1900/03/01 to 2094/12/31
    if (date < QDate(1900, 3, 1) || date > QDate(2094, 12, 31))
        return false;
    return true;
}

int PersianDate::suggestedLowPersianYear()
{
    return 1370; //Instead of 1279; to make the program dates more modern.
}

int PersianDate::suggestedHighPersianYear()
{
    return 1473;
}

QString PersianDate::nameOfWeekDay(int day)
{
    QString daysOfWeek[] = { QString(), u("دوشنبه"), u("سه‌شنبه"), u("چهارشنبه"),
                             u("پنج‌شنبه"), u("جمعه"), u("شنبه"), u("یک‌شنبه") };
    return daysOfWeek[day];
}

QString PersianDate::nameOfPersianWeekDay(int day)
{
    QString daysOfWeek[] = { QString(),  u("شنبه"), u("یک‌شنبه"), u("دوشنبه"),
                             u("سه‌شنبه"), u("چهارشنبه"), u("پنج‌شنبه"), u("جمعه"), };
    return daysOfWeek[day];
}

QString PersianDate::nameOfMonth(int month)
{
    QString months[] = { QString(),
                         u("فروردین"), u("اردیبهشت"), u("خرداد"), u("تیر"), u("مرداد"), u("شهریور"),
                         u("مهر"), u("آبان"), u("آذر"), u("دی"), u("بهمن"), u("اسفند") };
    return months[month];
}

QString PersianDate::fullPersianDate(const QDate& date)
{
    int j_y, j_m, j_d;
    Ct::Date::PersianDate::GregorianToJalali(date, j_y, j_m, j_d);

    return nameOfWeekDay(date.dayOfWeek()) + " " + QString::number(j_d) + " " +
           nameOfMonth(j_m) + u("‌ماه ") + QString::number(j_y);
}

QString PersianDate::persianNumericTime(const QTime& time)
{
    int h = time.hour();
    QString hours = QString(h < 10 ? "0" : "") + QString::number(h);

    int m = time.minute();
    QString minutes = QString(m < 10 ? "0" : "") + QString::number(m);

    return hours + ":" + minutes;
}

} // namespace Date
} // namespace Ct
