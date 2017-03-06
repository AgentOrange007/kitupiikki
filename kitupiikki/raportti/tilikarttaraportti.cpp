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

#include "tilikarttaraportti.h"

TilikarttaRaportti::TilikarttaRaportti(QPrinter *printer)
    : Raportti(printer)
{
    ui = new Ui::TilikarttaRaportti;
    ui->setupUi( raporttiWidget);

    connect( ui->tilikaudeltaCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(paivitaPaiva()));

    ui->tilikaudeltaCombo->setModel( kp()->tilikaudet() );
    ui->tilikaudeltaCombo->setModelColumn( TilikausiModel::KAUSI );
    ui->tilikaudeltaCombo->setCurrentIndex( ui->tilikaudeltaCombo->count() - 1);

    ui->saldotDate->setDateRange( kp()->tilikaudet()->kirjanpitoAlkaa(),
                                  kp()->tilikaudet()->kirjanpitoLoppuu());
}

TilikarttaRaportti::~TilikarttaRaportti()
{

}

RaportinKirjoittaja TilikarttaRaportti::raportti()
{
    Tilikausi kausi = kp()->tilikaudet()->tilikausiPaivalle( ui->tilikaudeltaCombo->currentData( TilikausiModel::PaattyyRooli ).toDate() );

    KarttaValinta valinta = KAIKKI_TILIT;
    if( ui->kaytossaRadio->isChecked())
        valinta = KAYTOSSA_TILIT;
    else if( ui->kirjauksiaRadio->isChecked())
        valinta = KIRJATUT_TILIT;
    else if( ui->suosikkiRadio->isChecked())
        valinta = SUOSIKKI_TILIT;

    QDate saldopaiva;
    if( ui->saldotCheck->isChecked())
        saldopaiva = ui->saldotDate->date();

    return kirjoitaRaportti(valinta, kausi, ui->tilityypitCheck->isChecked(), saldopaiva);
}

RaportinKirjoittaja TilikarttaRaportti::kirjoitaRaportti(TilikarttaRaportti::KarttaValinta valinta, Tilikausi tilikaudelta, bool tulostatyypi, QDate saldopvm)
{
    RaportinKirjoittaja rk;


    return rk;
}



void TilikarttaRaportti::paivitaPaiva()
{
    Tilikausi kausi = kp()->tilikaudet()->tilikausiPaivalle( ui->tilikaudeltaCombo->currentData( TilikausiModel::PaattyyRooli ).toDate() );
    ui->saldotDate->setDate( kausi.paattyy());
}
