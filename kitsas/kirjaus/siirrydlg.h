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

#ifndef SIIRRYDLG_H
#define SIIRRYDLG_H

#include <QDialog>
#include "ui_siirry.h"

/**
 * @brief Dialogi tositenumeron perusteella siirtymiseen
 */
class SiirryDlg : public QDialog
{
    Q_OBJECT
protected:
    SiirryDlg();
    ~SiirryDlg() = default;

protected slots:
    void tarkista();

    void kausiVaihtui();
    void dataSaapui(QVariant* data);

public:
    static int tositeId(QDate pvm, const QString &tositelaji);

protected:
    Ui::SiirryDlg *ui;
    int tosite = 0;

    QVariantList lista_;
};

#endif // SIIRRYDLG_H
