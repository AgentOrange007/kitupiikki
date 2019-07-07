/*
   Copyright (C) 2019 Arto Hyvättinen

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
#ifndef TOSITE_H
#define TOSITE_H


#include <QObject>
#include <QVariant>
#include <map>

class TositeViennit;

/**
 * @brief Kirjanpitotosite
 */
class Tosite : public QObject
{
    Q_OBJECT
public:
    enum Avain {
        ID,
        PVM,
        TYYPPI,
        TILA,
        TUNNISTE,
        OTSIKKO,
        VIITE,
        ERAPVM,
        TOIMITTAJA,
        ASIAKAS,
        INFO
    };

    explicit Tosite(QObject *parent = nullptr);

    QVariant data(int kentta) const;
    void setData(int kentta, QVariant arvo);

    TositeViennit* viennit() { return viennit_; }

signals:

public slots:
    void lataa(QVariant *variant);

private:
    QVariantMap data_;
    TositeViennit* viennit_;

    static std::map<int,QString> avaimet__;
};

#endif // TOSITE_H
