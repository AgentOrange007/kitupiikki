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

#ifndef RIVIAPUANALYSAATTORI_H
#define RIVIAPUANALYSAATTORI_H

#include <QDate>
#include <QStringList>

/**
 * @brief Pdf-tiliotteen tuonnin tilioterivin analysaattori
 */
class RiviApuAnalysaattori
{
public:
    RiviApuAnalysaattori();
    void analysoi(QStringList rivi);

    QDate kirjauspvm() const { return kirjauspvm_;}
    QString iban() const { return iban_;}
    QString viite() const { return viite_; }
    QString arkistotunnus() const { return arkistotunnus_; }
    qlonglong maara() const { return maara_; }
    QString selite() const { return selite_;}

protected:
    QDate kirjauspvm_;
    QString iban_;
    QString viite_;
    QString arkistotunnus_;
    qlonglong maara_;
    QString selite_;

};

#endif // RIVIAPUANALYSAATTORI_H
