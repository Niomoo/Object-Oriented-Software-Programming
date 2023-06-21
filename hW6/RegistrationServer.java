// This file contains material supporting section 3.7 of the textbook:
// "Object Oriented Software Engineering" and is issued under the open-source
// license found at www.lloseng.com 

import java.io.*;
import java.net.Socket;

import ocsf.server.*;

import data.MockDB;
import models.course.Course;
import models.exceptions.CourseException;
import models.users.Student;
import services.StudentService;

/**
 * This class overrides some of the methods in the abstract 
 * superclass in order to give more functionality to the server.
 *
 * @author Dr Timothy C. Lethbridge
 * @author Dr Robert Lagani&egrave;re
 * @author Fran&ccedil;ois B&eacute;langer
 * @author Paul Holden
 * @version July 2000
 */
public class RegistrationServer extends AbstractServer 
{
  //Class variables *************************************************
  
  /**
   * The default port to listen on.
   */
  final public static int DEFAULT_PORT = 5555;

	// The database.
	private MockDB db = new MockDB();

  //Constructors ****************************************************
  
  /**
   * Constructs an instance of the echo server.
   *
   * @param port The port number to connect on.
   */
  public RegistrationServer(int port) 
  {
    super(port);
  }

  
  //Instance methods ************************************************
  
  /**
   * This method handles any messages received from the client.
   *
   * @param msg The message received from the client.
   * @param client The connection from which the message originated.
   */
  public void handleMessageFromClient
    (Object msg, ConnectionToClient client)
  {
    System.out.println("Message received: " + msg + " from " + client);
    String[] message = ((String) msg).split("/");
    Student student = findStudent(message[0]);
    Course course = findCourse(message[1]);
    try {
      StudentService.takeCourse(student, course);
      this.sendToAllClients(
        "Successfully registered!\n" +
				"---------------------------\n" + 
				student.getInfoString() + "\n" +
				"---------------------------\n" + 
				course.getInfoString() + "\n" +
				"---------------------------\n"
      );
    } catch (CourseException e) {
      this.sendToAllClients(
        "Fail to register!\n" + 
        e.getMessage()
      );
    }
  }

  private Student findStudent(String name) {
    try{
      for (Student student : db.students) {
        if (student.getName().equals(name)) {
          return student;
        }
      }
    } catch (Exception e) {
      System.out.println("Student not found");
    }
    return null;
  }

  private Course findCourse(String name) {
    try{
      for (Course course : db.courses) {
        if (course.getName().equals(name)) {
          return course;
        }
      }
    } catch (Exception e) {
      System.out.println("Course not found");
    }
    return null;
  }

  public MockDB getDb() {
		return db;
	}

	public void setDb(MockDB db) {
		this.db = db;
	}
  /**
   * This method overrides the one in the superclass.  Called
   * when the server starts listening for connections.
   */
  protected void serverStarted()
  {
    System.out.println
      ("Server listening for connections on port " + getPort());
  }
  
  /**
   * This method overrides the one in the superclass.  Called
   * when the server stops listening for connections.
   */
  protected void serverStopped()
  {
    System.out.println
      ("Server has stopped listening for connections.");
  }
  
  //Class methods ***************************************************
  
  /**
   * This method is responsible for the creation of 
   * the server instance (there is no UI in this phase).
   *
   * @param args[0] The port number to listen on.  Defaults to 5555 
   *          if no argument is entered.
   */
  public static void main(String[] args) 
  {
    int port = 0; //Port to listen on

    try
    {
      port = Integer.parseInt(args[0]); //Get port from command line
    }
    catch(Throwable t)
    {
      port = DEFAULT_PORT; //Set port to 5555
    }
	
    RegistrationServer sv = new RegistrationServer(port);
    
    try 
    {
      sv.listen(); //Start listening for connections
      sv.sendToAllClients("");
    } 
    catch (Exception ex) 
    {
      System.out.println("ERROR - Could not listen for clients!");
    }
  }
}
//End of EchoServer class
