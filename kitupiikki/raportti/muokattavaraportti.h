/*
   Copyright (C) 2017 Arto Hyvättinen

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

#ifndef MUOKATTAVARAPORTTI_H
#define MUOKATTAVARAPORTTI_H


#include "raportti.h"
#include "ui_muokattavaraportti.h"

#include "raportoija.h"

/**
 * @brief Muokattavien Tase/Tulosraporttien tulostaminen
 *
 */
class MuokattavaRaportti : public Raportti
{
    Q_OBJECT
public:
    MuokattavaRaportti(const QString& raporttinimi);
    ~MuokattavaRaportti();

    RaportinKirjoittaja raportti() override;


public slots:
    void paivitaUi();

protected:
    Ui::MuokattavaRaportti *ui;   
    QString raporttiNimi;
    bool monimuoto = false;
};

#endif // MUOKATTAVARAPORTTI_H
