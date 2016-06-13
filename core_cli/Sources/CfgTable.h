/*
 * CfgTable.h
 *
 *  Created on: Jun 12, 2016
 *      Author: avs
 */

#ifndef CFGTABLE_H_
#define CFGTABLE_H_

//#include "Uncopy.h"
#include "Common.h"
#include "Table.h"

namespace Core {

class CfgTable: public Uncopy {
public:
	explicit CfgTable();
	virtual ~CfgTable();
};

} /* namespace Core */

#endif /* CFGTABLE_H_ */
