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
#include <QWidget>
#include <QPixmap>

class QPushButton;

class CalendarWidget : public QWidget
{
    Q_OBJECT

private:
    QPushButton* btnPrevMonth;
    QPushButton* btnNextMonth;

    QPixmap monthPixmap;
    qint64 datestamps[7][7];

    int realCurrent_j_y;
    int realCurrent_j_m;
    int realCurrent_j_d;

    int active_j_y;
    int active_j_m;

public:
    explicit CalendarWidget(QWidget *parent = 0);

    struct CalendarWidgetSettings
    {
        CalendarWidgetSettings() : showGregorianDates(true) { }
        bool showGregorianDates;
    } settings;
    
protected:
    void resizeEvent(QResizeEvent*);
    void showEvent(QShowEvent*);
    void paintEvent(QPaintEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

    void calculateAndDrawMonth(int j_y, int j_m, int j_d);

public slots:
    void calculateDrawMonthUpdate();

    void today();
    void prevMonth();
    void nextMonth();

signals:
    void monthChanged(int active_j_y, int active_j_m);
};
