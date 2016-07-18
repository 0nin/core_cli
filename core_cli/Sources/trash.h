/*
 * trash.h
 *
 *  Created on: Jun 29, 2016
 *      Author: avs
 */




//
//int main(int argc, char* args[]) {
//    // We create a console. The '>' character is used as the prompt.
//    // Note that multiple Consoles can exist at once, as they automatically
//    // manage the underlying global readline state.
//
//	const char* prompt = ">>> ";
//    cr::Console c(prompt);
//
//    // Here we register a new command. The string "info" names the command that
//    // the user will have to type in in order to trigger this command (it can
//    // be different from the function name).
//    c.registerCommand("info", info);
//    c.registerCommand("calc", calc);
//
//    // Here we call one of the defaults command of the console, "help". It lists
//    // all currently registered commands within the console, so that the user
//    // can know which commands are available.
//    c.executeCommand("help");
//
//    // Here we try to call a script. The script is read line by line, and each line
//    // (be it empty or not) is treated as a separate command. The execution is stopped
//    // as soon as any command returns an error.
////    c.executeFile("exampleScript");
//
//    // This basic loops continues to read input from the user until a command returns
//    // the termination code (ret::Quit). Here it would be one of the default
//    // quitting commands ("quit" or "exit").
//    /*
//     * while ( c.readLine() != ret::Quit );
//     */
//
//    // Otherwise we can modify the code to catch Console error codes
//    int retCode;
//    do {
//        retCode = c.readLine();
//        // We can also change the prompt based on last return value:
//        if ( retCode == ret::Ok )
//            c.setGreeting(prompt);
//        else
//            c.setGreeting(prompt);
//
//        if ( retCode == 1 ) {
//            std::cout << "Received error code 1\n";
//        }
//        else if ( retCode == 2 ) {
//            std::cout << "Received error code 2\n";
//        }
//    }
//    while ( retCode != ret::Quit );
//
//    return 0;
//}

//#ifdef __cplusplus
//extern "C" {
//#endif
//
//#if defined __WIN32__ || _WIN32 && defined _MSC_VER
//#include <Windows.h>
//#include <locale>
//#define WIN32_LEAN_AND_MEAN
//INT WINAPI WinMain
//(
//		_In_ HINSTANCE hInstance,
//		_In_opt_ HINSTANCE hPrevInstance,
//		_In_ LPSTR lpCmdLine,
//		_In_ int nShowCmd
//) {
//#else
//int main(int argc, char* args[]) {
//#endif
//	return _main(argc, args);
//}
//
//#ifdef __cplusplus
//}
//#endif

//	while (_exit != true) {
//		printf("> ");
//		std::cin >> in;
////		tt->stop(in_prev);
////		tt->start(in);
//		in_prev = in;
//		if (in == "exit") {
//			quit();
//		} else if (in == "add") {
//			std::string x, y;
//			std::cin >> x;
//			std::cin >> y;
//			if (!x.empty() && !y.empty()) {
//				Library::getSingletonPtr()->addParam(x, y);
//			}
//		} else if (in == "show") {
//			Library::getSingletonPtr()->printAll();
//		} else if (in == "get") {
//			std::string x;
//			std::cin >> x;
//			std::cout << Library::getSingletonPtr()->getParam(x) << std::endl;
//		} else if (in == "start") {
//			std::string x;
//			std::cin >> x;
//			tt->start(x);
//		} else if (in == "stop") {
//			std::string x;
//			std::cin >> x;
//			tt->stop(x);
//		} else if (in == "time") {
//			tt->print();
//		} else {
//			std::cout << "LOL:" << std::endl;
//		}
	//handle(in)
