/*
 * Cmd.h
 *
 *  Created on: 3 Aug 2016
 *      Author: avs
 */

#ifndef CMD_HPP_
#define CMD_HPP_

#include "Common.h"

// Readline commands
extern unsigned rtCmd(const std::vector<std::string> &);
extern unsigned plotCmd(const std::vector<std::string> &input);
extern unsigned calcCmd(const std::vector<std::string> & input);
extern unsigned csv2datCmd(const std::vector<std::string> &input);
extern unsigned infoCmd(const std::vector<std::string> &);


#endif /* CMD_HPP_ */
