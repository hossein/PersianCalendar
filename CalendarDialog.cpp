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

#include "CalendarDialog.h"
#include "ui_CalendarDialog.h"

#include "CalendarWidget.h"
#include "CtCommon.h"
#include "CtDate.h"

#include <QDate>
#include <QMessageBox>
#include <QTimer>

CalendarDialog::CalendarDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CalendarDialog)
{
    ui->setupUi(this);

    this->setFixedSize(640, 480);
    this->setWindowFlags(this->windowFlags() | Qt::MSWindowsFixedSizeDialogHint);
    setWindowModality(Qt::WindowModal); //This dialog shouldn't be modal at all, this is for fun only!

    setTodayText("text-decoration: none;");

    int indexToInsert = ui->vlMain->indexOf(ui->widCalendarWidget);
    ui->vlMain->removeWidget(ui->widCalendarWidget);

    QFont calFont = this->font();
    calFont.setPointSize(calFont.pointSize() * 4 / 3);

    widCal = new CalendarWidget(this);
    widCal->setFont(calFont);
    ui->vlMain->insertWidget(indexToInsert, widCal, 1);
    connect(widCal, SIGNAL(monthChanged(int,int)), this, SLOT(monthChanged(int,int)));
}

CalendarDialog::~CalendarDialog()
{
    delete ui;
}

void CalendarDialog::on_btnAccept_clicked()
{
    accept();
}

void CalendarDialog::on_lblTodayDate_linkActivated(const QString& link)
{
    Q_UNUSED(link)
    widCal->today();
}

void CalendarDialog::on_btnAbout_clicked()
{
    QMessageBox::information(this, u("درباره"),
     u("<strong>روزشمار پارسی</strong><br/>ساخته‌ی "
       "<span style=\"font-family: Tahoma, sans-serif; font-size: 12pt\">"
       "<a href=\"mailto:mhazadmanesh2009@gmail.com\">mhazadmanesh2009@gmail.com</a>"
       "</span>"

       "<div dir=\"ltr\" style=\"font-family: Tahoma, sans-serif; font-size: 10pt\"><br/>"
       "Persian Calendar, simple Persian calendar<br/>"
       "Copyright (C) 2014 mhazadmanesh2009@gmail.com<br/>"
       "<br/>"
       "This program is free software: you can redistribute it and/or modify<br/>"
       "it under the terms of the GNU General Public License as published by<br/>"
       "the Free Software Foundation, either version 3 of the License, or<br/>"
       "(at your option) any later version.<br/>"
       "<br/>"
       "This program is distributed in the hope that it will be useful,<br/>"
       "but WITHOUT ANY WARRANTY; without even the implied warranty of<br/>"
       "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the<br/>"
       "GNU General Public License for more details.<br/>"
       "<br/>"
       "You should have received a copy of the GNU General Public License"
       "along with this program.  If not, see <a href=\"http://www.gnu.org/licenses/\">"
       "http://www.gnu.org/licenses/</a>."
       "<br/></div>"));
}

void CalendarDialog::monthChanged(int out_active_j_y, int out_active_j_m)
{
    //int j_y, j_m, j_d;
    //if Ct::Date::PersianDate::GregorianToJalali()
    setTodayText("color: red; text-decoration: underline;");

    emphRemaining = 6; //Must be even to end up with no emphasis
    QTimer::singleShot(EmphTimerInterval, this, SLOT(todayEmphasisOn()));
}

void CalendarDialog::todayEmphasisOn()
{
    setTodayText("text-decoration: underline;"); //Uses default color for links, i.e color: blue;

    if (--emphRemaining > 0)
        QTimer::singleShot(EmphTimerInterval, this, SLOT(todayEmphasisOff()));
}

void CalendarDialog::todayEmphasisOff()
{
    setTodayText("text-decoration: none;"); //Uses default color for links, i.e color: blue;

    if (--emphRemaining > 0)
        QTimer::singleShot(EmphTimerInterval, this, SLOT(todayEmphasisOn()));
}

void CalendarDialog::setTodayText(const QString& style)
{
    ui->lblTodayDate->setText(u("<strong>امروز: <a style=\"") + style + u("\" href=\"0\">%1</a></strong>")
                              .arg(Ct::Date::PersianDate::fullPersianDate(QDate::currentDate())));
}
