#include "java.util.ArrayList"
#include "java.util.List"



//#include de.hykops.lpd.core.Activator;
#include "../hykops_core/ESurfaceIdentifiers.h"
#include "../hykops_data/HCurve2D.h"
#include "../hykops_data/HLoft.h"
#include "../hykops_data/HLoftElement.h"
#include "../hykops_data/HSurfaceIdentifier.h"
#include "../hykops_data/uniquelist.h"
#include "SIS.h"

using namespace std;

class SurfaceIdentifierSupport {

//	HSurfaceIdentifier createHSurfaceIdentifier(HLoft loft, ESurfaceIdentifiers ident) {
//		HSurfaceIdentifier identifier = Activator.getFactoryService().getFactory().createSurfaceIdentifier();
//		identifier.setName(to_string(ident));
//		identifier->setHParent(loft);
//		loft.getHSurfaceIdentifications().add(identifier);
//		return identifier;
//	}

	UniqueList<HCurve2D> getLoftedCurves(HLoft loft, HSurfaceIdentifier identifier) {
		UniqueList<HCurve2D*> curves;
		HLoftElement HLEs= loft.getHLoftElements();
		for (int i=0; i<loft.getHLoftElements()->length(); i++) {
			for (int j=0; j<HLEs.mHCurve2Ds->length(); j++) {
				if (loft.getHLoftElements()->at(i)->getHCurve2Ds()->at(j)->getHSurfaceIdentifiers()!= NULL) {
					curves.append(loft.getHLoftElements()->at(i)->getHCurve2Ds()->at(j));
				}
			}
		}
		return curves;
	}

	HSurfaceIdentifier getSurfaceIdentifierInstance(HLoft loft, ESurfaceIdentifiers ident) {
		for (int i=0; i<loft.getHSurfaceIdentifications()->length(); i++) {
			if (loft.getHSurfaceIdentifications()->at(i)->getName()==ident) {
				return loft.getHSurfaceIdentifications();
			}
		}
		return NULL;
	}
}
