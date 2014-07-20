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

#include <QApplication>
#include <CalendarDialog.h>
#include <QFontDatabase>

bool AddApplicationFont(const QString& fileName)
{
    int result = QFontDatabase::addApplicationFont(fileName);
    return result != -1;
}

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    app.setApplicationName("PersianCalendar");
    app.setOrganizationName("mhazadmanesh");

    AddApplicationFont(":/res/BRoya.ttf");
    AddApplicationFont(":/res/BRoyaBD.ttf");
    QApplication::setLayoutDirection(Qt::RightToLeft);
    QApplication::setFont(QFont("B Roya", 14));

    CalendarDialog dlg;
    dlg.show();

    return app.exec();
}
