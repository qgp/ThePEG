// -*- C++ -*-
//
// FermionSpinInfo.h is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 2003-2011 Peter Richardson, Leif Lonnblad
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
#ifndef ThePEG_FermionSpinInfo_H
#define ThePEG_FermionSpinInfo_H
// This is the declaration of the FermionSpinInfo class.

#include "ThePEG/EventRecord/SpinInfo.h"
#include "ThePEG/Helicity/LorentzSpinor.h"
#include "FermionSpinInfo.fh"

namespace ThePEG {
namespace Helicity {

/**
 *  The FermionSpinInfo class inherits from the SpinInfo class and
 *  implements the storage of the basis vectors for a spin-1/2
 *  particle.  The basis states are the u-spinors for a particle and
 *  the v-spinors for an antiparticle. The barred spinors can be
 *  obtained from these.
 *
 *  These basis states should be set by either matrixelements or
 *  decayers which are capable of generating spin correlation
 *  information.
 *
 *  The basis states in the rest frame of the particles can then be
 *  accessed by decayers to produce the correct correlations.
 *
 *  N.B. in our convention 0 is the \f$-\frac12\f$ helicity state and
 *  1 is the \f$+\frac12\f$ helicity state.
 *
 * @author Peter Richardson
 */
class FermionSpinInfo: public SpinInfo {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor.
   */
  FermionSpinInfo() : SpinInfo(PDT::Spin1Half), _productionstates(2), 
		      _currentstates(2), _decaystates(2), 
		      _decaycalc(false) {}

  /**
   * Standard Constructor.
   * @param p the production momentum.
   * @param time true if the particle is time-like.
   */
  FermionSpinInfo(const Lorentz5Momentum & p, bool time)
    : SpinInfo(PDT::Spin1Half, p, time),
      _productionstates(2), _currentstates(2), _decaystates(2),
      _decaycalc(false) {}
  //@}

public:

  /** @name Set and get methods for the basis state. */
  //@{
  /**
   * Set the basis state, this is production state.
   * @param hel the helicity (0 or 1 as described above.)
   * @param in the LorentzSpinor for the given helicity.
   */
  void setBasisState(unsigned int hel,
		     const LorentzSpinor<SqrtEnergy> & in) const {
    assert(hel<2);
    _productionstates[hel] = in;
    _currentstates   [hel] = in;
  }

  /**
   * Set the basis state for the decay.
   * @param hel the helicity (0 or 1 as described above.)
   * @param in the LorentzSpinor for the given helicity.
   */
  void setDecayState(unsigned int hel,
		     const LorentzSpinor<SqrtEnergy> & in) const {
    assert(hel<2);
    _decaycalc = true;
    _decaystates[hel] = in;
  }

  /**
   * Get the basis state for the production for the given helicity, \a
   * hel (which is 0 or 1 as described above.)
   */
  const LorentzSpinor<SqrtEnergy> & getProductionBasisState(unsigned int hel) const {
    assert(hel<2);
    return _productionstates[hel];
  }

  /**
   * Get the current basis state for the given helicity, \a
   * hel (which is 0 or 1 as described above.)
   */
  const LorentzSpinor<SqrtEnergy> & getCurrentBasisState(unsigned int hel) const {
    assert(hel<2);
    return _currentstates[hel];
  }

  /**
   * Get the basis state for the decay for the given helicity, \a hel
   * (which is 0 or 1 as described above.)
   */
  const LorentzSpinor<SqrtEnergy> & getDecayBasisState(unsigned int hel) const {
    assert(hel<2);
    if(!_decaycalc) {
      for(unsigned int ix=0;ix<2;++ix) _decaystates[ix]=_currentstates[ix];
      _decaycalc=true;
    }
    return _decaystates[hel];
  }
  //@}

  /**
   * Perform a lorentz rotation of the spin information
   */
  virtual void transform(const LorentzMomentum &,const LorentzRotation &);

public:

  /**
   * Standard Init function.
   */
  static void Init();

  /**
   * Standard clone method.
   */
  virtual EIPtr clone() const;

private:

  /**
   * Describe a concrete class without persistent data.
   */
  static NoPIOClassDescription<FermionSpinInfo> initFermionSpinInfo;

  /**
   * Private and non-existent assignment operator.
   */
  FermionSpinInfo & operator=(const FermionSpinInfo &);

private:

  /**
   * basis states in the frame in which the particle was produced
   */
  mutable vector<LorentzSpinor<SqrtEnergy> > _productionstates;

  /**
   * basis states in the current frame of the particle
   */
  mutable vector<LorentzSpinor<SqrtEnergy> > _currentstates;

  /**
   * basis states in the frame in which the particle decays
   */
  mutable vector<LorentzSpinor<SqrtEnergy> > _decaystates;

  /**
   * True if the decay state has been set.
   */
  mutable bool _decaycalc;

};

}
}

namespace ThePEG {

/** @cond TRAITSPECIALIZATIONS */

/**
 * This template specialization informs ThePEG about the base class of
 * FermionSpinInfo.
 */
template <>
struct BaseClassTrait<ThePEG::Helicity::FermionSpinInfo,1>
  : public ClassTraitsType {
  /** Typedef of the base class of FermionSpinInfo. */
  typedef ThePEG::SpinInfo NthBase;
};

/**
 * This template specialization informs ThePEG about the name of the
 * FermionSpinInfo class and the shared object where it is defined.
 */
template <>
struct ClassTraits<ThePEG::Helicity::FermionSpinInfo>
  : public ClassTraitsBase<ThePEG::Helicity::FermionSpinInfo> {
  /**
   * Return the class name.
   */
  static string className() { return "ThePEG::Helicity::FermionSpinInfo"; }
};

/** @endcond */

}

#endif /* ThePEG_FermionSpinInfo_H */
