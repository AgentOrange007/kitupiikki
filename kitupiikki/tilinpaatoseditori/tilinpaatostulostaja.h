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

#ifndef TILINPAATOSTULOSTAJA_H
#define TILINPAATOSTULOSTAJA_H

#include "raportti/raportti.h"

#include <QTextDocument>
#include <QPagedPaintDevice>
#include "db/tilikausi.h"
#include "raportti/raportinkirjoittaja.h"
#include "naytin/esikatseltava.h"

#include <QVector>
#include <QPagedPaintDevice>
/**
 * @brief Tilinpäätöksen tulostus
*/
class TilinpaatosTulostaja : public QObject, public Esikatseltava
{
    Q_OBJECT
public:
    TilinpaatosTulostaja(Tilikausi tilikausi, const QString& teksti, const QStringList& raportit, QObject* parent = nullptr);
    virtual ~TilinpaatosTulostaja() override;

    void nayta();
    void tallenna();

    virtual void tulosta(QPagedPaintDevice *writer) const override;
    virtual QString otsikko() const override;

signals:
    void tallennettu();

private:
    void tilaaRaportit();
    void tulostaKansilehti(QPainter *painter) const;

protected:
    void tilaaRaportti(const QString& raportinnimi);

protected slots:
    void raporttiSaapuu(int raportti, RaportinKirjoittaja rk);
    void kirjoita();

protected:
    Tilikausi tilikausi_;
    QVector<RaportinKirjoittaja> kirjoittajat_;
    int tilattuja_;
    QString teksti_;
    QStringList raportit_;
    bool tallenna_;

};

#endif // TILINPAATOSTULOSTAJA_H
