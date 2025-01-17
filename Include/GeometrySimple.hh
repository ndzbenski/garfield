#ifndef G_GEOMETRY_SIMPLE_H
#define G_GEOMETRY_SIMPLE_H

#include <vector>

#include "GeometryBase.hh"
#include "Solid.hh"

namespace Garfield {

/// "Native" geometry, using simple shapes.

class GeometrySimple : public GeometryBase {

 public:
  // Constructor
  GeometrySimple();
  // Destructor
  virtual ~GeometrySimple() {}

  // Add a solid to the geometry
  void AddSolid(Solid* s, Medium* m);
  // Get the solid at a given location (x, y, z)
  Solid* GetSolid(const double x, const double y, const double z) const;
  // Get the medium at a given location (x, y, z)
  Medium* GetMedium(const double x, const double y, const double z) const;
  // Number of solids/media in the geometry
  unsigned int GetNumberOfSolids() const { return m_solids.size(); }
  unsigned int GetNumberOfMedia() const { return m_media.size(); }
  // Get a solid/medium from the list
  Solid* GetSolid(const unsigned int i) const;
  virtual Medium* GetMedium(const unsigned int i) const;
  // Reset the geometry
  void Clear();
  void PrintSolids();

  bool IsInside(const double x, const double y, const double z) const;
  // Bounding box (envelope of geometry)
  bool IsInBoundingBox(const double x, const double y, const double z) const;
  bool GetBoundingBox(double& xmin, double& ymin, double& zmin, double& xmax,
                      double& ymax, double& zmax) {
    xmin = m_xMinBoundingBox;
    ymin = m_yMinBoundingBox;
    zmin = m_zMinBoundingBox;
    xmax = m_xMaxBoundingBox;
    ymax = m_yMaxBoundingBox;
    zmax = m_zMaxBoundingBox;
    return true;
  }

  // Switch on/off debugging and warning messages
  void EnableDebugging(const bool on = true) { m_debug = on; }

 protected:
  // List of media.
  std::vector<Medium*> m_media;

  // List of solids
  std::vector<std::pair<Solid*, int> > m_solids;

  // Bounding box ranges
  bool m_hasBoundingBox = false;
  double m_xMinBoundingBox, m_yMinBoundingBox, m_zMinBoundingBox;
  double m_xMaxBoundingBox, m_yMaxBoundingBox, m_zMaxBoundingBox;

  // Switch on/off debugging messages
  bool m_debug = false;
};
}

#endif
