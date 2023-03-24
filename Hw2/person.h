#ifndef PERSON_H
#define PERSON_H

#include <string>

#include "general.h"

using namespace std;

/**
 * @brief class for Person
*/
class Person
{
  protected:
    string name_;     // person name
    Gender gender_;   // gender

  public:
    // constructor
    Person(string name, Gender gender)
      : name_(name), gender_(gender){};
    
    // return the person name
    string getName() const { return name_; }
    
    // return the gender of the person
    Gender getGender() const { return gender_; }
};

#endif