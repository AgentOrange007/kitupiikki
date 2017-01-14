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

#include "tili.h"

#include <QDebug>
#include <QSqlQuery>

Tili::Tili() : numero_(0), tila_(-1)
{

}

Tili::Tili(int tnumero, const QString tnimi, const QString &tohje, const QString ttyyppi, int ttila, const QString tjson) :
    numero_(tnumero), nimi_(tnimi), ohje_(tohje),tyyppi_(ttyyppi) , tila_(ttila), json_(tjson)
{
}

int Tili::kertymaPaivalle(const QDate &pvm)
{
    QString kysymys = QString("select sum(debetsnt), sum(kreditsnt) from vienti "
            " where tili = %1 and pvm <= \"%2\" ")
            .arg(numero())
            .arg(pvm.toString(Qt::ISODate));

    QSqlQuery kysely(kysymys);
    if( kysely.next())
    {
        int debetKertyma = kysely.value(0).toInt();
        int kreditKertyma = kysely.value(1).toInt();

        if( onkoTasetili() )
            return debetKertyma - kreditKertyma;
        else
            return kreditKertyma - debetKertyma;
    }
    return 0;
}

bool Tili::onkoTasetili() const
{
    return( tyyppi().startsWith('A') || tyyppi().startsWith('B'));
}

