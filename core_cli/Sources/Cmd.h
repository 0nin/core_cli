/*
 * Cmd.h
 *
 *  Created on: 3 Aug 2016
 *      Author: avs
 */

#ifndef CMD_H_
#define CMD_H_

namespace Core {

//Readline Commands
extern unsigned rtCmd(const std::vector<std::string> &);
extern unsigned plotCmd(const std::vector<std::string> &input);
extern unsigned calcCmd(const std::vector<std::string> & input);
extern unsigned csv2datCmd(const std::vector<std::string> &input);
extern unsigned infoCmd(const std::vector<std::string> &);

}



#endif /* CMD_H_ */
