/*
   Copyright (C) 2018 Arto Hyvättinen

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef MYYNTIRAPORTTI_H
#define MYYNTIRAPORTTI_H


#include "raportti.h"

namespace Ui {
    class TaseErittely;
}

/**
 * @brief Myyntiraportin kirjoittaminen
 */
class MyyntiRaportti : public Raportti
{
public:
    MyyntiRaportti();
    ~MyyntiRaportti();

    RaportinKirjoittaja raportti();

    /**
     * @brief Kirjoittaa myyntiraportin
     * @param mista Pvm alkaen
     * @param mihin Pvm saakka
     * @param summat Tulostetaanko lopuksi summarivi
     * @return
     */
    static RaportinKirjoittaja kirjoitaRaportti(QDate mista, QDate mihin, bool summat = true);

protected:
    Ui::TaseErittely *ui;
};

#endif // MYYNTIRAPORTTI_H
