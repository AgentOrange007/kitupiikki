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

#include <QDesktopServices>
#include <QRegularExpression>
#include <QRegularExpressionMatch>

#include "tilinpaatoseditori.h"
#include "tilinpaatostulostaja.h"
#include "db/kirjanpito.h"

TilinpaatosEditori::TilinpaatosEditori(Tilikausi tilikausi)
    : QMainWindow(),
      tilikausi_(tilikausi),
      printer_( QPrinter::HighResolution)
{
    editori_ = new QTextEdit;
    setCentralWidget( editori_);
    setWindowTitle( tr("Tilinpäätöksen liitetiedot %1").arg(tilikausi.kausivaliTekstina()));

    setWindowIcon( QIcon(":/pic/Possu64.png"));

    printer_.setPageMargins( 25,10,10,10, QPrinter::Millimeter);

    luoAktiot();
    luoPalkit();

    lataa();

}

void TilinpaatosEditori::esikatsele()
{
    TilinpaatosTulostaja::tulostaTilinpaatos( tilikausi_, editori_->document(), &printer_);
    QDesktopServices::openUrl( QUrl::fromLocalFile( kp()->hakemisto().absoluteFilePath("arkisto/" + tilikausi_.arkistoHakemistoNimi() + "/tilinpaatos.pdf") ));
}

void TilinpaatosEditori::luoAktiot()
{
    esikatseleAction_ = new QAction( QIcon(":/pic/print.png"), tr("Esikatsele"), this);
    connect( esikatseleAction_, SIGNAL(triggered(bool)), this, SLOT(esikatsele()));
    vahvistaAction_ = new QAction( QIcon(":/pic/ok.png"), tr("Valmis"), this);
    liitaAction_ = new QAction( QIcon(":/pic/tuotiedosto.png"), tr("Tuo"), this);
}

void TilinpaatosEditori::luoPalkit()
{
    tilinpaatosTb_ = addToolBar( tr("&Tilinpäätös"));
    tilinpaatosTb_->addAction( esikatseleAction_ );
    tilinpaatosTb_->addAction( liitaAction_ );
    tilinpaatosTb_->addAction( vahvistaAction_ );
    tilinpaatosTb_->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
}

void TilinpaatosEditori::lataa()
{
    QStringList pohja = kp()->asetukset()->lista("TilinpaatosPohja");
    QStringList valinnat = kp()->asetukset()->lista("TilinpaatosValinnat");
    QRegularExpression tunnisteRe("#(?<tunniste>\\w+).*");
    tunnisteRe.setPatternOptions(QRegularExpression::UseUnicodePropertiesOption);
    QRegularExpression raporttiRe("@(?<raportti>.+)!(?<otsikko).+)@");

    QString teksti;

    bool tulosta = true;

    foreach (QString rivi, pohja)
    {
        if( rivi.startsWith('#') )
        {
            QRegularExpressionMatch tmats = tunnisteRe.match(rivi);
            if( tmats.hasMatch())
            {
                QString tunniste = tmats.captured(1);
                tulosta = valinnat.contains(tunniste);
            }
            else
                tulosta = true;
        }
        else if( rivi.startsWith('@'))
        {
            // Näillä tulostetaan erityisiä kenttiä
            if( rivi == "@sha@")
                teksti.append( tilikausi_.json()->str("ArkistoSHA"));
        }
        else if( tulosta )
            teksti.append(rivi);
    }
    editori_->setHtml(teksti);
}