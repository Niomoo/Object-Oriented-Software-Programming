#ifndef DIRECTOR_H
#define DIRECTOR_H

#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>

#include "general.h"
#include "person.h"

using namespace std;

class Company;


/**
 * @brief class for BoardOfDirectors inherited from Person class
 * @param name director name
 * @param gender gender
*/
class BoardOfDirectors {
  private:
    vector<Person *> memberList_;       // list of board members
    Company *company_{ nullptr };       // company of the board
  public:
    // constructor
    BoardOfDirectors() {};

    //  Polymorphism constructor: check if the number of members is available
    BoardOfDirectors(vector<Person *> &p)
    {
      if (p.size() >= 3 && p.size() <= 8)
      {
        memberList_ = p;
      }
      else
      {
        cout << "The number of Board members is not accepted!";
      }
    };

    // get the board members
    vector<Person *> getDirectors() const { return memberList_; }

    // get the number of board members
    int getDirectorsCount() { return memberList_.size(); };

    // set company to the board
    void setCompany(Company *company) { company_ = company; };
    
    // get the company name
    Company* getCompany() { return company_; };


};

#endif