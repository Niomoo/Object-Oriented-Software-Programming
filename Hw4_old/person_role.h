#ifndef PERSON_ROLE_H
#define PERSON_ROLE_H

class Person;

/**
 * @brief class of PersonRole
 * @param person - link the person to the role
*/
class PersonRole {
 public:

  virtual ~PersonRole() = default;

  // link the person to the role
  void linkPerson(Person* person) { this->person = person; }

  // return the person of the role
  Person* getPerson() const { return person; }

 protected:
  Person* person{nullptr};
};

#endif /* PERSON_ROLE_H */
