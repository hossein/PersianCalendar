PersianCalendar
===============

<h2 dir="rtl">روزشمار پارسی</h2>
<p dir="rtl">این یک تقویم ساده هجری شمسی (جلالی) است. صرفاً تقویم نمایش داده می‌شود و با زدن دکمه‌های چپ و راست بالای پنجره به ماه قبل و بعد می‌روید. با کلیک روی تاریخ امروز به ماه و سال جاری برمی‌گردید.</p>

<p dir="rtl">امکاناتی نظیر نمایش مناسبت‌ها، تنظیم یادداشت و قرار ملاقات‌ها و تبدیل به تاریخ میلادی وجود ندارد. <strong>با این وجود</strong> این تقویم با داشتن دکمه‌ها و متون درشت و پشتیبانی از HiDPI می‌تواند روی تبلت‌های x86 مورد استفاده قرار بگیرد.</p>

<p dir="rtl">نسخه ویندوزی این تقویم که وابستگی اضافی و نیاز به نصب ندارد را از <a href="https://github.com/hossein/PersianCalendar/releases/tag/v1.0">اینجا</a> می‌توانید بگیرید.</p>

<p dir="rtl">برای Linux و OSX و هر پلتفرم دیگری که Qt4 پشتیبانی می‌کند، خودتان باید برنامه را با استفاده از Qt بسازید. برای اطلاعات بیشتر در این مورد و لیسانس برنامه  به توضیحیت انگلیسی مراجعه کنید.</p>

English
---
A Very Tiny Persian Calendar in Qt.

This calendar lets you view the Persian/Jalali calendar. Use the buttons on top to navigate to previous/next month. Click on today's date to return back to the current year and month.

This calendar lacks showing national holidays, appointment scheduling and conversions to/from Gregorian calendar.
**However,** its big and clear text and buttons make it easy to use on x86-based tablets.

Releases
---
You can get the Windows executable that doesn't have additional dependencies and doesn't need installation from this repo's Releases (look at the "Releases" link at the top, or click [Here](https://github.com/hossein/PersianCalendar/releases/tag/v1.0)).

For Linux, Apple OSX or other platforms which Qt4 supports you must make it using Qt:

```
$ git clone git://github.com/hossein/PersianCalendar.git
$ cd PersianCalendar
$ qmake
$ make
```

License
---
This program is released under the GNU GPL version 3, or any other later version. See the About dialog or sources for the license.

It uses the [Jalali calendar conversion routines](http://www.farsiweb.info/jalali/jalali.c) from the FarsiWeb project, released under LGPL.

The icons are from Crystal Clear set by Everaldo Coelho, released under LGPL.

The fonts are common Persian fonts.
