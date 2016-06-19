#ifndef _Application_h_
#define _Application_h_

#include "Common.hpp"
#include "Engine.hpp"
//#include "Uncopy.h"

//#include <string>

namespace Core {
/**
 * 
 */
class Application :public Engine {
protected:
    bool _exit;
    std::string config;
    std::string path;
public:
  /**
   * 
   */
//    explicit Application ();

    explicit Application (std::string path, std::string configFile);

    virtual ~Application ();
    
    virtual void init ();

    virtual void loop ();

    virtual void go ();

    virtual void handle (std::string msg);

    virtual void kill ();

    virtual void quit ();

//    static Application* getSingletonPtr();
//
//    static Application getSingleton();
}; // class Application

}
#endif // #ifndef _Application_h_
