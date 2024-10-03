#include "mvn.h"

Maven::Maven() {
}

Maven::~Maven() {
}

int Maven::install(std::string package) {
    std::string mvnCall = "mvn dependency:get -Dartifact=" + package;
    return system(mvnCall.c_str());
}

int Maven::install(std::vector<std::string> packages) {
    std::string mvnPackages = "mvn dependency:get";
    for(std::string package : packages) {
        mvnPackages += " -Dartifact=" + package;
    }
    return system(mvnPackages.c_str());
}

int Maven::uninstall(std::string package) {
    std::cout << "maven does not support uninstalling packages" << std::endl;
    return 0;
}

int Maven::uninstall(std::vector<std::string> packages) {
    std::cout << "maven does not support uninstalling packages" << std::endl;
    return 0;
}

int Maven::update(std::string package) {
    return this->install(package);
}

int Maven::update(std::vector<std::string> packages) {
    int result = 0;
    for(std::string package : packages) {
        result += this->update(package);
    }
    return result;
}

int Maven::update() {
    std::cout << "maven does not support updating all Repositories" << std::endl;
    return 0;
}

int Maven::search(std::string package) {
    std::cout << "maven does not support searching for packages" << std::endl;
    return 0;
}

int Maven::list() {
    std::cout << "maven does not support listing all installed packages" << std::endl;
    return 0;
}

int Maven::info(std::string package) {
    std::cout << "maven does not support getting information about a package" << std::endl;
    return 0;
}

void Maven::setToolkit(PackageManagerToolkit * toolkit) {
    this->toolkit = toolkit;
    this->checkMaven();
}

void Maven::checkMaven() {
    std::string mavenCall = "mvn -v > /dev/null 2>&1";
    
    if(system(mavenCall.c_str()) == 0) {
        return;
    }
    
    this->toolkit->installInSys("maven");
}


extern "C" PackageManager * create() {
    return new Maven();
}

extern "C" void destroy(PackageManager * pm) {
    delete pm;
}