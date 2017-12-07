
#ifndef XTESTSTUFF_NOZTEST_H_
#define XTESTSTUFF_NOZTEST_H_

#include "../hykops_core/ESurfaceIdentifiers.h"
#include "../hykops_data/HCurve2D.h"
#include "../hykops_data/HLoft.h"
#include "../hykops_data/HLoftElement.h"
#include "../hykops_data/HSurfaceIdentifier.h"
#include "../hykops_data/uniquelist.h"

using namespace std;

class noztest {
public:
	static HComponent* createExampleNozzle(HComposition* composition, double xref, double yref, double zref, double radius, double chord);
//, QString profileSeries, QString profileName
};

#endif /* XTESTSTUFF_NOZTEST_H_ */
