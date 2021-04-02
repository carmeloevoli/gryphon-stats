// Copyright 2020 Carmelo Evoli (GSSI) - MIT License
#include <memory>

#include "Chi2.h"
#include "Data.h"
#include "Logging.h"
#include "Utilities.h"
#include "models/PositronPWNe.h"
#include "models/PrimaryElectrons.h"
#include "models/PrimaryProtons.h"

void computeFluxAtEnergy(double Energy, std::string inputname, int nModels) {
    auto protons = std::make_shared<STATS::PrimaryProtons>("gryphon_output/" + inputname, nModels);
    auto fluxes = protons->getInterpolatedFlux(Energy);

    std::ostringstream oss;
    oss << "output/" << inputname << "_" << std::setprecision(0) << std::fixed << Energy << ".txt";
    const std::string outname = oss.str();

    std::ofstream outfile(outname);
    if (outfile.is_open()) {
        outfile << std::scientific << std::setprecision(10);
        for (auto f : fluxes) outfile << f << "\n";
    }
    outfile.close();
    LOGI << "saving fluxes at " << outname;
}

void computeSingleSourceF(double Energy, std::string inputname, int nModels) {
    auto fluxes = std::make_shared<STATS::Particle>("gryphon_output/" + inputname, nModels);
    auto maxSingleFlux =
        std::make_shared<STATS::Particle>("gryphon_output/" + inputname, nModels, false);
    const auto E = fluxes->getE();
    const auto size = fluxes->getSize();

    std::ostringstream oss;
    oss << "output/" << inputname << "_" << std::setprecision(0) << std::fixed << Energy
        << "_maxsingle.txt";
    const std::string outname = oss.str();
    std::ofstream outfile(outname);
    if (outfile.is_open()) {
        for (int i = 0; i < size; ++i) {
            const auto flux = fluxes->getSample().at(i);
            const auto maxSingle = maxSingleFlux->getSample().at(i);
            double f_sum = UTILS::LinearInterpolatorLog(E, flux, Energy);
            double f_max = UTILS::LinearInterpolatorLog(E, maxSingle, Energy);
            outfile << std::scientific << f_sum << " " << f_max << " " << f_max / (f_sum - f_max)
                    << "\n";
        }
    }
    outfile.close();
    LOGI << "saving fluxes at " << outname;
}

void fitProtons(std::string inputname, int nModels) {
    auto ams = std::make_shared<STATS::Data>(60, 250);
    ams->loadDatafile("kiss_tables/H_AMS-02_Ek.txt");
    auto protons = std::make_shared<STATS::PrimaryProtons>("gryphon_output/" + inputname, nModels);
    STATS::Chi2 chi2(protons, ams);
    auto eff = chi2.run(0.01, 1);
    protons->setEfficiency(eff);
    protons->print("output/" + inputname + ".stats");
}

void fitHelium(std::string inputname, int nModels) {
    auto ams = std::make_shared<STATS::Data>(120, 500);
    ams->loadDatafile("kiss_tables/He_AMS-02_Etot.txt");
    auto helium = std::make_shared<STATS::PrimaryProtons>("gryphon_output/" + inputname, nModels);
    STATS::Chi2 chi2(helium, ams);
    auto eff = chi2.run(0.01, 1);
    helium->setEfficiency(eff);
    helium->print("output/" + inputname + ".stats");
}

void fitPositrons(std::string inputname_pwn, int nModels) {
    auto ams = std::make_shared<STATS::Data>(1e2, 1e4);
    ams->loadDatafile("kiss_tables/e+_AMS-02_Ek.txt");
    auto positrons =
        std::make_shared<STATS::PositronPWNe>("gryphon_output/" + inputname_pwn, nModels);
    STATS::Chi2 chi2(positrons, ams);
    auto eff_pwn = chi2.run(0.01, 1);
    positrons->setEfficiency(eff_pwn);
    positrons->print("output/" + inputname_pwn + ".stats");
}

void fitElectrons(std::string inputname_pwn, std::string inputname_snr, int nModels) {
    double eff_pwn = 0;
    {
        auto ams = std::make_shared<STATS::Data>(1e2, 1e4);
        ams->loadDatafile("kiss_tables/e+_AMS-02_Ek.txt");
        auto positrons =
            std::make_shared<STATS::PositronPWNe>("gryphon_output/" + inputname_pwn, nModels);
        STATS::Chi2 chi2(positrons, ams);
        eff_pwn = chi2.run(0.01, 1);
        positrons->setEfficiency(eff_pwn);
        positrons->print("output/" + inputname_pwn + ".stats");
    }
    {
        auto ams = std::make_shared<STATS::Data>(80, 500);
        ams->loadDatafile("kiss_tables/e-_AMS-02_Ek.txt");
        auto electrons = std::make_shared<STATS::PrimaryElectrons>(
            "gryphon_output/" + inputname_snr, "gryphon_output/" + inputname_pwn, eff_pwn, nModels);
        STATS::Chi2 chi2(electrons, ams);
        auto eff_snr = chi2.run(0.001, 0.1);
        electrons->setEfficiency(eff_snr);
        electrons->print("output/" + inputname_snr + ".stats");
    }
}

int main(int argc, char* argv[]) {
    logStartupInformation();
    try {
        {
            const int N = 11000;

            fitProtons("protons_jelly_2.29", N);
            fitProtons("protons_spirals_2.30", N);
            fitHelium("helium_jelly_2.25", N);
            fitHelium("helium_spirals_2.26", N);

            computeFluxAtEnergy(1e2, "protons_jelly_2.29", N);
            computeFluxAtEnergy(1e3, "protons_jelly_2.29", N);
            computeFluxAtEnergy(1e4, "protons_jelly_2.29", N);
            computeFluxAtEnergy(1e2, "protons_spirals_2.30", N);
            computeFluxAtEnergy(1e3, "protons_spirals_2.30", N);
            computeFluxAtEnergy(1e4, "protons_spirals_2.30", N);
            computeSingleSourceF(1e2, "protons_jelly_2.29", N);
            computeSingleSourceF(1e3, "protons_jelly_2.29", N);
            computeSingleSourceF(1e4, "protons_jelly_2.29", N);
            computeSingleSourceF(1e2, "protons_spirals_2.30", N);
            computeSingleSourceF(1e3, "protons_spirals_2.30", N);
            computeSingleSourceF(1e4, "protons_spirals_2.30", N);

            fitElectrons("pairs_spirals_1.80_2.80", "electrons_spirals_2.58", N);
            fitElectrons("pairs_spirals_1.80_2.80", "electrons_jelly_2.62", N);
            fitPositrons("pairs_jelly_1.90_3.00", N);

            computeFluxAtEnergy(1e2, "electrons_jelly_2.62", N);
            computeFluxAtEnergy(1e3, "electrons_jelly_2.62", N);
            computeFluxAtEnergy(1e4, "electrons_jelly_2.62", N);
            computeFluxAtEnergy(1e2, "electrons_spirals_2.58", N);
            computeFluxAtEnergy(1e3, "electrons_spirals_2.58", N);
            computeFluxAtEnergy(1e4, "electrons_spirals_2.58", N);

            computeSingleSourceF(1e2, "electrons_jelly_2.62", N);
            computeSingleSourceF(1e3, "electrons_jelly_2.62", N);
            computeSingleSourceF(1e4, "electrons_jelly_2.62", N);
            computeSingleSourceF(1e2, "electrons_spirals_2.58", N);
            computeSingleSourceF(1e3, "electrons_spirals_2.58", N);
            computeSingleSourceF(1e4, "electrons_spirals_2.58", N);
        }
    } catch (const std::exception& e) {
        LOGE << "exception caught with message: " << e.what();
    }
    return 0;
}