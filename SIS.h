
#ifndef XTESTSTUFF_SIS_H_
#define XTESTSTUFF_SIS_H_

#include "../hykops_core/ESurfaceIdentifiers.h"
#include "../hykops_data/HCurve2D.h"
#include "../hykops_data/HLoft.h"
#include "../hykops_data/HLoftElement.h"
#include "../hykops_data/HSurfaceIdentifier.h"
#include "../hykops_data/uniquelist.h"

using namespace std;

class SIS {
public:
	static UniqueList<HCurve2D> getLoftedCurves(HLoft loft, HSurfaceIdentifier identifier);
	static HSurfaceIdentifier getSurfaceIdentifierInstance(HLoft loft, ESurfaceIdentifiers ident);
};

#endif /* XTESTSTUFF_SIS_H_ */
