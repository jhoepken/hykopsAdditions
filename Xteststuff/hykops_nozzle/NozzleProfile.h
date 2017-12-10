#ifndef HYKOPS_NOZZLE_NOZZLEPROFILE_H_
#define HYKOPS_NOZZLE_NOZZLEPROFILE_H_

class NozzleProfile
{
    public:
//! returns the absolute nozzle radius defined by the coordinate system of the loft
    static double getRelRadius(HLoftElement* element);
//! sets the nozzle radius
    static void setRelRadius(HLoftElement* element, double relRadius);
//! returns
    static double getProfileAxialShift(HLoftElement* element);
//! sets
    static void setProfileAxialShift(HLoftElement* element, double axialShift);
//! returns the nozzle's diffusor angle
    static double getDiffusorAngle(HLoftElement* element);
//! sets the nozzle's diffusor angle
    static void setDiffusorAngle(HLoftElement* element, double alpha);
//! returns the nozzle's chord length
    static double getChordlength(HLoftElement* element);
//! sets the nozzle's chord length
    static void setChordlength(HLoftElement* element, double chord);
};



#endif /* HYKOPS_NOZZLE_NOZZLEPROFILE_H_ */
