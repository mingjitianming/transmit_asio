/**
 * @file type.h
 * @author zmy (mingyuzhang@sfmail.sf-express.com)
 * @brief 
 * @version 0.1
 * @date 2020-11-20
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef TRANSMIT_TYPE_H
#define TRANSMIT_TYPE_H

#include <array>

constexpr int BUF_SIZE = 1024;
// using Buffer = std::array<char, BUF_SIZE>;
using Buffer = char[BUF_SIZE];
using DataHeader = unsigned int;

#endif