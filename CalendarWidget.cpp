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

#include "CalendarWidget.h"

#include "CtCommon.h"
#include "CtDate.h"

#include <QDate>
#include <QtGui/QFont>
#include <QtGui/QPainter>
#include <QtGui/QPushButton>

CalendarWidget::CalendarWidget(QWidget *parent) :
    QWidget(parent)
{
    QDate currentDate = QDate::currentDate();
    Ct::Date::PersianDate::GregorianToJalali(currentDate, realCurrent_j_y, realCurrent_j_m, realCurrent_j_d);

    active_j_y = realCurrent_j_y;
    active_j_m = realCurrent_j_m;



    int hUnit = this->width() / 7;
    int vUnit = this->height() / 7;

    btnPrevMonth = new QPushButton(this);
    btnPrevMonth->setIcon(QIcon(":/res/1rightarrow.png"));
    btnPrevMonth->setToolTip(u("ماه قبل"));
    btnPrevMonth->setGeometry(this->width() - hUnit / 2, 0, hUnit / 2, vUnit);
    int iconDimension = qMin(btnPrevMonth->width(), btnPrevMonth->height()) - 4;
    btnPrevMonth->setIconSize(QSize(iconDimension, iconDimension));
    connect(btnPrevMonth, SIGNAL(clicked()), this, SLOT(prevMonth()));

    btnNextMonth = new QPushButton(this);
    btnNextMonth->setIcon(QIcon(":/res/1leftarrow.png"));
    btnNextMonth->setToolTip(u("ماه بعد"));
    btnNextMonth->setGeometry(0, 0, hUnit / 2, vUnit);
    btnNextMonth->setIconSize(QSize(iconDimension, iconDimension));
    connect(btnNextMonth, SIGNAL(clicked()), this, SLOT(nextMonth()));
}

void CalendarWidget::resizeEvent(QResizeEvent*)
{
    int hUnit = this->width() / 7;
    int vUnit = this->height() / 7;

    btnPrevMonth->setGeometry(this->width() - hUnit / 2, 0, hUnit / 2, vUnit);
    btnNextMonth->setGeometry(0, 0, hUnit / 2, vUnit);

    int iconDimension = qMin(btnPrevMonth->width(), btnPrevMonth->height()) - 4;
    btnPrevMonth->setIconSize(QSize(iconDimension, iconDimension));
    btnNextMonth->setIconSize(QSize(iconDimension, iconDimension));
}

void CalendarWidget::paintEvent(QPaintEvent* event)
{
    QWidget::paintEvent(event);
    QPainter p(this);

    bool realCurrentMonth = (active_j_y == realCurrent_j_y && active_j_m == realCurrent_j_m);
    drawMonth(p, active_j_y, active_j_m, realCurrentMonth ? realCurrent_j_d : 0);
}

void CalendarWidget::drawMonth(QPainter& p, int j_y, int j_m, int j_d)
{
    p.setPen(Qt::black);

    int hUnit = this->width() / 7;
    int vUnit = this->height() / 7;

    QString title = Ct::Date::PersianDate::nameOfMonth(j_m) + " " + QString::number(j_y);
    QRect titleRect(0, 0, this->width(), vUnit);
    titleRect.adjust(1, 1, -1, -1);
    p.fillRect(titleRect, QColor(64, 128, 255));
    QFont boldFont = this->font();
    boldFont.setBold(true);
    p.setFont(boldFont);
    p.drawText(titleRect, Qt::AlignCenter, title);
    p.setFont(this->font());

    for (int i = 0; i < 7; i++)
    {
        QRect cellRect((6 - i) * hUnit, vUnit, hUnit, vUnit);
        cellRect.adjust(1, 1, -1, -1);
        if (i == 6)
            p.fillRect(cellRect, QColor(96, 160, 255));
        else
            p.fillRect(cellRect, QColor(128, 192, 255));
        p.drawText(cellRect, Qt::AlignCenter, Ct::Date::PersianDate::nameOfPersianWeekDay(i + 1));
    }

    QDate firstDayOfJalaliMonth;
    Ct::Date::PersianDate::JalaliToGregorian(firstDayOfJalaliMonth, j_y, j_m, 1);

    int hPos = 0;
    int vPos = 2;

    int mapWeekStartDayFromMondayToSaturday[] = { 0, 3, 4, 5, 6, 7, 1, 2 };
    int PersianWeekStartDay = mapWeekStartDayFromMondayToSaturday[firstDayOfJalaliMonth.dayOfWeek()];
    hPos = PersianWeekStartDay - 1;

    int modFridays = (8 - PersianWeekStartDay) % 7;

    int jalaliMonthDayCount = Ct::Date::PersianDate::numberOfDaysInJalaliMonth(j_y, j_m);

    for (int i = 1; i <= jalaliMonthDayCount; i++)
    {
        QRect cellRect((6 - hPos) * hUnit, vPos * vUnit, hUnit, vUnit);
        cellRect.adjust(1, 1, -1, -1);
        if (i % 7 == modFridays)
            p.fillRect(cellRect, QColor(128, 192, 255));
        else
            p.fillRect(cellRect, Qt::white);
        if (i == j_d) //Today
        {
            QPen pen = p.pen();
            p.setPen(QPen(QColor(0, 0, 255), 2));
            p.drawRect(cellRect);
            p.setPen(pen);
        }
        p.drawText(cellRect, Qt::AlignCenter, QString::number(i));

        hPos++;
        if (hPos == 7)
        {
            hPos = 0;
            vPos++;

            if (vPos == 7)
                vPos = 2; //Draw the excess 30th and 31th day in the top row.
        }
    }
}

void CalendarWidget::today()
{
    bool emitMonthChanged = (active_j_y != realCurrent_j_y || active_j_m != realCurrent_j_m);

    active_j_y = realCurrent_j_y;
    active_j_m = realCurrent_j_m;


    update();
    if (emitMonthChanged)
        emit monthChanged(active_j_y, active_j_y);
}

void CalendarWidget::prevMonth()
{
    active_j_m -= 1;
    if (active_j_m == 0)
    {
        active_j_m = 12;
        active_j_y -= 1;
    }

    update();
    emit monthChanged(active_j_y, active_j_y);
}

void CalendarWidget::nextMonth()
{
    active_j_m += 1;
    if (active_j_m == 13)
    {
        active_j_m = 1;
        active_j_y += 1;
    }

    update();
    emit monthChanged(active_j_y, active_j_y);
}
