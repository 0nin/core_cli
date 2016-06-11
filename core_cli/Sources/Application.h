#ifndef _Application_h_
#define _Application_h_

#include "Common.h"

namespace Core {
/**
 * 
 */
class Application
:public Uncopy
{
protected:
    bool _exit;
    std::string config;
    std::string path;
public:
  /**
   * 
   */
    Application (std::string path, std::string configFile);
    virtual ~Application ();
    
    virtual void init ();
    virtual void loop ();
    virtual void go ();
    virtual void handle (std::string msg);
    virtual void kill ();
    virtual void quit ();
}; // class Application

}
#endif // #ifndef _Application_h_
