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
    std::string homePath = getenv("HOME");
    std::string pathToPackage = homePath + "/.m2/repository/";
    std::string innerPath;
    std::string versionPath;
    int cut = package.find_last_of(":");
    
    if(cut != std::string::npos) {
        versionPath = package.substr(cut + 1);
    }
    
    innerPath = package.substr(0, cut);
    innerPath = innerPath.replace(innerPath.begin(), innerPath.end() ,":", "/");
    innerPath = innerPath.replace(innerPath.begin(), innerPath.end() ,".", "/");
    
    std::string mvnPath = pathToPackage + "/" + innerPath + "/" + versionPath;
    
    std::cout << "path to delete: " << mvnPath << std::endl;
    
    if(std::filesystem::exists(mvnPath)) {
        std::filesystem::remove_all(mvnPath);
    }

    return 0;
}

int Maven::uninstall(std::vector<std::string> packages) {
    int result = 0;
    for(std::string package : packages) {
        result += this->uninstall(package);
    }
    return result;
}

int Maven::update(std::string package) {
    return this->uninstall(package) + this->install(package);
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