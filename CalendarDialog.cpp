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

#include <QMenu>
#include <QDate>
#include <QMessageBox>
#include <QTimer>
#include <QSettings>

CalendarDialog::CalendarDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CalendarDialog)
{
    ui->setupUi(this);

    this->setFixedSize(640, 480);
    this->setWindowFlags(this->windowFlags() | Qt::MSWindowsFixedSizeDialogHint);
    setWindowModality(Qt::WindowModal); //This dialog shouldn't be modal at all, this is for fun only!

    QFont calFont = this->font();
    calFont.setPointSize(calFont.pointSize() * 4 / 3);
    ui->widCal->setFont(calFont);
    connect(ui->widCal, SIGNAL(monthChanged(int,int)), this, SLOT(monthChanged(int,int)));

    //Make the drop options button square-shaped
    this->ensurePolished();
    ui->btnDropOptions->setFixedWidth(ui->btnDropOptions->sizeHint().height());

    setTodayText("text-decoration: none;");
    m_emphTimer = new QTimer(this);
    m_emphTimer->setInterval(EmphTimerInterval);

    loadSettings();
}

CalendarDialog::~CalendarDialog()
{
    delete ui;
}

void CalendarDialog::closeEvent(QCloseEvent*)
{
    saveSettings();
}

void CalendarDialog::on_btnAccept_clicked()
{
    accept();
}

void CalendarDialog::on_lblTodayDate_linkActivated(const QString& link)
{
    Q_UNUSED(link)
    ui->widCal->today();
}

void CalendarDialog::on_btnDropOptions_clicked()
{
    ui->btnDropOptions->setCheckable(true);
    ui->btnDropOptions->setChecked(true);

    QMenu optionsMenu("Options");

    QAction* a_showGregorian = new QAction(u("نمایش تاریخ میلادی"), &optionsMenu);
    a_showGregorian->setCheckable(true);
    a_showGregorian->setChecked(ui->widCal->settings.showGregorianDates);
    connect(a_showGregorian, SIGNAL(triggered()), this, SLOT(toggleShowGregorianDates()));

    optionsMenu.addActions(QList<QAction*>() << a_showGregorian);
    optionsMenu.addSeparator();
    optionsMenu.addAction(u("درباره..."), this, SLOT(showAbout()));

    QPoint pos = ui->btnDropOptions->mapToGlobal(ui->btnDropOptions->rect().bottomLeft());
    optionsMenu.exec(pos);

    //Menu executing is synchronous, i.e the exec call above blocks.
    ui->btnDropOptions->setChecked(false);
    ui->btnDropOptions->setCheckable(false);
}

void CalendarDialog::monthChanged(int active_j_y, int active_j_m)
{
    int j_y, j_m, j_d;
    Ct::Date::PersianDate::GregorianToJalali(QDate::currentDate(), j_y, j_m, j_d);

    if (j_y == active_j_y && j_m == active_j_m)
        return; //User has come back to the current month.

    setTodayText("color: red; text-decoration: underline;");

    //Stop previous blinking, if it is.
    m_emphTimer->stop();
    disconnect(m_emphTimer, SIGNAL(timeout()), 0, 0);

    //start the new blinking
    emphRemaining = 5; //Must be an odd number to end up with no emphasis
    connect(m_emphTimer, SIGNAL(timeout()), this, SLOT(toggleTodayEmphasis()));
    m_emphTimer->start();
}

void CalendarDialog::toggleTodayEmphasis()
{
    //Uses default color for links, i.e color: blue;
    setTodayText(emphRemaining % 2 == 0
                 ? "text-decoration: underline;"
                 : "text-decoration: none;");

    if (--emphRemaining == 0)
        m_emphTimer->stop();
}

void CalendarDialog::setTodayText(const QString& style)
{
    ui->lblTodayDate->setText(u("<strong>امروز: <a style=\"") + style + u("\" href=\"0\">%1</a></strong>")
                              .arg(Ct::Date::PersianDate::fullPersianDate(QDate::currentDate())));
}

void CalendarDialog::loadSettings()
{
    QSettings sets(qApp->organizationName(), qApp->applicationName());
    ui->widCal->settings.showGregorianDates = sets.value("showgregorian", true).toBool();
}

void CalendarDialog::saveSettings()
{
    QSettings sets(qApp->organizationName(), qApp->applicationName());
    sets.setValue("showgregorian", ui->widCal->settings.showGregorianDates);
}

void CalendarDialog::toggleShowGregorianDates()
{
    ui->widCal->settings.showGregorianDates = !ui->widCal->settings.showGregorianDates;
    ui->widCal->calculateDrawMonthUpdate();
}

void CalendarDialog::showAbout()
{
    QMessageBox::information(this, u("درباره"),
     u("<strong>روزشمار پارسی</strong>"
       "<br/>نگارش 1‌/‌1"
       "<br/>ساخته‌ی <span style=\"font-family: Tahoma, sans-serif; font-size: 12pt\">"
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
