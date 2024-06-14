// Copyright 2020 Carmelo Evoli (GSSI) - MIT License
#include <memory>

#include "Chi2.h"
#include "Data.h"
#include "Logging.h"
#include "Utilities.h"
#include "models/Secondary.h"
#include "models/SingleGalaxy.h"

void fitPositrons(std::string inputname_pwn, int iModel) {
    std::string s = "secondary_1e1_1e5_64_secondary.txt";
    auto secondary = std::make_shared<STATS::SecondaryPositrons>(s);
    std::shared_ptr<STATS::SinglePositrons> positrons;
    {
        auto ams = std::make_shared<STATS::Data>(50, 1e3);
        ams->loadDatafile("kiss_tables/AMS-02_e+_kineticEnergy.txt");
        auto filename = "gryphon_output/" + inputname_pwn + "_" + std::to_string(iModel) + ".txt";
        positrons = std::make_shared<STATS::SinglePositrons>(filename);
        STATS::Chi2 chi2(positrons, ams);
        auto eff_pwn = chi2.run(0.01, 1);
        positrons->setEfficiency(eff_pwn);
        positrons->print("output/" + inputname_pwn + "_" + std::to_string(iModel) + ".stats");
    }
}

void fitLeptons(std::string inputname_pwn, std::string inputname_snr, int iModel) {
    std::shared_ptr<STATS::SinglePositrons> positrons;
    {
        auto ams = std::make_shared<STATS::Data>(50, 1e3);
        ams->loadDatafile("kiss_tables/AMS-02_e+_kineticEnergy.txt");
        auto filename = "gryphon_output/" + inputname_pwn + "_" + std::to_string(iModel) + ".txt";
        positrons = std::make_shared<STATS::SinglePositrons>(filename);
        STATS::Chi2 chi2(positrons, ams);
        auto eff_pwn = chi2.run(0.01, 1);
        positrons->setEfficiency(eff_pwn);
        // positrons->print("output/" + inputname_pwn + ".stats");
    }
    {
        auto ams = std::make_shared<STATS::Data>(50, 3e2);
        ams->loadDatafile("kiss_tables/DAMPE_e+e-_kineticEnergy.txt");
        auto filename = "gryphon_output/" + inputname_snr + "_" + std::to_string(iModel) + ".txt";
        auto leptons = std::make_shared<STATS::SingleLeptons>(filename, positrons);
        STATS::Chi2 chi2(leptons, ams);
        auto eff_snr = chi2.run(0.001, 1);
        leptons->setEfficiency(eff_snr);
    }
}

int main(int argc, char* argv[]) {
    logStartupInformation();
    try {
        for (int i = 0; i < 10; ++i) fitPositrons("pairs_dampe", i);
    } catch (const std::exception& e) {
        LOGE << "exception caught with message: " << e.what();
    }
    return 0;
}