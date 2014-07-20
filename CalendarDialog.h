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
#include <QDialog>

class QTimer;

class CalendarWidget;
namespace Ui { class CalendarDialog; }

class CalendarDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit CalendarDialog(QWidget *parent = 0);
    ~CalendarDialog();

protected:
    void closeEvent(QCloseEvent*);
    
private slots:
    void on_btnAccept_clicked();
    void on_lblTodayDate_linkActivated(const QString& link);
    void on_btnDropOptions_clicked();

    void monthChanged(int active_j_y, int active_j_m);
    void toggleTodayEmphasis();
    void setTodayText(const QString& style);

    void loadSettings();
    void saveSettings();

    void toggleShowGregorianDates();
    void showAbout();

private:
    Ui::CalendarDialog *ui;
    CalendarWidget* m_widCal;

    QTimer* m_emphTimer;
    enum { EmphTimerInterval = 300 };
    int emphRemaining;

};
