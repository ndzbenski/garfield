#ifndef G_MEDIUM_CONDUCTOR_H
#define G_MEDIUM_CONDUCTOR_H

#include "Medium.hh"

namespace Garfield {

/// Conducting medium.

class MediumConductor : public Medium {

 public:
  /// Constructor
  MediumConductor() : Medium() {
    m_className = "MediumConductor";
    m_name = "Conductor";
  }
  /// Destructor
  virtual ~MediumConductor() {}

  void EnableDrift() {}
  void EnableIonisation() {}
};
}

#endif
