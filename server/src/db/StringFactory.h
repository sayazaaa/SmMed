#ifndef STRINGFACTORY_H

#define STRINGFACTORY_H
#include<uuid/uuid.h>
#include<botan-2/botan/hash.h>


namespace StringFactory{

    std::pair<std::string,std::string> salt_hash(const std::string in);
    std::string gen_uuid();
    bool verify_salt_hash(const std::string in,const std::string slat, const std::string key);
}
#endif // STRINGFACTORY_H
