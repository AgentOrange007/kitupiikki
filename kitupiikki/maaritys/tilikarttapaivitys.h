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
#ifndef TILIKARTTAPAIVITYS_H
#define TILIKARTTAPAIVITYS_H

#include "maarityswidget.h"

#include "ui_tilikarttapaivitys.h"

class TilikarttaPaivitys : public MaaritysWidget
{
    Q_OBJECT
public:
    TilikarttaPaivitys(QWidget *parent = nullptr);

    bool nollaa() override;

    bool naytetaankoTallennus() override { return false;}

    static QDate paivitysPvm();
    static bool onkoPaivitettavaa();

public slots:
    void paivita();

protected:
    Ui::TilikarttaPaivitys *ui;

    static QVariantMap lataaPaivitys(const QString& polku);


};

#endif // TILIKARTTAPAIVITYS_H
