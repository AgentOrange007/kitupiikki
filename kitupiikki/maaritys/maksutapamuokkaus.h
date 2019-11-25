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
#ifndef MAKSUTAPAMUOKKAUS_H
#define MAKSUTAPAMUOKKAUS_H

#include <QWidget>

namespace Ui {
class MaksutapaMuokkaus;
}

class MaksutapaModel;

class MaksutapaMuokkaus : public QWidget
{
    Q_OBJECT

public:
    explicit MaksutapaMuokkaus(QWidget *parent = nullptr);
    ~MaksutapaMuokkaus();

    void setModel(MaksutapaModel *model);

protected slots:
    void uusi();
    void muokkaa();
    void poista();

private:
    Ui::MaksutapaMuokkaus *ui;

    MaksutapaModel *model_;
};

#endif // MAKSUTAPAMUOKKAUS_H
