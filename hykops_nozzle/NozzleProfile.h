#ifndef HYKOPS_NOZZLE_NOZZLEPROFILE_H_
#define HYKOPS_NOZZLE_NOZZLEPROFILE_H_

class NozzleProfile
{
    public:
//! returns the absolute nozzle radius defined by the coordinate system of the loft
    double getRelRadius(HLoftElement* element);
//! sets the nozzle radius
    void setRelRadius(HLoftElement* element, double relRadius);
//! returns
    double getProfileAxialShift(HLoftElement* element);
//! sets
    void setProfileAxialShift(HLoftElement* element, double axialShift);
//! returns the nozzle's diffusor angle
    double getDiffusorAngle(HLoftElement* element);
//! sets the nozzle's diffusor angle
    void setDiffusorAngle(HLoftElement* element, double alpha);
//! returns the nozzle's chord length
    double getChordlength(HLoftElement* element);
//! sets the nozzle's chord length
    void setChordlength(HLoftElement* element, double chord);
};



#endif /* HYKOPS_NOZZLE_NOZZLEPROFILE_H_ */
