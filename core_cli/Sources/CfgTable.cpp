/*
 * CfgTable.cpp
 *
 *  Created on: Jun 12, 2016
 *      Author: avs
 */

#include "CfgTable.hpp"

namespace Core
{

static CfgTable singletonCfgTable;

CfgTable::CfgTable(void)
{
}

CfgTable::~CfgTable(void)
{
}

CfgTable* CfgTable::getSingletonPtr(void)
{
	return &singletonCfgTable;
}


} /* namespace Core */
