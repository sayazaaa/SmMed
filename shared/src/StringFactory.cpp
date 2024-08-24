#include"StringFactory.h"


std::pair<std::string,std::string> StringFactory::salt_hash(const std::string in){
    return {in,""};
}
