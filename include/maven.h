#ifndef PYTHON_H
#define PYTHON_H

#include <filesystem>
#include <iostream>
#include "PackageManager.h"

class Maven : public PackageManager {
private:
    PackageManagerToolkit * toolkit;
    
    void checkMaven();

public:
    Maven();
    virtual ~Maven();
    
    virtual int install(std::string package) override;
    virtual int install(std::vector<std::string> packages) override;
    virtual int uninstall(std::string package) override;
    virtual int uninstall(std::vector<std::string> packages) override;
    virtual int update(std::string package) override;
    virtual int update(std::vector<std::string> packages) override;
    virtual int update() override;
    virtual int search(std::string package) override;
    virtual int list() override;
    virtual int info(std::string package) override;
    virtual void setToolkit(PackageManagerToolkit * toolkit) override;
};

#endif