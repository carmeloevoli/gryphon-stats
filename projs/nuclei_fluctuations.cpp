// Copyright 2020 Carmelo Evoli (GSSI) - MIT License
#include <memory>

#include "Chi2.h"
#include "Data.h"
#include "Logging.h"
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

int main(int argc, char* argv[]) {
    logStartupInformation();
    try {
        int N = 1000;
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
    } catch (const std::exception& e) {
        LOGE << "exception caught with message: " << e.what();
    }
    return 0;
}