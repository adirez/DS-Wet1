//
// Created by adire on 29-Nov-17.
//

#ifndef WET1_EXCEPTIONS_H
#define WET1_EXCEPTIONS_H


#include <exception>
#include <stdexcept>

class SplayException : public std::exception{};

class EmptyTree : public SplayException{};
class KeyAlreadyExists : public SplayException{};
class KeyNotFound : public SplayException{};
class InvalidParameter : public SplayException{};
class MemoryProblem : public SplayException{};

#endif //WET1_EXCEPTIONS_H
