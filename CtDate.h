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

#pragma once
#include <QDate>

namespace Ct {
namespace Date {

/// Note about calculation range:
/// This is based on Jalali, which matches Microsoft's implementation for the new era.
/// However jdf did not match the other too, possibly because of bad leap year calculation.
/// The range here is the common range that all three accept, or to be more precise, the
/// ranage in which jdf matches the other two.
class PersianDate
{
private:
    static const char daysInMonth_Jalali[13];
    static const char daysInMonth_LeapJalali[13];
    static const int JalaliLeapYears_33YearModel[33];

public:
    /// These two functions don't generate or preserve input times.
    static void GregorianToJalali(const QDate& date, int& y, int& m, int& d);
    static void JalaliToGregorian(QDate& date, int  y, int  m, int  d);

    /// Checks 1. overall validity of date numbers (month between 1 and 12, etc)
    /// 2. if day of month is valid wrt number of days in each month;
    /// 3. whether date is in range this class's backend; and
    /// 4. whether the leap day is actually in a leap year.
    static bool isJalaliDateValid(int y, int m, int d);

    /// Returns number of days in jalali month with regard to year.
    static int numberOfDaysInJalaliMonth(int y, int m);

    /// Checks whether the dates are in acceptable range for conversion by this class's backend.
    static bool isJalaliDateInRange(int y, int m, int d);
    static bool isGregorianDateInRange(const QDate& date);

    /// Suggest a range INCLUSIVE to be thought of as valid persian year values.
    static int suggestedLowPersianYear();
    static int suggestedHighPersianYear();

    /// Return name of different things. THEY BEGIN FROM 1, i.e 1 <= day <= 7 and 1 <= month <= 12.
    static QString nameOfWeekDay(int day);
    static QString nameOfPersianWeekDay(int day);
    static QString nameOfMonth(int month);

    /// Return date/time in persian.
    static QString fullPersianDate(const QDate& date);
    static QString persianNumericTime(const QTime& time);
};

} // namespace Date
} // namespace Ct
