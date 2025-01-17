#ifndef G_SOLID_TUBE_H
#define G_SOLID_TUBE_H

#include "Solid.hh"

namespace Garfield {

/// Cylindrical tube.

class SolidTube : public Solid {

 public:
  /// Constructor from centre, inner/outer radii, and length.
  SolidTube(const double cx, const double cy, const double cz,
            const double rmin, const double rmax, const double lz);
  /// Constructor from centre, inner/outer radii, length and orientation.
  SolidTube(const double cx, const double cy, const double cz,
            const double rmin, const double rmax, const double lz,
            const double dx, const double dy, const double dz);
  /// Destructor
  ~SolidTube() {}

  virtual bool IsInside(const double x, const double y, 
                        const double z) const override;
  virtual bool GetBoundingBox(double& xmin, double& ymin, 
                              double& zmin, 
                              double& xmax, double& ymax, 
                              double& zmax) const override;
  virtual bool IsTube() const override { return true; }

  virtual bool GetCenter(double& x, double& y, double& z) const override;
  virtual bool GetDimensions(double& l1, double& l2, double& l3) const override;
  virtual bool GetOrientation(double& ctheta, double& stheta, double& cphi,
                              double& sphi) const override;

  void SetInnerRadius(const double rmin);
  void SetOuterRadius(const double rmax);
  void SetHalfLengthZ(const double lz);

 private:
  // Center of the tube
  double m_cX, m_cY, m_cZ;
  // Inner and outer radius
  double m_rMin, m_rMax;
  // Length
  double m_lZ;
  // Direction
  double m_dX, m_dY, m_dZ;
  double m_cPhi, m_sPhi;
  double m_cTheta, m_sTheta;
};
}

#endif
