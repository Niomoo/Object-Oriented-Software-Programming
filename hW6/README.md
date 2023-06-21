#  Object-Oriented Software Engineering - Hw6
## Problem
Design a  course registration system that check the prerequisites and the course capacity simultaneously.
### Activity Diagram
![](https://hackmd.io/_uploads/B1NIfHxO3.png)

![](https://hackmd.io/_uploads/ryGczBgu3.png)
## Project Structure
```sh
├── ocsf
│   ├── client
│   │   └── AbstractClient.java
│   ├── server
│   │   ├── AbstractServer.java
│   │   └── ConnectionToClient.java
├── client
│   ├── ChatIF
│   │   └── ChatIF.java
│   └── ChatClient.java
├── data
│   └── MockDB.java
├── models
│   ├── course
│   │   └── Course.java
│   ├── exceptions
│   │   ├── AlreadyTakenException.java
│   │   ├── CourseException.java
│   │   ├── IsFullException.java
│   │   └── NotPassedException.java
│   ├── roles
│   │   └── StudentRole.java
│   └── users
│       └── Student.java
├── services
│   └── StudentService.java
├── ClientConsole.java
└── RegistrationServer.java
```
### Description
- oscf
    - contains server package and client package
    - provides abstract of server and client classes
- client
    - contains chatIF package and ChatClient classes
    - provides functionality of client to send and receive messages
- data
    - contains MockDB class
    - provide the mock student and course information to initialize a database for the course registration system
- models
    - contains course, exceptions, roles and users package
    - provides the data schema and methods for course, exceptions, roles and users classes
- services
    - contains StudentService class
    - provides the relationship operations for models
- ClientConsole.java
    - provides the entry point for client
- RegistrationServer.java
    - provides the entry point for course registration server
### Implementation process
- Start EchoServer with port 5555.
- Start ClientConsole with port 5555 to connect to the server.
- Input "Student name"/"Course name" to register the course.
- Output shows whether the registration is successful.
## Result
### Initialization
- Course Information
    ![](https://hackmd.io/_uploads/HySO8IeOn.png)
- Student Information
    ![](https://hackmd.io/_uploads/B1fYU8x_3.png)

### Scenario
1. Failure: already passed the course

    ![](https://hackmd.io/_uploads/SJxAzUlu2.png)
2. Failure: didn't pass the prerequisite course

    ![](https://hackmd.io/_uploads/rJlQX8l_h.png)
3. Success: passed the prerequisite course and the course is not full

    ![](https://hackmd.io/_uploads/SJMkN8g_2.png)
4. Failure: the course is full
    
    ![](https://hackmd.io/_uploads/B1_7E8ld2.png)
5. Success: the course doesn't have prerequisites and is not full
    
    ![](https://hackmd.io/_uploads/HydU4Igd3.png)
6. Success: didn't pass the prerequisite course but has special permission
    
    ![](https://hackmd.io/_uploads/H16mrUgu2.png)
7. Failure: didn't pass the prerequisite course but has special permission while the course is full
    
    ![](https://hackmd.io/_uploads/HkcYrLl_2.png)
