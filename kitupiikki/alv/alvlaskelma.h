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
#ifndef ALVLASKELMA_H
#define ALVLASKELMA_H

#include "raportti/raportteri.h"
#include "model/tositevienti.h"

#include <QMap>
#include <QVariantMap>

class Tosite;

class AlvLaskelma : public Raportteri
{               
    Q_OBJECT

protected:
    struct TiliTaulu {
        QList<QVariantMap> viennit;
        void lisaa(const QVariantMap& rivi);
        qlonglong summa(bool debetista = false) const;
    };

    struct KantaTaulu {
        void lisaa(const QVariantMap& rivi);
        qlonglong summa(bool debetista = false) const;

        QMap<int, TiliTaulu> tilit;
    };

    struct KoodiTaulu {
        void lisaa(const QVariantMap& rivi);
        qlonglong summa(bool debetista = false) const;

        QMap<int, KantaTaulu> kannat;
    };

    struct AlvTaulu {
        void lisaa(const QVariantMap& rivi);
        qlonglong summa(int koodista, int koodiin = 0);

        QMap<int, KoodiTaulu> koodit;
    };


public:
    explicit AlvLaskelma(QObject *parent = nullptr);
    ~AlvLaskelma() override;

    void kirjoitaLaskelma();

    qlonglong maksettava() const { return maksettava_;}
    qlonglong huojennus() const { return huojennus_;}

signals:
    void tallennettu();

public slots:
    void laske(const QDate& alkupvm, const QDate& loppupvm);
    void kirjaaHuojennus();
    void tallenna();

protected slots:
    void viennitSaapuu(QVariant* viennit);
    void laskeHuojennus(QVariant* viennit);
    void tallennusValmis();

protected:
    void hae();
    void lisaaKirjausVienti(TositeVienti vienti);

    void oikaiseBruttoKirjaukset();

    void kirjoitaOtsikot();
    void kirjoitaYhteenveto();
    void kirjaaVerot();
    void kirjoitaErittely();
    void yvRivi(int koodi, const QString& selite, qlonglong sentit);
    qlonglong kotimaanmyyntivero(int prosentinsadasosa);

protected:
    QDate alkupvm_;
    QDate loppupvm_;

    AlvTaulu taulu_;
    QMap<int,qlonglong> koodattu_;

    qlonglong maksettava_ = 0l;

    qlonglong liikevaihto_ = 0l;
    qlonglong verohuojennukseen_ = 0l;
    int suhteutuskuukaudet_ = 12;
    qlonglong huojennus_ = 0;

    Tosite* tosite_;


public:
    static bool debetistaKoodilla(int alvkoodi);
};

#endif // ALVLASKELMA_H