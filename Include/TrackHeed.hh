#ifndef G_TRACK_HEED_H
#define G_TRACK_HEED_H

#include <vector>
#include <list>
#include <memory>

#include "Track.hh"
#ifndef __CINT__
#include "heed++/code/HeedParticle.h"
#include "heed++/code/HeedCondElectron.h"
#endif /* __CINT __ */

namespace Heed {
class gparticle;
class HeedParticle;
class HeedMatterDef;
class GasDef;
class MatterDef;
class AtomPhotoAbsCS;
class MolecPhotoAbsCS;
class EnergyMesh;
class EnTransfCS;
class ElElasticScat;
class ElElasticScatLowSigma;
class PairProd;
class HeedDeltaElectronCS;
class HeedFieldMap;
}

namespace Garfield {

class HeedChamber;
class Medium;

/// Generate tracks using Heed++.

class TrackHeed : public Track {

 public:
  /// Constructor
  TrackHeed();
  /// Destructor
  virtual ~TrackHeed();

  virtual bool NewTrack(const double x0, const double y0, const double z0,
                        const double t0, const double dx0, const double dy0,
                        const double dz0);
  virtual bool GetCluster(double& xcls, double& ycls, double& zcls, double& tcls,
                          int& n, double& e, double& extra);
  bool GetCluster(double& xcls, double& ycls, double& zcls, double& tcls,
                  int& ne, int& ni, double& e, double& extra);
  /** Retrieve the properties of a conduction or delta electron 
    * in the current cluster.
    * \param i index of the electron
    * \param x,y,z coordinates of the electron
    * \param t time
    * \param e kinetic energy (only meaningful for delta-electrons)
    * \param dx,dy,dz direction vector (only meaningful for delta-electrons)
    **/ 
  bool GetElectron(const unsigned int i, 
                   double& x, double& y, double& z, double& t,
                   double& e, double& dx, double& dy, double& dz);
  /** Retrieve the properties of an ion in the current cluster.
    * \param i index of the ion
    * \param x,y,z coordinates of the ion
    * \param t time
    **/ 
  bool GetIon(const unsigned int i, 
              double& x, double& y, double& z, double& t) const;

  virtual double GetClusterDensity();
  virtual double GetStoppingPower();
  double GetW() const;
  double GetFanoFactor() const;

  void TransportDeltaElectron(const double x0, const double y0, const double z0,
                              const double t0, const double e0,
                              const double dx0, const double dy0,
                              const double dz0, int& nel, int& ni);
  void TransportDeltaElectron(const double x0, const double y0, const double z0,
                              const double t0, const double e0,
                              const double dx0, const double dy0,
                              const double dz0, int& nel);

  void TransportPhoton(const double x0, const double y0, const double z0,
                       const double t0, const double e0, const double dx0,
                       const double dy0, const double dz0, int& nel, int& ni);
  void TransportPhoton(const double x0, const double y0, const double z0,
                       const double t0, const double e0, const double dx0,
                       const double dy0, const double dz0, int& nel);

  // Specify whether the electric and magnetic field should be
  // taken into account in the stepping algorithm.
  void EnableElectricField();
  void DisableElectricField();
  void EnableMagneticField();
  void DisableMagneticField();

  void EnableDeltaElectronTransport() { m_doDeltaTransport = true; }
  void DisableDeltaElectronTransport() { m_doDeltaTransport = false; }

  void EnablePhotonReabsorption() { m_usePhotonReabsorption = true; }
  void DisablePhotonReabsorption() { m_usePhotonReabsorption = false; }

  void EnablePhotoAbsorptionCrossSectionOutput() { m_usePacsOutput = true; }
  void DisablePhotoAbsorptionCrossSectionOutput() { m_usePacsOutput = false; }
  void SetEnergyMesh(const double e0, const double e1, const int nsteps);

  // Define particle mass and charge (for exotic particles).
  // For standard particles Track::SetParticle should be used.
  void SetParticleUser(const double m, const double z);

 private:
  // Prevent usage of copy constructor and assignment operator
  TrackHeed(const TrackHeed& heed);
  TrackHeed& operator=(const TrackHeed& heed);

  bool m_ready = false;
  bool m_hasActiveTrack = false;

  double m_mediumDensity = -1.;
  std::string m_mediumName = "";

  bool m_usePhotonReabsorption = true;
  bool m_usePacsOutput = false;

  bool m_doDeltaTransport = true;
  struct deltaElectron {
    double x, y, z, t;
    double e;
    double dx, dy, dz;
  };
  std::vector<deltaElectron> m_deltaElectrons;
  std::vector<Heed::HeedCondElectron> m_conductionElectrons;
  std::vector<Heed::HeedCondElectron> m_conductionIons;

  // Material properties
  std::unique_ptr<Heed::HeedMatterDef> m_matter;
  std::unique_ptr<Heed::GasDef> m_gas;
  std::unique_ptr<Heed::MatterDef> m_material;

  // Energy mesh
  double m_emin = 2.e-6;
  double m_emax = 2.e-1;
  unsigned int m_nEnergyIntervals = 200;
  std::unique_ptr<Heed::EnergyMesh> m_energyMesh;

  // Cross-sections
  std::unique_ptr<Heed::EnTransfCS> m_transferCs;
  std::unique_ptr<Heed::ElElasticScat> m_elScat;
  std::unique_ptr<Heed::ElElasticScatLowSigma> m_lowSigma;
  std::unique_ptr<Heed::PairProd> m_pairProd;
  std::unique_ptr<Heed::HeedDeltaElectronCS> m_deltaCs;

  // Interface classes
  std::unique_ptr<HeedChamber> m_chamber;
  Heed::HeedFieldMap m_fieldMap;

  // Bounding box
  double m_lX = 0., m_lY = 0., m_lZ = 0.;
  double m_cX = 0., m_cY = 0., m_cZ = 0.;

#ifndef __CINT__
  std::vector<Heed::gparticle*> m_particleBank;
  std::vector<Heed::gparticle*>::iterator m_bankIterator;
#endif /* __CINT __ */
  bool Setup(Medium* medium);
  bool SetupGas(Medium* medium);
  bool SetupMaterial(Medium* medium);
  bool SetupDelta(const std::string& databasePath);
  std::string FindUnusedMaterialName(const std::string& namein);
  void ClearParticleBank(); 
  bool IsInside(const double x, const double y, const double z);
  bool UpdateBoundingBox(bool& update);
};
}

#endif
