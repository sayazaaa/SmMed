#include"StringFactory.h"
#include<uuid/uuid.h>
#include<botan-2/botan/pbkdf2.h>
#include<botan-2/botan/hex.h>
#include <botan-2/botan/hash.h>
#include <botan-2/botan/hex.h>
#include <botan-2/botan/rng.h>
#include <botan-2/botan/pbkdf.h>
#include <botan-2/botan/auto_rng.h>
#include<botan-2/botan/secmem.h>
#include <botan-2/botan/exceptn.h>
#include <botan-2/botan/mutex.h>
#include <chrono>
#include<iostream>
#include<bits/stdc++.h>
#include<vector>
#include<QDebug>
std::pair<std::string,std::string> StringFactory::salt_hash(const std::string in){
    Botan::AutoSeeded_RNG rng;
    Botan::secure_vector<uint8_t> salt = rng.random_vec(16); // 生成16字节的随机盐

    // 设置PBKDF2的参数
    const size_t iterations = 100000; // PBKDF2迭代次数
    const size_t output_len = 32; // 生成的哈希长度

    // 获取PBKDF2的实例
    std::unique_ptr<Botan::PBKDF> pbkdf = std::unique_ptr<Botan::PBKDF>(Botan::get_pbkdf("PBKDF2(SHA-256)"));

    // 生成哈希值
    Botan::secure_vector<uint8_t> key = pbkdf->derive_key(output_len, in, salt.data(), salt.size(), iterations).bits_of();

    std::string salt_hex = Botan::hex_encode(salt);
    std::string key_hex = Botan::hex_encode(key);

    return {key_hex,salt_hex};
}
std::string StringFactory::gen_uuid(){
    uuid_t id;
    char str[40];
    uuid_generate(id);
    uuid_unparse(id,str);
    std::string fin(str);
    return fin;
}
bool StringFactory::verify_salt_hash(const std::string inhex,const std::string salthex, const std::string keyhex){
    //qDebug() << QString(inhex.c_str()) << " " << QString(salthex.c_str()) << " " << QString(keyhex.c_str());
    std::vector<uint8_t> salt = Botan::hex_decode(salthex);
    const size_t iterations = 100000; // PBKDF2迭代次数
    const size_t output_len = 32; // 生成的哈希长度
    std::unique_ptr<Botan::PBKDF> pbkdf = std::unique_ptr<Botan::PBKDF>(Botan::get_pbkdf("PBKDF2(SHA-256)"));
    Botan::secure_vector<uint8_t> orkey = pbkdf->derive_key(output_len,inhex,salt.data(),salt.size(),iterations).bits_of();
    std::string orkeyhex = Botan::hex_encode(orkey);
    //qDebug() << QString(orkeyhex.c_str());
    return orkeyhex == keyhex;
}

