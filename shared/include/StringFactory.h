#ifndef STRINGFACTORY_H

#define STRINGFACTORY_H
#include<uuid.h>
#include<botan-2/botan/hash.h>


namespace StringFactory{

    std::pair<std::string,std::string> salt_hash(const std::string in);
    std::string gen_uuid();
    std::string fir_hash_password(const std::string in);
}
#endif // STRINGFACTORY_H
