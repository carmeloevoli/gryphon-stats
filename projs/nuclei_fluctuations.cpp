// Copyright 2020 Carmelo Evoli (GSSI) - MIT License
#include "Chi2.h"
#include "Data.h"
#include "Logging.h"

// #include "fitters/TFitProtons.h"
// #include "models/TProtons.h"

// void compute_median_flux(int n_max) {
//     {
//         double epsilon = 0;
//         auto fitProtons = STATS::TFitProtons(40, 200);
//         fitProtons.buildChi2("data/H_AMS02_rigidity.txt");
//         fitProtons.buildProtons("ulite/protons_uniform", n_max);
//         epsilon = fitProtons.run(0.1, 2.);
//         fitProtons.print("output/protons_uniform.stats", epsilon);
//     }

//     {
//         double epsilon = 0;
//         auto fitProtons = STATS::TFitProtons(40, 200);
//         fitProtons.buildChi2("data/H_AMS02_rigidity.txt");
//         fitProtons.buildProtons("ulite/protons_jelly", n_max);
//         epsilon = fitProtons.run(0.1, 2.);
//         fitProtons.print("output/protons_jelly.stats", epsilon);
//     }

//     {
//         double epsilon = 0;
//         auto fitProtons = STATS::TFitProtons(40, 200);
//         fitProtons.buildChi2("data/H_AMS02_rigidity.txt");
//         fitProtons.buildProtons("ulite/protons_spirals", n_max);
//         epsilon = fitProtons.run(0.1, 2.);
//         fitProtons.print("output/protons_spirals.stats", epsilon);
//     }
// }

// void compute_flux_at_energy(int n_max) {
//     {
//         const auto protons = STATS::TProtons("ulite/protons_uniform", n_max);
//         const auto fluxes = protons.getInterpolatedFlux(1e3, 1.);
//         std::ofstream outfile("output/protons_uniform_at1TeV.txt");
//         if (outfile.is_open()) {
//             outfile << std::scientific << std::setprecision(10);
//             for (auto f : fluxes) outfile << f << "\n";
//         }
//         outfile.close();
//     }

//     {
//         const auto protons = STATS::TProtons("ulite/protons_jelly", n_max);
//         const auto fluxes = protons.getInterpolatedFlux(1e3, 1.);
//         std::ofstream outfile("output/protons_jelly_at1TeV.txt");
//         if (outfile.is_open()) {
//             outfile << std::scientific << std::setprecision(10);
//             for (auto f : fluxes) outfile << f << "\n";
//         }
//         outfile.close();
//     }

//     {
//         const auto protons = STATS::TProtons("ulite/protons_spirals", n_max);
//         const auto fluxes = protons.getInterpolatedFlux(1e3, 1.);
//         std::ofstream outfile("output/protons_spirals_at1TeV.txt");
//         if (outfile.is_open()) {
//             outfile << std::scientific << std::setprecision(10);
//             for (auto f : fluxes) outfile << f << "\n";
//         }
//         outfile.close();
//     }
// }

int main(int argc, char* argv[]) {
    logStartupInformation();
    try {
        STATS::Data ams;
        ams.loadDatafile("kiss_tables/H_AMS-02_Ek.txt");

        // STATS::Chi2 chi2(ams);
        // chi2.run(0.1, 1);

    } catch (const std::exception& e) {
        LOGE << "exception caught with message: " << e.what();
    }
    return 0;
}